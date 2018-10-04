/********************************************
 *          六足话题发布及客户端程序            *
 *          Copyright (c) V5_Lab, 2018      *
 *          Author:    Kingsley             *
 *          Version number:  0.00           *
 *          Date:                           *
 * *****************************************/

#include "control.h"

Control::Control(const std::string name, bool spin_thread) : hexapod_client_(name, spin_thread)
{
  ros::param::get("NUMBER_OF_LEGS", NUMBER_OF_LEGS);
  ros::param::get("NUMBER_OF_LEG_SEGMENTS", NUMBER_OF_LEG_JOINTS);
  ros::param::get("MASTER_LOOP_RATE", MASTER_LOOP_RATE);
  ros::param::get("VELOCITY_DIVISION", VELOCITY_DIVISION);
  nh_.param<int>("VkBHexSM/sm_max_point_one_transmit", feedDriver_points_, 300);
  nh_.param<int>("VkBHexSM/sm_point_buf_size", sm_point_buf_size, 3000);
  ros::param::get("KPALIMIT", KPALIMIT);

  bufferFree_ = true;
  motionActive_ = true;
  stick_control_ = false;

  // Topics we are subscribing
  cmd_vel_sub_ = nh_.subscribe<geometry_msgs::Twist>("/cmd_vel", 1, &Control::cmd_velCallback, this);

  boost::format roll;
  boost::format pitch1;
  boost::format pitch2;
  boost::format pitch3;
  for (int leg_index = 0, j = 1; leg_index < NUMBER_OF_LEGS; leg_index++, j++)
  {
    roll = boost::format("/hexapod/leg%d_roll_joint_position_controller/command") % j;
    pitch1 = boost::format("/hexapod/leg%d_pitch1_joint_position_controller/command") % j;
    pitch2 = boost::format("/hexapod/leg%d_pitch2_joint_position_controller/command") % j;
    pitch3 = boost::format("/hexapod/leg%d_pitch3_joint_position_controller/command") % j;
    leg_topic[leg_index] = roll.str();
    leg_topic[leg_index + 1] = pitch1.str();
    leg_topic[leg_index + 2] = pitch2.str();
    leg_topic[leg_index + 3] = pitch3.str();
    leg_roll_p[leg_index] = nh_.advertise<std_msgs::Float64>(leg_topic[leg_index], 10);
    leg_pitch1_p[leg_index] = nh_.advertise<std_msgs::Float64>(leg_topic[leg_index + 1], 10);
    leg_pitch2_p[leg_index] = nh_.advertise<std_msgs::Float64>(leg_topic[leg_index + 2], 10);
    leg_pitch3_p[leg_index] = nh_.advertise<std_msgs::Float64>(leg_topic[leg_index + 3], 10);
  }

  linear_x_max = 0.1;
  linear_y_max = 0.1;
  angular_z_max = 0.5;

  feet_position = nh_.advertise<hexapod_msgs::FeetPositions>("feet_position", 10);

  ros::param::get("JOINT_NAME", joint_name);
  sm_pos_sub = nh_.subscribe<hexapodservice::leg>("/hexapod_sm_pose", 1, &Control::sm_pos_Cb, this);
  sm_pos_pub = nh_.advertise<sensor_msgs::JointState>("/joint_states", 1);

  stick_client_ = nh_.serviceClient<link_com::hexcom>("hexapod_st_service");
  heartbag_sub_ = nh_.subscribe<link_com::heartbag>("/hexapod_st_heartbag", 1, &Control::heartbag_Callback, this);
}

void Control::robotInit()
{
  //关节转动角度
  for (int leg_index = 0; leg_index < NUMBER_OF_LEGS; leg_index++)
  {
    leg_roll[leg_index].data = 0.0;
    leg_pitch1[leg_index].data = 0.0;
    leg_pitch2[leg_index].data = 0.0;
    leg_pitch3[leg_index].data = 0.0;
  }
  for (int leg_index = 0; leg_index < NUMBER_OF_LEGS; leg_index++)
  {
    leg_roll_p[leg_index].publish(leg_roll[leg_index]);
    leg_pitch1_p[leg_index].publish(leg_pitch1[leg_index]);
    leg_pitch2_p[leg_index].publish(leg_pitch2[leg_index]);
    leg_pitch3_p[leg_index].publish(leg_pitch3[leg_index]);
  }
}

