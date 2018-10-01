#ifndef CONTROL_H
#define CONTROL_H

#include <cmath>
#include <ros/ros.h>
#include <geometry_msgs/Pose2D.h>
#include <sensor_msgs/JointState.h>
#include <hexapod_msgs/Pose.h>
#include <hexapod_msgs/RPY.h>
#include <hexapod_msgs/LegsJoints.h>
#include <hexapod_msgs/FeetPositions.h>
#include <std_msgs/Float64.h>
#include <string>
#include <boost/format.hpp>
#include "gait.h"
#include "ik.h"
#include <actionlib/client/simple_action_client.h>
#include <hexapodservice/hexapodserviceAction.h>
#include "define.h"
#include <std_msgs/Int32.h>
#include <sensor_msgs/JointState.h>
#include <link_com/hexcom.h>
#include <link_com/heartbag.h>

class Control
{
public:
  actionlib::SimpleActionClient<hexapodservice::hexapodserviceAction> hexapod_client_;

  hexapodservice::hexapodserviceGoal leg_goal_;
  hexapodservice::hexapodserviceGoal maxpoints_goal_;

  void legcontrol_doneCb(const actionlib::SimpleClientGoalState &state, const hexapodservice::hexapodserviceResultConstPtr &result);
  void maxpoint_doneCb(const actionlib::SimpleClientGoalState &state, const hexapodservice::hexapodserviceResultConstPtr &result);

  //吸盘客户端
  ros::ServiceClient stick_client_;
  link_com::hexcom stick_srv_;
  //吸盘心跳包订阅者
  ros::Subscriber heartbag_sub_;
  void heartbag_Callback(const link_com::heartbagConstPtr &heartbag);
  int io[7];
  float kpa;
  float KPALIMIT;
  bool isStickDone(const int Reqio[]);


  Control(const std::string name, bool spin_thread);

  void partitionCmd_vel(geometry_msgs::Twist *cmd_vel); //把速度离散化？
  void publishJointStates(const hexapod_msgs::LegsJoints &legs, int &origin_period_, std::vector<int> &cycle_leg_number_, const hexapod_msgs::FeetPositions *feet);
  void robotInit();
  int MASTER_LOOP_RATE;              // Master loop rate
  hexapod_msgs::Pose body_;          // Body link rotation,没有用到
  hexapod_msgs::LegsJoints legs_;    //各个关节的角度信息
  hexapod_msgs::FeetPositions feet_; //足端轨迹
  geometry_msgs::Twist cmd_vel_;
  void feedDrives(const bool &start_cycle, const int &cycle_period_, const bool &is_traveling_, std::vector<int> &cycle_leg_number_, geometry_msgs::Pose2D &smooth_base_, bool &hexapod_stop_flag);
  Gait gait;
  IK ik;

private:
  double VELOCITY_DIVISION;
  int NUMBER_OF_LEGS;       // Number of legs
  int NUMBER_OF_LEG_JOINTS; // Number of leg segments

  geometry_msgs::Twist cmd_vel_incoming_;

  // 订阅速度信息
  ros::Subscriber cmd_vel_sub_;
  void cmd_velCallback(const geometry_msgs::TwistConstPtr &cmd_vel_msg);

  // Node Handle
  ros::NodeHandle nh_;  

  // 发布每个关节的角度话题
  std::string leg_topic[24];
  ros::Publisher leg_roll_p[6];
  ros::Publisher leg_pitch1_p[6];
  ros::Publisher leg_pitch2_p[6];
  ros::Publisher leg_pitch3_p[6];
  std_msgs::Float64 leg_roll[6];
  std_msgs::Float64 leg_pitch1[6];
  std_msgs::Float64 leg_pitch2[6];
  std_msgs::Float64 leg_pitch3[6];

  ros::Publisher feet_position;

  int freeSpace_;
  int minimumBufferFreeBytes_;
  int maxpoints_;
  bool motionActive_;
  int status_;
  int feedDriver_points_;
  bool bufferFree_;
  bool stick_control_;
  int sm_point_buf_size;

  double linear_x_max;
  double linear_y_max;
  double angular_z_max;

  ros::Subscriber sm_pos_sub;
  ros::Publisher sm_pos_pub;
  void sm_pos_Cb(const hexapodservice::legConstPtr &leg);
  std::vector<std::string> joint_name;
  sensor_msgs::JointState joint_states;

};

#endif
