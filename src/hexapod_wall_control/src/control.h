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
#include <std_msgs/String.h>
#include <time.h>
#include <fstream>
#include <string.h>

#define MACHINE 1    //仿真和实体机标志位。置0时为gazebo仿真，置1时为实体机（发送角度控制给服务器）
#define STICK 1 //吸盘控制。置0时取消，置1开启

struct ErrMode
{
  int mode;
  int gaitCnt;
  std::string dirn;
};

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

  void partitionCmd_vel(geometry_msgs::Twist *cmd_vel); //把速度转换为步幅
  void publishJointStates(const hexapod_msgs::LegsJoints &legs, const int &origin_period_, std::vector<int> &cycle_leg_number_, const hexapod_msgs::FeetPositions *feet);
  int MASTER_LOOP_RATE;              // Master loop rate
  hexapod_msgs::LegsJoints legs_;    //各个关节的角度信息
  hexapod_msgs::FeetPositions feet_; //足端轨迹
  geometry_msgs::Twist cmd_vel_;
  void feedDrivers(const int &cycle_period_, std::vector<int> &cycle_leg_number_);
  Gait gait;
  Hexapod_IK hexapod_ik;  //六足六边形姿态行走
  Crab_IK crab_ik;        //六足螃蟹步态行走

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

  unsigned int robot_mode;
  enum{hexapod_mode = 1, crab_mode, climb2wall_mode, HEX2CRAB, CRAB2HEX};
  bool hexapod2crab_flag;
  bool crab2hexapod_flag;
  bool climb2wall_flag;
  ros::Subscriber hexapod_mode_sub;
  void hexapod_mode_cb(const std_msgs::Int32ConstPtr &mode);
  void hexapod2crab_control();
  void crab2hexapod_control();

  //平面调整位姿
  double COXA_LENGTH, FEMUR_LENGTH, TIBIA_LENGTH, TARSUS_LENGTH, BODY_RADIUS;
  double sign[6];
  std::vector<double> INIT_COXA_ANGLE;
  std::vector<double> posBuffer[24];
  void positionCalculate(const int leg_index, const hexapod_msgs::LegJoints &leg, geometry_msgs::Point &pos);
  void legs2position(const hexapod_msgs::LegsJoints &legs, hexapod_msgs::FeetPositions &feet_position);
  void legAdjustOnGround(const int MODE, const int leg_index, const geometry_msgs::Point &initPos, const geometry_msgs::Point &finalPos, const double liftHeight, const int cycle_length, hexapod_msgs::LegsJoints &legs);
  void interpolationOnGround(const geometry_msgs::Point &initPos, const geometry_msgs::Point &finalPos, const double liftHeight, const double cycle_period, const int cycle_length, geometry_msgs::Point &outputPos);
  void jointCalculate(const int leg_index, const geometry_msgs::Point &pos, const double roll_t, hexapod_msgs::LegJoints &leg);
  void publishTransformJointStates(const int leg_index);

  bool transformFeedDrviers(const int leg_index);
  void maxpointsRequest();
  void stickControl(const int leg_index);
  bool legControl();

  float MeclErrUnit;
  std::vector<float> MeclErr;
  std::vector<float> HEXxPosDirnMeclErrBalnRate1st, HEXxPosDirnMeclErrBalnRate1st_update;
  std::vector<float> HEXxNegDirnMeclErrBalnRate1st, HEXxNegDirnMeclErrBalnRate1st_update;
  std::vector<float> HEXyPosDirnMeclErrBalnRate1st, HEXyPosDirnMeclErrBalnRate1st_update;
  std::vector<float> HEXyNegDirnMeclErrBalnRate1st, HEXyNegDirnMeclErrBalnRate1st_update;
  std::vector<float> HEXzPosDirnMeclErrBalnRate1st, HEXzPosDirnMeclErrBalnRate1st_update;
  std::vector<float> HEXzNegDirnMeclErrBalnRate1st, HEXzNegDirnMeclErrBalnRate1st_update;

  std::vector<float> HEXxPosDirnMeclErrBalnRate2nd, HEXxPosDirnMeclErrBalnRate2nd_update;
  std::vector<float> HEXxNegDirnMeclErrBalnRate2nd, HEXxNegDirnMeclErrBalnRate2nd_update;
  std::vector<float> HEXyPosDirnMeclErrBalnRate2nd, HEXyPosDirnMeclErrBalnRate2nd_update;
  std::vector<float> HEXyNegDirnMeclErrBalnRate2nd, HEXyNegDirnMeclErrBalnRate2nd_update;
  std::vector<float> HEXzPosDirnMeclErrBalnRate2nd, HEXzPosDirnMeclErrBalnRate2nd_update;
  std::vector<float> HEXzNegDirnMeclErrBalnRate2nd, HEXzNegDirnMeclErrBalnRate2nd_update;
  

  std::vector<float> CRABxPosDirnMeclErrBalnRate1st, CRABxPosDirnMeclErrBalnRate1st_update;
  std::vector<float> CRABxNegDirnMeclErrBalnRate1st, CRABxNegDirnMeclErrBalnRate1st_update;
  std::vector<float> CRAByPosDirnMeclErrBalnRate1st, CRAByPosDirnMeclErrBalnRate1st_update;
  std::vector<float> CRAByNegDirnMeclErrBalnRate1st, CRAByNegDirnMeclErrBalnRate1st_update;
  std::vector<float> CRABzPosDirnMeclErrBalnRate1st, CRABzPosDirnMeclErrBalnRate1st_update;
  std::vector<float> CRABzNegDirnMeclErrBalnRate1st, CRABzNegDirnMeclErrBalnRate1st_update;

  std::vector<float> CRABxPosDirnMeclErrBalnRate2nd, CRABxPosDirnMeclErrBalnRate2nd_update;
  std::vector<float> CRABxNegDirnMeclErrBalnRate2nd, CRABxNegDirnMeclErrBalnRate2nd_update;
  std::vector<float> CRAByPosDirnMeclErrBalnRate2nd, CRAByPosDirnMeclErrBalnRate2nd_update;
  std::vector<float> CRAByNegDirnMeclErrBalnRate2nd, CRAByNegDirnMeclErrBalnRate2nd_update;
  std::vector<float> CRABzPosDirnMeclErrBalnRate2nd, CRABzPosDirnMeclErrBalnRate2nd_update;
  std::vector<float> CRABzNegDirnMeclErrBalnRate2nd, CRABzNegDirnMeclErrBalnRate2nd_update;


  void walkGaitMeclErrCompensate(hexapod_msgs::LegsJoints &legs, std::vector<float> &MeclErrBalnRate, const int cycle_period, const int cycle_length);
  int meclRecoverLength;
  void publishMeclErrRecover();

  double PREPRESS;
  int PREPRESS_CYCLE_LENGTH;
  void walkGaitPrePress(const std::vector<int> &cycle_leg_number, double prePress, const int cycle_length, const struct ErrMode robotMeclErrMode, hexapod_msgs::LegsJoints &legs);
  void publishWalkGaitPrePressPos(const std::vector<int> &cycle_leg_number, const int leg_index);
  bool walkGaitPrePressFeedDrviers(const std::vector<int> &cycle_leg_number, const int leg_index);
  bool posBufferLegControlHalf();
  bool posBufferLegControlRest();

  std::vector< std::vector<float> > hex2crabMeclErrBalnRate, hex2crabMeclErrBalnRate_update;
  std::vector<float> hex2crabMeclErrBalnRateLeg1;
  std::vector<float> hex2crabMeclErrBalnRateLeg2;
  std::vector<float> hex2crabMeclErrBalnRateLeg3;
  std::vector<float> hex2crabMeclErrBalnRateLeg4;
  std::vector<float> hex2crabMeclErrBalnRateLeg5;
  std::vector<float> hex2crabMeclErrBalnRateLeg6;

  std::vector< std::vector<float> > crab2hexMeclErrBalnRate, crab2hexMeclErrBalnRate_update;
  std::vector<float> crab2hexMeclErrBalnRateLeg1;
  std::vector<float> crab2hexMeclErrBalnRateLeg2;
  std::vector<float> crab2hexMeclErrBalnRateLeg3;
  std::vector<float> crab2hexMeclErrBalnRateLeg4;
  std::vector<float> crab2hexMeclErrBalnRateLeg5;
  std::vector<float> crab2hexMeclErrBalnRateLeg6;
  
  void modeTransmPrePress(const int MODE, const int leg_index, double prePress, const int cycle_length, hexapod_msgs::LegsJoints &legs);
  void publishModeTransmPrePressPos();
  bool modeTransmPrePressFeedDrivers();

  ros::Subscriber saveMeclErrBalnRate_sub;
  void saveMeclErrBalnRate_cb(const std_msgs::StringConstPtr &msg);

  //预压前角度误差补偿话题
  bool prePress_confirm_flag;
  double prePress_confirm;
  bool leg_meclErr_flag;
  hexapod_msgs::LegJoints leg_meclErr_balance;
  void meclErrBaln_beforPrepress(const int leg_index, double &prePress, hexapod_msgs::LegsJoints &legs, const struct ErrMode robotMeclErrMode);
  ros::Subscriber leg_meclErr_balance_sub;
  void leg_meclErr_balance_cb(const hexapod_msgs::LegJointsConstPtr &leg_meclErr_balance_msg);
  void meclErr_balance(const int leg_index, hexapod_msgs::LegsJoints &legs, const struct ErrMode robotMeclErrMode);
  ros::Subscriber leg_prePress_confirm_sub;
  void leg_prePress_confirm_cb(const std_msgs::Float64ConstPtr &prePress_confirm_msg);
  int meclErr_balance_length;

  void publishPosBuffer();
  bool posBufferFeedDrivers();

  void prePress_forward(const int leg_index, double prePress, const int cycle_length, hexapod_msgs::LegsJoints &legs);
  void prePress_backward(const int leg_index, double prePress, const int cycle_length, hexapod_msgs::LegsJoints &legs);
  void rawJointStatesStore(const hexapod_msgs::LegsJoints &legs);

  //预压后角度误差补偿话题
  ros::Subscriber meclErr_afterPrePress_sub;
  void meclErr_afterPrePress_cb(const hexapod_msgs::LegJointsConstPtr &leg_meclErr_balance_msg);
  hexapod_msgs::LegJoints leg_meclErr_afterPrePress;
  void completely_prePress_balance(const int leg_index, hexapod_msgs::LegsJoints &legs);
  bool leg_meclErr_afterPrePress_flag;

  void meclErrBalnRate_update_reset();
};

#endif