//订阅发布的速度信息
void Control::cmd_velCallback(const geometry_msgs::TwistConstPtr &cmd_vel_msg)
{
  if (cmd_vel_msg->linear.x > linear_x_max || cmd_vel_msg->linear.x < -linear_x_max)
  {
    ROS_FATAL("The linear.x exceeds the upper limit, set it to max: %f.", linear_x_max);
    cmd_vel_incoming_.linear.x = (cmd_vel_msg->linear.x > 0 ? linear_x_max : -linear_x_max);
  }
  else
  {
    cmd_vel_incoming_.linear.x = cmd_vel_msg->linear.x;
  }

  if (cmd_vel_msg->linear.y > linear_y_max || cmd_vel_msg->linear.y < -linear_y_max)
  {
    ROS_FATAL("The linear.y exceeds the upper limit, set it to max: %f.", linear_y_max);
    cmd_vel_incoming_.linear.y = (cmd_vel_msg->linear.y > 0 ? linear_y_max : -linear_y_max);
    ;
  }
  else
  {
    cmd_vel_incoming_.linear.y = cmd_vel_msg->linear.y;
  }

  if (cmd_vel_msg->angular.z > angular_z_max || cmd_vel_msg->angular.z < -angular_z_max)
  {
    ROS_FATAL("The angular.z exceeds the upper limit, set it to max: %f.", angular_z_max);
    cmd_vel_incoming_.angular.z = (cmd_vel_msg->angular.z > 0 ? angular_z_max : -angular_z_max);
  }
  else
  {
    cmd_vel_incoming_.angular.z = cmd_vel_msg->angular.z;
  }
}

//速度转化成歩幅
void Control::partitionCmd_vel(geometry_msgs::Twist *cmd_vel)
{
  // Instead of getting delta time we are calculating with a static division
  double dt = VELOCITY_DIVISION;

  double delta_th = cmd_vel_incoming_.angular.z * dt;
  double delta_x = (cmd_vel_incoming_.linear.x * cos(delta_th) - cmd_vel_incoming_.linear.y * sin(delta_th)) * dt;
  double delta_y = (cmd_vel_incoming_.linear.x * sin(delta_th) + cmd_vel_incoming_.linear.y * cos(delta_th)) * dt;
  cmd_vel->linear.x = delta_x;
  cmd_vel->linear.y = delta_y;
  cmd_vel->angular.z = delta_th;
}

