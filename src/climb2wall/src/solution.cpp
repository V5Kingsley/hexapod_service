/*****************************************
 *        六足爬墙算法ros仿真程序           *
 *     Copyright (c) V5_Lab, 2018        *
 *     Author:  Andy, Kingsley           *
 *     Version number:  1.00             *
 *     Date:                             *
 * ***************************************/

#include "solution.h"

Solution::Solution(const std::string name, bool spin_thread) : hexapodClient(name, spin_thread)
{
  ros::param::get("INIT_COXA_ANGLE", INIT_COXA_ANGLE);
  ros::param::get("BODY_RADIUS", BODY_RADIUS);
  ros::param::get("COXA_LENGTH", COXA_LENGTH);
  ros::param::get("FEMUR_LENGTH", FEMUR_LENGTH);
  ros::param::get("TIBIA_LENGTH", TIBIA_LENGTH);
  ros::param::get("TARSUS_LENGTH", TARSUS_LENGTH);
  ros::param::get("KPALIMIT", KPALIMIT);
  nh_.param<int>("VkBHexSM/sm_point_buf_size", sm_point_buf_size, 3000);

  //发布的关节角度话题
  boost::format coxa;
  boost::format femur;
  boost::format tibia;
  boost::format tarsus;
  for (int leg_index = 0, j = 1; leg_index < 6; leg_index++, j++)
  {
    coxa = boost::format("/hexapod/leg%d_roll_joint_position_controller/command") % j;
    femur = boost::format("/hexapod/leg%d_pitch1_joint_position_controller/command") % j;
    tibia = boost::format("/hexapod/leg%d_pitch2_joint_position_controller/command") % j;
    tarsus = boost::format("/hexapod/leg%d_pitch3_joint_position_controller/command") % j;
    leg_topic[leg_index] = coxa.str();
    leg_topic[leg_index + 1] = femur.str();
    leg_topic[leg_index + 2] = tibia.str();
    leg_topic[leg_index + 3] = tarsus.str();
    leg_coxa_p[leg_index] = nh_.advertise<std_msgs::Float64>(leg_topic[leg_index], 10);
    leg_femur_p[leg_index] = nh_.advertise<std_msgs::Float64>(leg_topic[leg_index + 1], 10);
    leg_tibia_p[leg_index] = nh_.advertise<std_msgs::Float64>(leg_topic[leg_index + 2], 10);
    leg_tarsus_p[leg_index] = nh_.advertise<std_msgs::Float64>(leg_topic[leg_index + 3], 10);
  }

  //订阅角度反馈，发布给rviz
  ros::param::get("JOINT_NAME", joint_name);
  sm_pos_sub = nh_.subscribe<hexapodservice::leg>("/hexapod_sm_pose", 1, &Solution::sm_pos_Cb, this);
  sm_pos_pub = nh_.advertise<sensor_msgs::JointState>("/joint_states", 1);

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
    posBuffer[i].reserve(5200);
    smoothPosBuffer[i].reserve(5200);
  }

  bufferFree = true;
  motionActive = true;

  stickClient = nh_.serviceClient<link_com::hexcom>("hexapod_st_service");
  heartbagSub = nh_.subscribe<link_com::heartbag>("/hexapod_st_heartbag", 1, &Solution::heartbagCallBack, this);
}

/******************************************************
 *                 %由给定角度计算六足位姿%               *
 *                  输入： 腿序号、腿角度                 *
 *                  输出： 六足相应位姿                  *
 ******************************************************/
void Solution::positionCalculate(const int &leg_index, const hexapod_msgs::LegJoints &leg, geometry_msgs::Point &pos)
{
  pos.x = BODY_RADIUS * cos(INIT_COXA_ANGLE[leg_index]) +
          (COXA_LENGTH + FEMUR_LENGTH * cos(leg.femur) + TIBIA_LENGTH * sin(leg.femur + leg.tibia) + TARSUS_LENGTH * sin(leg.femur + leg.tibia + leg.tarsus)) * cos(INIT_COXA_ANGLE[leg_index] + leg.coxa);

  pos.y = BODY_RADIUS * sin(INIT_COXA_ANGLE[leg_index]) +
          (COXA_LENGTH + FEMUR_LENGTH * cos(leg.femur) + TIBIA_LENGTH * sin(leg.femur + leg.tibia) + TARSUS_LENGTH * sin(leg.femur + leg.tibia + leg.tarsus)) * sin(INIT_COXA_ANGLE[leg_index] + leg.coxa);

  pos.z = FEMUR_LENGTH * sin(leg.femur) - TIBIA_LENGTH * cos(leg.femur + leg.tibia) - TARSUS_LENGTH * cos(leg.femur + leg.tibia + leg.tarsus);
}

/*******************************************************************************
*                      %从初始位姿到终止位姿插值%                                  *
*        输入：初始位姿、终止位姿、抬腿高度、cycle_period、周期长度、插值所得位姿        *
*                         输出： 插值所得位姿                                     *
********************************************************************************/
void Solution::interpolationOnGround(const geometry_msgs::Point &initPos, const geometry_msgs::Point &finalPos, const double &liftHeight, const double &cycle_period, const int &cycle_length, geometry_msgs::Point &outputPos)
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
void Solution::jointCalculate(const bool &groundOrWall, const int &leg_index, const geometry_msgs::Point &pos, const double roll_t, hexapod_msgs::LegJoints &leg)
{
  if (groundOrWall == GROUND)
    leg.coxa = atan2(pos.y - BODY_RADIUS * sin(INIT_COXA_ANGLE[leg_index]), pos.x - BODY_RADIUS * cos(INIT_COXA_ANGLE[leg_index])) - INIT_COXA_ANGLE[leg_index];
  else
    leg.coxa = sign[leg_index] * M_PI / 2 - INIT_COXA_ANGLE[leg_index];

  double beta;
  if (groundOrWall == WALL)
    beta = (1.0 + sign[leg_index]) / 2.0 * M_PI / 2.0;
  else
    beta = 0.0;

  double A = pos.z + TARSUS_LENGTH * cos(beta - sign[leg_index] * roll_t);

  double B;

  if (groundOrWall == GROUND)
    B = (pos.y - BODY_RADIUS * sin(INIT_COXA_ANGLE[leg_index])) / sin(INIT_COXA_ANGLE[leg_index] + leg.coxa) - COXA_LENGTH - TARSUS_LENGTH * sin(beta - sign[leg_index] * roll_t);
  else
    B = sign[leg_index] * (pos.y - BODY_RADIUS * sin(INIT_COXA_ANGLE[leg_index])) - COXA_LENGTH - TARSUS_LENGTH * sin(beta - sign[leg_index] * roll_t);

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

  legSafeControl(leg);
}

