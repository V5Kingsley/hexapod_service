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

  ros::param::get("LINEAR_X_MAX", linear_x_max);
  ros::param::get("LINEAR_Y_MAX", linear_y_max);
  ros::param::get("ANGULAR_Z_MAX", angular_z_max);

  feet_position = nh_.advertise<hexapod_msgs::FeetPositions>("feet_position", 10);

  ros::param::get("JOINT_NAME", joint_name);
  sm_pos_sub = nh_.subscribe<hexapodservice::leg>("/hexapod_sm_pose", 1, &Control::sm_pos_Cb, this);
  sm_pos_pub = nh_.advertise<sensor_msgs::JointState>("/joint_states", 1);

  stick_client_ = nh_.serviceClient<link_com::hexcom>("hexapod_st_service");
  heartbag_sub_ = nh_.subscribe<link_com::heartbag>("/hexapod_st_heartbag", 1, &Control::heartbag_Callback, this);

  robot_mode = climb2wall_mode;
  hexapod_mode_sub = nh_.subscribe<std_msgs::Int32>("hexapod_mode_select", 1, &Control::hexapod_mode_cb, this); //模式切换话题 1为六角形步态，2为螃蟹步态，3为爬墙模式。默认为1
  hexapod2crab_flag = false;
  crab2hexapod_flag = false;
  climb2wall_flag = false;
  ros::param::get("INIT_COXA_ANGLE", INIT_COXA_ANGLE);
  ros::param::get("BODY_RADIUS", BODY_RADIUS);
  ros::param::get("COXA_LENGTH", COXA_LENGTH);
  ros::param::get("FEMUR_LENGTH", FEMUR_LENGTH);
  ros::param::get("TIBIA_LENGTH", TIBIA_LENGTH);
  ros::param::get("TARSUS_LENGTH", TARSUS_LENGTH);

  //符号位， 角度大于等于0时sign取1， 否则取-1
  for (int leg_index = 0; leg_index < 6; leg_index++)
  {
    if (INIT_COXA_ANGLE[leg_index] >= 0)
    {
      sign[leg_index] = 1.0;
    }
    else
    {
      sign[leg_index] = -1.0;
    }
  }
  //存储关节角角度buffer初始化
  for (int i = 0; i < 24; i++)
  {
    posBuffer[i].reserve(3000);
  }

  ros::param::get("JOINT_MECHANICAL_ERROR_UNIT", MeclErrUnit);
  ros::param::get("JOINT_MECHANICAL_ERROR", MeclErr);

  //蜘蛛形态沿x，y，z正负方向运动差补比重
  ros::param::get("HEX_X_POS_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_1st_STEP", HEXxPosDirnMeclErrBalnRate1st);
  ros::param::get("HEX_X_NEG_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_1st_STEP", HEXxNegDirnMeclErrBalnRate1st);
  ros::param::get("HEX_Y_POS_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_1st_STEP", HEXyPosDirnMeclErrBalnRate1st);
  ros::param::get("HEX_Y_NEG_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_1st_STEP", HEXyNegDirnMeclErrBalnRate1st);
  ros::param::get("HEX_Z_POS_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_1st_STEP", HEXzPosDirnMeclErrBalnRate1st);
  ros::param::get("HEX_Z_NEG_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_1st_STEP", HEXzNegDirnMeclErrBalnRate1st);
  ros::param::get("HEX_X_POS_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_1st_STEP", HEXxPosDirnMeclErrBalnRate1st_update);
  ros::param::get("HEX_X_NEG_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_1st_STEP", HEXxNegDirnMeclErrBalnRate1st_update);
  ros::param::get("HEX_Y_POS_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_1st_STEP", HEXyPosDirnMeclErrBalnRate1st_update);
  ros::param::get("HEX_Y_NEG_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_1st_STEP", HEXyNegDirnMeclErrBalnRate1st_update);
  ros::param::get("HEX_Z_POS_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_1st_STEP", HEXzPosDirnMeclErrBalnRate1st_update);
  ros::param::get("HEX_Z_NEG_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_1st_STEP", HEXzNegDirnMeclErrBalnRate1st_update);

  ros::param::get("HEX_X_POS_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_2nd_STEP", HEXxPosDirnMeclErrBalnRate2nd);
  ros::param::get("HEX_X_NEG_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_2nd_STEP", HEXxNegDirnMeclErrBalnRate2nd);
  ros::param::get("HEX_Y_POS_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_2nd_STEP", HEXyPosDirnMeclErrBalnRate2nd);
  ros::param::get("HEX_Y_NEG_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_2nd_STEP", HEXyNegDirnMeclErrBalnRate2nd);
  ros::param::get("HEX_Z_POS_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_2nd_STEP", HEXzPosDirnMeclErrBalnRate2nd);
  ros::param::get("HEX_Z_NEG_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_2nd_STEP", HEXzNegDirnMeclErrBalnRate2nd);
  ros::param::get("HEX_X_POS_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_2nd_STEP", HEXxPosDirnMeclErrBalnRate2nd_update);
  ros::param::get("HEX_X_NEG_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_2nd_STEP", HEXxNegDirnMeclErrBalnRate2nd_update);
  ros::param::get("HEX_Y_POS_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_2nd_STEP", HEXyPosDirnMeclErrBalnRate2nd_update);
  ros::param::get("HEX_Y_NEG_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_2nd_STEP", HEXyNegDirnMeclErrBalnRate2nd_update);
  ros::param::get("HEX_Z_POS_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_2nd_STEP", HEXzPosDirnMeclErrBalnRate2nd_update);
  ros::param::get("HEX_Z_NEG_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_2nd_STEP", HEXzNegDirnMeclErrBalnRate2nd_update);

  //螃蟹形态沿x，y，z正负方向运动差补比重
  ros::param::get("CRAB_X_POS_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_1st_STEP", CRABxPosDirnMeclErrBalnRate1st);
  ros::param::get("CRAB_X_NEG_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_1st_STEP", CRABxNegDirnMeclErrBalnRate1st);
  ros::param::get("CRAB_Y_POS_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_1st_STEP", CRAByPosDirnMeclErrBalnRate1st);
  ros::param::get("CRAB_Y_NEG_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_1st_STEP", CRAByNegDirnMeclErrBalnRate1st);
  ros::param::get("CRAB_Z_POS_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_1st_STEP", CRABzPosDirnMeclErrBalnRate1st);
  ros::param::get("CRAB_Z_NEG_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_1st_STEP", CRABzNegDirnMeclErrBalnRate1st);
  ros::param::get("CRAB_X_POS_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_1st_STEP", CRABxPosDirnMeclErrBalnRate1st_update);
  ros::param::get("CRAB_X_NEG_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_1st_STEP", CRABxNegDirnMeclErrBalnRate1st_update);
  ros::param::get("CRAB_Y_POS_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_1st_STEP", CRAByPosDirnMeclErrBalnRate1st_update);
  ros::param::get("CRAB_Y_NEG_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_1st_STEP", CRAByNegDirnMeclErrBalnRate1st_update);
  ros::param::get("CRAB_Z_POS_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_1st_STEP", CRABzPosDirnMeclErrBalnRate1st_update);
  ros::param::get("CRAB_Z_NEG_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_1st_STEP", CRABzNegDirnMeclErrBalnRate1st_update);

  ros::param::get("CRAB_X_POS_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_2nd_STEP", CRABxPosDirnMeclErrBalnRate2nd);
  ros::param::get("CRAB_X_NEG_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_2nd_STEP", CRABxNegDirnMeclErrBalnRate2nd);
  ros::param::get("CRAB_Y_POS_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_2nd_STEP", CRAByPosDirnMeclErrBalnRate2nd);
  ros::param::get("CRAB_Y_NEG_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_2nd_STEP", CRAByNegDirnMeclErrBalnRate2nd);
  ros::param::get("CRAB_Z_POS_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_2nd_STEP", CRABzPosDirnMeclErrBalnRate2nd);
  ros::param::get("CRAB_Z_NEG_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_2nd_STEP", CRABzNegDirnMeclErrBalnRate2nd);
  ros::param::get("CRAB_X_POS_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_2nd_STEP", CRABxPosDirnMeclErrBalnRate2nd_update);
  ros::param::get("CRAB_X_NEG_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_2nd_STEP", CRABxNegDirnMeclErrBalnRate2nd_update);
  ros::param::get("CRAB_Y_POS_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_2nd_STEP", CRAByPosDirnMeclErrBalnRate2nd_update);
  ros::param::get("CRAB_Y_NEG_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_2nd_STEP", CRAByNegDirnMeclErrBalnRate2nd_update);
  ros::param::get("CRAB_Z_POS_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_2nd_STEP", CRABzPosDirnMeclErrBalnRate2nd_update);
  ros::param::get("CRAB_Z_NEG_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_2nd_STEP", CRABzNegDirnMeclErrBalnRate2nd_update);

  //蜘蛛形态转换成螃蟹形态的机械误差差补比重
  ros::param::get("HEXAPOD_TO_CRAB_LEG1MOVE_MECHANICAL_ERROR_BALANCE_RATE", hex2crabMeclErrBalnRateLeg1);
  hex2crabMeclErrBalnRate.push_back(hex2crabMeclErrBalnRateLeg1);
  hex2crabMeclErrBalnRate_update.push_back(hex2crabMeclErrBalnRateLeg1);
  ros::param::get("HEXAPOD_TO_CRAB_LEG2MOVE_MECHANICAL_ERROR_BALANCE_RATE", hex2crabMeclErrBalnRateLeg2);
  hex2crabMeclErrBalnRate.push_back(hex2crabMeclErrBalnRateLeg2);
  hex2crabMeclErrBalnRate_update.push_back(hex2crabMeclErrBalnRateLeg2);
  ros::param::get("HEXAPOD_TO_CRAB_LEG3MOVE_MECHANICAL_ERROR_BALANCE_RATE", hex2crabMeclErrBalnRateLeg3);
  hex2crabMeclErrBalnRate.push_back(hex2crabMeclErrBalnRateLeg3);
  hex2crabMeclErrBalnRate_update.push_back(hex2crabMeclErrBalnRateLeg3);
  ros::param::get("HEXAPOD_TO_CRAB_LEG4MOVE_MECHANICAL_ERROR_BALANCE_RATE", hex2crabMeclErrBalnRateLeg4);
  hex2crabMeclErrBalnRate.push_back(hex2crabMeclErrBalnRateLeg4);
  hex2crabMeclErrBalnRate_update.push_back(hex2crabMeclErrBalnRateLeg4);
  ros::param::get("HEXAPOD_TO_CRAB_LEG5MOVE_MECHANICAL_ERROR_BALANCE_RATE", hex2crabMeclErrBalnRateLeg5);
  hex2crabMeclErrBalnRate.push_back(hex2crabMeclErrBalnRateLeg5);
  hex2crabMeclErrBalnRate_update.push_back(hex2crabMeclErrBalnRateLeg5);
  ros::param::get("HEXAPOD_TO_CRAB_LEG6MOVE_MECHANICAL_ERROR_BALANCE_RATE", hex2crabMeclErrBalnRateLeg6);
  hex2crabMeclErrBalnRate.push_back(hex2crabMeclErrBalnRateLeg6);
  hex2crabMeclErrBalnRate_update.push_back(hex2crabMeclErrBalnRateLeg6);

  //螃蟹形态转换成蜘蛛形态的机械误差差补比重
  ros::param::get("CRAB_TO_HEXAPOD_LEG1MOVE_MECHANICAL_ERROR_BALANCE_RATE", crab2hexMeclErrBalnRateLeg1);
  crab2hexMeclErrBalnRate.push_back(crab2hexMeclErrBalnRateLeg1);
  crab2hexMeclErrBalnRate_update.push_back(crab2hexMeclErrBalnRateLeg1);
  ros::param::get("CRAB_TO_HEXAPOD_LEG2MOVE_MECHANICAL_ERROR_BALANCE_RATE", crab2hexMeclErrBalnRateLeg2);
  crab2hexMeclErrBalnRate.push_back(crab2hexMeclErrBalnRateLeg2);
  crab2hexMeclErrBalnRate_update.push_back(crab2hexMeclErrBalnRateLeg2);
  ros::param::get("CRAB_TO_HEXAPOD_LEG3MOVE_MECHANICAL_ERROR_BALANCE_RATE", crab2hexMeclErrBalnRateLeg3);
  crab2hexMeclErrBalnRate.push_back(crab2hexMeclErrBalnRateLeg3);
  crab2hexMeclErrBalnRate_update.push_back(crab2hexMeclErrBalnRateLeg3);
  ros::param::get("CRAB_TO_HEXAPOD_LEG4MOVE_MECHANICAL_ERROR_BALANCE_RATE", crab2hexMeclErrBalnRateLeg4);
  crab2hexMeclErrBalnRate.push_back(crab2hexMeclErrBalnRateLeg4);
  crab2hexMeclErrBalnRate_update.push_back(crab2hexMeclErrBalnRateLeg4);
  ros::param::get("CRAB_TO_HEXAPOD_LEG5MOVE_MECHANICAL_ERROR_BALANCE_RATE", crab2hexMeclErrBalnRateLeg5);
  crab2hexMeclErrBalnRate.push_back(crab2hexMeclErrBalnRateLeg5);
  crab2hexMeclErrBalnRate_update.push_back(crab2hexMeclErrBalnRateLeg5);
  ros::param::get("CRAB_TO_HEXAPOD_LEG6MOVE_MECHANICAL_ERROR_BALANCE_RATE", crab2hexMeclErrBalnRateLeg6);
  crab2hexMeclErrBalnRate.push_back(crab2hexMeclErrBalnRateLeg6);
  crab2hexMeclErrBalnRate_update.push_back(crab2hexMeclErrBalnRateLeg6);

  ros::param::get("MECL_RECOVER_CYCLE_LENGTH", meclRecoverLength);
  ros::param::get("PREPRESS", PREPRESS);
  ros::param::get("PREPRESS_CYCLE_LENGTH", PREPRESS_CYCLE_LENGTH);

  saveMeclErrBalnRate_sub = nh_.subscribe<std_msgs::String>("/save_meclErrBalnRate", 1, &Control::saveMeclErrBalnRate_cb, this);

  prePress_confirm_flag = false;
  leg_meclErr_flag = false;
  leg_meclErr_balance_sub = nh_.subscribe<hexapod_msgs::LegJoints>("/hexapod_meclErr_balance", 1, &Control::leg_meclErr_balance_cb, this);
  leg_prePress_confirm_sub = nh_.subscribe<std_msgs::Float64>("/hexapod_confirm_prePress", 1, &Control::leg_prePress_confirm_cb, this);
  ros::param::get("MECLERR_BALANCE_LENGTH", meclErr_balance_length);

  //预压后的角度误差
  meclErr_afterPrePress_sub = nh_.subscribe<hexapod_msgs::LegJoints>("/hexapod_completely_prePress_balance", 1, &Control::meclErr_afterPrePress_cb, this);
  leg_meclErr_afterPrePress_flag = false;

  ROS_INFO("*********************************");
  ROS_INFO("         WeLCH-CLIMBING          ");
  if (MACHINE == 1)
    ROS_INFO(" Machine/Simulation: Machine    ");
  else
    ROS_INFO(" Machine/Simulation: Simulation ");
  if (STICK == 1)
    ROS_INFO("      Stick Control: ON         ");
  else
    ROS_INFO("      Stick Control: OFF        ");
  ROS_INFO("          by Kingsley             ");
  ROS_INFO("**********************************");
}

//订阅发布的速度信息，处理上下限速度信息.
//只接收一个方向的速度
void Control::cmd_velCallback(const geometry_msgs::TwistConstPtr &cmd_vel_msg)
{
  if (std::abs(cmd_vel_msg->linear.x) > 0.001)
  {
    if (std::abs(cmd_vel_msg->linear.y) > 0.001 || std::abs(cmd_vel_msg->angular.z) > 0.001)
    {
      ROS_WARN("ERROR SPEED. Only single direction is accepted.");
      return;
    }
  }

  if (std::abs(cmd_vel_msg->linear.y) > 0.001)
  {
    if (std::abs(cmd_vel_msg->linear.x) > 0.001 || std::abs(cmd_vel_msg->angular.z) > 0.001)
    {
      ROS_WARN("ERROR SPEED. Only single direction is accepted.");
      return;
    }
  }

  if (std::abs(cmd_vel_msg->angular.z) > 0.001)
  {
    if (std::abs(cmd_vel_msg->linear.x) > 0.001 || std::abs(cmd_vel_msg->linear.y) > 0.001)
    {
      ROS_WARN("ERROR SPEED. Only single direction is accepted.");
      return;
    }
  }

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

  if (robot_mode == crab_mode) //六足处于螃蟹形态时，不接收x方向速度和自转速度
  {
    cmd_vel_incoming_.linear.x = 0;
    cmd_vel_incoming_.angular.z = 0;
  }

  partitionCmd_vel(&cmd_vel_);
}

//速度转化成歩幅
void Control::partitionCmd_vel(geometry_msgs::Twist *cmd_vel)
{
  double dt = VELOCITY_DIVISION; //dt为1，将速度转换成1s内的运动距离，即步幅

  double delta_th = cmd_vel_incoming_.angular.z * dt;
  double delta_x = (cmd_vel_incoming_.linear.x * cos(delta_th) - cmd_vel_incoming_.linear.y * sin(delta_th)) * dt;
  double delta_y = (cmd_vel_incoming_.linear.x * sin(delta_th) + cmd_vel_incoming_.linear.y * cos(delta_th)) * dt;
  cmd_vel->linear.x = delta_x;
  cmd_vel->linear.y = delta_y;
  cmd_vel->angular.z = delta_th;
}

//发布角度话题，gazebo仿真
void Control::publishJointStates(const hexapod_msgs::LegsJoints &legs, const int &origin_period_, std::vector<int> &cycle_leg_number_, const hexapod_msgs::FeetPositions *feet)
{
  for (int leg_index = 0; leg_index < NUMBER_OF_LEGS; leg_index++)
  {
    leg_roll[leg_index].data = legs.leg[leg_index].coxa;
    leg_pitch1[leg_index].data = legs.leg[leg_index].femur;
    leg_pitch2[leg_index].data = legs.leg[leg_index].tibia;
    leg_pitch3[leg_index].data = legs.leg[leg_index].tarsus;
  }

  //发布关节角度话题
  for (int leg_index = 0; leg_index < NUMBER_OF_LEGS; leg_index++)
  {
    leg_roll_p[leg_index].publish(leg_roll[leg_index]);
    leg_pitch1_p[leg_index].publish(leg_pitch1[leg_index]);
    leg_pitch2_p[leg_index].publish(leg_pitch2[leg_index]);
    leg_pitch3_p[leg_index].publish(leg_pitch3[leg_index]);
  }

  ros::Duration(0.005).sleep();

  //feet_position.publish(*feet); //发布足端轨迹话题

#if 0
  //吸盘吸附力控制
  if (origin_period_ == 1)
  {

    for (int leg_index = 0; leg_index < NUMBER_OF_LEGS; leg_index++)
    {

      if (cycle_leg_number_[leg_index] == 0)
      {
        srv.request.body_name = force_to_stick[leg_index];
        srv.request.reference_frame = force_to_stick[leg_index];
        srv.request.wrench.force.z = 0;
        srv.request.duration.sec = 2;
        force_client.call(srv);
      }
      if (cycle_leg_number_[leg_index] == 1)
      {
        srv.request.body_name = force_to_stick[leg_index];
        srv.request.reference_frame = force_to_stick[leg_index];
        srv.request.wrench.force.z = -STICK_FORCE;
        srv.request.duration.sec = 3;
        force_client.call(srv);
      }
    }
    ros::Duration(15).sleep();
  }
#endif
}