//向服务器请求maxpoints，填充buffer
void Control::feedDrives(const bool &start_cycle, const int &cycle_period_, const bool &is_traveling_, std::vector<int> &cycle_leg_number_, geometry_msgs::Pose2D &smooth_base_, bool &hexapod_stop_flag)
{
  //feedDriver条件： 所给的六足速度不为0或者给的速度为0但六足仍在运动（复位周期）
  if (std::abs(cmd_vel_incoming_.linear.x) > 0.001 || std::abs(cmd_vel_incoming_.linear.y) > 0.001 || std::abs(cmd_vel_incoming_.angular.z) > 0.001 || is_traveling_ == true)
  {
    ROS_INFO("in");
    //status不为1或者abortMotion时，关闭算法节点
    if (motionActive_ == false)
    {
      ros::shutdown();
      return;
    }

    if (bufferFree_) /*当buffer空间充足，即大于sm_max_point_one_transmit，填充buffer*/
    {
      maxpoints_ = feedDriver_points_; //固定每次填充buffer点数

      //每个关节的填充buffer数值初始化
      for (int position_resize = 0; position_resize < 6; position_resize++)
      {
        leg_goal_.ALLLEGS.leg[position_resize].coxa.resize(maxpoints_);
        leg_goal_.ALLLEGS.leg[position_resize].femur.resize(maxpoints_);
        leg_goal_.ALLLEGS.leg[position_resize].tibia.resize(maxpoints_);
        leg_goal_.ALLLEGS.leg[position_resize].tarsus.resize(maxpoints_);
      }

      //调用maxpoints次算法
      for (int i = 0; i < maxpoints_; i++)
      {
        partitionCmd_vel(&cmd_vel_);
        gait.gaitCycle(cmd_vel_, &feet_);
        ik.calculateIK(feet_, &legs_);

        for (int leg_index = 0; leg_index < 6; leg_index++)
        {
          leg_goal_.ALLLEGS.leg[leg_index].coxa[i] = round(4096.0 * (3005640.0 / 1300.0) * (legs_.leg[leg_index].coxa / M_PI * 180.0) / 360.0);
          leg_goal_.ALLLEGS.leg[leg_index].femur[i] = round(4096.0 * (3005640.0 / 1300.0) * (-legs_.leg[leg_index].femur / M_PI * 180.0) / 360.0);
          leg_goal_.ALLLEGS.leg[leg_index].tibia[i] = round(4096.0 * (3005640.0 / 1300.0) * (-legs_.leg[leg_index].tibia / M_PI * 180.0) / 360.0);
          leg_goal_.ALLLEGS.leg[leg_index].tarsus[i] = round(4096.0 * (3005640.0 / 1300.0) * (-legs_.leg[leg_index].tarsus / M_PI * 180.0) / 360.0);
        }

        if (cycle_period_ == 1)
        {
          maxpoints_ = i + 1;
          stick_control_ = true;
          break;
        }
      }

      //发送关节运动控制请求
      leg_goal_.MODE = ALLLEGS_CONTROL;
      leg_goal_.MAXPOINTS = maxpoints_;
      bool server_exists = hexapod_client_.waitForServer(ros::Duration(5.0));
      while (!server_exists) //查看服务器是否开启
      {
        ROS_WARN("could not connect to server, retrying...");
        server_exists = hexapod_client_.waitForServer(ros::Duration(5.0));
      }
      hexapod_client_.sendGoal(leg_goal_, boost::bind(&Control::legcontrol_doneCb, this, _1, _2));

      bool finished = hexapod_client_.waitForResult(ros::Duration(5.0));
      if (!finished) //未在规定时间发送成功时，关闭算法节点
      {
        ROS_WARN("Waiting for result...");
        finished = hexapod_client_.waitForResult(ros::Duration(5.0));
        if (!finished)
        {
          ROS_WARN("Connecting failed.");
          ros::shutdown();
          return;
        }
      }

      //  if (stick_control_)
      if (false)
      {
        ROS_INFO("------stick control-------");
        ROS_INFO("io: %d, %d, %d, %d, %d, %d", cycle_leg_number_[0], cycle_leg_number_[1], cycle_leg_number_[2], cycle_leg_number_[3], cycle_leg_number_[4], cycle_leg_number_[5]);
        ros::Duration(3).sleep();

        //发送请求确保六足buffer已接近空
        while (freeSpace_ < (sm_point_buf_size - 30))
        {
          maxpoints_goal_.MODE = MAXPOINT_REQUEST;

          bool server_exists = hexapod_client_.waitForServer(ros::Duration(5.0));
          while (!server_exists)
          {
            ROS_WARN("Could not connect to hexapod server, retrying...");
            server_exists = hexapod_client_.waitForServer(ros::Duration(5.0));
          }
          hexapod_client_.sendGoal(maxpoints_goal_, boost::bind(&Control::maxpoint_doneCb, this, _1, _2));

          bool finished = hexapod_client_.waitForResult(ros::Duration(5.0));
          if (!finished)
          {
            ROS_WARN("Waiting for result...");
            finished = hexapod_client_.waitForResult(ros::Duration(5.0));
            if (!finished)
            {
              ROS_WARN("Connecting failed.");
              ros::shutdown();
              return;
            }
          }
          ros::Duration(1).sleep();
        }

        ROS_INFO("---Buffer is almost empty. Start to control stick---");
        int Reqio[7];

        if (hexapod_stop_flag == true) /*当六足停止时，把所有吸盘都抽至真空*/
        {
          /*****把所有的吸盘与真空泵连接*****/
          stick_srv_.request.chose = 2;
          for (int i = 0; i < 6; i++)
          {
            stick_srv_.request.io[i] = 0;
            Reqio[i] = 0;
          }
          stick_srv_.request.io[6] = 1;
          while (!stick_client_.call(stick_srv_))
          {
            ROS_WARN("Failed to call stick service. Retrying...");
            ros::Duration(1).sleep();
          }
          ROS_INFO("%s", stick_srv_.response.back.c_str());

          ros::Duration(3).sleep();
          //查看吸盘是否吸放气完毕
          while (!isStickDone(Reqio))
          {
            ros::Duration(3).sleep();
          }
          ROS_INFO("All sticks are vacuumed.");

          if (hexapod_stop_flag == true)
          {
            partitionCmd_vel(&cmd_vel_); /*走完下一个点使得is_traveling 和smooth_base更新*/
            gait.gaitCycle(cmd_vel_, &feet_);
            ik.calculateIK(feet_, &legs_);
            while (hexapod_stop_flag == true) /*当新的速度到来时才跳出循环*/
            {
              if (std::abs(cmd_vel_incoming_.linear.x) > 0.001 || std::abs(cmd_vel_incoming_.linear.y) > 0.001 || std::abs(cmd_vel_incoming_.angular.z) > 0.001)
              {
                hexapod_stop_flag = false; //六足停止标志位复位
                break;
              }
              ros::Duration(1.0).sleep();
              ROS_INFO("hexapod stoped.");
            }
          }
        }

        /*****先把所有的吸盘与真空泵连接*****/
        stick_srv_.request.chose = 2;
        for (int i = 0; i < 6; i++)
        {
          stick_srv_.request.io[i] = 0;
          Reqio[i] = 0;
        }
        stick_srv_.request.io[6] = 1;
        while (!stick_client_.call(stick_srv_))
        {
          ROS_WARN("Failed to call stick service. Retrying...");
          ros::Duration(1).sleep();
        }
        ROS_INFO("%s", stick_srv_.response.back.c_str());

        ros::Duration(3).sleep();
        //查看吸盘是否吸放气完毕
        while (!isStickDone(Reqio))
        {
          ros::Duration(3).sleep();
        }
        ROS_INFO("All sticks are vacuumed.");

        /****把摆动腿的吸盘与真空泵阻塞****/
        stick_srv_.request.chose = 2;
        for (int i = 0; i < 6; i++)
        {
          stick_srv_.request.io[i] = cycle_leg_number_[i];
          Reqio[i] = stick_srv_.request.io[i];
        }
        stick_srv_.request.io[6] = 1;
        while (!stick_client_.call(stick_srv_))
        {
          ROS_WARN("Failed to call stick service. Retrying...");
          ros::Duration(1).sleep();
        }
        ROS_INFO("%s", stick_srv_.response.back.c_str());

        ros::Duration(6).sleep(); //吸盘放气等待时间
        //查看吸盘是否吸放气完毕
        while (!isStickDone(Reqio))
        {
          ros::Duration(3).sleep();
        }
        ROS_INFO("Stick control done. Ready to move.");

        stick_control_ = false; //吸盘控制标志位复位
      }
    }
    else /*buffer空间不足时，请求maxpoints，直至sm反馈buffer空间充足*/
    {
      maxpoints_goal_.MODE = MAXPOINT_REQUEST;

      bool server_exists = hexapod_client_.waitForServer(ros::Duration(5.0));
      while (!server_exists)
      {
        ROS_WARN("Could not connect to hexapod server, retrying...");
        server_exists = hexapod_client_.waitForServer(ros::Duration(5.0));
      }
      hexapod_client_.sendGoal(maxpoints_goal_, boost::bind(&Control::maxpoint_doneCb, this, _1, _2));

      bool finished = hexapod_client_.waitForResult(ros::Duration(5.0));
      if (!finished)
      {
        ROS_WARN("Waiting for result...");
        finished = hexapod_client_.waitForResult(ros::Duration(5.0));
        if (!finished)
        {
          ROS_WARN("Connecting failed.");
          ros::shutdown();
          return;
        }
      }
    }
  }
}