/************************************************
*                %发布关节角度话题%                *
*                输入： 所有关节角度               *
*************************************************/
void Solution::publishJointStates(const hexapod_msgs::LegsJoints &legs)
{
  /* for (int leg_index = 0; leg_index < 6; leg_index++)
  {
    leg_coxa[leg_index].data = legs.leg[leg_index].coxa;
    leg_femur[leg_index].data = legs.leg[leg_index].femur;
    leg_tibia[leg_index].data = legs.leg[leg_index].tibia;
    leg_tarsus[leg_index].data = legs.leg[leg_index].tarsus;
  }

  for (int leg_index = 0; leg_index < 6; leg_index++)
  {
    leg_coxa_p[leg_index].publish(leg_coxa[leg_index]);
    leg_femur_p[leg_index].publish(leg_femur[leg_index]);
    leg_tibia_p[leg_index].publish(leg_tibia[leg_index]);
    leg_tarsus_p[leg_index].publish(leg_tarsus[leg_index]);
  }*/
  for (int leg_index = 0; leg_index < 6; leg_index++)
  {
    posBuffer[leg_index * 4].push_back(legs.leg[leg_index].coxa);
    posBuffer[leg_index * 4 + 1].push_back(legs.leg[leg_index].femur);
    posBuffer[leg_index * 4 + 2].push_back(legs.leg[leg_index].tibia);
    posBuffer[leg_index * 4 + 3].push_back(legs.leg[leg_index].tarsus);
  }
}

/*********************************************************************
*                  %在地面上时调整腿的姿态%                              *
*      输入：腿序号、初始位姿、终止位姿、抬腿高度、周期长度、关节角            *
*                       输出：关节角                                   *      
**********************************************************************/
void Solution::legAdjustOnGround(const int leg_index, const geometry_msgs::Point &initPos, const geometry_msgs::Point &finalPos, const double &liftHeight, const int cycle_length, hexapod_msgs::LegsJoints &legs)
{
  geometry_msgs::Point pos;
  double i = 0.0;
  while (i <= cycle_length)
  {
    interpolationOnGround(initPos, finalPos, liftHeight, i, cycle_length, pos); //插值
    jointCalculate(GROUND, leg_index, pos, 0, legs.leg[leg_index]);             //角度计算
    publishJointStates(legs);                                                   //发布关节角度话题
    if (i <= 1.0 / 3.0 * cycle_length || i >= 2.0 / 3.0 * cycle_length)
      i += 2.0;
    else
      i++;
  }
  posMeanFilter();
  publishSmoothPos(leg_index);
}

/*************************************************************************************************
*                                 %俯仰、平移、提升子函数%                                           *
*          输入： 墙或地、腿序、插值俯仰角、俯仰初始角、插值平移值、插值提升值、关节初始角度、关节角度          *
*                                    输出： 关节角度                                                *
**************************************************************************************************/
void Solution::rollTranslationLift(const bool &groundOrWall, const int &leg_index, const double &interpRoll, const double &roll_0, const double &translation, const double &height, const hexapod_msgs::LegsJoints &initLegs, hexapod_msgs::LegsJoints &legs)
{
  double beta;
  if (groundOrWall == GROUND)
    beta = 0;
  else
    beta = (1 + sign[leg_index]) / 2 * M_PI / 2;

  double A = -height * cos(interpRoll) - (BODY_RADIUS * sin(INIT_COXA_ANGLE[leg_index]) + sign[leg_index] * COXA_LENGTH) * sin(interpRoll) + FEMUR_LENGTH * sin(initLegs.leg[leg_index].femur - sign[leg_index] * interpRoll) - TIBIA_LENGTH * cos((initLegs.leg[leg_index].femur + initLegs.leg[leg_index].tibia) - sign[leg_index] * interpRoll);

  double B = sign[leg_index] * (-height * sin(interpRoll) - translation + BODY_RADIUS * sin(INIT_COXA_ANGLE[leg_index]) * (cos(interpRoll) - 1)) + COXA_LENGTH * (cos(interpRoll) - 1) + FEMUR_LENGTH * cos(initLegs.leg[leg_index].femur - sign[leg_index] * interpRoll) + TIBIA_LENGTH * sin(initLegs.leg[leg_index].femur + initLegs.leg[leg_index].tibia - sign[leg_index] * interpRoll);

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

  legs.leg[leg_index].coxa = sign[leg_index] * M_PI / 2.0 - INIT_COXA_ANGLE[leg_index];
  legs.leg[leg_index].femur = x;
  legs.leg[leg_index].tibia = y - x;
  legs.leg[leg_index].tarsus = beta - sign[leg_index] * (interpRoll + roll_0) - y;

  legSafeControl(legs.leg[leg_index]);
}

/*******************************************************************************
*                           %俯仰、平移、提升%                                    *
*         输入： 墙或地面、俯仰终止角度、俯仰初始脚、平移、提升、关节角度、周期长度        *
*                            输出： 关节角度                                      *
********************************************************************************/
void Solution::publishRollTranslationLift(const bool &groundOrWall, const double &roll_t, const double &roll_0, const double &translation, const double &height, hexapod_msgs::LegsJoints &legs, const int cycle_length)
{
  hexapod_msgs::LegsJoints initLegs; //缓存初始关节角度
  for (int leg_index = 0; leg_index < 6; leg_index++)
  {
    initLegs.leg[leg_index].coxa = legs.leg[leg_index].coxa;
    initLegs.leg[leg_index].femur = legs.leg[leg_index].femur;
    initLegs.leg[leg_index].tibia = legs.leg[leg_index].tibia;
    initLegs.leg[leg_index].tarsus = legs.leg[leg_index].tarsus;
  }

  //插值发布关节角度话题
  for (int i = 0; i <= cycle_length; i++)
  {
    double interpHeight = height * (-0.5 * cos(M_PI * i / cycle_length) + 0.5);           //提升高度插值
    double interpTranslation = translation * (-0.5 * cos(M_PI * i / cycle_length) + 0.5); //平移距离插值
    double interpRoll = (roll_t - roll_0) * (-0.5 * cos(M_PI * i / cycle_length) + 0.5);  //俯仰角插值
    for (int leg_index = 0; leg_index < 6; leg_index++)
    {
      rollTranslationLift(groundOrWall, leg_index, interpRoll, roll_0, interpTranslation, interpHeight, initLegs, legs); //根据插值的俯仰、提升、平移值计算关节角度
    }
    publishJointStates(legs);
    //ros::Duration(0.005).sleep();
  }
  posMeanFilter();
  publishSmoothPos(6);
}