//六足螃蟹姿态和蜘蛛姿态模式订阅回调函数，当模式改变时，置相应的模式切换标志位为真
//六足切换到爬墙模式前需处于蜘蛛形态
void Control::hexapod_mode_cb(const std_msgs::Int32ConstPtr &mode)
{
  if (mode->data != robot_mode)
  {
    if (mode->data == hexapod_mode)
      crab2hexapod_flag = (hexapod2crab_flag | climb2wall_flag) ? false : true; //三个标志位只能有一个为真

    if (mode->data == crab_mode && robot_mode != climb2wall_mode) //当执行完爬墙程序时，机器人处于螃蟹姿态
      hexapod2crab_flag = (crab2hexapod_flag | climb2wall_flag) ? false : true;
    if (mode->data == crab_mode && robot_mode == climb2wall_mode) //此时置模式为crab_mode时，直接改变不需执行变换程序
      robot_mode = crab_mode;

    if (mode->data == climb2wall_mode)
      climb2wall_flag = (hexapod2crab_flag | crab2hexapod_flag) ? false : true;
  }
  ROS_INFO("%d", crab2hexapod_flag);
}

//蜘蛛形态转为螃蟹形态控制函数
void Control::hexapod2crab_control()
{
  meclErrBalnRate_update_reset();

  ROS_INFO("-----Hexapod2crab-----");
  hexapod_msgs::LegsJoints legs_;
  for (int leg_index = 0; leg_index < 6; leg_index++)
  {
    legs_.leg[leg_index].coxa = 0;
    legs_.leg[leg_index].femur = 0;
    legs_.leg[leg_index].tibia = 0;
    legs_.leg[leg_index].tarsus = 0;
  }

  geometry_msgs::Point initPos[6];
  for (int leg_index = 0; leg_index < 6; leg_index++)
  {
    positionCalculate(leg_index, legs_.leg[leg_index], initPos[leg_index]);
  }

  //计算螃蟹形态时的终止姿态
  geometry_msgs::Point finalPos[6];
  hexapod_msgs::LegsJoints finalLegs;
  finalLegs.leg[0].coxa = 1.0471975511965979;
  finalLegs.leg[0].femur = -0.038758520830718061;
  finalLegs.leg[0].tibia = -0.22365627124495968;
  finalLegs.leg[0].tarsus = 0.26241479207567775;

  finalLegs.leg[1].coxa = 0;
  finalLegs.leg[1].femur = -0.059724262471019439;
  finalLegs.leg[1].tibia = -0.16509683859324015;
  finalLegs.leg[1].tarsus = 0.22482110106425959;

  finalLegs.leg[2].coxa = -1.0471975511965979;
  finalLegs.leg[2].femur = -0.038758537257535017;
  finalLegs.leg[2].tibia = -0.22365627515359282;
  finalLegs.leg[2].tarsus = 0.26241481241112785;

  finalLegs.leg[3].coxa = 1.0471975511965979;
  finalLegs.leg[3].femur = -0.018897554015098201;
  finalLegs.leg[3].tibia = -0.24467115841576767;
  finalLegs.leg[3].tarsus = 0.26356871243086588;

  finalLegs.leg[4].coxa = 0;
  finalLegs.leg[4].femur = -0.036513660820203096;
  finalLegs.leg[4].tibia = -0.19001813422958463;
  finalLegs.leg[4].tarsus = 0.22653179504978774;

  finalLegs.leg[5].coxa = -1.0471975511965979;
  finalLegs.leg[5].femur = -0.018897537546665254;
  finalLegs.leg[5].tibia = -0.24467115439928608;
  finalLegs.leg[5].tarsus = 0.26356869194595134;
  for (int leg_index = 0; leg_index < 6; leg_index++)
  {
    positionCalculate(leg_index, finalLegs.leg[leg_index], finalPos[leg_index]);
  }

  //还原关节角度为0
  legs_.leg[0].coxa = 0;
  legs_.leg[2].coxa = 0;
  legs_.leg[3].coxa = 0;
  legs_.leg[5].coxa = 0;

  double liftHeight = 0.1; //抬腿高度
  int cycle_length = 1800; //1800

  for (int leg_index = 0; leg_index < 6; leg_index++)
  {
    legAdjustOnGround(HEX2CRAB, leg_index, initPos[leg_index], finalPos[leg_index], liftHeight, cycle_length, legs_);
  }
  ROS_INFO("Hexapod2crab finished. Now robot is in state of crab.");
}

//螃蟹形态转为蜘蛛形态控制函数
void Control::crab2hexapod_control()
{
  meclErrBalnRate_update_reset();

  ROS_INFO("-----Crab2hexapod-----");

  /*  for (int leg_index = 0; leg_index < 6; leg_index++)
  {
    legs_.leg[leg_index].coxa = 0;
    legs_.leg[leg_index].femur = 0;
    legs_.leg[leg_index].tibia = 0;
    legs_.leg[leg_index].tarsus = 0;
  }
  legs_.leg[0].coxa = M_PI / 3.0;
  legs_.leg[2].coxa = -M_PI / 3.0;
  legs_.leg[3].coxa = M_PI / 3.0;
  legs_.leg[5].coxa = -M_PI / 3.0;*/

  legs_.leg[0].coxa = 1.0471975511965979;
  legs_.leg[0].femur = -0.038758520830718061;
  legs_.leg[0].tibia = -0.22365627124495968;
  legs_.leg[0].tarsus = 0.26241479207567775;

  legs_.leg[1].coxa = 0;
  legs_.leg[1].femur = -0.059724262471019439;
  legs_.leg[1].tibia = -0.16509683859324015;
  legs_.leg[1].tarsus = 0.22482110106425959;

  legs_.leg[2].coxa = -1.0471975511965979;
  legs_.leg[2].femur = -0.038758537257535017;
  legs_.leg[2].tibia = -0.22365627515359282;
  legs_.leg[2].tarsus = 0.26241481241112785;

  legs_.leg[3].coxa = 1.0471975511965979;
  legs_.leg[3].femur = -0.018897554015098201;legs_.leg[0].coxa = 1.0471975511965979;
  legs_.leg[0].femur = -0.038758520830718061;
  legs_.leg[0].tibia = -0.22365627124495968;
  legs_.leg[0].tarsus = 0.26241479207567775;

  legs_.leg[1].coxa = 0;
  legs_.leg[1].femur = -0.059724262471019439;
  legs_.leg[1].tibia = -0.16509683859324015;
  legs_.leg[1].tarsus = 0.22482110106425959;

  legs_.leg[2].coxa = -1.0471975511965979;
  legs_.leg[2].femur = -0.038758537257535017;
  legs_.leg[2].tibia = -0.22365627515359282;
  legs_.leg[2].tarsus = 0.26241481241112785;

  legs_.leg[3].coxa = 1.0471975511965979;
  legs_.leg[3].femur = -0.018897554015098201;
  legs_.leg[3].tibia = -0.24467115841576767;
  legs_.leg[3].tarsus = 0.26356871243086588;

  legs_.leg[4].coxa = 0;
  legs_.leg[4].femur = -0.036513660820203096;
  legs_.leg[4].tibia = -0.19001813422958463;
  legs_.leg[4].tarsus = 0.22653179504978774;

  legs_.leg[5].coxa = -1.0471975511965979;
  legs_.leg[5].femur = -0.018897537546665254;
  legs_.leg[5].tibia = -0.24467115439928608;
  legs_.leg[5].tarsus = 0.26356869194595134;
  legs_.leg[3].tibia = -0.24467115841576767;
  legs_.leg[3].tarsus = 0.26356871243086588;

  legs_.leg[4].coxa = 0;
  legs_.leg[4].femur = -0.036513660820203096;
  legs_.leg[4].tibia = -0.19001813422958463;
  legs_.leg[4].tarsus = 0.22653179504978774;

  legs_.leg[5].coxa = -1.0471975511965979;
  legs_.leg[5].femur = -0.018897537546665254;
  legs_.leg[5].tibia = -0.24467115439928608;
  legs_.leg[5].tarsus = 0.26356869194595134;

  geometry_msgs::Point initPos[6];
  for (int leg_index = 0; leg_index < 6; leg_index++)
  {
    positionCalculate(leg_index, legs_.leg[leg_index], initPos[leg_index]);
  }

  //计算蜘蛛形态时的终止姿态
  geometry_msgs::Point finalPos[6];
  hexapod_msgs::LegsJoints finalLegs;
  for (int leg_index = 0; leg_index < 6; leg_index++)
  {
    finalLegs.leg[leg_index].coxa = 0;
    finalLegs.leg[leg_index].femur = 0;
    finalLegs.leg[leg_index].tibia = 0;
    finalLegs.leg[leg_index].tarsus = 0;
  }
  for (int leg_index = 0; leg_index < 6; leg_index++)
  {
    positionCalculate(leg_index, finalLegs.leg[leg_index], finalPos[leg_index]);
  }

  double liftHeight = 0.1; //抬腿高度
  int cycle_length = 1800; //1800

  for (int leg_index = 0; leg_index < 6; leg_index++)
  {
    legAdjustOnGround(CRAB2HEX, leg_index, initPos[leg_index], finalPos[leg_index], liftHeight, cycle_length, legs_);
  }
  ROS_INFO("Crab2hexapod finished. Now robot is in state of hexapod.");
}

//向服务器请求maxpoints，填充buffer
void Control::feedDrivers(const int &cycle_period_, std::vector<int> &cycle_leg_number_)
{
  //feedDriver条件：每运动一次后的速度不为0
  if (std::abs(cmd_vel_.linear.x) > 0.001 || std::abs(cmd_vel_.linear.y) > 0.001 || std::abs(cmd_vel_.angular.z) > 0.001)
  {
    if (robot_mode == climb2wall_mode) //当六足处于爬墙模式时，不进行速度控制，直接返回
    {
      ROS_INFO("Robot is in state of climb2wall. Please set speed to zero.");
      return;
    }

    geometry_msgs::Twist cmd_vel_step; //每次运动的步幅
    cmd_vel_step.linear.x = cmd_vel_.linear.x;
    cmd_vel_step.linear.y = cmd_vel_.linear.y;
    cmd_vel_step.angular.z = cmd_vel_.angular.z;

    maxpoints_ = gait.getCycleLength(cmd_vel_step); //获取周期长度

    //机械误差赋值，分x，y，z正负方向共六种
    struct ErrMode robotMeclErrMode;
    meclErrBalnRate_update_reset(); //重设update的误差表
    std::vector<std::vector<float>> MeclErrBalnRate;
    if (robot_mode == hexapod_mode) //蜘蛛形态运动时的误差
    {
      robotMeclErrMode.mode = hexapod_mode;
      if (cmd_vel_step.linear.x > 0.001)
      {
        MeclErrBalnRate.push_back(HEXxPosDirnMeclErrBalnRate1st);
        MeclErrBalnRate.push_back(HEXxPosDirnMeclErrBalnRate2nd);
        robotMeclErrMode.dirn = "xp";
      }
      else if (cmd_vel_step.linear.x < -0.001)
      {
        MeclErrBalnRate.push_back(HEXxNegDirnMeclErrBalnRate1st);
        MeclErrBalnRate.push_back(HEXxNegDirnMeclErrBalnRate2nd);
        robotMeclErrMode.dirn = "xn";
      }
      else if (cmd_vel_step.linear.y > 0.001)
      {
        MeclErrBalnRate.push_back(HEXyPosDirnMeclErrBalnRate1st);
        MeclErrBalnRate.push_back(HEXyPosDirnMeclErrBalnRate2nd);
        robotMeclErrMode.dirn = "yp";
      }
      else if (cmd_vel_step.linear.y < -0.001)
      {
        MeclErrBalnRate.push_back(HEXyNegDirnMeclErrBalnRate1st);
        MeclErrBalnRate.push_back(HEXyNegDirnMeclErrBalnRate2nd);
        robotMeclErrMode.dirn = "yn";
      }
      else if (cmd_vel_step.angular.z > 0.001)
      {
        MeclErrBalnRate.push_back(HEXzPosDirnMeclErrBalnRate1st);
        MeclErrBalnRate.push_back(HEXzPosDirnMeclErrBalnRate2nd);
        robotMeclErrMode.dirn = "zp";
      }
      else if (cmd_vel_step.angular.z < -0.001)
      {
        MeclErrBalnRate.push_back(HEXzNegDirnMeclErrBalnRate1st);
        MeclErrBalnRate.push_back(HEXzNegDirnMeclErrBalnRate2nd);
        robotMeclErrMode.dirn = "zn";
      }
    }
    else //螃蟹形态时的误差
    {
      robotMeclErrMode.mode = crab_mode;
      if (cmd_vel_step.linear.x > 0.001)
      {
        MeclErrBalnRate.push_back(CRABxPosDirnMeclErrBalnRate1st);
        MeclErrBalnRate.push_back(CRABxPosDirnMeclErrBalnRate2nd);
        robotMeclErrMode.dirn = "xp";
      }
      else if (cmd_vel_step.linear.x < -0.001)
      {
        MeclErrBalnRate.push_back(CRABxNegDirnMeclErrBalnRate1st);
        MeclErrBalnRate.push_back(CRABxNegDirnMeclErrBalnRate2nd);
        robotMeclErrMode.dirn = "xn";
      }
      else if (cmd_vel_step.linear.y > 0.001)
      {
        MeclErrBalnRate.push_back(CRAByPosDirnMeclErrBalnRate1st);
        MeclErrBalnRate.push_back(CRAByPosDirnMeclErrBalnRate2nd);
        robotMeclErrMode.dirn = "yp";
      }
      else if (cmd_vel_step.linear.y < -0.001)
      {
        MeclErrBalnRate.push_back(CRAByNegDirnMeclErrBalnRate1st);
        MeclErrBalnRate.push_back(CRAByNegDirnMeclErrBalnRate2nd);
        robotMeclErrMode.dirn = "yn";
      }
      else if (cmd_vel_step.angular.z > 0.001)
      {
        MeclErrBalnRate.push_back(CRABzPosDirnMeclErrBalnRate1st);
        MeclErrBalnRate.push_back(CRABzPosDirnMeclErrBalnRate2nd);
        robotMeclErrMode.dirn = "zp";
      }
      else if (cmd_vel_step.angular.z < -0.001)
      {
        MeclErrBalnRate.push_back(CRABzNegDirnMeclErrBalnRate1st);
        MeclErrBalnRate.push_back(CRABzNegDirnMeclErrBalnRate2nd);
        robotMeclErrMode.dirn = "zn";
      }
    }

    //每一次运动由两部分组成，两部分运动完后六足处于原始姿态
    for (int gaitCnt = 0; gaitCnt < 2; gaitCnt++)
    {
      robotMeclErrMode.gaitCnt = gaitCnt;
#if MACHINE
      maxpointsRequest(); //请求maxpoints，确认motionActive和freeSpace

      while (freeSpace_ < sm_point_buf_size - 30) //当六足服务器的freeSpace大于一个周期时，进行吸盘控制
      {
        ros::Duration(3).sleep();
        ROS_INFO("freeSpace(%d) is not enough", freeSpace_);
        maxpointsRequest();
      }

      //status不为1或者abortMotion时，关闭算法节点
      if (motionActive_ == false)
      {
        ros::shutdown();
        return;
      }
#endif

      //运动前将摆动腿的吸盘放气
#if STICK
      stick_srv_.request.chose = 2;
      int Reqio[7];
      for (int i = 0; i < 6; i++)
      {
        stick_srv_.request.io[i] = cycle_leg_number_[i];
        Reqio[i] = stick_srv_.request.io[i];
      }
      Reqio[6] = stick_srv_.request.io[6] = 1;

      while (!stick_client_.call(stick_srv_))
      {
        ROS_WARN("Failed to call stick service. Retrying...");
        ros::Duration(1).sleep();
      }
      ROS_INFO("%s", stick_srv_.response.back.c_str());

      ros::Duration(5).sleep(); //吸盘放气等待时间
      //查看吸盘是否放气完毕
      while (!isStickDone(Reqio))
      {
        ros::Duration(3).sleep();
      }
      ROS_INFO("Stick control done. Ready to move.");
#endif

#if MACHINE
      maxpointsRequest(); //请求maxpoints，确认motionActive和freeSpace

      //status不为1或者abortMotion时，关闭算法节点
      if (motionActive_ == false)
      {
        ros::shutdown();
        return;
      }

      while (freeSpace_ < maxpoints_) //当六足服务器的freeSpace大于一个周期时，才填充六足服务器buffer
      {
        ros::Duration(3).sleep();
        ROS_INFO("freeSpace(%d) is not enough", freeSpace_);
        maxpointsRequest();
      }

      //每个关节的填充buffer大小初始化
      for (int position_resize = 0; position_resize < 6; position_resize++)
      {
        leg_goal_.ALLLEGS.leg[position_resize].coxa.resize(maxpoints_);
        leg_goal_.ALLLEGS.leg[position_resize].femur.resize(maxpoints_);
        leg_goal_.ALLLEGS.leg[position_resize].tibia.resize(maxpoints_);
        leg_goal_.ALLLEGS.leg[position_resize].tarsus.resize(maxpoints_);
      }
#endif

      //调用maxpoints次算法，即一个周期
      for (int i = 0; i < maxpoints_; i++)
      {
        gait.gaitCycle(cmd_vel_step, &feet_); //足端轨迹计算
        if (robot_mode == hexapod_mode)
        {
          hexapod_ik.calculateIK(feet_, &legs_); //蜘蛛形态ik计算
        }
        else
        {
          crab_ik.calculateIK(feet_, &legs_); //螃蟹形态ik计算
        }

        walkGaitMeclErrCompensate(legs_, MeclErrBalnRate[gaitCnt], i, maxpoints_); //加入机械误差补偿

#if !MACHINE
        publishJointStates(legs_, cycle_period_, cycle_leg_number_, &feet_); //发布角度话题信息，gazebo仿真
#else
        for (int leg_index = 0; leg_index < 6; leg_index++)
        {
          leg_goal_.ALLLEGS.leg[leg_index].coxa[i] = round(4096.0 * (3005640.0 / 1300.0) * (legs_.leg[leg_index].coxa / M_PI * 180.0) / 360.0);
          leg_goal_.ALLLEGS.leg[leg_index].femur[i] = round(4096.0 * (3005640.0 / 1300.0) * (-legs_.leg[leg_index].femur / M_PI * 180.0) / 360.0);
          leg_goal_.ALLLEGS.leg[leg_index].tibia[i] = round(4096.0 * (3005640.0 / 1300.0) * (-legs_.leg[leg_index].tibia / M_PI * 180.0) / 360.0);
          leg_goal_.ALLLEGS.leg[leg_index].tarsus[i] = round(4096.0 * (3005640.0 / 1300.0) * (-legs_.leg[leg_index].tarsus / M_PI * 180.0) / 360.0);
        }
#endif
      }

#if MACHINE
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
#endif

      hexapod_msgs::LegsJoints legs_before_prePress;  //预压前的角度
      for (int leg_index = 0; leg_index < 6; leg_index++)
      {
        legs_before_prePress.leg[leg_index].coxa = legs_.leg[leg_index].coxa;
        legs_before_prePress.leg[leg_index].femur = legs_.leg[leg_index].femur;
        legs_before_prePress.leg[leg_index].tibia = legs_.leg[leg_index].tibia;
        legs_before_prePress.leg[leg_index].tarsus = legs_.leg[leg_index].tarsus;
      }
      /****************预压*************************/
      walkGaitPrePress(cycle_leg_number_, PREPRESS, PREPRESS_CYCLE_LENGTH, robotMeclErrMode, legs_);

      hexapod_msgs::LegsJoints legs_meclErrBaln; //总的角度误差补偿值
      for (int leg_index = 0; leg_index < 6; leg_index++)
      {
        legs_meclErrBaln.leg[leg_index].coxa = legs_.leg[leg_index].coxa - legs_before_prePress.leg[leg_index].coxa + MeclErrUnit * MeclErr[leg_index * 4] * MeclErrBalnRate[gaitCnt][leg_index * 4];
        legs_meclErrBaln.leg[leg_index].femur = legs_.leg[leg_index].femur - legs_before_prePress.leg[leg_index].femur + MeclErrUnit * MeclErr[leg_index * 4 + 1] * MeclErrBalnRate[gaitCnt][leg_index * 4 + 1];
        legs_meclErrBaln.leg[leg_index].tibia = legs_.leg[leg_index].tibia - legs_before_prePress.leg[leg_index].tibia + MeclErrUnit * MeclErr[leg_index * 4 + 2] * MeclErrBalnRate[gaitCnt][leg_index * 4 + 2];
        legs_meclErrBaln.leg[leg_index].tarsus = legs_.leg[leg_index].tarsus - legs_before_prePress.leg[leg_index].tarsus + MeclErrUnit * MeclErr[leg_index * 4 + 3] * MeclErrBalnRate[gaitCnt][leg_index * 4 + 3];
      }

      /***********************误差恢复*************************************/
      for (int i = 0; i < 24; i++)
      {
        posBuffer[i].clear(); //清空缓存
      }
      // 缓存恢复后的角度
      hexapod_msgs::LegsJoints initlegs;
      for (int leg_index = 0; leg_index < 6; leg_index++)
      {
        initlegs.leg[leg_index].coxa = legs_.leg[leg_index].coxa - legs_meclErrBaln.leg[leg_index].coxa;
        initlegs.leg[leg_index].femur = legs_.leg[leg_index].femur - legs_meclErrBaln.leg[leg_index].femur;
        initlegs.leg[leg_index].tibia = legs_.leg[leg_index].tibia - legs_meclErrBaln.leg[leg_index].tibia;
        initlegs.leg[leg_index].tarsus = legs_.leg[leg_index].tarsus - legs_meclErrBaln.leg[leg_index].tarsus;
      }
      //用三角函数将角度从加入机械误差后的角度恢复至原始角度
      for (int i = 0; i <= meclRecoverLength; i++)
      {
        for (int leg_index = 0; leg_index < 6; leg_index++)
        {
          legs_.leg[leg_index].coxa = 0.5 * legs_meclErrBaln.leg[leg_index].coxa * cos(M_PI * i / meclRecoverLength) + initlegs.leg[leg_index].coxa + 0.5 * legs_meclErrBaln.leg[leg_index].coxa;

          legs_.leg[leg_index].femur = 0.5 * legs_meclErrBaln.leg[leg_index].femur * cos(M_PI * i / meclRecoverLength) + initlegs.leg[leg_index].femur + 0.5 * legs_meclErrBaln.leg[leg_index].femur;

          legs_.leg[leg_index].tibia = 0.5 * legs_meclErrBaln.leg[leg_index].tibia * cos(M_PI * i / meclRecoverLength) + initlegs.leg[leg_index].tibia + 0.5 * legs_meclErrBaln.leg[leg_index].tibia;

          legs_.leg[leg_index].tarsus = 0.5 * legs_meclErrBaln.leg[leg_index].tarsus * cos(M_PI * i / meclRecoverLength) + initlegs.leg[leg_index].tarsus + 0.5 * legs_meclErrBaln.leg[leg_index].tarsus;
        }
        //将角度值填充进posBuffer缓存
        for (int leg_index = 0; leg_index < 6; leg_index++)
        {
          posBuffer[leg_index * 4].push_back(legs_.leg[leg_index].coxa);
          posBuffer[leg_index * 4 + 1].push_back(legs_.leg[leg_index].femur);
          posBuffer[leg_index * 4 + 2].push_back(legs_.leg[leg_index].tibia);
          posBuffer[leg_index * 4 + 3].push_back(legs_.leg[leg_index].tarsus);
        }
      }
#if MACHINE
      maxpointsRequest(); //请求maxpoints，确认motionActive/freeSpace

      //status不为1或者abortMotion时，关闭算法节点
      if (motionActive_ == false)
      {
        ros::shutdown();
        return;
      }

      while (freeSpace_ < meclRecoverLength) //六足服务器freeSpace大于误差恢复周期时，再填充六足服务器buffer
      {
        ros::Duration(3).sleep();
        ROS_INFO("freeSpace(%d) is not enough", freeSpace_);
        maxpointsRequest();
      }
#endif

      publishMeclErrRecover(); //发布误差恢复角度控制话题或填充六足服务器buffer
    }
    cmd_vel_.linear.x = cmd_vel_.linear.y = cmd_vel_.angular.z = 0; //步幅设置为0，接收新的速度指令
  }
  else /*当六足停止时，检查姿态变换标志位，是否需要进行螃蟹姿态和蜘蛛形态的切换*/
  {
    if (hexapod2crab_flag == true)
    {
      hexapod2crab_control();
      robot_mode = crab_mode;
      hexapod2crab_flag = false;
    }
    if (crab2hexapod_flag == true)
    {
      crab2hexapod_control();
      robot_mode = hexapod_mode;
      crab2hexapod_flag = false;
    }
    if (climb2wall_flag == true)
    {
      robot_mode = climb2wall_mode;
      climb2wall_flag = false;
    }
  }
}