//关节控制回调函数，确认六足status/freespace/motionActive
void Control::legcontrol_doneCb(const actionlib::SimpleClientGoalState &state, const hexapodservice::hexapodserviceResultConstPtr &result)
{
  ROS_INFO("Leg control: server responded with state[%s]", state.toString().c_str());
  motionActive_ = result->motionActive;
  status_ = result->status;
  freeSpace_ = result->freespace;

  if (status_ != 1)
  {
    ROS_WARN("simplemotion status fault, status: %d", status_);
    motionActive_ = false;
  }

  if (freeSpace_ < feedDriver_points_)
  {
    bufferFree_ = false;
  }
  else
  {
    bufferFree_ = true;
  }
}

//读取最大填充点回调函数
void Control::maxpoint_doneCb(const actionlib::SimpleClientGoalState &state, const hexapodservice::hexapodserviceResultConstPtr &result)
{
  ROS_INFO("Request maxpoint: server responded with state[%s]", state.toString().c_str());
  motionActive_ = result->motionActive;
  status_ = result->status;
  freeSpace_ = result->freespace;

  if (status_ != 1)
  {
    ROS_WARN("simplemotion status fault, status: %d", status_);
    motionActive_ = false;
  }

  if (freeSpace_ < feedDriver_points_)
  {
    bufferFree_ = false;
  }
  else
  {
    bufferFree_ = true;
  }
}

