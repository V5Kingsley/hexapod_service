#ifndef SOLUTION_H_
#define SOLUTION_H_

#include <cmath>
#include <ros/ros.h>
#include <vector>
#include <string>
#include <cmath>
#include <std_msgs/Float64.h>
#include <gazebo_msgs/ApplyBodyWrench.h>
#include <hexapod_msgs/LegsJoints.h>
#include <actionlib/client/simple_action_client.h>
#include <geometry_msgs/Point.h>
#include <hexapodservice/hexapodserviceAction.h>
#include "define.h"
#include <sensor_msgs/JointState.h>
#include <link_com/hexcom.h>
#include <link_com/heartbag.h>

#define GROUND 1
#define WALL 0

using std::vector;

class Solution
{
private:
  vector<double> INIT_COXA_ANGLE;
  double BODY_RADIUS;
  // double COXA_LENGTH, FEMUR_LENGTH, TIBIA_LENGTH, TARSUS_LENGTH;
  double sign[6];

  ros::NodeHandle nh_;
  //关节话题
  std::string leg_topic[24];
  ros::Publisher leg_coxa_p[6];
  ros::Publisher leg_femur_p[6];
  ros::Publisher leg_tibia_p[6];
  ros::Publisher leg_tarsus_p[6];
  std_msgs::Float64 leg_coxa[6];
  std_msgs::Float64 leg_femur[6];
  std_msgs::Float64 leg_tibia[6];
  std_msgs::Float64 leg_tarsus[6];

  actionlib::SimpleActionClient<hexapodservice::hexapodserviceAction> hexapodClient;
  hexapodservice::hexapodserviceGoal legGoal;
  hexapodservice::hexapodserviceGoal maxpointsGoal;
  bool bufferFree;
  bool motionActive;
  int freeSpace;
  int sm_point_buf_size;