//机械误差补偿函数
void Control::walkGaitMeclErrCompensate(hexapod_msgs::LegsJoints &legs, std::vector<float> &MeclErrBalnRate, const int cycle_period, const int cycle_length)
{
  for (int leg_index = 0; leg_index < 6; leg_index++)
  {
    legs.leg[leg_index].coxa = legs.leg[leg_index].coxa + double(cycle_period) / double(cycle_length) * MeclErrUnit * MeclErr[leg_index * 4] * MeclErrBalnRate[leg_index * 4];
    legs.leg[leg_index].femur = legs.leg[leg_index].femur + double(cycle_period) / double(cycle_length) * MeclErrUnit * MeclErr[leg_index * 4 + 1] * MeclErrBalnRate[leg_index * 4 + 1];
    legs.leg[leg_index].tibia = legs.leg[leg_index].tibia + double(cycle_period) / double(cycle_length) * MeclErrUnit * MeclErr[leg_index * 4 + 2] * MeclErrBalnRate[leg_index * 4 + 2];
    legs.leg[leg_index].tarsus = legs.leg[leg_index].tarsus + double(cycle_period) / double(cycle_length) * MeclErrUnit * MeclErr[leg_index * 4 + 3] * MeclErrBalnRate[leg_index * 4 + 3];
  }
}

//误差恢复控制，发布误差恢复角度(posBuffer中的缓存)至gazebo话题或填充六足服务器buffer
void Control::publishMeclErrRecover()
{
#if !MACHINE
  for (int i = 0; i < posBuffer[0].size(); i++)
  {
    for (int leg = 0; leg < 6; leg++)
    {
      leg_roll[leg].data = posBuffer[leg * 4][i];
      leg_pitch1[leg].data = posBuffer[leg * 4 + 1][i];
      leg_pitch2[leg].data = posBuffer[leg * 4 + 2][i];
      leg_pitch3[leg].data = posBuffer[leg * 4 + 3][i];
    }

    for (int leg = 0; leg < 6; leg++)
    {
      leg_roll_p[leg].publish(leg_roll[leg]);
      leg_pitch1_p[leg].publish(leg_pitch1[leg]);
      leg_pitch2_p[leg].publish(leg_pitch2[leg]);
      leg_pitch3_p[leg].publish(leg_pitch3[leg]);
    }

    ros::Duration(0.005).sleep();
  }
#endif

#if MACHINE
  legControl(); //填充六足服务器buffer
#endif
}

/********三角步态预压函数*********/
void Control::walkGaitPrePress(const std::vector<int> &cycle_leg_number, double prePress, const int cycle_length, const struct ErrMode robotMeclErrMode, hexapod_msgs::LegsJoints &legs)
{
  for (int leg_index = 0; leg_index < 6; leg_index++)
  {
    if (cycle_leg_number[leg_index] == 0) //摆动腿依次进行预压
    {
      meclErrBaln_beforPrepress(leg_index, prePress, legs, robotMeclErrMode); //预压前的角度补偿

#if 0
      hexapod_msgs::LegJoints initLeg; //缓存初始关节角
      initLeg.coxa = legs.leg[leg_index].coxa;
      initLeg.femur = legs.leg[leg_index].femur;
      initLeg.tibia = legs.leg[leg_index].tibia;
      initLeg.tarsus = legs.leg[leg_index].tarsus;
      
      for (int i = 0; i < 24; i++)
      {
        posBuffer[i].clear(); //清空缓存
      }
      for (int cycle_period = 0; cycle_period <= cycle_length; cycle_period++)
      {

        double interFuncX = -0.5 * cos(2.0 * M_PI * cycle_period / cycle_length) + 0.5;
        double foot2foot_x = prePress * interFuncX;

        double foot2foot_y = 0;

        double A = FEMUR_LENGTH * sin(initLeg.tibia + initLeg.tarsus) + TIBIA_LENGTH * cos(initLeg.tarsus) + foot2foot_x;
        double B = FEMUR_LENGTH * cos(initLeg.tibia + initLeg.tarsus) - TIBIA_LENGTH * sin(initLeg.tarsus) + foot2foot_y;
        double C = FEMUR_LENGTH;
        double D = TIBIA_LENGTH;

        double temp = 4.0 * pow(C, 2) * pow(D, 2) - pow((A * A + B * B - C * C - D * D), 2);
        temp = temp > 0 ? temp : 0;

        double x = 2.0 * atan(
                             (2.0 * A * C - sqrt(temp)) /
                             (A * A + pow((B + C), 2) - D * D));

        double y = 2.0 * atan(
                             (-2.0 * B * D + sqrt(temp)) /
                             (pow((A + D), 2) + B * B - C * C));

        legs.leg[leg_index].coxa = initLeg.coxa;
        legs.leg[leg_index].femur = initLeg.femur + initLeg.tarsus + initLeg.tibia - x;
        legs.leg[leg_index].tibia = x - y;
        legs.leg[leg_index].tarsus = y;

        //将预压角度存至posBuffer缓存
        for (int leg = 0; leg < 6; leg++)
        {
          posBuffer[leg * 4].push_back(legs.leg[leg].coxa);
          posBuffer[leg * 4 + 1].push_back(legs.leg[leg].femur);
          posBuffer[leg * 4 + 2].push_back(legs.leg[leg].tibia);
          posBuffer[leg * 4 + 3].push_back(legs.leg[leg].tarsus);
        }
      }

      publishWalkGaitPrePressPos(cycle_leg_number, leg_index); //发布预压角度话题或填充六足服务器buffer
#endif

#if MACHINE
      maxpointsRequest(); //请求maxpoints，确认motionActive和freeSpace

      //status不为1或者abortMotion时，关闭算法节点
      if (motionActive_ == false)
      {
        ros::shutdown();
        return;
      }

      while (freeSpace_ < maxpoints_) //当六足服务器的freeSpace大于一个周期时，才填充六足服务器buffer
      {
        ros::Duration(3).sleep();
        ROS_INFO("freeSpace(%d) is not enough", freeSpace_);
        maxpointsRequest();
      }

      //status不为1或者abortMotion时，关闭算法节点
      if (motionActive_ == false)
      {
        ros::shutdown();
        return;
      }
#endif

      prePress_forward(leg_index, prePress, PREPRESS_CYCLE_LENGTH / 2, legs);
      prePress_backward(leg_index, prePress, PREPRESS_CYCLE_LENGTH / 2, legs);
    }
  }
}

//预压前半段控制函数，预压后在气压升至80前可以进行关节补偿
void Control::prePress_forward(const int leg_index, double prePress, const int cycle_length, hexapod_msgs::LegsJoints &legs)
{
  if (posBuffer[0].size() != 0)
  {
    for (int i = 0; i < 24; i++)
    {
      posBuffer[i].clear();
    }
  }

  hexapod_msgs::LegJoints initLeg; //缓存初始关节角

  initLeg.coxa = legs.leg[leg_index].coxa;
  initLeg.femur = legs.leg[leg_index].femur;
  initLeg.tibia = legs.leg[leg_index].tibia;
  initLeg.tarsus = legs.leg[leg_index].tarsus;

  for (int cycle_period = 0; cycle_period <= cycle_length; cycle_period++)
  {
    double interFuncX = -0.5 * cos(M_PI * cycle_period / cycle_length) + 0.5;
    double foot2foot_x = prePress * interFuncX;

    double foot2foot_y = 0;

    double A = FEMUR_LENGTH * sin(initLeg.tibia + initLeg.tarsus) + TIBIA_LENGTH * cos(initLeg.tarsus) + foot2foot_x;
    double B = FEMUR_LENGTH * cos(initLeg.tibia + initLeg.tarsus) - TIBIA_LENGTH * sin(initLeg.tarsus) + foot2foot_y;
    double C = FEMUR_LENGTH;
    double D = TIBIA_LENGTH;

    double temp = 4.0 * pow(C, 2) * pow(D, 2) - pow((A * A + B * B - C * C - D * D), 2);
    temp = temp > 0 ? temp : 0;

    double x = 2.0 * atan(
                         (2.0 * A * C - sqrt(temp)) /
                         (A * A + pow((B + C), 2) - D * D));

    double y = 2.0 * atan(
                         (-2.0 * B * D + sqrt(temp)) /
                         (pow((A + D), 2) + B * B - C * C));

    legs.leg[leg_index].coxa = initLeg.coxa;
    legs.leg[leg_index].femur = initLeg.femur + initLeg.tarsus + initLeg.tibia - x;
    legs.leg[leg_index].tibia = x - y;
    legs.leg[leg_index].tarsus = y;

    rawJointStatesStore(legs);
  }

  ROS_INFO("---prepress stick control---");

#if MACHINE
  maxpointsRequest(); //请求maxpoints，确认freeSpace/motionActive

  while (freeSpace_ < (sm_point_buf_size - 30)) //sm服务器buffer接近空时，进行吸盘控制
  {
    ros::Duration(2).sleep();
    maxpointsRequest();
  }

  if (!motionActive_)
  {
    ROS_FATAL("Motion not active!");
    ros::shutdown();
    //return false;
  }
#endif

#if STICK
  //预压前发送io口控制，将对应的腿吸盘抽至真空，其余不变
  stick_srv_.request.chose = 2;
  int requestIO[7];
  for (int i = 0; i < 6; i++)
  {
    stick_srv_.request.io[i] = io[i];
    requestIO[i] = io[i];
  }
  stick_srv_.request.io[leg_index] = requestIO[leg_index] = 0;
  stick_srv_.request.io[6] = requestIO[6] = 1;

  while (!stick_client_.call(stick_srv_))
  {
    ROS_WARN("Failed to call stick service. Retrying...");
    ros::Duration(2).sleep();
  }
  ROS_INFO("%s, request io: %d, %d, %d, %d, %d, %d", stick_srv_.response.back.c_str(), requestIO[0], requestIO[1], requestIO[2], requestIO[3], requestIO[4], requestIO[5]);
#endif

  publishPosBuffer(); //发送io口控制后进行预压

#if STICK
  ros::Duration(5.0).sleep(); //确保气压从80以上降到80以下再回升
  //查看吸盘是否吸气完成

  hexapod_msgs::LegsJoints initLegs; //缓存初始关节角度
  for (int leg_index = 0; leg_index < 6; leg_index++)
  {
    initLegs.leg[leg_index].coxa = legs.leg[leg_index].coxa;
    initLegs.leg[leg_index].femur = legs.leg[leg_index].femur;
    initLegs.leg[leg_index].tibia = legs.leg[leg_index].tibia;
    initLegs.leg[leg_index].tarsus = legs.leg[leg_index].tarsus;
  }
  bool leg_meclErr_reset_flag = false;

  leg_meclErr_afterPrePress_flag = false;
  leg_meclErr_afterPrePress.coxa = leg_meclErr_afterPrePress.femur = leg_meclErr_afterPrePress.tibia = leg_meclErr_afterPrePress.tarsus = 0.0;
  while (!isStickDone(requestIO)) //当气压未升至80时，进入循环，可发布话题进行角度调节
  {
    if (leg_meclErr_afterPrePress_flag == true) //当接收到角度调节话题时，进行误差补偿
    {
      completely_prePress_balance(leg_index, legs);
      leg_meclErr_afterPrePress_flag = false;
      leg_meclErr_reset_flag = true;
    }
    else
    {
      ros::Duration(3).sleep();
    }
  }

  ROS_INFO("Prepress finished. ");
#endif
}