/******************************************************
*                %由关节角度计算初始位姿%                 *
*           输入： 腿序、关节角、俯仰脚、初始位姿           *
*                   输出： 初始位姿                      *
*******************************************************/
void Solution::legInitPos(const int leg_index, const hexapod_msgs::LegJoints &leg, const double roll_t, geometry_msgs::Point &initPos)
{
  double beta = 0.0;
  initPos.x = BODY_RADIUS * cos(INIT_COXA_ANGLE[leg_index]);
  initPos.y = BODY_RADIUS * sin(INIT_COXA_ANGLE[leg_index]) + sign[leg_index] *
                                                                  (COXA_LENGTH + FEMUR_LENGTH * cos(leg.femur) + TIBIA_LENGTH * sin(leg.femur + leg.tibia) + TARSUS_LENGTH * sin(beta - sign[leg_index] * roll_t));
  initPos.z = FEMUR_LENGTH * sin(leg.femur) - TIBIA_LENGTH * cos(leg.femur + leg.tibia) - TARSUS_LENGTH * cos(beta - sign[leg_index] * roll_t);
}

/******************************************************************
*                       %左腿上墙后的终止姿态%                       *
*                输入： 腿序、 离墙体距离、 抬腿高度、 终止位姿          *
*                        输出： 终止位姿                            *
*******************************************************************/
void Solution::leftLeg2WallFinalPos(const int leg_index, const double &distance, const double &givenPosZ, geometry_msgs::Point &finalPos)
{
  finalPos.x = BODY_RADIUS * cos(INIT_COXA_ANGLE[leg_index]);
  finalPos.y = distance;
  finalPos.z = givenPosZ;
}

/*********************************************************************************************************
*                                     %左腿上墙插值函数%                                                    *
*           输入： 腿序、 初始位姿、 终止位姿、 cycle_period、 周期长度、 插值位姿、 beta(吸盘和地面夹角)            *
*                                    输出： 插值位姿、 beta                                                 *
**********************************************************************************************************/
void Solution::interpLeg2Wall(const int &leg_index, const geometry_msgs::Point &initPos, const geometry_msgs::Point &finalPos, const double &cycle_period, const int &cycle_length, geometry_msgs::Point &outputPos, double &beta)
{
  outputPos.x = initPos.x;
  double sigmoidy, sigmoidz;

  if (leg_index == 1)
  {
    sigmoidy = 1.0 / (1.0 + exp(-15.0 * (float(cycle_period) / cycle_length - 0.65)));
    sigmoidz = 1.0 / (1.0 + exp(-15.0 * (float(cycle_period) / cycle_length - 0.40)));
  }
  else
  {
    sigmoidy = 1.0 / (1.0 + exp(-15.0 * (float(cycle_period) / cycle_length - 0.60)));
    sigmoidz = 1.0 / (1.0 + exp(-15.0 * (float(cycle_period) / cycle_length - 0.35)));
  }
  outputPos.y = initPos.y + (finalPos.y - initPos.y) * sigmoidy;

  outputPos.z = initPos.z + (finalPos.z - initPos.z) * sigmoidz;

  double sigmoidbeta = 1.0 / (1.0 + exp(-15.0 * (float(cycle_period) / cycle_length - 0.50)));
  beta = (1.0 + sign[leg_index]) / 2.0 * M_PI / 2 * sigmoidbeta;
}

/*******************************************************************************
*                           %左腿上墙关节角度计算%                                 *
*              输入： 腿序、 插值位姿、 插值beta、 俯仰角、 关节角度                   *
*                              输出： 关节角                                      *
*********************************************************************************/
void Solution::leftLeg2WallJointCalculate(const int &leg_index, const geometry_msgs::Point &pos, const double &beta, const double &roll_t, hexapod_msgs::LegJoints &leg)
{
  double A = pos.z + TARSUS_LENGTH * cos(beta - sign[leg_index] * roll_t);

  double B = sign[leg_index] * (pos.y - BODY_RADIUS * sin(INIT_COXA_ANGLE[leg_index])) - COXA_LENGTH - TARSUS_LENGTH * sin(beta - sign[leg_index] * roll_t);

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

  leg.coxa = sign[leg_index] * M_PI / 2 - INIT_COXA_ANGLE[leg_index];
  leg.femur = x;
  legSafeControl(leg);
  leg.tibia = y - leg.femur;
  leg.tarsus = beta - sign[leg_index] * roll_t - (leg.tibia + leg.femur);
}

/***************************************************************************
*                           %左腿上墙控制函数%                                *
*                输入： 腿序、 初始位姿、 终止位姿、 关节角、 周期长度             *
*                             输出： 关节角                                  *
****************************************************************************/
void Solution::leftLeg2Wall(const int leg_index, const geometry_msgs::Point &initPos, const geometry_msgs::Point &finalPos, hexapod_msgs::LegsJoints &legs, const int cycle_length)
{
  double beta = 0.0;
  double roll_t = 0.0;
  geometry_msgs::Point pos;
  double i = 0;
  while (i <= cycle_length)
  {
    interpLeg2Wall(leg_index, initPos, finalPos, i, cycle_length, pos, beta);      //左腿上墙对位姿和beta插值
    leftLeg2WallJointCalculate(leg_index, pos, beta, roll_t, legs.leg[leg_index]); //根据插值结果计算关节角
    publishJointStates(legs);                                                      //发布关节角度话题
                                                                                   // ros::Duration(0.005).sleep();
    if (leg_index == 1)
    {
      if (i >= 1.0 / 2.0 * cycle_length && i <= 3.0 / 5.0 * cycle_length)
        i += 0.5;
      else if (i > 3.0 / 5.0 * cycle_length)
        i += 2;
      else
        i++;
    }
    else
    {
      i++;
    }
  }
  posMeanFilter();
  publishSmoothPos(leg_index);
}