void Control::sm_pos_Cb(const hexapodservice::legConstPtr &leg)
{
  joint_states.header.stamp = ros::Time::now();
  int i = 0;
  joint_states.name.resize(36);
  joint_states.position.resize(36);
  for (int leg_index = 0; leg_index < 6; leg_index++)
  {
    joint_states.name[i] = joint_name[i];
    joint_states.position[i] = leg->leg[leg_index].coxa;
    i++;
    joint_states.name[i] = joint_name[i];
    joint_states.position[i] = -leg->leg[leg_index].femur;
    i++;
    joint_states.name[i] = joint_name[i];
    joint_states.position[i] = -leg->leg[leg_index].tibia;
    i++;
    joint_states.name[i] = joint_name[i];
    joint_states.position[i] = -leg->leg[leg_index].tarsus;
    i++;
    //吸盘
    joint_states.name[i] = joint_name[i];
    joint_states.position[i] = 0;
    i++;
    //吸盘
    joint_states.name[i] = joint_name[i];
    joint_states.position[i] = 0;
    i++;
  }
  sm_pos_pub.publish(joint_states);
}

/*心跳包订阅程序， 订阅吸盘气压值和io口*/
void Control::heartbag_Callback(const link_com::heartbagConstPtr &heartbag)
{
  kpa = heartbag->kpa;
  for (int i = 0; i < 7; i++)
  {
    io[i] = heartbag->io[i];
  }
}

/*吸盘控制， 当io口和气压值均满足条件时返回true*/
bool Control::isStickDone(const int Reqio[])
{
  for (int i = 0; i < 6; i++)
  {
    if (io[i] != Reqio[i])
    {
      ROS_FATAL("io is not correct!!");
      return false;
    }
  }

  if (kpa > KPALIMIT)
  {
    ROS_INFO("stick kpa is not enough.");
    return false;
  }

  return true;
}