//预压后进行角度误差补偿
void Control::completely_prePress_balance(const int leg_index, hexapod_msgs::LegsJoints &legs)
{
  //缓存恢复后的角度
  hexapod_msgs::LegJoints initleg;
  initleg.coxa = legs.leg[leg_index].coxa;
  initleg.femur = legs.leg[leg_index].femur;
  initleg.tibia = legs.leg[leg_index].tibia;
  initleg.tarsus = legs.leg[leg_index].tarsus;

  //用三角函数处理角度补偿
  for (int i = 0; i < meclErr_balance_length; i++)
  {
    legs.leg[leg_index].coxa = -0.5 * leg_meclErr_afterPrePress.coxa * cos(M_PI * i / meclErr_balance_length) + 0.5 * leg_meclErr_afterPrePress.coxa + initleg.coxa;
    legs.leg[leg_index].femur = -0.5 * leg_meclErr_afterPrePress.femur * cos(M_PI * i / meclErr_balance_length) + 0.5 * leg_meclErr_afterPrePress.femur + initleg.femur;
    legs.leg[leg_index].tibia = -0.5 * leg_meclErr_afterPrePress.tibia * cos(M_PI * i / meclErr_balance_length) + 0.5 * leg_meclErr_afterPrePress.tibia + initleg.tibia;
    legs.leg[leg_index].tarsus = -0.5 * leg_meclErr_afterPrePress.tarsus * cos(M_PI * i / meclErr_balance_length) + 0.5 * leg_meclErr_afterPrePress.tarsus + initleg.tarsus;
    rawJointStatesStore(legs); //将角度缓存至posBuffer
  }
  publishPosBuffer();

  ROS_INFO("Mechanical balance for completely prepress...");
}


//将角度存至posBuffer缓存
void Control::rawJointStatesStore(const hexapod_msgs::LegsJoints &legs)
{
  for (int leg_index = 0; leg_index < 6; leg_index++)
  {
    posBuffer[leg_index * 4].push_back(legs.leg[leg_index].coxa);
    posBuffer[leg_index * 4 + 1].push_back(legs.leg[leg_index].femur);
    posBuffer[leg_index * 4 + 2].push_back(legs.leg[leg_index].tibia);
    posBuffer[leg_index * 4 + 3].push_back(legs.leg[leg_index].tarsus);
  }
}

void Control::prePress_backward(const int leg_index, double prePress, const int cycle_length, hexapod_msgs::LegsJoints &legs)
{
  if (posBuffer[0].size() != 0) //清空缓存
  {
    for (int i = 0; i < 24; i++)
    {
      posBuffer[i].clear();
    }
  }

  hexapod_msgs::LegJoints initLeg; //缓存初始关节角

  initLeg.coxa = legs.leg[leg_index].coxa;
  initLeg.femur = legs.leg[leg_index].femur;
  initLeg.tibia = legs.leg[leg_index].tibia;
  initLeg.tarsus = legs.leg[leg_index].tarsus;

  for (int cycle_period = 0; cycle_period <= cycle_length; cycle_period++)
  {
    double interFuncX = 0.5 * cos(M_PI * cycle_period / cycle_length) - 0.5;
    double foot2foot_x = prePress * interFuncX;

    double foot2foot_y = 0;

    double A = FEMUR_LENGTH * sin(initLeg.tibia + initLeg.tarsus) + TIBIA_LENGTH * cos(initLeg.tarsus) + foot2foot_x;
    double B = FEMUR_LENGTH * cos(initLeg.tibia + initLeg.tarsus) - TIBIA_LENGTH * sin(initLeg.tarsus) + foot2foot_y;
    double C = FEMUR_LENGTH;
    double D = TIBIA_LENGTH;

    double temp = 4.0 * pow(C, 2) * pow(D, 2) - pow((A * A + B * B - C * C - D * D), 2);
    temp = temp > 0 ? temp : 0;

    double x = 2.0 * atan(
                         (2.0 * A * C - sqrt(temp)) /
                         (A * A + pow((B + C), 2) - D * D));

    double y = 2.0 * atan(
                         (-2.0 * B * D + sqrt(temp)) /
                         (pow((A + D), 2) + B * B - C * C));

    legs.leg[leg_index].coxa = initLeg.coxa;
    legs.leg[leg_index].femur = initLeg.femur + initLeg.tarsus + initLeg.tibia - x;
    legs.leg[leg_index].tibia = x - y;
    legs.leg[leg_index].tarsus = y;

    rawJointStatesStore(legs);
  }
  publishPosBuffer();
}

//将预压角度发布gazebo话题或填充六足服务器buffer
void Control::publishWalkGaitPrePressPos(const std::vector<int> &cycle_leg_number, const int leg_index)
{
#if !MACHINE
  for (int i = 0; i < posBuffer[0].size(); i++)
  {
    for (int leg = 0; leg < 6; leg++)
    {
      leg_roll[leg].data = posBuffer[leg * 4][i];
      leg_pitch1[leg].data = posBuffer[leg * 4 + 1][i];
      leg_pitch2[leg].data = posBuffer[leg * 4 + 2][i];
      leg_pitch3[leg].data = posBuffer[leg * 4 + 3][i];
    }

    for (int leg = 0; leg < 6; leg++)
    {
      leg_roll_p[leg].publish(leg_roll[leg]);
      leg_pitch1_p[leg].publish(leg_pitch1[leg]);
      leg_pitch2_p[leg].publish(leg_pitch2[leg]);
      leg_pitch3_p[leg].publish(leg_pitch3[leg]);
    }

    ros::Duration(0.005).sleep();
  }
#endif

  if (walkGaitPrePressFeedDrviers(cycle_leg_number, leg_index) != true)
    ros::shutdown();
}

//将posBuffer中的预压角度发至六足服务器
//三条腿依次预压，吸盘依次吸气
bool Control::walkGaitPrePressFeedDrviers(const std::vector<int> &cycle_leg_number, const int leg_index)
{
  ROS_INFO("-----Prepress-----");

#if MACHINE
  maxpointsRequest(); //请求maxpoints，确认freeSpace/motionActive

  while (freeSpace_ < (sm_point_buf_size - 30)) //sm服务器buffer接近空时，进行吸盘控制
  {
    ros::Duration(2).sleep();
    maxpointsRequest();
  }

  if (!motionActive_)
  {
    ROS_FATAL("Motion not active!");
    ros::shutdown();
    return false;
  }
#endif

#if STICK
  stick_srv_.request.chose = 2;
  int requestIO[7];
  for (int i = 0; i < 7; i++)
  {
    requestIO[i] = io[i]; //读取当前的io口
  }
  requestIO[leg_index] = 0; //将相应预压后的腿io口置0，吸盘吸气
  for (int i = 0; i < 6; i++)
  {
    stick_srv_.request.io[i] = requestIO[i];
  }
  stick_srv_.request.io[6] = requestIO[6] = 1;

  while (!stick_client_.call(stick_srv_))
  {
    ROS_WARN("Failed to call stick service. Retrying...");
    ros::Duration(2).sleep();
  }
#endif

#if MACHINE
  if (posBufferLegControlHalf() != true) //发送前半个周期给服务器
    return false;

  if (!motionActive_)
  {
    ROS_FATAL("Motion not active!");
    ros::shutdown();
    return false;
  }
#endif

#if STICK
  ros::Duration(5.0).sleep(); //确保气压从80以上降到80以下再回升
  //查看吸盘是否吸气完成
  while (!isStickDone(requestIO))
  {
    ros::Duration(3).sleep();
  }
  ROS_INFO("Prepress finished. ");
#endif

#if MACHINE
  if (posBufferLegControlRest() != true) //发送后半个周期给服务器
    return false;
#endif

  return true;
}

//将预压角度的前半个周期发至六足服务器
//取的是posBuffer缓存的角度
bool Control::posBufferLegControlHalf()
{
  leg_goal_.MODE = ALLLEGS_CONTROL;
  leg_goal_.MAXPOINTS = 0.5 * posBuffer[0].size();
  ROS_INFO("half maxpoints: %d", leg_goal_.MAXPOINTS);

  for (int i = 0; i < 6; i++)
  {
    leg_goal_.ALLLEGS.leg[i].coxa.resize(leg_goal_.MAXPOINTS);
    leg_goal_.ALLLEGS.leg[i].femur.resize(leg_goal_.MAXPOINTS);
    leg_goal_.ALLLEGS.leg[i].tibia.resize(leg_goal_.MAXPOINTS);
    leg_goal_.ALLLEGS.leg[i].tarsus.resize(leg_goal_.MAXPOINTS);
  }

  for (int i = 0; i < leg_goal_.MAXPOINTS; i++)
  {
    for (int leg_index = 0; leg_index < 6; leg_index++)
    {
      leg_goal_.ALLLEGS.leg[leg_index].coxa[i] = round(4096.0 * (3005640.0 / 1300.0) * (posBuffer[leg_index * 4][i] / M_PI * 180.0) / 360.0);
      leg_goal_.ALLLEGS.leg[leg_index].femur[i] = round(4096.0 * (3005640.0 / 1300.0) * (-posBuffer[leg_index * 4 + 1][i] / M_PI * 180.0) / 360.0);
      leg_goal_.ALLLEGS.leg[leg_index].tibia[i] = round(4096.0 * (3005640.0 / 1300.0) * (-posBuffer[leg_index * 4 + 2][i] / M_PI * 180.0) / 360.0);
      leg_goal_.ALLLEGS.leg[leg_index].tarsus[i] = round(4096.0 * (3005640.0 / 1300.0) * (-posBuffer[leg_index * 4 + 3][i] / M_PI * 180.0) / 360.0);
    }
  }

  bool server_exists = hexapod_client_.waitForServer(ros::Duration(5.0));
  while (!server_exists)
  {
    ROS_WARN("could not connect to server, retrying...");
    server_exists = hexapod_client_.waitForServer(ros::Duration(5.0));
  }

  hexapod_client_.sendGoal(leg_goal_, boost::bind(&Control::legcontrol_doneCb, this, _1, _2));

  bool finished = hexapod_client_.waitForResult(ros::Duration(5.0));
  /*if (!finished)
  {
    ROS_WARN("Waiting for result...");
    finished = hexapodClient.waitForResult(ros::Duration(5.0));
    if (!finished)
    {
      ROS_FATAL("Connecting failed.");
      ros::shutdown();
      return false;
    }
  }*/
  while (!finished)
  {
    ROS_WARN("Waiting for result...");
    finished = hexapod_client_.waitForResult(ros::Duration(5.0));
  }
  return true;
}

//将预压角度的后半个周期发至六足服务器
//取的是posBuffer缓存的角度
bool Control::posBufferLegControlRest()
{
  leg_goal_.MODE = ALLLEGS_CONTROL;
  leg_goal_.MAXPOINTS = posBuffer[0].size() - (int)(posBuffer[0].size() * 0.5);
  ROS_INFO("rest maxpoints: %d", leg_goal_.MAXPOINTS);

  for (int i = 0; i < 6; i++)
  {
    leg_goal_.ALLLEGS.leg[i].coxa.resize(leg_goal_.MAXPOINTS);
    leg_goal_.ALLLEGS.leg[i].femur.resize(leg_goal_.MAXPOINTS);
    leg_goal_.ALLLEGS.leg[i].tibia.resize(leg_goal_.MAXPOINTS);
    leg_goal_.ALLLEGS.leg[i].tarsus.resize(leg_goal_.MAXPOINTS);
  }

  for (int cnt = 0.5 * posBuffer[0].size(), i = 0; cnt < posBuffer[0].size(); cnt++, i++)
  {
    for (int leg_index = 0; leg_index < 6; leg_index++)
    {
      leg_goal_.ALLLEGS.leg[leg_index].coxa[i] = round(4096.0 * (3005640.0 / 1300.0) * (posBuffer[leg_index * 4][cnt] / M_PI * 180.0) / 360.0);
      leg_goal_.ALLLEGS.leg[leg_index].femur[i] = round(4096.0 * (3005640.0 / 1300.0) * (-posBuffer[leg_index * 4 + 1][cnt] / M_PI * 180.0) / 360.0);
      leg_goal_.ALLLEGS.leg[leg_index].tibia[i] = round(4096.0 * (3005640.0 / 1300.0) * (-posBuffer[leg_index * 4 + 2][cnt] / M_PI * 180.0) / 360.0);
      leg_goal_.ALLLEGS.leg[leg_index].tarsus[i] = round(4096.0 * (3005640.0 / 1300.0) * (-posBuffer[leg_index * 4 + 3][cnt] / M_PI * 180.0) / 360.0);
    }
  }

  bool server_exists = hexapod_client_.waitForServer(ros::Duration(5.0));
  while (!server_exists)
  {
    ROS_WARN("could not connect to server, retrying...");
    server_exists = hexapod_client_.waitForServer(ros::Duration(5.0));
  }

  hexapod_client_.sendGoal(leg_goal_, boost::bind(&Control::legcontrol_doneCb, this, _1, _2));

  bool finished = hexapod_client_.waitForResult(ros::Duration(5.0));
  /*if (!finished)
  {
    ROS_WARN("Waiting for result...");
    finished = hexapodClient.waitForResult(ros::Duration(5.0));
    if (!finished)
    {
      ROS_FATAL("Connecting failed.");
      ros::shutdown();
      return false;
    }
  }*/
  while (!finished)
  {
    ROS_WARN("Waiting for result...");
    finished = hexapod_client_.waitForResult(ros::Duration(5.0));
  }
  return true;
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

  /* if (freeSpace_ < feedDriver_points_)
    {
      bufferFree_ = false;
    }
    else
    {
      bufferFree_ = true;
    }*/
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
  /* if (freeSpace_ < feedDriver_points_)
    {
      bufferFree_ = false;
    }
    else
    {
      bufferFree_ = true;
    }*/
}