/*同publishRollTranslationLift，第二腿保持不动*/
void Solution::publishRollTranslationLiftBut2(const bool &groundOrWall, const double &roll_t, const double &roll_0, const double &translation, const double &height, hexapod_msgs::LegsJoints &legs, const int cycle_length)
{
  hexapod_msgs::LegsJoints initLegs;
  for (int leg_index = 0; leg_index < 6; leg_index++)
  {
    initLegs.leg[leg_index].coxa = legs.leg[leg_index].coxa;
    initLegs.leg[leg_index].femur = legs.leg[leg_index].femur;
    initLegs.leg[leg_index].tibia = legs.leg[leg_index].tibia;
    initLegs.leg[leg_index].tarsus = legs.leg[leg_index].tarsus;
  }
  for (int i = 0; i <= cycle_length; i++)
  {
    double interpHeight = height * (-0.5 * cos(M_PI * i / cycle_length) + 0.5);
    double interpTranslation = translation * (-0.5 * cos(M_PI * i / cycle_length) + 0.5);
    double interpRoll = (roll_t - roll_0) * (-0.5 * cos(M_PI * i / cycle_length) + 0.5);
    for (int leg_index = 0; leg_index < 6; leg_index++)
    {
      if (leg_index != 1)
        rollTranslationLift(groundOrWall, leg_index, interpRoll, roll_0, interpTranslation, interpHeight, initLegs, legs);
    }
    publishJointStates(legs);
    // ros::Duration(0.005).sleep();
  }

  posMeanFilter();
  publishSmoothPos(1);
}

/**********************************************
*             %关节角度安全范围控制%             *
*                输入： 关节角                  *
*                输出： 关节角                  *    
***********************************************/
void Solution::legSafeControl(hexapod_msgs::LegJoints &leg)
{
  // if(leg.coxa<-0.925)
  //  leg.coxa = -0.925;
  // if(leg.coxa>1.3788)
  //   leg.coxa = 1.3788;

  if (leg.femur < -M_PI / 2) //第二关节控制在 -M_PI/2 ~ M_PI/2
    leg.femur = -M_PI / 2;
  if (leg.femur > 90.0 / 180 * M_PI)
    leg.femur = 90.0 / 180 * M_PI;

  if (leg.tibia > M_PI) //第三关节控制在 -M_PI/4 ~ M_PI
    leg.tibia = M_PI;
  if (leg.tibia < -45.0 / 180 * M_PI)
    leg.tibia = -45.0 / 180 * M_PI;

  if (leg.tarsus > M_PI / 2) //第四关节控制在 -M_PI/2 ~ M_PI/2
    leg.tarsus = M_PI / 2;
  if (leg.tarsus < -M_PI / 2)
    leg.tarsus = -M_PI / 2;
}

/*********************************************************************************************
*                               %右腿跨步的位姿插值函数%                                         *
*       输入： 腿序、 跨步距离、 抬腿高度、 初始位姿、 俯仰角、 cycle_period、 周期长度、 插值位姿       *
*                                  输出： 插值位姿                                              *
**********************************************************************************************/
void Solution::rightLegStrideInter(const int &leg_index, const double &stride, const double &liftHeight, const geometry_msgs::Point &initPos, const double &roll_t, const int &cycle_period, const int &cycle_length, geometry_msgs::Point &outputPos)
{
  double beta = 0;

  outputPos.x = initPos.x;

  double interFuncY = 1.0 / (1.0 + exp(-15.0 * (float(cycle_period) / cycle_length - 0.5)));
  outputPos.y = initPos.y + stride * cos(beta - sign[leg_index] * roll_t) * interFuncY;

  double interFuncZ = -0.5 * cos(2.0 * M_PI * cycle_period / cycle_length) + 0.5;
  outputPos.z = initPos.z + liftHeight * interFuncZ;
}

/***************************************************************************************
*                                %右腿跨步控制函数%                                       *
*            输入： 腿序、 跨步距离、 抬腿高度、 初始位姿、 俯仰角、 关节角、 周期长度            *
*                                  输出： 关节角                                         *
****************************************************************************************/
void Solution::rightLegStride(const int leg_index, const double &stride, const double &liftHeight, const geometry_msgs::Point &initPos, const double roll_t, hexapod_msgs::LegsJoints &legs, const int cycle_length)
{
  geometry_msgs::Point pos; //插值位姿
  for (int i = 0; i <= cycle_length; i++)
  {
    rightLegStrideInter(leg_index, stride, liftHeight, initPos, roll_t, i, cycle_length, pos); //插值位姿函数
    jointCalculate(WALL, leg_index, pos, roll_t, legs.leg[leg_index]);                         //根据插值位姿计算关节角
    publishJointStates(legs);                                                                  //发布关节角度话题
    //  ros::Duration(0.005).sleep();
  }
  posMeanFilter();
  publishSmoothPos(leg_index);
}

/********************************************************************************************
*                             %第一次俯仰45°时的控制函数%                                       *
*             %除了平移部分的插值函数特殊设置外，其他部分与publishRollTranslation相同%              *
*********************************************************************************************/
void Solution::publishRollTranslationLiftFirst45(const bool &groundOrWall, const double &roll_t, const double &roll_0, const double &translation, const double &height, hexapod_msgs::LegsJoints &legs, const int cycle_length)
{
  hexapod_msgs::LegsJoints initLegs;
  for (int leg_index = 0; leg_index < 6; leg_index++)
  {
    initLegs.leg[leg_index].coxa = legs.leg[leg_index].coxa;
    initLegs.leg[leg_index].femur = legs.leg[leg_index].femur;
    initLegs.leg[leg_index].tibia = legs.leg[leg_index].tibia;
    initLegs.leg[leg_index].tarsus = legs.leg[leg_index].tarsus;
  }
  for (int i = 0; i <= cycle_length; i++)
  {
    double interpHeight = height * (-0.5 * cos(M_PI * i / cycle_length) + 0.5);
    double interpTranslation;
    if (i <= 0.5 * cycle_length)
      interpTranslation = (0.01 * cos(M_PI * 4.0 / cycle_length * i) - 0.01); //先沿y轴平移-0.01后复位
    else
      interpTranslation = translation * (0.5 * cos(M_PI * 2.0 / cycle_length * i) + 0.5); //后沿y轴平移translation
    double interpRoll = (roll_t - roll_0) * (-0.5 * cos(M_PI * i / cycle_length) + 0.5);
    for (int leg_index = 0; leg_index < 6; leg_index++)
    {
      rollTranslationLift(groundOrWall, leg_index, interpRoll, roll_0, interpTranslation, interpHeight, initLegs, legs);
    }
    publishJointStates(legs);
    // ros::Duration(0.005).sleep();
  }
  posMeanFilter();
  publishSmoothPos(6);
}