  vector<float> MeclErr;
  vector<vector<float>> MeclErrBalnRate;
  float MeclErrUnit;
  int stepNUM;

public:
  double COXA_LENGTH, FEMUR_LENGTH, TIBIA_LENGTH, TARSUS_LENGTH;
  Solution(const std::string name, bool spin_thread);
  void positionCalculate(const int &leg_index, const hexapod_msgs::LegJoints &leg, geometry_msgs::Point &pos);
  void interpolationOnGround(const geometry_msgs::Point &initPos, const geometry_msgs::Point &finalPos, const double &liftHeight, const double &cycle_period, const int &cycle_length, geometry_msgs::Point &outputPos);
  void jointCalculate(const bool &groundOrWall, const int &leg_index, const geometry_msgs::Point &pos, const double roll_t, hexapod_msgs::LegJoints &leg);
  void publishJointStates(const hexapod_msgs::LegsJoints &legs);
  void legAdjustOnGround(const int leg_index, const geometry_msgs::Point &initPos, const geometry_msgs::Point &finalPos, const double &liftHeight, const int cycle_length, hexapod_msgs::LegsJoints &legs);
  void rollTranslationLift(const bool &groundOrWall, const int &leg_index, const double &interpRoll, const double &roll_0, const double &translation, const double &height, const hexapod_msgs::LegsJoints &initLegs, hexapod_msgs::LegsJoints &legs);
  void publishRollTranslationLift(const bool &groundOrWall, const double &roll_t, const double &roll_0, const double &translation, const double &height, hexapod_msgs::LegsJoints &legs, const int cycle_length);
  void publishRollTranslationLiftSpecial(const bool &groundOrWall, const double &roll_t, const double &roll_0, const double &translation, const double &height, hexapod_msgs::LegsJoints &legs, const int cycle_length);
  void legInitPos(const int leg_index, const hexapod_msgs::LegJoints &leg, const double roll_t, geometry_msgs::Point &initPos);
  void leftLeg2WallFinalPos(const int leg_index, const double &distance, const double &givenPosZ, geometry_msgs::Point &finalPos);
  void interpLeg2Wall(const int &leg_index, const geometry_msgs::Point &initPos, const geometry_msgs::Point &finalPos, const double &cycle_period, const int &cycle_length, geometry_msgs::Point &outputPos, double &beta);
  void leftLeg2WallJointCalculate(const int &leg_index, const geometry_msgs::Point &pos, const double &beta, const double &roll_t, hexapod_msgs::LegJoints &leg);
  void leftLeg2Wall(const int leg_index, const geometry_msgs::Point &initPos, const geometry_msgs::Point &finalPos, hexapod_msgs::LegsJoints &legs, const int cycle_length);
  void publishRollTranslationLiftBut2(const bool &groundOrWall, const double &roll_t, const double &roll_0, const double &translation, const double &height, hexapod_msgs::LegsJoints &legs, const int cycle_length);
  void legSafeControl(hexapod_msgs::LegJoints &leg);
  void rightLegStrideInter(const int &leg_index, const double &stride, const double &liftHeight, const geometry_msgs::Point &initPos, const double &roll_t, const int &cycle_period, const int &cycle_length, geometry_msgs::Point &outputPos);
  void rightLegStride(const int leg_index, const double &stride, const double &liftHeight, const geometry_msgs::Point &initPos, const double roll_t, hexapod_msgs::LegsJoints &legs, const int cycle_length);
  void publishRollTranslationLiftFirst45(const bool &groundOrWall, const double &roll_t, const double &roll_0, const double &translation, const double &height, hexapod_msgs::LegsJoints &legs, const int cycle_length);
  void leftLegStride(const int leg_index, const double &stride, const double &liftHeight, const double &roll, const int &cycle_length, hexapod_msgs::LegsJoints &legs);
  // void legAfterRollPosCalculate(const int &leg_index, const double &roll, hexapod_msgs::LegJoints leg, geometry_msgs::Point &pos);
  void legAfterRollPosCalculate(const int &leg_index, const double &roll, hexapod_msgs::LegJoints leg, geometry_msgs::Point &pos);
  void rightLeg2Wall(const int leg_index, const geometry_msgs::Point &initPos, const geometry_msgs::Point &finalPos, const double &roll, hexapod_msgs::LegsJoints &legs, const int cycle_length);
  void prePress(const int leg_index, const double &prePress, const double &roll, const int &cycle_length, hexapod_msgs::LegsJoints &legs);
  void leg2SpecialPrePress(const int leg_index, const double &prePress, const double &roll, const int &cycle_length, hexapod_msgs::LegsJoints &legs);
  void cyclePosPrePress(const int leg_index, const double &prePress, const int &cycle_length, hexapod_msgs::LegsJoints &legs);

  vector<double> posBuffer[24];
  vector<double> smoothPosBuffer[24];
  void posMeanFilter();
  double meanCalculate(const int bufferIndex, const int i, const int k);
  void publishSmoothPos(const int leg_index);
  void publishPrePressPos();
  void meclErrRecover(const int &cycle_length, hexapod_msgs::LegsJoints &legs);
  void publishMeclErrRecover();
  bool meclErrRecFeedDrivers();

  //六足客户端
  bool feedDrviers(const int leg_index);
  bool prePressFeedDrviers();
  bool legControlHalf();
  bool legControlRest();
  bool prePressLegControlHalf();
  bool prePressLegControlRest();
  void legcontrol_doneCb(const actionlib::SimpleClientGoalState &state, const hexapodservice::hexapodserviceResultConstPtr &result);
  void maxpoint_doneCb(const actionlib::SimpleClientGoalState &state, const hexapodservice::hexapodserviceResultConstPtr &result);
  void maxpointsRequest();

  //吸盘客户端
  ros::ServiceClient stickClient;
  link_com::hexcom stickSrv;
  //心跳包订阅者
  ros::Subscriber heartbagSub;
  void heartbagCallBack(const link_com::heartbagConstPtr &heartbag);
  int io[7];
  float kpa;
  float KPALIMIT;
  bool isStickDone(const int requestIO[]);
  void stickControl(const int leg_index);

  //反馈rviz角度
  ros::Subscriber sm_pos_sub;
  ros::Publisher sm_pos_pub;
  void sm_pos_Cb(const hexapodservice::legConstPtr &leg);
  std::vector<std::string> joint_name;
  sensor_msgs::JointState joint_states;


  int stepCnt;
};

#endif