/*将订阅到的六足服务器角度信息发至rviz*/
void Control::sm_pos_Cb(const hexapodservice::legConstPtr &leg)
{
  joint_states.header.stamp = ros::Time::now();
  int i = 0;
  joint_states.name.resize(30);
  joint_states.position.resize(30);
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

/*平面调整位姿*/
void Control::legAdjustOnGround(const int MODE, const int leg_index, const geometry_msgs::Point &initPos, const geometry_msgs::Point &finalPos, const double liftHeight, const int cycle_length, hexapod_msgs::LegsJoints &legs)
{

  geometry_msgs::Point pos;
  double i = 0.0;

  for (int i = 0; i < 24; i++)
  {
    posBuffer[i].clear(); //清空缓存
  }

  /*//1、3、4、6腿摆动分别对应hex2crabMeclErrBalnRate中的4步
  int modeTransmStep;
  if (leg_index == 0)
    modeTransmStep = 0;
  if (leg_index == 2)
    modeTransmStep = 1;
  if (leg_index == 3)
    modeTransmStep = 2;
  if (leg_index == 5)
    modeTransmStep = 3;*/

  while (i <= cycle_length)
  {
    interpolationOnGround(initPos, finalPos, liftHeight, i, cycle_length, pos); //插值
    jointCalculate(leg_index, pos, 0, legs.leg[leg_index]);                     //角度计算
    //存入缓存
    for (int leg = 0; leg < 6; leg++)
    {
      switch (MODE)
      {
      case HEX2CRAB: //hex2crab在posBuffer中加入误差补偿
      {
        posBuffer[leg * 4].push_back(legs.leg[leg].coxa + double(i) / double(cycle_length) * MeclErrUnit * MeclErr[leg * 4] * hex2crabMeclErrBalnRate[leg_index][leg * 4]);
        posBuffer[leg * 4 + 1].push_back(legs.leg[leg].femur + double(i) / double(cycle_length) * MeclErrUnit * MeclErr[leg * 4 + 1] * hex2crabMeclErrBalnRate[leg_index][leg * 4 + 1]);
        posBuffer[leg * 4 + 2].push_back(legs.leg[leg].tibia + double(i) / double(cycle_length) * MeclErrUnit * MeclErr[leg * 4 + 2] * hex2crabMeclErrBalnRate[leg_index][leg * 4 + 2]);
        posBuffer[leg * 4 + 3].push_back(legs.leg[leg].tarsus + double(i) / double(cycle_length) * MeclErrUnit * MeclErr[leg * 4 + 3] * hex2crabMeclErrBalnRate[leg_index][leg * 4 + 3]);
      }
      break;
      case CRAB2HEX: //crab2hex在posBuffer中加入误差补偿
      {
        posBuffer[leg * 4].push_back(legs.leg[leg].coxa + double(i) / double(cycle_length) * MeclErrUnit * MeclErr[leg * 4] * crab2hexMeclErrBalnRate[leg_index][leg * 4]);
        posBuffer[leg * 4 + 1].push_back(legs.leg[leg].femur + double(i) / double(cycle_length) * MeclErrUnit * MeclErr[leg * 4 + 1] * crab2hexMeclErrBalnRate[leg_index][leg * 4 + 1]);
        posBuffer[leg * 4 + 2].push_back(legs.leg[leg].tibia + double(i) / double(cycle_length) * MeclErrUnit * MeclErr[leg * 4 + 2] * crab2hexMeclErrBalnRate[leg_index][leg * 4 + 2]);
        posBuffer[leg * 4 + 3].push_back(legs.leg[leg].tarsus + double(i) / double(cycle_length) * MeclErrUnit * MeclErr[leg * 4 + 3] * crab2hexMeclErrBalnRate[leg_index][leg * 4 + 3]);
      }
      break;
      }
    }
    if (i <= 1.0 / 3.0 * cycle_length || i >= 2.0 / 3.0 * cycle_length)
      i += 2.0;
    else
      i++;
  }
  publishTransformJointStates(leg_index);

  hexapod_msgs::LegsJoints legs_before_prePress; //缓存预压前的角度
  for (int index = 0; index < 6; index++)
  {
    legs_before_prePress.leg[index].coxa = legs.leg[index].coxa;
    legs_before_prePress.leg[index].femur = legs.leg[index].femur;
    legs_before_prePress.leg[index].tibia = legs.leg[index].tibia;
    legs_before_prePress.leg[index].tarsus = legs.leg[index].tarsus;
  }

  modeTransmPrePress(MODE, leg_index, PREPRESS, PREPRESS_CYCLE_LENGTH, legs); //预压

  hexapod_msgs::LegsJoints legs_meclErrBaln; //总的角度误差补偿值
  switch (MODE)
  {
  case HEX2CRAB:
  {
    for (int index = 0; index < 6; index++)
    {
      legs_meclErrBaln.leg[index].coxa = legs.leg[index].coxa - legs_before_prePress.leg[index].coxa;
      legs_meclErrBaln.leg[index].femur = legs.leg[index].femur - legs_before_prePress.leg[index].femur;
      legs_meclErrBaln.leg[index].tibia = legs.leg[index].tibia - legs_before_prePress.leg[index].tibia;
      legs_meclErrBaln.leg[index].tarsus = legs.leg[index].tarsus - legs_before_prePress.leg[index].tarsus;
    }
  }
  break;
  case CRAB2HEX:
  {
    for (int index = 0; index < 6; index++)
    {
      legs_meclErrBaln.leg[index].coxa = legs.leg[index].coxa - legs_before_prePress.leg[index].coxa;
      legs_meclErrBaln.leg[index].femur = legs.leg[index].femur - legs_before_prePress.leg[index].femur;
      legs_meclErrBaln.leg[index].tibia = legs.leg[index].tibia - legs_before_prePress.leg[index].tibia;
      legs_meclErrBaln.leg[index].tarsus = legs.leg[index].tarsus - legs_before_prePress.leg[index].tarsus;
    }
  }
  break;
  }

  /***********************误差恢复*************************************/
  for (int i = 0; i < 24; i++)
  {
    posBuffer[i].clear(); //清空缓存
  }
  // 缓存恢复后的角度
  hexapod_msgs::LegsJoints initlegs;
  for (int index = 0; index < 6; index++)
  {
    initlegs.leg[index].coxa = legs.leg[index].coxa - legs_meclErrBaln.leg[index].coxa;
    initlegs.leg[index].femur = legs.leg[index].femur - legs_meclErrBaln.leg[index].femur;
    initlegs.leg[index].tibia = legs.leg[index].tibia - legs_meclErrBaln.leg[index].tibia;
    initlegs.leg[index].tarsus = legs.leg[index].tarsus - legs_meclErrBaln.leg[index].tarsus;
  }

  //用三角函数将角度从加入机械误差后的角度恢复至原始角度
  for (int i = 0; i <= meclRecoverLength; i++)
  {
    for (int index = 0; index < 6; index++)
    {
      legs.leg[index].coxa = 0.5 * legs_meclErrBaln.leg[index].coxa * cos(M_PI * i / meclRecoverLength) + initlegs.leg[index].coxa + 0.5 * legs_meclErrBaln.leg[index].coxa;

      legs.leg[index].femur = 0.5 * legs_meclErrBaln.leg[index].femur * cos(M_PI * i / meclRecoverLength) + initlegs.leg[index].femur + 0.5 * legs_meclErrBaln.leg[index].femur;

      legs.leg[index].tibia = 0.5 * legs_meclErrBaln.leg[index].tibia * cos(M_PI * i / meclRecoverLength) + initlegs.leg[index].tibia + 0.5 * legs_meclErrBaln.leg[index].tibia;

      legs.leg[index].tarsus = 0.5 * legs_meclErrBaln.leg[index].tarsus * cos(M_PI * i / meclRecoverLength) + initlegs.leg[index].tarsus + 0.5 * legs_meclErrBaln.leg[index].tarsus;
    }
    //将角度值填充进posBuffer缓存
    for (int leg = 0; leg < 6; leg++)
    {
      posBuffer[leg * 4].push_back(legs.leg[leg].coxa);
      posBuffer[leg * 4 + 1].push_back(legs.leg[leg].femur);
      posBuffer[leg * 4 + 2].push_back(legs.leg[leg].tibia);
      posBuffer[leg * 4 + 3].push_back(legs.leg[leg].tarsus);
    }
  }
#if MACHINE
  maxpointsRequest(); //请求maxpoints，确认motionActive/freeSpace

  //status不为1或者abortMotion时，关闭算法节点
  if (motionActive_ == false)
  {
    ros::shutdown();
    return;
  }

  while (freeSpace_ < meclRecoverLength) //六足服务器freeSpace大于误差恢复周期时，再填充六足服务器buffer
  {
    ros::Duration(3).sleep();
    ROS_INFO("freeSpace(%d) is not enough", freeSpace_);
    maxpointsRequest();
  }
#endif

  publishMeclErrRecover(); //发布误差恢复角度控制话题或填充六足服务器buffer
}

/*******************************************************************************
*                      %从初始位姿到终止位姿插值%                                  *
*        输入：初始位姿、终止位姿、抬腿高度、cycle_period、周期长度、插值所得位姿        *
*                         输出： 插值所得位姿                                     *
********************************************************************************/
void Control::interpolationOnGround(const geometry_msgs::Point &initPos, const geometry_msgs::Point &finalPos, const double liftHeight, const double cycle_period, const int cycle_length, geometry_msgs::Point &outputPos)
{
  double sigmoid = 1.0 / (1.0 + exp(-25.0 * (float(cycle_period) / float(cycle_length) - 0.5)));
  outputPos.x = initPos.x + (finalPos.x - initPos.x) * sigmoid;
  outputPos.y = initPos.y + (finalPos.y - initPos.y) * sigmoid;
  double cosInterp = -0.5 * cos(2.0 * M_PI * cycle_period / cycle_length) + 0.5;
  outputPos.z = initPos.z + liftHeight * cosInterp;
}

/**********************************************************
*             %腿在墙上或者在地上时由位姿计算关节角%            *
*           输入： 墙或地、腿序、位姿、俯仰角、关节角度          *
*                       输出： 关节角度                      *
***********************************************************/
void Control::jointCalculate(const int leg_index, const geometry_msgs::Point &pos, const double roll_t, hexapod_msgs::LegJoints &leg)
{
  leg.coxa = atan2(pos.y - BODY_RADIUS * sin(INIT_COXA_ANGLE[leg_index]), pos.x - BODY_RADIUS * cos(INIT_COXA_ANGLE[leg_index])) - INIT_COXA_ANGLE[leg_index];

  double beta = 0.0;

  double A = pos.z + TARSUS_LENGTH * cos(beta - sign[leg_index] * roll_t);

  double B = (pos.y - BODY_RADIUS * sin(INIT_COXA_ANGLE[leg_index])) / sin(INIT_COXA_ANGLE[leg_index] + leg.coxa) - COXA_LENGTH - TARSUS_LENGTH * sin(beta - sign[leg_index] * roll_t);

  double C = FEMUR_LENGTH;

  double D = -TIBIA_LENGTH;

  double temp = 4.0 * pow(C, 2) * pow(D, 2) - pow((A * A + B * B - C * C - D * D), 2);
  temp = temp > 0 ? temp : 0;

  double x = 2.0 * atan(
                       (2.0 * A * C + sqrt(temp)) /
                       (A * A + pow((B + C), 2) - D * D));

  double y = 2.0 * atan(
                       (-2.0 * B * D - sqrt(temp)) /
                       (pow((A + D), 2) + B * B - C * C));

  leg.femur = x;
  leg.tibia = y - x;
  leg.tarsus = beta - sign[leg_index] * roll_t - y;
}

/************************************************
*          %姿态切换发布关节角度话题%                *
*                                                *
*************************************************/
void Control::publishTransformJointStates(const int leg_index)
{
  if (transformFeedDrviers(leg_index) != true)
    ros::shutdown();
}

/******************************************************
 *                 %由给定角度计算六足位姿%               *
 *                  输入： 腿序号、腿角度                 *
 *                  输出： 六足相应位姿                  *
 ******************************************************/
void Control::positionCalculate(const int leg_index, const hexapod_msgs::LegJoints &leg, geometry_msgs::Point &pos)
{
  pos.x = BODY_RADIUS * cos(INIT_COXA_ANGLE[leg_index]) +
          (COXA_LENGTH + FEMUR_LENGTH * cos(leg.femur) + TIBIA_LENGTH * sin(leg.femur + leg.tibia) + TARSUS_LENGTH * sin(leg.femur + leg.tibia + leg.tarsus)) * cos(INIT_COXA_ANGLE[leg_index] + leg.coxa);

  pos.y = BODY_RADIUS * sin(INIT_COXA_ANGLE[leg_index]) +
          (COXA_LENGTH + FEMUR_LENGTH * cos(leg.femur) + TIBIA_LENGTH * sin(leg.femur + leg.tibia) + TARSUS_LENGTH * sin(leg.femur + leg.tibia + leg.tarsus)) * sin(INIT_COXA_ANGLE[leg_index] + leg.coxa);

  pos.z = FEMUR_LENGTH * sin(leg.femur) - TIBIA_LENGTH * cos(leg.femur + leg.tibia) - TARSUS_LENGTH * cos(leg.femur + leg.tibia + leg.tarsus);
}

//姿态切换发送buffer至服务器控制函数
bool Control::transformFeedDrviers(const int leg_index)
{
#if MACHINE
  maxpointsRequest(); //请求maxpoint, 取得freeSpace

  while (freeSpace_ < (sm_point_buf_size - 30)) //sm服务器buffer接近空时，进行吸盘控制
  {
    ros::Duration(3).sleep();
    maxpointsRequest();
  }

  if (!motionActive_)
  {
    ROS_FATAL("Motion not active!");
    ros::shutdown();
    return false;
  }
#endif

#if STICK
  stickControl(leg_index); //将相应的吸盘口io置1，放气
#endif

#if !MACHINE
  for (int i = 0; i < posBuffer[0].size(); i++)
  {
    for (int leg = 0; leg < 6; leg++)
    {
      leg_roll[leg].data = posBuffer[leg * 4][i];
      leg_pitch1[leg].data = posBuffer[leg * 4 + 1][i];
      leg_pitch2[leg].data = posBuffer[leg * 4 + 2][i];
      leg_pitch3[leg].data = posBuffer[leg * 4 + 3][i];
    }
    for (int leg = 0; leg < 6; leg++)
    {
      leg_roll_p[leg].publish(leg_roll[leg]);
      leg_pitch1_p[leg].publish(leg_pitch1[leg]);
      leg_pitch2_p[leg].publish(leg_pitch2[leg]);
      leg_pitch3_p[leg].publish(leg_pitch3[leg]);
    }
    ros::Duration(0.005).sleep();
  }
#else
  if (legControl() != true) //将buffer发送至服务器
    return false;
#endif

  return true;
}

//maxpoints请求函数，以确认motionActive/freeSpace
void Control::maxpointsRequest()
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
    }
  }
}

//吸盘控制，0-5对应1-6腿的io口，对应的吸盘放气
//6代表将所有io口设为0，即所有吸盘均吸气
void Control::stickControl(const int leg_index)
{
  ROS_INFO("-----Stick Control-----");
  stick_srv_.request.chose = 2;
  int requestIO[7];

  if (leg_index == 6)
  {
    for (int i = 0; i < 6; i++)
    {
      stick_srv_.request.io[i] = 0;
      requestIO[i] = 0;
    }
  }
  else
  {
    for (int i = 0; i < 6; i++)
    {
      if (i == leg_index)
      {
        stick_srv_.request.io[i] = 1;
        requestIO[i] = 1;
      }
      else
      {
        stick_srv_.request.io[i] = 0;
        requestIO[i] = 0;
      }
    }
  }
  stick_srv_.request.io[6] = requestIO[6] = 1;

  while (!stick_client_.call(stick_srv_))
  {
    ROS_WARN("Failed to call stick service. Retrying...");
    ros::Duration(2).sleep();
  }
  ROS_INFO("%s, request io: %d, %d, %d, %d, %d, %d", stick_srv_.response.back.c_str(), requestIO[0], requestIO[1], requestIO[2], requestIO[3], requestIO[4], requestIO[5]);

  //查看吸盘是否吸放气完毕
  while (!isStickDone(requestIO))
  {
    ros::Duration(3).sleep();
  }
  ROS_INFO("The control of all sticks are finished. ");

  if (leg_index != 6)
    ros::Duration(5).sleep(); //吸盘放气等待时间

  ROS_INFO("Hexapod is ready to move.");
}

//将posBuffer中的角度发送给六足服务器buffer
bool Control::legControl()
{
  leg_goal_.MODE = ALLLEGS_CONTROL;
  leg_goal_.MAXPOINTS = posBuffer[0].size();

  for (int i = 0; i < 6; i++)
  {
    leg_goal_.ALLLEGS.leg[i].coxa.resize(leg_goal_.MAXPOINTS);
    leg_goal_.ALLLEGS.leg[i].femur.resize(leg_goal_.MAXPOINTS);
    leg_goal_.ALLLEGS.leg[i].tibia.resize(leg_goal_.MAXPOINTS);
    leg_goal_.ALLLEGS.leg[i].tarsus.resize(leg_goal_.MAXPOINTS);
  }

  for (int i = 0; i < leg_goal_.MAXPOINTS; i++)
  {
    for (int leg_index = 0; leg_index < 6; leg_index++)
    {
      leg_goal_.ALLLEGS.leg[leg_index].coxa[i] = round(4096.0 * (3005640.0 / 1300.0) * (posBuffer[leg_index * 4][i] / M_PI * 180.0) / 360.0);
      leg_goal_.ALLLEGS.leg[leg_index].femur[i] = round(4096.0 * (3005640.0 / 1300.0) * (-posBuffer[leg_index * 4 + 1][i] / M_PI * 180.0) / 360.0);
      leg_goal_.ALLLEGS.leg[leg_index].tibia[i] = round(4096.0 * (3005640.0 / 1300.0) * (-posBuffer[leg_index * 4 + 2][i] / M_PI * 180.0) / 360.0);
      leg_goal_.ALLLEGS.leg[leg_index].tarsus[i] = round(4096.0 * (3005640.0 / 1300.0) * (-posBuffer[leg_index * 4 + 3][i] / M_PI * 180.0) / 360.0);
    }
  }

  bool server_exists = hexapod_client_.waitForServer(ros::Duration(5.0));
  while (!server_exists)
  {
    ROS_WARN("could not connect to server, retrying...");
    server_exists = hexapod_client_.waitForServer(ros::Duration(5.0));
  }

  hexapod_client_.sendGoal(leg_goal_, boost::bind(&Control::legcontrol_doneCb, this, _1, _2));

  bool finished = hexapod_client_.waitForResult(ros::Duration(5.0));
  if (!finished)
  {
    ROS_WARN("Waiting for result...");
    finished = hexapod_client_.waitForResult(ros::Duration(5.0));
    if (!finished)
    {
      ROS_FATAL("Connecting failed.");
      ros::shutdown();
      return false;
    }
  }
  return true;
}

/************************************************
*               %姿态切换预压程序%                 *
*                                                *
*************************************************/
void Control::modeTransmPrePress(const int MODE, const int leg_index, double prePress, const int cycle_length, hexapod_msgs::LegsJoints &legs)
{
  hexapod_msgs::LegJoints initLeg; //缓存初始关节角

  for (int i = 0; i < 6; i++)
  {
    switch (MODE)
    {
    case HEX2CRAB:
    {
      legs.leg[i].coxa = legs.leg[i].coxa + MeclErrUnit * MeclErr[i * 4] * hex2crabMeclErrBalnRate[leg_index][i * 4];
      legs.leg[i].femur = legs.leg[i].femur + MeclErrUnit * MeclErr[i * 4 + 1] * hex2crabMeclErrBalnRate[leg_index][i * 4 + 1];
      legs.leg[i].tibia = legs.leg[i].tibia + MeclErrUnit * MeclErr[i * 4 + 2] * hex2crabMeclErrBalnRate[leg_index][i * 4 + 2];
      legs.leg[i].tarsus = legs.leg[i].tarsus + MeclErrUnit * MeclErr[i * 4 + 3] * hex2crabMeclErrBalnRate[leg_index][i * 4 + 3];
    }
    break;
    case CRAB2HEX:
    {
      legs.leg[i].coxa = legs.leg[i].coxa + MeclErrUnit * MeclErr[i * 4] * crab2hexMeclErrBalnRate[leg_index][i * 4];
      legs.leg[i].femur = legs.leg[i].femur + MeclErrUnit * MeclErr[i * 4 + 1] * crab2hexMeclErrBalnRate[leg_index][i * 4 + 1];
      legs.leg[i].tibia = legs.leg[i].tibia + MeclErrUnit * MeclErr[i * 4 + 2] * crab2hexMeclErrBalnRate[leg_index][i * 4 + 2];
      legs.leg[i].tarsus = legs.leg[i].tarsus + MeclErrUnit * MeclErr[i * 4 + 3] * crab2hexMeclErrBalnRate[leg_index][i * 4 + 3];
    }
    break;
    }
  }

#if 0
  initLeg.coxa = legs.leg[leg_index].coxa;
  initLeg.femur = legs.leg[leg_index].femur;
  initLeg.tibia = legs.leg[leg_index].tibia;
  initLeg.tarsus = legs.leg[leg_index].tarsus;

  for (int i = 0; i < 24; i++)
  {
    posBuffer[i].clear(); //清空缓存
  }

  for (int cycle_period = 0; cycle_period <= cycle_length; cycle_period++)
  {
    double interFuncX = -0.5 * cos(2.0 * M_PI * cycle_period / cycle_length) + 0.5;
    double foot2foot_x = prePress * interFuncX;

    double foot2foot_y = 0;

    double A = FEMUR_LENGTH * sin(initLeg.tibia + initLeg.tarsus) + TIBIA_LENGTH * cos(initLeg.tarsus) + foot2foot_x;
    double B = FEMUR_LENGTH * cos(initLeg.tibia + initLeg.tarsus) - TIBIA_LENGTH * sin(initLeg.tarsus) + foot2foot_y;
    double C = FEMUR_LENGTH;
    double D = TIBIA_LENGTH;

    double temp = 4.0 * pow(C, 2) * pow(D, 2) - pow((A * A + B * B - C * C - D * D), 2);
    temp = temp > 0 ? temp : 0;

    double x = 2.0 * atan(
                         (2.0 * A * C - sqrt(temp)) /
                         (A * A + pow((B + C), 2) - D * D));

    double y = 2.0 * atan(
                         (-2.0 * B * D + sqrt(temp)) /
                         (pow((A + D), 2) + B * B - C * C));

    legs.leg[leg_index].coxa = initLeg.coxa;
    legs.leg[leg_index].femur = initLeg.femur + initLeg.tarsus + initLeg.tibia - x;
    legs.leg[leg_index].tibia = x - y;
    legs.leg[leg_index].tarsus = y;

    //将预压角度存至posBuffer缓存
    for (int leg = 0; leg < 6; leg++)
    {
      posBuffer[leg * 4].push_back(legs.leg[leg].coxa);
      posBuffer[leg * 4 + 1].push_back(legs.leg[leg].femur);
      posBuffer[leg * 4 + 2].push_back(legs.leg[leg].tibia);
      posBuffer[leg * 4 + 3].push_back(legs.leg[leg].tarsus);
    }
  }
  publishModeTransmPrePressPos();
#endif

  struct ErrMode robotMeclErrMode;
  robotMeclErrMode.mode = MODE;
  meclErrBaln_beforPrepress(leg_index, prePress, legs, robotMeclErrMode);
  prePress_forward(leg_index, prePress, cycle_length / 2, legs);
  prePress_backward(leg_index, prePress, cycle_length / 2, legs);
}