/***************************************************************************
*                          %左、右腿俯仰后跨步控制函数%                         *
*           输入： 腿序、 跨步距离、 抬腿高度、 俯仰角、 周期长度、 关节角           *
*                            输出： 关节角                                   *
****************************************************************************/
void Solution::leftLegStride(const int leg_index, const double &stride, const double &liftHeight, const double &roll, const int &cycle_length, hexapod_msgs::LegsJoints &legs)
{
  hexapod_msgs::LegJoints initLeg; //缓存初始关节角
  initLeg.coxa = legs.leg[leg_index].coxa;
  initLeg.femur = legs.leg[leg_index].femur;
  initLeg.tibia = legs.leg[leg_index].tibia;
  initLeg.tarsus = legs.leg[leg_index].tarsus;

  for (int cycle_period = 0; cycle_period <= cycle_length; cycle_period++)
  {
    double interFuncX = -0.5 * cos(2.0 * M_PI * cycle_period / cycle_length) + 0.5;
    double foot2foot_x = -liftHeight * interFuncX;

    double interFuncY = 1.0 / (1.0 + exp(-20.0 * (float(cycle_period) / cycle_length - 0.5)));
    double foot2foot_y = sign[leg_index] * stride * interFuncY;

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

    double beta = (1.0 + sign[leg_index]) / 2.0 * M_PI / 2.0;

    legs.leg[leg_index].coxa = sign[leg_index] * M_PI / 2 - INIT_COXA_ANGLE[leg_index];
    legs.leg[leg_index].femur = beta - sign[leg_index] * roll - x;
    legs.leg[leg_index].tibia = x - y;
    legs.leg[leg_index].tarsus = y;

    legSafeControl(legs.leg[leg_index]);

    publishJointStates(legs);
    // ros::Duration(0.005).sleep();
  }
  posMeanFilter();
  publishSmoothPos(leg_index);
}

/*void Solution::legAfterRollPosCalculate(const int &leg_index, const double &roll, hexapod_msgs::LegJoints leg, geometry_msgs::Point &pos)
{
  double beta = (1 + sign[leg_index]) / 2 * M_PI / 2;

  pos.x = BODY_RADIUS * cos(INIT_COXA_ANGLE[leg_index]);
  pos.y = BODY_RADIUS * sin(INIT_COXA_ANGLE[leg_index]) +
          sign[leg_index] * (COXA_LENGTH + FEMUR_LENGTH * cos(leg.femur) + TIBIA_LENGTH * sin(leg.femur + leg.tibia) + TARSUS_LENGTH * sin(beta - sign[leg_index] * roll));
  pos.z = FEMUR_LENGTH * sin(leg.femur) - TIBIA_LENGTH * cos(leg.femur + leg.tibia) - TARSUS_LENGTH * sin(beta - sign[leg_index] * roll);
}*/

/*****************************************************
*                 %俯仰90°后计算位姿%                  * 
*           输入： 腿序、 俯仰角、 关节角、位姿           *
*                   输出： 位姿                       *
*****************************************************/
void Solution::legAfterRollPosCalculate(const int &leg_index, const double &roll, hexapod_msgs::LegJoints leg, geometry_msgs::Point &pos)
{
  double beta = (1 + sign[leg_index]) / 2 * M_PI / 2;

  pos.x = BODY_RADIUS * cos(INIT_COXA_ANGLE[leg_index]);
  pos.y = BODY_RADIUS * sin(INIT_COXA_ANGLE[leg_index]) +
          sign[leg_index] * (COXA_LENGTH + FEMUR_LENGTH * cos(leg.femur) + TIBIA_LENGTH * sin(leg.femur + leg.tibia) + TARSUS_LENGTH * sin(leg.femur + leg.tibia + leg.tarsus));
  pos.z = FEMUR_LENGTH * sin(leg.femur) - TIBIA_LENGTH * cos(leg.femur + leg.tibia) - TARSUS_LENGTH * cos(leg.femur + leg.tibia + leg.tarsus);
}

/*****************************************************************************
*                            %右腿上墙控制程序%                                 *
*           输入： 腿序、 初始位姿、 终止位姿、 俯仰脚、 关节角、 周期长度             *
*                              输出： 关节角                                    *
******************************************************************************/
void Solution::rightLeg2Wall(const int leg_index, const geometry_msgs::Point &initPos, const geometry_msgs::Point &finalPos, const double &roll, hexapod_msgs::LegsJoints &legs, const int cycle_length)
{
  float cycle_period = 0;
  while (cycle_period <= cycle_length)
  {
    geometry_msgs::Point pos;

    pos.x = initPos.x;

    double interFuncY = 1.0 / (1.0 + exp(-15.0 * (float(cycle_period) / cycle_length - 0.40)));
    pos.y = initPos.y + (finalPos.y - initPos.y) * interFuncY;

    double interFuncZ = 1.0 / (1.0 + exp(-15.0 * (float(cycle_period) / cycle_length - 0.65)));
    pos.z = initPos.z + (finalPos.z - initPos.z) * interFuncZ;

    double interFuncBeta = -1.0 / (1.0 + exp(-15.0 * (float(cycle_period) / cycle_length - 0.5)));
    double beta = M_PI / 2 * interFuncBeta;

    double A = pos.z + TARSUS_LENGTH * cos(beta - sign[leg_index] * roll);
    double B = sign[leg_index] * (pos.y - BODY_RADIUS * sin(INIT_COXA_ANGLE[leg_index])) - COXA_LENGTH - TARSUS_LENGTH * sin(beta - sign[leg_index] * roll);
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

    legs.leg[leg_index].coxa = sign[leg_index] * M_PI / 2 - INIT_COXA_ANGLE[leg_index];
    legs.leg[leg_index].femur = x;
    legSafeControl(legs.leg[leg_index]);
    legs.leg[leg_index].tibia = y - legs.leg[leg_index].femur;
    legSafeControl(legs.leg[leg_index]);
    legs.leg[leg_index].tarsus = beta - sign[leg_index] * roll - (legs.leg[leg_index].femur + legs.leg[leg_index].tibia);

    legSafeControl(legs.leg[leg_index]);

    publishJointStates(legs);
    //  ros::Duration(0.005).sleep();

    if (cycle_period < 0.5 * cycle_length || cycle_period > 0.8 * cycle_length)
      cycle_period += 2;
    else
      cycle_period += 0.5;
  }
  posMeanFilter();
  publishSmoothPos(leg_index);
}

/************************************
*           %螃蟹步态时预压函数%        *
*
*
**************************************/
void Solution::prePress(const int leg_index, const double &prePress, const double &roll, const int &cycle_length, hexapod_msgs::LegsJoints &legs)
{
  hexapod_msgs::LegJoints initLeg; //缓存初始关节角
  initLeg.coxa = legs.leg[leg_index].coxa;
  initLeg.femur = legs.leg[leg_index].femur;
  initLeg.tibia = legs.leg[leg_index].tibia;
  initLeg.tarsus = legs.leg[leg_index].tarsus;

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

    double beta = (1.0 + sign[leg_index]) / 2.0 * M_PI / 2.0;

    legs.leg[leg_index].coxa = sign[leg_index] * M_PI / 2 - INIT_COXA_ANGLE[leg_index];
    legs.leg[leg_index].femur = beta - sign[leg_index] * roll - x;
    legs.leg[leg_index].tibia = x - y;
    legs.leg[leg_index].tarsus = y;

    legSafeControl(legs.leg[leg_index]);

    publishJointStates(legs);
    // ros::Duration(0.005).sleep();
  }
  posMeanFilter();
  publishPrePressPos();
}