//将posBuffer预压角度缓存发至gazebo话题或填充六足服务器
void Control::publishModeTransmPrePressPos()
{
#if !MACHINE
  for (int i = 0; i < posBuffer[0].size(); i++)
  {
    for (int leg = 0; leg < 6; leg++)
    {
      leg_roll[leg].data = posBuffer[leg * 4][i];
      leg_pitch1[leg].data = posBuffer[leg * 4 + 1][i];
      leg_pitch2[leg].data = posBuffer[leg * 4 + 2][i];
      leg_pitch3[leg].data = posBuffer[leg * 4 + 3][i];
    }

    for (int leg = 0; leg < 6; leg++)
    {
      leg_roll_p[leg].publish(leg_roll[leg]);
      leg_pitch1_p[leg].publish(leg_pitch1[leg]);
      leg_pitch2_p[leg].publish(leg_pitch2[leg]);
      leg_pitch3_p[leg].publish(leg_pitch3[leg]);
    }

    ros::Duration(0.005).sleep();
  }
#endif

  if (modeTransmPrePressFeedDrivers() != true)
    ros::shutdown();
}

//将posBuffer预压角度缓存填充至六足服务器
bool Control::modeTransmPrePressFeedDrivers()
{
  ROS_INFO("-----Prepress-----");

#if MACHINE
  maxpointsRequest(); //请求maxpoints，确认freeSpace/motionActive

  while (freeSpace_ < (sm_point_buf_size - 30)) //sm服务器buffer接近空时，进行吸盘控制
  {
    ros::Duration(2).sleep();
    maxpointsRequest();
  }

  if (!motionActive_)
  {
    ROS_FATAL("Motion not active!");
    ros::shutdown();
    return false;
  }
#endif

#if STICK
  //预压前发送io口控制，将所有吸盘均吸至真空
  stick_srv_.request.chose = 2;
  int requestIO[7];
  for (int i = 0; i < 6; i++)
  {
    stick_srv_.request.io[i] = 0;
    requestIO[i] = 0;
  }
  stick_srv_.request.io[6] = requestIO[6] = 1;

  while (!stick_client_.call(stick_srv_))
  {
    ROS_WARN("Failed to call stick service. Retrying...");
    ros::Duration(2).sleep();
  }
#endif

#if MACHINE
  if (posBufferLegControlHalf() != true) //发送前半个周期给服务器
    return false;

  if (!motionActive_)
  {
    ROS_FATAL("Motion not active!");
    ros::shutdown();
    return false;
  }
#endif

#if STICK
  ros::Duration(5.0).sleep(); //确保气压从80以上降到80以下再回升
  //查看吸盘是否吸气完成
  while (!isStickDone(requestIO))
  {
    ros::Duration(3).sleep();
  }
  ROS_INFO("Prepress finished. ");
#endif

#if MACHINE
  if (posBufferLegControlRest() != true) //发送后半个周期给服务器
    return false;
#endif

  return true;
}

void Control::saveMeclErrBalnRate_cb(const std_msgs::StringConstPtr &msg)
{
  ROS_INFO("Saving meclErrBalnRate...");

  HEXxPosDirnMeclErrBalnRate1st.assign(HEXxPosDirnMeclErrBalnRate1st_update.begin(), HEXxPosDirnMeclErrBalnRate1st_update.end());
  HEXxNegDirnMeclErrBalnRate1st.assign(HEXxNegDirnMeclErrBalnRate1st_update.begin(), HEXxNegDirnMeclErrBalnRate1st_update.end());
  HEXyPosDirnMeclErrBalnRate1st.assign(HEXyPosDirnMeclErrBalnRate1st_update.begin(), HEXyPosDirnMeclErrBalnRate1st_update.end());
  HEXyNegDirnMeclErrBalnRate1st.assign(HEXyNegDirnMeclErrBalnRate1st_update.begin(), HEXyNegDirnMeclErrBalnRate1st_update.end());
  HEXzPosDirnMeclErrBalnRate1st.assign(HEXzPosDirnMeclErrBalnRate1st_update.begin(), HEXzPosDirnMeclErrBalnRate1st_update.end());
  HEXzNegDirnMeclErrBalnRate1st.assign(HEXzNegDirnMeclErrBalnRate1st_update.begin(), HEXzNegDirnMeclErrBalnRate1st_update.end());

  HEXxPosDirnMeclErrBalnRate2nd.assign(HEXxPosDirnMeclErrBalnRate2nd_update.begin(), HEXxPosDirnMeclErrBalnRate2nd_update.end());
  HEXxNegDirnMeclErrBalnRate2nd.assign(HEXxNegDirnMeclErrBalnRate2nd_update.begin(), HEXxNegDirnMeclErrBalnRate2nd_update.end());
  HEXyPosDirnMeclErrBalnRate2nd.assign(HEXyPosDirnMeclErrBalnRate2nd_update.begin(), HEXyPosDirnMeclErrBalnRate2nd_update.end());
  HEXyNegDirnMeclErrBalnRate2nd.assign(HEXyNegDirnMeclErrBalnRate2nd_update.begin(), HEXyNegDirnMeclErrBalnRate2nd_update.end());
  HEXzPosDirnMeclErrBalnRate2nd.assign(HEXzPosDirnMeclErrBalnRate2nd_update.begin(), HEXzPosDirnMeclErrBalnRate2nd_update.end());
  HEXzNegDirnMeclErrBalnRate2nd.assign(HEXzNegDirnMeclErrBalnRate2nd_update.begin(), HEXzNegDirnMeclErrBalnRate2nd_update.end());

  CRABxPosDirnMeclErrBalnRate1st.assign(CRABxPosDirnMeclErrBalnRate1st_update.begin(), CRABxPosDirnMeclErrBalnRate1st_update.end());
  CRABxNegDirnMeclErrBalnRate1st.assign(CRABxNegDirnMeclErrBalnRate1st_update.begin(), CRABxNegDirnMeclErrBalnRate1st_update.end());
  CRAByPosDirnMeclErrBalnRate1st.assign(CRAByPosDirnMeclErrBalnRate1st_update.begin(), CRAByPosDirnMeclErrBalnRate1st_update.end());
  CRAByNegDirnMeclErrBalnRate1st.assign(CRAByNegDirnMeclErrBalnRate1st_update.begin(), CRAByNegDirnMeclErrBalnRate1st_update.end());
  CRABzPosDirnMeclErrBalnRate1st.assign(CRABzPosDirnMeclErrBalnRate1st_update.begin(), CRABzPosDirnMeclErrBalnRate1st_update.end());
  CRABzNegDirnMeclErrBalnRate1st.assign(CRABzNegDirnMeclErrBalnRate1st_update.begin(), CRABzNegDirnMeclErrBalnRate1st_update.end());

  CRABxPosDirnMeclErrBalnRate2nd.assign(CRABxPosDirnMeclErrBalnRate2nd_update.begin(), CRABxPosDirnMeclErrBalnRate2nd_update.end());
  CRABxNegDirnMeclErrBalnRate2nd.assign(CRABxNegDirnMeclErrBalnRate2nd_update.begin(), CRABxNegDirnMeclErrBalnRate2nd_update.end());
  CRAByPosDirnMeclErrBalnRate2nd.assign(CRAByPosDirnMeclErrBalnRate2nd_update.begin(), CRAByPosDirnMeclErrBalnRate2nd_update.end());
  CRAByNegDirnMeclErrBalnRate2nd.assign(CRAByNegDirnMeclErrBalnRate2nd_update.begin(), CRAByNegDirnMeclErrBalnRate2nd_update.end());
  CRABzPosDirnMeclErrBalnRate2nd.assign(CRABzPosDirnMeclErrBalnRate2nd_update.begin(), CRABzPosDirnMeclErrBalnRate2nd_update.end());
  CRABzNegDirnMeclErrBalnRate2nd.assign(CRABzNegDirnMeclErrBalnRate2nd_update.begin(), CRABzNegDirnMeclErrBalnRate2nd_update.end());

  for (int i = 0; i < hex2crabMeclErrBalnRate.size(); i++)
  {
    hex2crabMeclErrBalnRate[i].assign(hex2crabMeclErrBalnRate_update[i].begin(), hex2crabMeclErrBalnRate_update[i].end());
  }

  for (int i = 0; i < crab2hexMeclErrBalnRate.size(); i++)
  {
    crab2hexMeclErrBalnRate[i].assign(crab2hexMeclErrBalnRate_update[i].begin(), crab2hexMeclErrBalnRate_update[i].end());
  }

  std::ofstream meclErrBalnRateText;
  time_t tt;
  time(&tt);
  tt = tt + 8 * 3600; // transform the time zone
  tm *t = gmtime(&tt);
  std::string filename;
  filename = "/home/v5lab/hexapod_service_ws/src/hexapod_wall_control/params/meclErrBalnRate/meclErrBalnRate";
  filename += std::to_string(t->tm_year + 1900);
  filename += std::to_string(t->tm_mon + 1);
  filename += std::to_string(t->tm_mday);
  filename += std::to_string(t->tm_hour);
  filename += std::to_string(t->tm_min);
  filename += ".yaml";
  meclErrBalnRateText.open(filename);

  meclErrBalnRateText << msg->data << std::endl;

  /*#六足蜘蛛形态沿X，Y，Z正负方向运动时的差补比重，注意不同姿态下的补偿方向(正负号)百分比*/
  meclErrBalnRateText << "#六足蜘蛛形态沿X，Y，Z正负方向运动时的差补比重，注意不同姿态下的补偿方向(正负号)百分比" << std::endl;
  meclErrBalnRateText << "HEX_X_POS_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_1st_STEP: [";
  for (int i = 0; i < 24; i++)
  {
    meclErrBalnRateText << HEXxPosDirnMeclErrBalnRate1st[i] << ",";
  }
  meclErrBalnRateText << "]" << std::endl;
  meclErrBalnRateText << "HEX_X_NEG_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_1st_STEP: [";
  for (int i = 0; i < 24; i++)
  {
    meclErrBalnRateText << HEXxNegDirnMeclErrBalnRate1st[i] << ",";
  }
  meclErrBalnRateText << "]" << std::endl;
  meclErrBalnRateText << "HEX_Y_POS_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_1st_STEP: [";
  for (int i = 0; i < 24; i++)
  {
    meclErrBalnRateText << HEXyPosDirnMeclErrBalnRate1st[i] << ",";
  }
  meclErrBalnRateText << "]" << std::endl;
  meclErrBalnRateText << "HEX_Y_NEG_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_1st_STEP: [";
  for (int i = 0; i < 24; i++)
  {
    meclErrBalnRateText << HEXyNegDirnMeclErrBalnRate1st[i] << ",";
  }
  meclErrBalnRateText << "]" << std::endl;
  meclErrBalnRateText << "HEX_Z_POS_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_1st_STEP: [";
  for (int i = 0; i < 24; i++)
  {
    meclErrBalnRateText << HEXzPosDirnMeclErrBalnRate1st[i] << ",";
  }
  meclErrBalnRateText << "]" << std::endl;
  meclErrBalnRateText << "HEX_Z_NEG_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_1st_STEP: [";
  for (int i = 0; i < 24; i++)
  {
    meclErrBalnRateText << HEXzNegDirnMeclErrBalnRate1st[i] << ",";
  }
  meclErrBalnRateText << "]" << std::endl;

  meclErrBalnRateText << "HEX_X_POS_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_2nd_STEP: [";
  for (int i = 0; i < 24; i++)
  {
    meclErrBalnRateText << HEXxPosDirnMeclErrBalnRate2nd[i] << ",";
  }
  meclErrBalnRateText << "]" << std::endl;
  meclErrBalnRateText << "HEX_X_NEG_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_2nd_STEP: [";
  for (int i = 0; i < 24; i++)
  {
    meclErrBalnRateText << HEXxNegDirnMeclErrBalnRate2nd[i] << ",";
  }
  meclErrBalnRateText << "]" << std::endl;
  meclErrBalnRateText << "HEX_Y_POS_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_2nd_STEP: [";
  for (int i = 0; i < 24; i++)
  {
    meclErrBalnRateText << HEXyPosDirnMeclErrBalnRate2nd[i] << ",";
  }
  meclErrBalnRateText << "]" << std::endl;
  meclErrBalnRateText << "HEX_Y_NEG_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_2nd_STEP: [";
  for (int i = 0; i < 24; i++)
  {
    meclErrBalnRateText << HEXyNegDirnMeclErrBalnRate2nd[i] << ",";
  }
  meclErrBalnRateText << "]" << std::endl;
  meclErrBalnRateText << "HEX_Z_POS_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_2nd_STEP: [";
  for (int i = 0; i < 24; i++)
  {
    meclErrBalnRateText << HEXzPosDirnMeclErrBalnRate2nd[i] << ",";
  }
  meclErrBalnRateText << "]" << std::endl;
  meclErrBalnRateText << "HEX_Z_NEG_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_2nd_STEP: [";
  for (int i = 0; i < 24; i++)
  {
    meclErrBalnRateText << HEXzNegDirnMeclErrBalnRate2nd[i] << ",";
  }
  meclErrBalnRateText << "]" << std::endl;

  /*#六足螃蟹形态沿X，Y，Z正负方向运动时的差补比重，注意不同姿态下的补偿方向(正负号)百分比*/
  meclErrBalnRateText << "#六足螃蟹形态沿X，Y，Z正负方向运动时的差补比重，注意不同姿态下的补偿方向(正负号)百分比" << std::endl;
  meclErrBalnRateText << "CRAB_X_POS_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_1st_STEP: [";
  for (int i = 0; i < 24; i++)
  {
    meclErrBalnRateText << CRABxPosDirnMeclErrBalnRate1st[i] << ",";
  }
  meclErrBalnRateText << "]" << std::endl;
  meclErrBalnRateText << "CRAB_X_NEG_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_1st_STEP: [";
  for (int i = 0; i < 24; i++)
  {
    meclErrBalnRateText << CRABxNegDirnMeclErrBalnRate1st[i] << ",";
  }
  meclErrBalnRateText << "]" << std::endl;
  meclErrBalnRateText << "CRAB_Y_POS_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_1st_STEP: [";
  for (int i = 0; i < 24; i++)
  {
    meclErrBalnRateText << CRAByPosDirnMeclErrBalnRate1st[i] << ",";
  }
  meclErrBalnRateText << "]" << std::endl;
  meclErrBalnRateText << "CRAB_Y_NEG_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_1st_STEP: [";
  for (int i = 0; i < 24; i++)
  {
    meclErrBalnRateText << CRAByNegDirnMeclErrBalnRate1st[i] << ",";
  }
  meclErrBalnRateText << "]" << std::endl;
  meclErrBalnRateText << "CRAB_Z_POS_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_1st_STEP: [";
  for (int i = 0; i < 24; i++)
  {
    meclErrBalnRateText << CRABzPosDirnMeclErrBalnRate1st[i] << ",";
  }
  meclErrBalnRateText << "]" << std::endl;
  meclErrBalnRateText << "CRAB_Z_NEG_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_1st_STEP: [";
  for (int i = 0; i < 24; i++)
  {
    meclErrBalnRateText << CRABzNegDirnMeclErrBalnRate1st[i] << ",";
  }
  meclErrBalnRateText << "]" << std::endl;

  meclErrBalnRateText << "CRAB_X_POS_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_2nd_STEP: [";
  for (int i = 0; i < 24; i++)
  {
    meclErrBalnRateText << CRABxPosDirnMeclErrBalnRate2nd[i] << ",";
  }
  meclErrBalnRateText << "]" << std::endl;
  meclErrBalnRateText << "CRAB_X_NEG_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_2nd_STEP: [";
  for (int i = 0; i < 24; i++)
  {
    meclErrBalnRateText << CRABxNegDirnMeclErrBalnRate2nd[i] << ",";
  }
  meclErrBalnRateText << "]" << std::endl;
  meclErrBalnRateText << "CRAB_Y_POS_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_2nd_STEP: [";
  for (int i = 0; i < 24; i++)
  {
    meclErrBalnRateText << CRAByPosDirnMeclErrBalnRate2nd[i] << ",";
  }
  meclErrBalnRateText << "]" << std::endl;
  meclErrBalnRateText << "CRAB_Y_NEG_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_2nd_STEP: [";
  for (int i = 0; i < 24; i++)
  {
    meclErrBalnRateText << CRAByNegDirnMeclErrBalnRate2nd[i] << ",";
  }
  meclErrBalnRateText << "]" << std::endl;
  meclErrBalnRateText << "CRAB_Z_POS_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_2nd_STEP: [";
  for (int i = 0; i < 24; i++)
  {
    meclErrBalnRateText << CRABzPosDirnMeclErrBalnRate2nd[i] << ",";
  }
  meclErrBalnRateText << "]" << std::endl;
  meclErrBalnRateText << "CRAB_Z_NEG_DIRECTION_MECHANICAL_ERROR_BALANCE_RATE_2nd_STEP: [";
  for (int i = 0; i < 24; i++)
  {
    meclErrBalnRateText << CRABzNegDirnMeclErrBalnRate2nd[i] << ",";
  }
  meclErrBalnRateText << "]" << std::endl;

  /*#六足切换姿态（蜘蛛和螃蟹）的差补比重，注意不同姿态下的补偿方向(正负号)百分比*/
  meclErrBalnRateText << "#六足切换姿态（蜘蛛和螃蟹）的差补比重，注意不同姿态下的补偿方向(正负号)百分比" << std::endl;
  meclErrBalnRateText << "#hexapod2crab" << std::endl;
  for (int i = 0; i < 6; i++)
  {
    meclErrBalnRateText << "HEXAPOD_TO_CRAB_LEG" << i + 1 << "MOVE_MECHANICAL_ERROR_BALANCE_RATE: [";
    for (int j = 0; j < 24; j++)
    {
      meclErrBalnRateText << hex2crabMeclErrBalnRate[i][j] << ",";
    }
    meclErrBalnRateText << "]" << std::endl;
  }

  meclErrBalnRateText << "#crab2hexapod" << std::endl;
  for (int i = 0; i < 6; i++)
  {
    meclErrBalnRateText << "CRAB_TO_HEXAPOD_LEG" << i + 1 << "MOVE_MECHANICAL_ERROR_BALANCE_RATE: [";
    for (int j = 0; j < 24; j++)
    {
      meclErrBalnRateText << crab2hexMeclErrBalnRate[i][j] << ",";
    }
    meclErrBalnRateText << "]" << std::endl;
  }

  meclErrBalnRateText.close();

  ROS_INFO("Mechanical error balance rate have been saved to %s", filename.c_str());
}