void Solution::leg2SpecialPrePress(const int leg_index, const double &prePress, const double &roll, const int &cycle_length, hexapod_msgs::LegsJoints &legs)
{
  {
    hexapod_msgs::LegJoints initLeg; //缓存初始关节角
    initLeg.coxa = legs.leg[leg_index].coxa;
    initLeg.femur = legs.leg[leg_index].femur;
    initLeg.tibia = legs.leg[leg_index].tibia;
    initLeg.tarsus = legs.leg[leg_index].tarsus;
    bool flag = true;

    for (int cycle_period = 0; cycle_period <= cycle_length; cycle_period++)
    {
      double interFuncX;
      double foot2foot_x;

      if (cycle_period <= 0.5 * cycle_length)
      {
        interFuncX = -0.5 * cos(2.0 * M_PI * cycle_period / cycle_length) + 0.5;
        foot2foot_x = (prePress + 0.02) * interFuncX;
      }
      else
      {
        if (flag)
        {
          initLeg.coxa = legs.leg[leg_index].coxa;
          initLeg.femur = legs.leg[leg_index].femur;
          initLeg.tibia = legs.leg[leg_index].tibia;
          initLeg.tarsus = legs.leg[leg_index].tarsus;
          flag = false;
        }
        interFuncX = -0.5 * cos(2.0 * M_PI * cycle_period / cycle_length) - 0.5;
        foot2foot_x = prePress * interFuncX;
      }

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

      double beta = (1.0 + sign[leg_index]) / 2.0 * M_PI / 2.0;

      legs.leg[leg_index].coxa = sign[leg_index] * M_PI / 2 - INIT_COXA_ANGLE[leg_index];
      legs.leg[leg_index].femur = beta - sign[leg_index] * roll - x;
      legs.leg[leg_index].tibia = x - y;
      legs.leg[leg_index].tarsus = y;

      legSafeControl(legs.leg[leg_index]);

      publishJointStates(legs);
      // ros::Duration(0.005).sleep();
    }
    posMeanFilter();
    publishPrePressPos();
  }
}

/************************************
*           %蜘蛛圆周步态预压函数(无俯仰时)%        *
*
*
**************************************/
void Solution::cyclePosPrePress(const int leg_index, const double &prePress, const int &cycle_length, hexapod_msgs::LegsJoints &legs)
{
  hexapod_msgs::LegJoints initLeg; //缓存初始关节角
  initLeg.coxa = legs.leg[leg_index].coxa;
  initLeg.femur = legs.leg[leg_index].femur;
  initLeg.tibia = legs.leg[leg_index].tibia;
  initLeg.tarsus = legs.leg[leg_index].tarsus;

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
    legs.leg[leg_index].femur = -x;
    legs.leg[leg_index].tibia = x - y;
    legs.leg[leg_index].tarsus = y;

    legSafeControl(legs.leg[leg_index]);

    publishJointStates(legs);
    // ros::Duration(0.005).sleep();
  }
  posMeanFilter();
  publishPrePressPos();
}

void Solution::posMeanFilter()
{
  int k = 100; //均值取点数
  for (int i = 0; i < 24; i++)
  {
    smoothPosBuffer[i].clear(); //清空均值平滑点缓存
  }

  //前面k个点直接存储
  for (int i = 0; i < k; i++)
  {
    for (int bufferIndex = 0; bufferIndex < 24; bufferIndex++)
    {
      smoothPosBuffer[bufferIndex].push_back(posBuffer[bufferIndex][i]);
    }
  }

  //k均值平滑处理
  for (int i = k; i < posBuffer[0].size() - k; i++)
  {
    for (int bufferIndex = 0; bufferIndex < 24; bufferIndex++)
    {
      smoothPosBuffer[bufferIndex].push_back(meanCalculate(bufferIndex, i, k));
    }
  }

  //尾数处理
  for (int i = posBuffer[0].size() - k; i < posBuffer[0].size(); i++)
  {
    for (int bufferIndex = 0; bufferIndex < 24; bufferIndex++)
    {
      smoothPosBuffer[bufferIndex].push_back(posBuffer[bufferIndex][i]);
    }
  }

  for (int i = 0; i < 24; i++)
  {
    posBuffer[i].clear(); //清空缓存
  }
}

double Solution::meanCalculate(const int bufferIndex, const int i, const int k)
{
  double result;
  double sum = posBuffer[bufferIndex][i];
  for (int j = 1; j <= k; j++)
  {
    sum = sum + posBuffer[bufferIndex][i - j] + posBuffer[bufferIndex][i + j];
  }
  result = sum / (2.0 * k + 1.0);
  return result;
}

void Solution::publishSmoothPos(const int leg_index)
{
  /* for (int i = 0; i < smoothPosBuffer[0].size(); i++)
  {
    for (int leg = 0; leg < 6; leg++)
    {
      leg_coxa[leg].data = smoothPosBuffer[leg * 4][i];
      leg_femur[leg].data = smoothPosBuffer[leg * 4 + 1][i];
      leg_tibia[leg].data = smoothPosBuffer[leg * 4 + 2][i];
      leg_tarsus[leg].data = smoothPosBuffer[leg * 4 + 3][i];
    }

    for (int leg = 0; leg < 6; leg++)
    {
      leg_coxa_p[leg].publish(leg_coxa[leg]);
      leg_femur_p[leg].publish(leg_femur[leg]);
      leg_tibia_p[leg].publish(leg_tibia[leg]);
      leg_tarsus_p[leg].publish(leg_tarsus[leg]);
    }

    ros::Duration(0.005).sleep();
  }*/
  ROS_INFO("size: %d", smoothPosBuffer[0].size());

  if (feedDrviers(leg_index) != true)
    ros::shutdown();
}