//预压前的角度误差补偿
void Control::meclErrBaln_beforPrepress(const int leg_index, double &prePress, hexapod_msgs::LegsJoints &legs, const struct ErrMode robotMeclErrMode)
{
  //预压前确定角度补偿
  prePress_confirm_flag = false;
  ROS_INFO("Please publish '/hexapod_confirm_prePress' topic to confirm prePress.");
  ROS_INFO("leg_index: %d", leg_index);
  ROS_INFO("Before prePress confirm, you can publish '/hexapod_meclErr_balance' topic to correct the mechanical error");
  leg_meclErr_flag = false;
  leg_meclErr_balance.coxa = leg_meclErr_balance.femur = leg_meclErr_balance.tibia = leg_meclErr_balance.tarsus = 0.0;
  while (prePress_confirm_flag == false) //没有发布预压确定话题时，进入循环检查是否需要进行角度补偿
  {
    if (leg_meclErr_flag == true) //当收到角度补偿话题时，进行角度补偿
    {
      meclErr_balance(leg_index, legs, robotMeclErrMode);
      leg_meclErr_flag = false;
    }
  }
  prePress = prePress_confirm;
  ROS_INFO("Ready to prepress. Prepress length: %fm", prePress);
}

void Control::leg_prePress_confirm_cb(const std_msgs::Float64ConstPtr &prePress_confirm_msg)
{
  if (leg_meclErr_flag == true)
    return;

  if (prePress_confirm_msg->data < 0 || prePress_confirm_msg->data > 0.05)
  {
    ROS_WARN("Incorrect request for prepress length. Out of range(0~0.05m)!");
    return;
  }

  prePress_confirm_flag = true;
  prePress_confirm = prePress_confirm_msg->data;
}


//处理预压前的角度误差补偿
void Control::meclErr_balance(const int leg_index, hexapod_msgs::LegsJoints &legs, const struct ErrMode robotMeclErrMode)
{
  ROS_INFO("meclErr_balance");
  ROS_INFO("Correcting mechanical error...");
  ROS_INFO("coxa: %f, femur: %f°, tibia: %f°, tarsus: %f°", leg_meclErr_balance.coxa, leg_meclErr_balance.femur, leg_meclErr_balance.tibia, leg_meclErr_balance.tarsus);

  //缓存初始角度
  hexapod_msgs::LegJoints initleg;
  initleg.coxa = legs.leg[leg_index].coxa;
  initleg.femur = legs.leg[leg_index].femur;
  initleg.tibia = legs.leg[leg_index].tibia;
  initleg.tarsus = legs.leg[leg_index].tarsus;

  //清空posbuffer缓存
  if (posBuffer[0].size() != 0)
  {
    for (int i = 0; i < 24; i++)
    {
      posBuffer[i].clear();
    }
  }

  //用三角函数处理角度补偿
  for (int i = 0; i < meclErr_balance_length; i++)
  {
    legs.leg[leg_index].coxa = -0.5 * leg_meclErr_balance.coxa * cos(M_PI * i / meclErr_balance_length) + 0.5 * leg_meclErr_balance.coxa + initleg.coxa;
    legs.leg[leg_index].femur = -0.5 * leg_meclErr_balance.femur * cos(M_PI * i / meclErr_balance_length) + 0.5 * leg_meclErr_balance.femur + initleg.femur;
    legs.leg[leg_index].tibia = -0.5 * leg_meclErr_balance.tibia * cos(M_PI * i / meclErr_balance_length) + 0.5 * leg_meclErr_balance.tibia + initleg.tibia;
    legs.leg[leg_index].tarsus = -0.5 * leg_meclErr_balance.tarsus * cos(M_PI * i / meclErr_balance_length) + 0.5 * leg_meclErr_balance.tarsus + initleg.tarsus;
    //将角度缓存至posBuffer
    for (int leg_index = 0; leg_index < 6; leg_index++)
    {
      posBuffer[leg_index * 4].push_back(legs.leg[leg_index].coxa);
      posBuffer[leg_index * 4 + 1].push_back(legs.leg[leg_index].femur);
      posBuffer[leg_index * 4 + 2].push_back(legs.leg[leg_index].tibia);
      posBuffer[leg_index * 4 + 3].push_back(legs.leg[leg_index].tarsus);
    }
  }
  publishPosBuffer();  //发布角度信息

  //将此次补偿的角度误差更新至update表
  switch (robotMeclErrMode.mode)
  {
  case hexapod_mode:
  {
    switch (robotMeclErrMode.gaitCnt)
    {
    case 0:
    {
      if (robotMeclErrMode.dirn == "xp")
      {
        HEXxPosDirnMeclErrBalnRate1st_update[leg_index * 4] += (leg_meclErr_balance.coxa / MeclErrUnit / MeclErr[leg_index * 4]);
        HEXxPosDirnMeclErrBalnRate1st_update[leg_index * 4 + 1] += (leg_meclErr_balance.femur / MeclErrUnit / MeclErr[leg_index * 4 + 1]);
        HEXxPosDirnMeclErrBalnRate1st_update[leg_index * 4 + 2] += (leg_meclErr_balance.tibia / MeclErrUnit / MeclErr[leg_index * 4 + 2]);
        HEXxPosDirnMeclErrBalnRate1st_update[leg_index * 4 + 3] += (leg_meclErr_balance.tarsus / MeclErrUnit / MeclErr[leg_index * 4 + 3]);
      }
      else if (robotMeclErrMode.dirn == "xn")
      {
        HEXxNegDirnMeclErrBalnRate1st_update[leg_index * 4] += (leg_meclErr_balance.coxa / MeclErrUnit / MeclErr[leg_index * 4]);
        HEXxNegDirnMeclErrBalnRate1st_update[leg_index * 4 + 1] += (leg_meclErr_balance.femur / MeclErrUnit / MeclErr[leg_index * 4 + 1]);
        HEXxNegDirnMeclErrBalnRate1st_update[leg_index * 4 + 2] += (leg_meclErr_balance.tibia / MeclErrUnit / MeclErr[leg_index * 4 + 2]);
        HEXxNegDirnMeclErrBalnRate1st_update[leg_index * 4 + 3] += (leg_meclErr_balance.tarsus / MeclErrUnit / MeclErr[leg_index * 4 + 3]);
      }
      else if (robotMeclErrMode.dirn == "yp")
      {
        HEXyPosDirnMeclErrBalnRate1st_update[leg_index * 4] += (leg_meclErr_balance.coxa / MeclErrUnit / MeclErr[leg_index * 4]);
        HEXyPosDirnMeclErrBalnRate1st_update[leg_index * 4 + 1] += (leg_meclErr_balance.femur / MeclErrUnit / MeclErr[leg_index * 4 + 1]);
        HEXyPosDirnMeclErrBalnRate1st_update[leg_index * 4 + 2] += (leg_meclErr_balance.tibia / MeclErrUnit / MeclErr[leg_index * 4 + 2]);
        HEXyPosDirnMeclErrBalnRate1st_update[leg_index * 4 + 3] += (leg_meclErr_balance.tarsus / MeclErrUnit / MeclErr[leg_index * 4 + 3]);
      }
      else if (robotMeclErrMode.dirn == "yn")
      {
        HEXyNegDirnMeclErrBalnRate1st_update[leg_index * 4] += (leg_meclErr_balance.coxa / MeclErrUnit / MeclErr[leg_index * 4]);
        HEXyNegDirnMeclErrBalnRate1st_update[leg_index * 4 + 1] += (leg_meclErr_balance.femur / MeclErrUnit / MeclErr[leg_index * 4 + 1]);
        HEXyNegDirnMeclErrBalnRate1st_update[leg_index * 4 + 2] += (leg_meclErr_balance.tibia / MeclErrUnit / MeclErr[leg_index * 4 + 2]);
        HEXyNegDirnMeclErrBalnRate1st_update[leg_index * 4 + 3] += (leg_meclErr_balance.tarsus / MeclErrUnit / MeclErr[leg_index * 4 + 3]);
      }
      else if (robotMeclErrMode.dirn == "zp")
      {
        HEXzPosDirnMeclErrBalnRate1st_update[leg_index * 4] += (leg_meclErr_balance.coxa / MeclErrUnit / MeclErr[leg_index * 4]);
        HEXzPosDirnMeclErrBalnRate1st_update[leg_index * 4 + 1] += (leg_meclErr_balance.femur / MeclErrUnit / MeclErr[leg_index * 4 + 1]);
        HEXzPosDirnMeclErrBalnRate1st_update[leg_index * 4 + 2] += (leg_meclErr_balance.tibia / MeclErrUnit / MeclErr[leg_index * 4 + 2]);
        HEXzPosDirnMeclErrBalnRate1st_update[leg_index * 4 + 3] += (leg_meclErr_balance.tarsus / MeclErrUnit / MeclErr[leg_index * 4 + 3]);
      }
      else if (robotMeclErrMode.dirn == "zn")
      {
        HEXzNegDirnMeclErrBalnRate1st_update[leg_index * 4] += (leg_meclErr_balance.coxa / MeclErrUnit / MeclErr[leg_index * 4]);
        HEXzNegDirnMeclErrBalnRate1st_update[leg_index * 4 + 1] += (leg_meclErr_balance.femur / MeclErrUnit / MeclErr[leg_index * 4 + 1]);
        HEXzNegDirnMeclErrBalnRate1st_update[leg_index * 4 + 2] += (leg_meclErr_balance.tibia / MeclErrUnit / MeclErr[leg_index * 4 + 2]);
        HEXzNegDirnMeclErrBalnRate1st_update[leg_index * 4 + 3] += (leg_meclErr_balance.tarsus / MeclErrUnit / MeclErr[leg_index * 4 + 3]);
      }
    }
    break;
    case 1:
    {
      if (robotMeclErrMode.dirn == "xp")
      {
        HEXxPosDirnMeclErrBalnRate2nd_update[leg_index * 4] += (leg_meclErr_balance.coxa / MeclErrUnit / MeclErr[leg_index * 4]);
        HEXxPosDirnMeclErrBalnRate2nd_update[leg_index * 4 + 1] += (leg_meclErr_balance.femur / MeclErrUnit / MeclErr[leg_index * 4 + 1]);
        HEXxPosDirnMeclErrBalnRate2nd_update[leg_index * 4 + 2] += (leg_meclErr_balance.tibia / MeclErrUnit / MeclErr[leg_index * 4 + 2]);
        HEXxPosDirnMeclErrBalnRate2nd_update[leg_index * 4 + 3] += (leg_meclErr_balance.tarsus / MeclErrUnit / MeclErr[leg_index * 4 + 3]);
      }
      else if (robotMeclErrMode.dirn == "xn")
      {
        HEXxNegDirnMeclErrBalnRate2nd_update[leg_index * 4] += (leg_meclErr_balance.coxa / MeclErrUnit / MeclErr[leg_index * 4]);
        HEXxNegDirnMeclErrBalnRate2nd_update[leg_index * 4 + 1] += (leg_meclErr_balance.femur / MeclErrUnit / MeclErr[leg_index * 4 + 1]);
        HEXxNegDirnMeclErrBalnRate2nd_update[leg_index * 4 + 2] += (leg_meclErr_balance.tibia / MeclErrUnit / MeclErr[leg_index * 4 + 2]);
        HEXxNegDirnMeclErrBalnRate2nd_update[leg_index * 4 + 3] += (leg_meclErr_balance.tarsus / MeclErrUnit / MeclErr[leg_index * 4 + 3]);
      }
      else if (robotMeclErrMode.dirn == "yp")
      {
        HEXyPosDirnMeclErrBalnRate2nd_update[leg_index * 4] += (leg_meclErr_balance.coxa / MeclErrUnit / MeclErr[leg_index * 4]);
        HEXyPosDirnMeclErrBalnRate2nd_update[leg_index * 4 + 1] += (leg_meclErr_balance.femur / MeclErrUnit / MeclErr[leg_index * 4 + 1]);
        HEXyPosDirnMeclErrBalnRate2nd_update[leg_index * 4 + 2] += (leg_meclErr_balance.tibia / MeclErrUnit / MeclErr[leg_index * 4 + 2]);
        HEXyPosDirnMeclErrBalnRate2nd_update[leg_index * 4 + 3] += (leg_meclErr_balance.tarsus / MeclErrUnit / MeclErr[leg_index * 4 + 3]);
      }
      else if (robotMeclErrMode.dirn == "yn")
      {
        HEXyNegDirnMeclErrBalnRate2nd_update[leg_index * 4] += (leg_meclErr_balance.coxa / MeclErrUnit / MeclErr[leg_index * 4]);
        HEXyNegDirnMeclErrBalnRate2nd_update[leg_index * 4 + 1] += (leg_meclErr_balance.femur / MeclErrUnit / MeclErr[leg_index * 4 + 1]);
        HEXyNegDirnMeclErrBalnRate2nd_update[leg_index * 4 + 2] += (leg_meclErr_balance.tibia / MeclErrUnit / MeclErr[leg_index * 4 + 2]);
        HEXyNegDirnMeclErrBalnRate2nd_update[leg_index * 4 + 3] += (leg_meclErr_balance.tarsus / MeclErrUnit / MeclErr[leg_index * 4 + 3]);
      }
      else if (robotMeclErrMode.dirn == "zp")
      {
        HEXzPosDirnMeclErrBalnRate2nd_update[leg_index * 4] += (leg_meclErr_balance.coxa / MeclErrUnit / MeclErr[leg_index * 4]);
        HEXzPosDirnMeclErrBalnRate2nd_update[leg_index * 4 + 1] += (leg_meclErr_balance.femur / MeclErrUnit / MeclErr[leg_index * 4 + 1]);
        HEXzPosDirnMeclErrBalnRate2nd_update[leg_index * 4 + 2] += (leg_meclErr_balance.tibia / MeclErrUnit / MeclErr[leg_index * 4 + 2]);
        HEXzPosDirnMeclErrBalnRate2nd_update[leg_index * 4 + 3] += (leg_meclErr_balance.tarsus / MeclErrUnit / MeclErr[leg_index * 4 + 3]);
      }
      else if (robotMeclErrMode.dirn == "zn")
      {
        HEXzNegDirnMeclErrBalnRate2nd_update[leg_index * 4] += (leg_meclErr_balance.coxa / MeclErrUnit / MeclErr[leg_index * 4]);
        HEXzNegDirnMeclErrBalnRate2nd_update[leg_index * 4 + 1] += (leg_meclErr_balance.femur / MeclErrUnit / MeclErr[leg_index * 4 + 1]);
        HEXzNegDirnMeclErrBalnRate2nd_update[leg_index * 4 + 2] += (leg_meclErr_balance.tibia / MeclErrUnit / MeclErr[leg_index * 4 + 2]);
        HEXzNegDirnMeclErrBalnRate2nd_update[leg_index * 4 + 3] += (leg_meclErr_balance.tarsus / MeclErrUnit / MeclErr[leg_index * 4 + 3]);
      }
    }
    break;
    }
  }
  break;
  case crab_mode:
  {
    switch (robotMeclErrMode.gaitCnt)
    {
    case 0:
    {
      if (robotMeclErrMode.dirn == "xp")
      {
        CRABxPosDirnMeclErrBalnRate1st_update[leg_index * 4] += (leg_meclErr_balance.coxa / MeclErrUnit / MeclErr[leg_index * 4]);
        CRABxPosDirnMeclErrBalnRate1st_update[leg_index * 4 + 1] += (leg_meclErr_balance.femur / MeclErrUnit / MeclErr[leg_index * 4 + 1]);
        CRABxPosDirnMeclErrBalnRate1st_update[leg_index * 4 + 2] += (leg_meclErr_balance.tibia / MeclErrUnit / MeclErr[leg_index * 4 + 2]);
        CRABxPosDirnMeclErrBalnRate1st_update[leg_index * 4 + 3] += (leg_meclErr_balance.tarsus / MeclErrUnit / MeclErr[leg_index * 4 + 3]);
      }
      else if (robotMeclErrMode.dirn == "xn")
      {
        CRABxNegDirnMeclErrBalnRate1st_update[leg_index * 4] += (leg_meclErr_balance.coxa / MeclErrUnit / MeclErr[leg_index * 4]);
        CRABxNegDirnMeclErrBalnRate1st_update[leg_index * 4 + 1] += (leg_meclErr_balance.femur / MeclErrUnit / MeclErr[leg_index * 4 + 1]);
        CRABxNegDirnMeclErrBalnRate1st_update[leg_index * 4 + 2] += (leg_meclErr_balance.tibia / MeclErrUnit / MeclErr[leg_index * 4 + 2]);
        CRABxNegDirnMeclErrBalnRate1st_update[leg_index * 4 + 3] += (leg_meclErr_balance.tarsus / MeclErrUnit / MeclErr[leg_index * 4 + 3]);
      }
      else if (robotMeclErrMode.dirn == "yp")
      {
        CRAByPosDirnMeclErrBalnRate1st_update[leg_index * 4] += (leg_meclErr_balance.coxa / MeclErrUnit / MeclErr[leg_index * 4]);
        CRAByPosDirnMeclErrBalnRate1st_update[leg_index * 4 + 1] += (leg_meclErr_balance.femur / MeclErrUnit / MeclErr[leg_index * 4 + 1]);
        CRAByPosDirnMeclErrBalnRate1st_update[leg_index * 4 + 2] += (leg_meclErr_balance.tibia / MeclErrUnit / MeclErr[leg_index * 4 + 2]);
        CRAByPosDirnMeclErrBalnRate1st_update[leg_index * 4 + 3] += (leg_meclErr_balance.tarsus / MeclErrUnit / MeclErr[leg_index * 4 + 3]);
      }
      else if (robotMeclErrMode.dirn == "yn")
      {
        CRAByNegDirnMeclErrBalnRate1st_update[leg_index * 4] += (leg_meclErr_balance.coxa / MeclErrUnit / MeclErr[leg_index * 4]);
        CRAByNegDirnMeclErrBalnRate1st_update[leg_index * 4 + 1] += (leg_meclErr_balance.femur / MeclErrUnit / MeclErr[leg_index * 4 + 1]);
        CRAByNegDirnMeclErrBalnRate1st_update[leg_index * 4 + 2] += (leg_meclErr_balance.tibia / MeclErrUnit / MeclErr[leg_index * 4 + 2]);
        CRAByNegDirnMeclErrBalnRate1st_update[leg_index * 4 + 3] += (leg_meclErr_balance.tarsus / MeclErrUnit / MeclErr[leg_index * 4 + 3]);
      }
      else if (robotMeclErrMode.dirn == "zp")
      {
        CRABzPosDirnMeclErrBalnRate1st_update[leg_index * 4] += (leg_meclErr_balance.coxa / MeclErrUnit / MeclErr[leg_index * 4]);
        CRABzPosDirnMeclErrBalnRate1st_update[leg_index * 4 + 1] += (leg_meclErr_balance.femur / MeclErrUnit / MeclErr[leg_index * 4 + 1]);
        CRABzPosDirnMeclErrBalnRate1st_update[leg_index * 4 + 2] += (leg_meclErr_balance.tibia / MeclErrUnit / MeclErr[leg_index * 4 + 2]);
        CRABzPosDirnMeclErrBalnRate1st_update[leg_index * 4 + 3] += (leg_meclErr_balance.tarsus / MeclErrUnit / MeclErr[leg_index * 4 + 3]);
      }
      else if (robotMeclErrMode.dirn == "zn")
      {
        CRABzNegDirnMeclErrBalnRate1st_update[leg_index * 4] += (leg_meclErr_balance.coxa / MeclErrUnit / MeclErr[leg_index * 4]);
        CRABzNegDirnMeclErrBalnRate1st_update[leg_index * 4 + 1] += (leg_meclErr_balance.femur / MeclErrUnit / MeclErr[leg_index * 4 + 1]);
        CRABzNegDirnMeclErrBalnRate1st_update[leg_index * 4 + 2] += (leg_meclErr_balance.tibia / MeclErrUnit / MeclErr[leg_index * 4 + 2]);
        CRABzNegDirnMeclErrBalnRate1st_update[leg_index * 4 + 3] += (leg_meclErr_balance.tarsus / MeclErrUnit / MeclErr[leg_index * 4 + 3]);
      }
    }
    break;
    case 1:
    {
      if (robotMeclErrMode.dirn == "xp")
      {
        CRABxPosDirnMeclErrBalnRate2nd_update[leg_index * 4] += (leg_meclErr_balance.coxa / MeclErrUnit / MeclErr[leg_index * 4]);
        CRABxPosDirnMeclErrBalnRate2nd_update[leg_index * 4 + 1] += (leg_meclErr_balance.femur / MeclErrUnit / MeclErr[leg_index * 4 + 1]);
        CRABxPosDirnMeclErrBalnRate2nd_update[leg_index * 4 + 2] += (leg_meclErr_balance.tibia / MeclErrUnit / MeclErr[leg_index * 4 + 2]);
        CRABxPosDirnMeclErrBalnRate2nd_update[leg_index * 4 + 3] += (leg_meclErr_balance.tarsus / MeclErrUnit / MeclErr[leg_index * 4 + 3]);
      }
      else if (robotMeclErrMode.dirn == "xn")
      {
        CRABxNegDirnMeclErrBalnRate2nd_update[leg_index * 4] += (leg_meclErr_balance.coxa / MeclErrUnit / MeclErr[leg_index * 4]);
        CRABxNegDirnMeclErrBalnRate2nd_update[leg_index * 4 + 1] += (leg_meclErr_balance.femur / MeclErrUnit / MeclErr[leg_index * 4 + 1]);
        CRABxNegDirnMeclErrBalnRate2nd_update[leg_index * 4 + 2] += (leg_meclErr_balance.tibia / MeclErrUnit / MeclErr[leg_index * 4 + 2]);
        CRABxNegDirnMeclErrBalnRate2nd_update[leg_index * 4 + 3] += (leg_meclErr_balance.tarsus / MeclErrUnit / MeclErr[leg_index * 4 + 3]);
      }
      else if (robotMeclErrMode.dirn == "yp")
      {
        CRAByPosDirnMeclErrBalnRate2nd_update[leg_index * 4] += (leg_meclErr_balance.coxa / MeclErrUnit / MeclErr[leg_index * 4]);
        CRAByPosDirnMeclErrBalnRate2nd_update[leg_index * 4 + 1] += (leg_meclErr_balance.femur / MeclErrUnit / MeclErr[leg_index * 4 + 1]);
        CRAByPosDirnMeclErrBalnRate2nd_update[leg_index * 4 + 2] += (leg_meclErr_balance.tibia / MeclErrUnit / MeclErr[leg_index * 4 + 2]);
        CRAByPosDirnMeclErrBalnRate2nd_update[leg_index * 4 + 3] += (leg_meclErr_balance.tarsus / MeclErrUnit / MeclErr[leg_index * 4 + 3]);
      }
      else if (robotMeclErrMode.dirn == "yn")
      {
        CRAByNegDirnMeclErrBalnRate2nd_update[leg_index * 4] += (leg_meclErr_balance.coxa / MeclErrUnit / MeclErr[leg_index * 4]);
        CRAByNegDirnMeclErrBalnRate2nd_update[leg_index * 4 + 1] += (leg_meclErr_balance.femur / MeclErrUnit / MeclErr[leg_index * 4 + 1]);
        CRAByNegDirnMeclErrBalnRate2nd_update[leg_index * 4 + 2] += (leg_meclErr_balance.tibia / MeclErrUnit / MeclErr[leg_index * 4 + 2]);
        CRAByNegDirnMeclErrBalnRate2nd_update[leg_index * 4 + 3] += (leg_meclErr_balance.tarsus / MeclErrUnit / MeclErr[leg_index * 4 + 3]);
      }
      else if (robotMeclErrMode.dirn == "zp")
      {
        CRABzPosDirnMeclErrBalnRate2nd_update[leg_index * 4] += (leg_meclErr_balance.coxa / MeclErrUnit / MeclErr[leg_index * 4]);
        CRABzPosDirnMeclErrBalnRate2nd_update[leg_index * 4 + 1] += (leg_meclErr_balance.femur / MeclErrUnit / MeclErr[leg_index * 4 + 1]);
        CRABzPosDirnMeclErrBalnRate2nd_update[leg_index * 4 + 2] += (leg_meclErr_balance.tibia / MeclErrUnit / MeclErr[leg_index * 4 + 2]);
        CRABzPosDirnMeclErrBalnRate2nd_update[leg_index * 4 + 3] += (leg_meclErr_balance.tarsus / MeclErrUnit / MeclErr[leg_index * 4 + 3]);
      }
      else if (robotMeclErrMode.dirn == "zn")
      {
        CRABzNegDirnMeclErrBalnRate2nd_update[leg_index * 4] += (leg_meclErr_balance.coxa / MeclErrUnit / MeclErr[leg_index * 4]);
        CRABzNegDirnMeclErrBalnRate2nd_update[leg_index * 4 + 1] += (leg_meclErr_balance.femur / MeclErrUnit / MeclErr[leg_index * 4 + 1]);
        CRABzNegDirnMeclErrBalnRate2nd_update[leg_index * 4 + 2] += (leg_meclErr_balance.tibia / MeclErrUnit / MeclErr[leg_index * 4 + 2]);
        CRABzNegDirnMeclErrBalnRate2nd_update[leg_index * 4 + 3] += (leg_meclErr_balance.tarsus / MeclErrUnit / MeclErr[leg_index * 4 + 3]);
      }
    }
    break;
    }
  }
  break;
  case HEX2CRAB:
  {
    hex2crabMeclErrBalnRate_update[leg_index][leg_index * 4] += (leg_meclErr_balance.coxa / MeclErrUnit / MeclErr[leg_index * 4]);
    hex2crabMeclErrBalnRate_update[leg_index][leg_index * 4 + 1] += (leg_meclErr_balance.femur / MeclErrUnit / MeclErr[leg_index * 4 + 1]);
    hex2crabMeclErrBalnRate_update[leg_index][leg_index * 4 + 2] += (leg_meclErr_balance.tibia / MeclErrUnit / MeclErr[leg_index * 4 + 2]);
    hex2crabMeclErrBalnRate_update[leg_index][leg_index * 4 + 3] += (leg_meclErr_balance.tarsus / MeclErrUnit / MeclErr[leg_index * 4 + 3]);
  }
  break;
  case CRAB2HEX:
  {
    crab2hexMeclErrBalnRate_update[leg_index][leg_index * 4] += (leg_meclErr_balance.coxa / MeclErrUnit / MeclErr[leg_index * 4]);
    crab2hexMeclErrBalnRate_update[leg_index][leg_index * 4 + 1] += (leg_meclErr_balance.femur / MeclErrUnit / MeclErr[leg_index * 4 + 1]);
    crab2hexMeclErrBalnRate_update[leg_index][leg_index * 4 + 2] += (leg_meclErr_balance.tibia / MeclErrUnit / MeclErr[leg_index * 4 + 2]);
    crab2hexMeclErrBalnRate_update[leg_index][leg_index * 4 + 3] += (leg_meclErr_balance.tarsus / MeclErrUnit / MeclErr[leg_index * 4 + 3]);
  }
  break;
  }

  ROS_INFO("Correction done");
}


//预压前角度误差补偿回调函数
void Control::leg_meclErr_balance_cb(const hexapod_msgs::LegJointsConstPtr &leg_meclErr_balance_msg)
{
  if (leg_meclErr_flag == true)
    return;

  if (leg_meclErr_balance_msg->coxa > 10 || leg_meclErr_balance_msg->coxa < -10)
  {
    ROS_WARN("Incorrect request for mechanical error. Out of range(-10°~10°)!");
    return;
  }
  if (leg_meclErr_balance_msg->femur > 10 || leg_meclErr_balance_msg->femur < -10)
  {
    ROS_WARN("Incorrect request for mechanical error. Out of range(-10°~10°)!");
    return;
  }
  if (leg_meclErr_balance_msg->tibia > 10 || leg_meclErr_balance_msg->tibia < -10)
  {
    ROS_WARN("Incorrect request for mechanical error. Out of range(-10°~10°)!");
    return;
  }
  if (leg_meclErr_balance_msg->tarsus > 10 || leg_meclErr_balance_msg->tarsus < -10)
  {
    ROS_WARN("Incorrect request for mechanical error. Out of range(-10°~10°)!");
    return;
  }

  leg_meclErr_balance.coxa = leg_meclErr_balance_msg->coxa / 180.0 * M_PI;
  leg_meclErr_balance.femur = leg_meclErr_balance_msg->femur / 180.0 * M_PI;
  leg_meclErr_balance.tibia = leg_meclErr_balance_msg->tibia / 180.0 * M_PI;
  leg_meclErr_balance.tarsus = leg_meclErr_balance_msg->tarsus / 180.0 * M_PI;

  leg_meclErr_flag = true;
}

//将posBuffer中缓存的角度发至gazebo话题或六足服务器
void Control::publishPosBuffer()
{
#if !MACHINE
  for (int i = 0; i < posBuffer[0].size(); i++)
  {
    for (int leg = 0; leg < 6; leg++)
    {
      leg_roll[leg].data = posBuffer[leg * 4][i];
      leg_pitch1[leg].data = posBuffer[leg * 4 + 1][i];
      leg_pitch2[leg].data = posBuffer[leg * 4 + 2][i];
      leg_pitch3[leg].data = posBuffer[leg * 4 + 3][i];
    }

    for (int leg = 0; leg < 6; leg++)
    {
      leg_roll_p[leg].publish(leg_roll[leg]);
      leg_pitch1_p[leg].publish(leg_pitch1[leg]);
      leg_pitch2_p[leg].publish(leg_pitch2[leg]);
      leg_pitch3_p[leg].publish(leg_pitch3[leg]);
    }

    ros::Duration(0.005).sleep();
  }
#endif

#if MACHINE
  posBufferFeedDrivers();
#endif

  for (int i = 0; i < 24; i++)
  {
    posBuffer[i].clear(); //清空缓存
  }
}

//将posBuffer缓存的误差恢复角度发至六足服务器
bool Control::posBufferFeedDrivers()
{
  maxpointsRequest(); //请求maxpoints，确认freeSpace/motionActive

  while (freeSpace_ < (sm_point_buf_size - 30)) //当六足服务器缓存接近空时再发送角度
  {
    ros::Duration(3).sleep();
    maxpointsRequest();
  }

  if (!motionActive_)
  {
    ROS_FATAL("Motion not active!");
    ros::shutdown();
    return false;
  }

  if (posBufferLegControlHalf() != true) //发送前半个周期给服务器
    return false;

  if (posBufferLegControlRest() != true) //发送后半个周期给服务器
    return false;

  return true;
}


//预压后角度补偿回调函数
void Control::meclErr_afterPrePress_cb(const hexapod_msgs::LegJointsConstPtr &leg_meclErr_balance_msg)
{
  if (leg_meclErr_afterPrePress_flag == true)
    return;

  if (leg_meclErr_balance_msg->coxa > 10 || leg_meclErr_balance_msg->coxa < -10)
  {
    ROS_WARN("Incorrect request for mechanical error. Out of range(-10°~10°)!");
    return;
  }
  if (leg_meclErr_balance_msg->femur > 10 || leg_meclErr_balance_msg->femur < -10)
  {
    ROS_WARN("Incorrect request for mechanical error. Out of range(-10°~10°)!");
    return;
  }
  if (leg_meclErr_balance_msg->tibia > 10 || leg_meclErr_balance_msg->tibia < -10)
  {
    ROS_WARN("Incorrect request for mechanical error. Out of range(-10°~10°)!");
    return;
  }
  if (leg_meclErr_balance_msg->tarsus > 10 || leg_meclErr_balance_msg->tarsus < -10)
  {
    ROS_WARN("Incorrect request for mechanical error. Out of range(-10°~10°)!");
    return;
  }

  leg_meclErr_afterPrePress.coxa = leg_meclErr_balance_msg->coxa / 180.0 * M_PI;
  leg_meclErr_afterPrePress.femur = leg_meclErr_balance_msg->femur / 180.0 * M_PI;
  leg_meclErr_afterPrePress.tibia = leg_meclErr_balance_msg->tibia / 180.0 * M_PI;
  leg_meclErr_afterPrePress.tarsus = leg_meclErr_balance_msg->tarsus / 180.0 * M_PI;

  leg_meclErr_afterPrePress_flag = true;
}


//将update的误差表格恢复
void Control::meclErrBalnRate_update_reset()
{
  HEXxPosDirnMeclErrBalnRate1st_update.assign(HEXxPosDirnMeclErrBalnRate1st.begin(), HEXxPosDirnMeclErrBalnRate1st.end());
  HEXxNegDirnMeclErrBalnRate1st_update.assign(HEXxNegDirnMeclErrBalnRate1st.begin(), HEXxNegDirnMeclErrBalnRate1st.end());
  HEXyPosDirnMeclErrBalnRate1st_update.assign(HEXyPosDirnMeclErrBalnRate1st.begin(), HEXyPosDirnMeclErrBalnRate1st.end());
  HEXyNegDirnMeclErrBalnRate1st_update.assign(HEXyNegDirnMeclErrBalnRate1st.begin(), HEXyNegDirnMeclErrBalnRate1st.end());
  HEXzPosDirnMeclErrBalnRate1st_update.assign(HEXzPosDirnMeclErrBalnRate1st.begin(), HEXzPosDirnMeclErrBalnRate1st.end());
  HEXzNegDirnMeclErrBalnRate1st_update.assign(HEXzNegDirnMeclErrBalnRate1st.begin(), HEXzNegDirnMeclErrBalnRate1st.end());

  HEXxPosDirnMeclErrBalnRate2nd_update.assign(HEXxPosDirnMeclErrBalnRate2nd.begin(), HEXxPosDirnMeclErrBalnRate2nd.end());
  HEXxNegDirnMeclErrBalnRate2nd_update.assign(HEXxNegDirnMeclErrBalnRate2nd.begin(), HEXxNegDirnMeclErrBalnRate2nd.end());
  HEXyPosDirnMeclErrBalnRate2nd_update.assign(HEXyPosDirnMeclErrBalnRate2nd.begin(), HEXyPosDirnMeclErrBalnRate2nd.end());
  HEXyNegDirnMeclErrBalnRate2nd_update.assign(HEXyNegDirnMeclErrBalnRate2nd.begin(), HEXyNegDirnMeclErrBalnRate2nd.end());
  HEXzPosDirnMeclErrBalnRate2nd_update.assign(HEXzPosDirnMeclErrBalnRate2nd.begin(), HEXzPosDirnMeclErrBalnRate2nd.end());
  HEXzNegDirnMeclErrBalnRate2nd_update.assign(HEXzNegDirnMeclErrBalnRate2nd.begin(), HEXzNegDirnMeclErrBalnRate2nd.end());

  CRABxPosDirnMeclErrBalnRate1st_update.assign(CRABxPosDirnMeclErrBalnRate1st.begin(), CRABxPosDirnMeclErrBalnRate1st.end());
  CRABxNegDirnMeclErrBalnRate1st_update.assign(CRABxNegDirnMeclErrBalnRate1st.begin(), CRABxNegDirnMeclErrBalnRate1st.end());
  CRAByPosDirnMeclErrBalnRate1st_update.assign(CRAByPosDirnMeclErrBalnRate1st.begin(), CRAByPosDirnMeclErrBalnRate1st.end());
  CRAByNegDirnMeclErrBalnRate1st_update.assign(CRAByNegDirnMeclErrBalnRate1st.begin(), CRAByNegDirnMeclErrBalnRate1st.end());
  CRABzPosDirnMeclErrBalnRate1st_update.assign(CRABzPosDirnMeclErrBalnRate1st.begin(), CRABzPosDirnMeclErrBalnRate1st.end());
  CRABzNegDirnMeclErrBalnRate1st_update.assign(CRABzNegDirnMeclErrBalnRate1st.begin(), CRABzNegDirnMeclErrBalnRate1st.end());

  CRABxPosDirnMeclErrBalnRate2nd_update.assign(CRABxPosDirnMeclErrBalnRate2nd.begin(), CRABxPosDirnMeclErrBalnRate2nd.end());
  CRABxNegDirnMeclErrBalnRate2nd_update.assign(CRABxNegDirnMeclErrBalnRate2nd.begin(), CRABxNegDirnMeclErrBalnRate2nd.end());
  CRAByPosDirnMeclErrBalnRate2nd_update.assign(CRAByPosDirnMeclErrBalnRate2nd.begin(), CRAByPosDirnMeclErrBalnRate2nd.end());
  CRAByNegDirnMeclErrBalnRate2nd_update.assign(CRAByNegDirnMeclErrBalnRate2nd.begin(), CRAByNegDirnMeclErrBalnRate2nd.end());
  CRABzPosDirnMeclErrBalnRate2nd_update.assign(CRABzPosDirnMeclErrBalnRate2nd.begin(), CRABzPosDirnMeclErrBalnRate2nd.end());
  CRABzNegDirnMeclErrBalnRate2nd_update.assign(CRABzNegDirnMeclErrBalnRate2nd.begin(), CRABzNegDirnMeclErrBalnRate2nd.end());

  for (int i = 0; i < hex2crabMeclErrBalnRate.size(); i++)
  {
    hex2crabMeclErrBalnRate_update[i].assign(hex2crabMeclErrBalnRate[i].begin(), hex2crabMeclErrBalnRate[i].end());
  }

  for (int i = 0; i < crab2hexMeclErrBalnRate.size(); i++)
  {
    crab2hexMeclErrBalnRate_update[i].assign(crab2hexMeclErrBalnRate[i].begin(), crab2hexMeclErrBalnRate[i].end());
  }
}