void Solution::publishPrePressPos()
{
  /*for (int i = 0; i < smoothPosBuffer[0].size(); i++)
  {
    for (int leg = 0; leg < 6; leg++)
    {
      leg_coxa[leg].data = smoothPosBuffer[leg * 4][i];
      leg_femur[leg].data = smoothPosBuffer[leg * 4 + 1][i];
      leg_tibia[leg].data = smoothPosBuffer[leg * 4 + 2][i];
      leg_tarsus[leg].data = smoothPosBuffer[leg * 4 + 3][i];
    }

    for (int leg = 0; leg < 6; leg++)
    {
      leg_coxa_p[leg].publish(leg_coxa[leg]);
      leg_femur_p[leg].publish(leg_femur[leg]);
      leg_tibia_p[leg].publish(leg_tibia[leg]);
      leg_tarsus_p[leg].publish(leg_tarsus[leg]);
    }

    ros::Duration(0.005).sleep();
  }*/
  ROS_INFO("size: %d", smoothPosBuffer[0].size());

  if (prePressFeedDrviers() != true)
    ros::shutdown();
}

bool Solution::feedDrviers(const int leg_index)
{
  maxpointsRequest();

  while (freeSpace < (sm_point_buf_size - 30)) //sm服务器buffer接近空时，进行吸盘控制
  {
    ros::Duration(3).sleep();
    maxpointsRequest();
  }

  if (!motionActive)
  {
    ROS_FATAL("Motion not active!");
    ros::shutdown();
    return false;
  }

  ros::Duration(2).sleep();

  stickControl(leg_index); //吸盘控制

  if (legControlHalf() != true) //发送前半个周期给服务器
    return false;

  maxpointsRequest();

  while (!bufferFree)
  {
    ros::Duration(3).sleep();
    maxpointsRequest();
  }

  if (!motionActive)
  {
    ROS_FATAL("Motion not active!");
    ros::shutdown();
    return false;
  }

  if (legControlRest() != true) //发送后半个周期给服务器
    return false;

  return true;
}

bool Solution::prePressFeedDrviers()
{
  ROS_INFO("-----Prepress-----");

  maxpointsRequest();

  while (freeSpace < (sm_point_buf_size - 30)) //sm服务器buffer接近空时，进行吸盘控制
  {
    ros::Duration(2).sleep();
    maxpointsRequest();
  }

  if (!motionActive)
  {
    ROS_FATAL("Motion not active!");
    ros::shutdown();
    return false;
  }

  //预压前发送io口控制
  stickSrv.request.chose = 2;
  int requestIO[7];
  for (int i = 0; i < 6; i++)
  {
    stickSrv.request.io[i] = 0;
    requestIO[i] = 0;
  }
  stickSrv.request.io[6] = requestIO[6] = 1;

  while (!stickClient.call(stickSrv))
  {
    ROS_WARN("Failed to call stick service. Retrying...");
    ros::Duration(2).sleep();
  }
  ROS_INFO("%s, request io: %d, %d, %d, %d, %d, %d", stickSrv.response.back.c_str(), requestIO[0], requestIO[1], requestIO[2], requestIO[3], requestIO[4], requestIO[5]);

  if (legControlHalf() != true) //发送前半个周期给服务器
    return false;

  maxpointsRequest();

  while (!bufferFree)
  {
    ros::Duration(2).sleep();
    maxpointsRequest();
  }

  if (!motionActive)
  {
    ROS_FATAL("Motion not active!");
    ros::shutdown();
    return false;
  }

  ros::Duration(5.0).sleep(); //确保气压从80以上降到80以下再回升
  //查看吸盘是否吸气完成
  while (!isStickDone(requestIO))
  {
    ros::Duration(3).sleep();
  }
  ROS_INFO("Prepress finished. ");

  if (legControlRest() != true) //发送后半个周期给服务器
    return false;

  return true;
}

void Solution::maxpointsRequest()
{
  maxpointsGoal.MODE = MAXPOINT_REQUEST;

  bool server_exists = hexapodClient.waitForServer(ros::Duration(5.0));
  while (!server_exists)
  {
    ROS_WARN("Could not connect to hexapod server, retrying...");
    server_exists = hexapodClient.waitForServer(ros::Duration(5.0));
  }
  hexapodClient.sendGoal(maxpointsGoal, boost::bind(&Solution::maxpoint_doneCb, this, _1, _2));

  bool finished = hexapodClient.waitForResult(ros::Duration(5.0));
  if (!finished)
  {
    ROS_WARN("Waiting for result...");
    finished = hexapodClient.waitForResult(ros::Duration(5.0));
    if (!finished)
    {
      ROS_WARN("Connecting failed.");
      ros::shutdown();
    }
  }
}

//关节控制回调函数，确认六足status/freespace/motionActive
void Solution::legcontrol_doneCb(const actionlib::SimpleClientGoalState &state, const hexapodservice::hexapodserviceResultConstPtr &result)
{
  ROS_INFO("Leg control: server responded with state[%s]", state.toString().c_str());
  motionActive = result->motionActive;
  int status = result->status;

  if (status != 1)
  {
    ROS_WARN("simplemotion status fault, status: %d", status);
    motionActive = false;
  }
}

//读取最大填充点回调函数
void Solution::maxpoint_doneCb(const actionlib::SimpleClientGoalState &state, const hexapodservice::hexapodserviceResultConstPtr &result)
{
  ROS_INFO("Request maxpoint: server responded with state[%s]", state.toString().c_str());
  motionActive = result->motionActive;
  int status = result->status;
  freeSpace = result->freespace;
  ROS_INFO("simple motion buffer free space: %d", freeSpace);

  if (status != 1)
  {
    ROS_WARN("simplemotion status fault, status: %d", status);
    motionActive = false;
  }

  if (freeSpace < 0.5 * smoothPosBuffer[0].size())
  {
    bufferFree = false;
  }
  else
  {
    bufferFree = true;
  }
}

bool Solution::legControlHalf()
{
  legGoal.MODE = ALLLEGS_CONTROL;
  legGoal.MAXPOINTS = 0.5 * smoothPosBuffer[0].size();
  ROS_INFO("half maxpoints: %d", legGoal.MAXPOINTS);

  for (int i = 0; i < 6; i++)
  {
    legGoal.ALLLEGS.leg[i].coxa.resize(legGoal.MAXPOINTS);
    legGoal.ALLLEGS.leg[i].femur.resize(legGoal.MAXPOINTS);
    legGoal.ALLLEGS.leg[i].tibia.resize(legGoal.MAXPOINTS);
    legGoal.ALLLEGS.leg[i].tarsus.resize(legGoal.MAXPOINTS);
  }

  for (int i = 0; i < legGoal.MAXPOINTS; i++)
  {
    for (int leg_index = 0; leg_index < 6; leg_index++)
    {
      legGoal.ALLLEGS.leg[leg_index].coxa[i] = round(4096.0 * (3005640.0 / 1300.0) * (smoothPosBuffer[leg_index * 4][i] / M_PI * 180.0) / 360.0);
      legGoal.ALLLEGS.leg[leg_index].femur[i] = round(4096.0 * (3005640.0 / 1300.0) * (-smoothPosBuffer[leg_index * 4 + 1][i] / M_PI * 180.0) / 360.0);
      legGoal.ALLLEGS.leg[leg_index].tibia[i] = round(4096.0 * (3005640.0 / 1300.0) * (-smoothPosBuffer[leg_index * 4 + 2][i] / M_PI * 180.0) / 360.0);
      legGoal.ALLLEGS.leg[leg_index].tarsus[i] = round(4096.0 * (3005640.0 / 1300.0) * (-smoothPosBuffer[leg_index * 4 + 3][i] / M_PI * 180.0) / 360.0);
    }
  }

  bool server_exists = hexapodClient.waitForServer(ros::Duration(5.0));
  while (!server_exists)
  {
    ROS_WARN("could not connect to server, retrying...");
    server_exists = hexapodClient.waitForServer(ros::Duration(5.0));
  }

  hexapodClient.sendGoal(legGoal, boost::bind(&Solution::legcontrol_doneCb, this, _1, _2));

  bool finished = hexapodClient.waitForResult(ros::Duration(5.0));
  if (!finished)
  {
    ROS_WARN("Waiting for result...");
    finished = hexapodClient.waitForResult(ros::Duration(5.0));
    if (!finished)
    {
      ROS_FATAL("Connecting failed.");
      ros::shutdown();
      return false;
    }
  }
  return true;
}

bool Solution::legControlRest()
{
  legGoal.MODE = ALLLEGS_CONTROL;
  legGoal.MAXPOINTS = smoothPosBuffer[0].size() - (int)(smoothPosBuffer[0].size() * 0.5);
  ROS_INFO("rest maxpoints: %d", legGoal.MAXPOINTS);

  for (int i = 0; i < 6; i++)
  {
    legGoal.ALLLEGS.leg[i].coxa.resize(legGoal.MAXPOINTS);
    legGoal.ALLLEGS.leg[i].femur.resize(legGoal.MAXPOINTS);
    legGoal.ALLLEGS.leg[i].tibia.resize(legGoal.MAXPOINTS);
    legGoal.ALLLEGS.leg[i].tarsus.resize(legGoal.MAXPOINTS);
  }

  for (int cnt = 0.5 * smoothPosBuffer[0].size(), i = 0; cnt < smoothPosBuffer[0].size(); cnt++, i++)
  {
    for (int leg_index = 0; leg_index < 6; leg_index++)
    {
      legGoal.ALLLEGS.leg[leg_index].coxa[i] = round(4096.0 * (3005640.0 / 1300.0) * (smoothPosBuffer[leg_index * 4][cnt] / M_PI * 180.0) / 360.0);
      legGoal.ALLLEGS.leg[leg_index].femur[i] = round(4096.0 * (3005640.0 / 1300.0) * (-smoothPosBuffer[leg_index * 4 + 1][cnt] / M_PI * 180.0) / 360.0);
      legGoal.ALLLEGS.leg[leg_index].tibia[i] = round(4096.0 * (3005640.0 / 1300.0) * (-smoothPosBuffer[leg_index * 4 + 2][cnt] / M_PI * 180.0) / 360.0);
      legGoal.ALLLEGS.leg[leg_index].tarsus[i] = round(4096.0 * (3005640.0 / 1300.0) * (-smoothPosBuffer[leg_index * 4 + 3][cnt] / M_PI * 180.0) / 360.0);
    }
  }

  bool server_exists = hexapodClient.waitForServer(ros::Duration(5.0));
  while (!server_exists)
  {
    ROS_WARN("could not connect to server, retrying...");
    server_exists = hexapodClient.waitForServer(ros::Duration(5.0));
  }

  hexapodClient.sendGoal(legGoal, boost::bind(&Solution::legcontrol_doneCb, this, _1, _2));

  bool finished = hexapodClient.waitForResult(ros::Duration(5.0));
  if (!finished)
  {
    ROS_WARN("Waiting for result...");
    finished = hexapodClient.waitForResult(ros::Duration(5.0));
    if (!finished)
    {
      ROS_FATAL("Connecting failed.");
      ros::shutdown();
      return false;
    }
  }
  return true;
}

//发布角度反馈给rviz同步显示
void Solution::sm_pos_Cb(const hexapodservice::legConstPtr &leg)
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

/*********************吸盘控制*****************************/

/*心跳包订阅程序， 订阅吸盘气压值和io口*/
void Solution::heartbagCallBack(const link_com::heartbagConstPtr &heartbag)
{
  kpa = heartbag->kpa;
  for (int i = 0; i < 7; i++)
  {
    io[i] = heartbag->io[i];
  }
}

/*吸盘控制，当io口和气压值均满足条件时返回true*/
bool Solution::isStickDone(const int requestIO[])
{
  for (int i = 0; i < 6; i++)
  {
    if (io[i] != requestIO[i])
    {
      ROS_FATAL("io is not correct!!");
      return false;
    }

    if (kpa > KPALIMIT)
    {
      ROS_INFO("Stick kpa is not enough.");
      return false;
    }

    return true;
  }
}

//吸盘控制，0-5对应1-6腿的io口，对应的吸盘放气
//6代表将所有io口设为0，即所有吸盘均吸气
void Solution::stickControl(const int leg_index)
{
  ROS_INFO("-----Stick Control-----");

  stickSrv.request.chose = 2;
  int requestIO[7];

  if (leg_index == 6)
  {
    for (int i = 0; i < 6; i++)
    {
      stickSrv.request.io[i] = 0;
      requestIO[i] = 0;
    }
  }
  else
  {
    for (int i = 0; i < 6; i++)
    {
      if (i == leg_index)
      {
        stickSrv.request.io[i] = 1;
        requestIO[i] = 1;
      }
      else
      {
        stickSrv.request.io[i] = 0;
        requestIO[i] = 0;
      }
    }
  }
  stickSrv.request.io[6] = requestIO[6] = 1;

  while (!stickClient.call(stickSrv))
  {
    ROS_WARN("Failed to call stick service. Retrying...");
    ros::Duration(2).sleep();
  }
  ROS_INFO("%s, request io: %d, %d, %d, %d, %d, %d", stickSrv.response.back.c_str(), requestIO[0], requestIO[1], requestIO[2], requestIO[3], requestIO[4], requestIO[5]);

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
