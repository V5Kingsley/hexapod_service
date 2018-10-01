/*****************************************
 *                   六足服务器程序                                    *
 *                   Copyright (c) V5_Lab, 2018                  *
 *                   Author:                               *
 *                   Version number:  0.00                         *
 *                   Date:                                                      *
 * ***************************************/
#include <ros/ros.h>
#include <simplemotion.h>
#include <hexapodservice/hexapodserviceAction.h>
#include <actionlib/server/simple_action_server.h>
#include <hexapodservice/legs.h>
#include <hexapodservice/legjoints.h>
#include "define.h"
#include "bufferedmotion.h"

class Hexapodservice
{
private:
  ros::NodeHandle nh_;
  actionlib::SimpleActionServer<hexapodservice::hexapodserviceAction> as_;
  hexapodservice::hexapodserviceGoal goal_;
  hexapodservice::hexapodserviceResult result_;
  hexapodservice::hexapodserviceFeedback feedback_;
  hexapodservice::legjoints oneleg_;
  hexapodservice::legs legs_[6];
  smbus bushandle;
  smint32 Temp;
  BufferedMotionAxis axis[24];
  bool motionActive;
public:
  Hexapodservice();
  ~Hexapodservice(){};
  smint32 pulseout_[24];
  smint32 pulsefb_[24];
  void executeCB(const actionlib::SimpleActionServer<hexapodservice::hexapodserviceAction>::GoalConstPtr& goal);
  void singlejoint2motor(const float pos, smint32 *pulse);
//   bool velControl(smint32 pulse[4], smint32 vel[4]);
  smint32 MaxVel;
  std::vector<int32_t> pointsBuf[24];
  smint32 smPosFb[24][64];
  smint32 smPosFbAmount[24];
  void spinOnce();
};

Hexapodservice::Hexapodservice(): as_(nh_, "hexapodservice", boost::bind(&Hexapodservice::executeCB, this, _1), false)
{
  as_.start();
  ROS_INFO("hexapod service started.");
  bushandle = -1;
  pulseout_[4] = {0};
  MaxVel = 10000;
  motionActive = false;
  
  for(int i=0; i<24; i++)
  {
    pointsBuf[i].reserve(3000);
    pointsBuf[i].clear();
    ROS_INFO("hexapod pointBuf[%d] capacity:%d, size:%d", i, (int)pointsBuf[i].capacity(), (int)pointsBuf[i].size());
  }
}

void Hexapodservice::singlejoint2motor(const float pos, smint32* pulse)
{
  *pulse = round(4096*(3005640.0/1300.0)*pos/360.0);
}

/*bool Hexapodservice::velControl(smint32* pulse, smint32* vel)
{
  smint32 max_pulse;
  max_pulse = pulse[0];
  float t = 1.0f;
  int i = 0;
 
  for (i = 1; i < 4; i ++)
  {
    max_pulse = (max_pulse >= pulse[i] ? max_pulse : pulse[i] );
  }
  
  if ( max_pulse == 0) 
  {
    return false;
  }
  else
  {
//     MaxVel = max_pulse / 0.1;
    t = max_pulse / (float)MaxVel;
    for(i = 0; i < 4; i ++)
    {
      vel[i] = pulse[i] / t;
    }
    return true;
  }
}*/

void Hexapodservice::executeCB(const actionlib::SimpleActionServer< hexapodservice::hexapodserviceAction >::GoalConstPtr& goal)
{
  //simplemotion 控制, 开总线，使能电机，初始化总线等
  if (goal->MODE == SIMPLEMOTION_CONTROL)
  {
    switch(goal->SIMPLEMOTION_MODE)
    {
      //开总线
      case OPENBUS:{
	bushandle = smOpenBus("/dev/ttyUSB0");
	if(bushandle<0)
	{
	  ROS_WARN("Open bus error!");
	  result_.result = "Open bus error!";
	  as_.setAborted(result_);
	}
	else
	{
	  ROS_INFO("Open bus succeeded.");
	  result_.result = "Open bus succeeded.";
	  result_.status = getCumulativeStatus(bushandle);
	  ROS_INFO("simplemotion status: %d", result_.status);
	  as_.setSucceeded(result_);  
	}
      }
      break;
      
      //关总线
      case CLOSEBUS:{
	smCloseBus(bushandle);
	ROS_INFO("Closed bus.");
	result_.result = "Closed bus.";
	result_.status = getCumulativeStatus(bushandle);
	ROS_INFO("simplemotion status: %d", result_.status);
	as_.setSucceeded(result_);  
      }
      break;
      
      //使能电机
      case ENABLEMOTOR:{
	for(int i=1; i<25; i++ )
	{
	  smSetParameter(bushandle, i, SMP_CONTROL_BITS1, 33);
	}
	result_.status = getCumulativeStatus(bushandle);
	ROS_INFO("simplemotion status: %d", result_.status);
	if (result_.status == 1)
	{
	  result_.result = "enable motor finished";
	  as_.setSucceeded(result_);  
	}
	else
	{
	  result_.result = "enable motor failed";
	  as_.setAborted(result_);  
	}
      }
      break;
      
      
      //关电机
      case DISABLEMOTOR:{
	for(int i=1; i<25; i++ )
	{
	  smSetParameter(bushandle, i, SMP_CONTROL_BITS1, 0);
	}
	 result_.status = getCumulativeStatus(bushandle);
	 if(result_.status == 1)
	 {
	   result_.result = "disable motor finished";
	   as_.setSucceeded(result_);  
	}
	else
	{
	  result_.result = "disable motor failed";
	  as_.setAborted(result_);  
	}
      }
      break;
      
      //初始化总线
      case INITAXIS:{
	for( int i = 0; i < 24; i++ )
	{
	  smBufferedInit(&axis[i], bushandle, i+1, SAMPLE_RATE, SMP_ACTUAL_POSITION_FB, SM_RETURN_VALUE_24B);
	  smAppendSMCommandToQueue(bushandle, SM_SET_WRITE_ADDRESS, SMP_TRAJ_PLANNER_VEL);
          smAppendSMCommandToQueue(bushandle, SM_WRITE_VALUE_32B, 10000); //速度设置为10000
          smExecuteCommandQueue(bushandle, i+1);
          smGetQueuedSMCommandReturnValue(bushandle, &Temp);
          smGetQueuedSMCommandReturnValue(bushandle, &Temp);
	}
	result_.status = getCumulativeStatus(bushandle);
	if(result_.status == 1)
	{
	  result_.result = "Init axis finished.";
	  as_.setSucceeded(result_);
	  motionActive = true;
	}
	else
	{
	  result_.result = "Init axis failed.";
	  as_.setAborted(result_);
	  motionActive = false;
	}
      }
      break;
      
      //获取simplemotion状态值
      case GETSTATUS:{
	result_.status = getCumulativeStatus(bushandle);
	boost::format result_fm = boost::format("simplemotion status: %d") % result_.status;
	result_.result = result_fm.str();
	as_.setSucceeded(result_);
      }
      break;
      
      
      //清楚错误
      case CLEARFAULT:{
	for(int i=1; i<25; i++)
	{
	  smSetParameter(bushandle, i, SMP_FAULTS, 0);
	}
	if(result_.status == 1)
	{
	  result_.result = "clear fault  finished";
	  as_.setSucceeded(result_);  
	}
	else
	{
	  result_.result = "clear fault  failed";
	  as_.setAborted(result_);  
	}
      }
      break;
      
      
      //关节复位，控制速度为5000
      case ALLLEGRESET:{
	for(int i=0; i<24; i++)
	{
	  smAppendSMCommandToQueue(bushandle, SM_SET_WRITE_ADDRESS, SMP_TRAJ_PLANNER_VEL);
	  smAppendSMCommandToQueue(bushandle, SM_WRITE_VALUE_32B, 5000);
	  smAppendSMCommandToQueue(bushandle, SM_SET_WRITE_ADDRESS, SMP_ABSOLUTE_POS_TARGET);
          smAppendSMCommandToQueue(bushandle, SM_WRITE_VALUE_32B, 0);
          smAppendSMCommandToQueue(bushandle, SM_SET_WRITE_ADDRESS, SMP_RETURN_PARAM_ADDR);
          smAppendSMCommandToQueue(bushandle, SM_WRITE_VALUE_24B, SMP_ACTUAL_POSITION_FB);
          smExecuteCommandQueue(bushandle, i+1);
          smGetQueuedSMCommandReturnValue(bushandle, &Temp);
          smGetQueuedSMCommandReturnValue(bushandle, &Temp);
          smGetQueuedSMCommandReturnValue(bushandle, &Temp);
	  smGetQueuedSMCommandReturnValue(bushandle, &Temp);
          smGetQueuedSMCommandReturnValue(bushandle, &Temp);
          smGetQueuedSMCommandReturnValue(bushandle, &pulsefb_[i]);
	}
	result_.status = getCumulativeStatus(bushandle);
	if(result_.status == 1)
	{
	  result_.result = "Reseting all legs...";
          as_.setSucceeded(result_);
	}
	else
	{
	  result_.result = "Reseting all legs failed.";
	  as_.setAborted(result_);
	}
      }
      break;
      
      //清空buffer
      case ABORTMOTION:
      {
	for(int i = 0; i < 24; i++)
	{
	  smBufferedAbort(&axis[i]);
	  smBufferedDeinit(&axis[i]);
	}
	for(int i=0; i<24; i++)
	{
	  pointsBuf[i].clear();
	}
	result_.status = getCumulativeStatus(bushandle);
	if(result_.status == 1)
	{
	  result_.result = "Aborting motion and deinitializing axis..";
	  as_.setSucceeded(result_);
	  motionActive = false;
	}
	else
	{
	  result_.result = "Aborting motion and deinitializing axis failed";
	  as_.setAborted(result_);
	}
      }
      break;
      
      //读取所有电机编码器反馈
      case READALLLEGS:
      {
	for(int i = 0; i < 24; i++)
        {
          smAppendSMCommandToQueue(bushandle, SM_SET_WRITE_ADDRESS, SMP_RETURN_PARAM_ADDR);
          smAppendSMCommandToQueue(bushandle, SM_WRITE_VALUE_24B, SMP_ACTUAL_POSITION_FB);
          smExecuteCommandQueue(bushandle, i+1);
          smGetQueuedSMCommandReturnValue(bushandle, &Temp);
          smGetQueuedSMCommandReturnValue(bushandle, &pulsefb_[i]);
    //      std::cout<<"motor"<<i<<" "<<pulsefb_[i]<<std::endl;
        }
        for(int leg_index = 0; leg_index < 6; leg_index++)
        {
          result_.ALLLEGS_fdbk.leg[leg_index].coxa = pulsefb_[4*leg_index]*360.0/4096.0/(3005640.0/1300.0);
          result_.ALLLEGS_fdbk.leg[leg_index].femur = pulsefb_[4*leg_index+1]*360.0/4096.0/(3005640.0/1300.0);
          result_.ALLLEGS_fdbk.leg[leg_index].tibia = pulsefb_[4*leg_index+2]*360.0/4096.0/(3005640.0/1300.0);
          result_.ALLLEGS_fdbk.leg[leg_index].tarsus = pulsefb_[4*leg_index+3]*360.0/4096.0/(3005640.0/1300.0);
        }
        result_.status = getCumulativeStatus(bushandle);
        if(result_.status == 1)
        {
          result_.result = "Read all motor succeeded.";
          as_.setSucceeded(result_);
        }
        else
        {
          result_.result = "Read all motor failed.";
          as_.setAborted(result_);
        }
      }
      break;
      
    }
  }
  
  
  //控制一条腿
  if (goal->MODE == ONELEG_CONTROL)
  {
    smint32 positions[4][64];
    smint32 readData[4][64];
    smint32 readDataAmount[4];
    
    int total_num = goal->MAXPOINTS;
    int leg_index = goal->LEG_INDEX;
    int remain_num = goal->MAXPOINTS;
    int length = sizeof(goal->ONELEG.coxa[total_num]);
    ROS_INFO("size: %d");
    
    smint32 freeSpace;
    smBufferedGetFree(&axis[leg_index*4], &freeSpace);
    int maxpoints = smBufferedGetMaxFillSize(&axis[leg_index*4], freeSpace);
    int minimumBufferFreeBytes = axis[leg_index*4].bufferLength - 0.9 * axis[leg_index*4].bufferLength;
     
    while(remain_num!=0)
    {
      smBufferedGetFree(&axis[leg_index*4], &freeSpace);
      maxpoints = smBufferedGetMaxFillSize(&axis[leg_index*4], freeSpace);
      while(maxpoints>=1 && freeSpace>=minimumBufferFreeBytes)
      {
        maxpoints = (maxpoints < remain_num ? maxpoints : remain_num);
        ROS_INFO("maxpoints: %d", maxpoints);
        for ( int i = 0; i < maxpoints; i++ )
        {
          positions[0][i] = goal->ONELEG.coxa[i+total_num-remain_num];
          positions[1][i] = goal->ONELEG.femur[i+total_num-remain_num];
          positions[2][i] = goal->ONELEG.tibia[i+total_num-remain_num];
          positions[3][i] = goal->ONELEG.tarsus[i+total_num-remain_num];
        }
      //发总线
        smint32 bytesFilled;
        for(int i=0; i<4; i++)
       {
        smBufferedFillAndReceive(&axis[leg_index*4+i], maxpoints, positions[i], &readDataAmount[0], readData[0], &bytesFilled);
       }
        smBufferedRunAndSyncClocks(&axis[leg_index*4]); 
        remain_num = remain_num - maxpoints;
        if(remain_num==0)
        {
          ROS_INFO("one leg control done.");
          break;
        }
        else
        {
	  smBufferedGetFree(&axis[leg_index*4], &freeSpace);
          maxpoints = smBufferedGetMaxFillSize(&axis[leg_index*4], freeSpace);
        }
         result_.status = getCumulativeStatus(bushandle);
         if(result_.status!=1)
         {
           ROS_FATAL("ERROR");
           break;
         }
        ros::Duration(0.02).sleep();
      }
    }

    result_.status = getCumulativeStatus(bushandle);
    result_.motionActive = motionActive;
    if (result_.status == 1 && motionActive == true)
    {
      as_.setSucceeded(result_);
    }
    else
    {
      as_.setAborted(result_);
    }
  }
  
  //控制六条腿
  if(goal->MODE == ALLLEGS_CONTROL)
  {
    smint32 positions[24][64];
    smint32 readData[24][64];
    smint32 readDataAmount[24];
    int maxpoints = goal->MAXPOINTS;
    
    //填充24个电机buffer
    for ( int leg_index = 0; leg_index < 6; leg_index++ )
    {
      for ( int j = 0; j < maxpoints; j++ )
      {
	pointsBuf[leg_index*4].push_back(goal->ALLLEGS.leg[leg_index].coxa[j]);
	pointsBuf[leg_index*4+1].push_back(goal->ALLLEGS.leg[leg_index].femur[j]);
	pointsBuf[leg_index*4+2].push_back(goal->ALLLEGS.leg[leg_index].tibia[j]);
	pointsBuf[leg_index*4+3].push_back(goal->ALLLEGS.leg[leg_index].tarsus[j]);
      }
    }

    //反馈编码器信息
    for(int leg_index = 0; leg_index < 6; leg_index++)
    {
      /*
      result_.ALLLEGS_fdbk.leg[leg_index].coxa = readData[4*leg_index][readDataAmount[4*leg_index]-1]/4096.0/(3005640.0/1300.0)*360.0/180.0*M_PI;
      result_.ALLLEGS_fdbk.leg[leg_index].femur = readData[4*leg_index+1][readDataAmount[4*leg_index+1]-1]/4096.0/(3005640.0/1300.0)*360.0/180.0*M_PI;
      result_.ALLLEGS_fdbk.leg[leg_index].tibia = readData[4*leg_index+2][readDataAmount[4*leg_index+2]-1]/4096.0/(3005640.0/1300.0)*360.0/180.0*M_PI;
      result_.ALLLEGS_fdbk.leg[leg_index].tarsus = readData[4*leg_index+3][readDataAmount[4*leg_index+3]-1]/4096.0/(3005640.0/1300.0)*360.0/180.0*M_PI;
      */
      result_.ALLLEGS_fdbk.leg[leg_index].coxa = readData[4*leg_index][readDataAmount[4*leg_index]-1]*0.00000066347767;
      result_.ALLLEGS_fdbk.leg[leg_index].femur = readData[4*leg_index+1][readDataAmount[4*leg_index+1]-1]*0.00000066347767;
      result_.ALLLEGS_fdbk.leg[leg_index].tibia = readData[4*leg_index+2][readDataAmount[4*leg_index+2]-1]*0.00000066347767;
      result_.ALLLEGS_fdbk.leg[leg_index].tarsus = readData[4*leg_index+3][readDataAmount[4*leg_index+3]-1]*0.00000066347767;
    }
 
    as_.setSucceeded(result_);
  }
  
  //一条腿复位
  if(goal->MODE == ONELEG_RESET)
  {

  }
  
  //六条腿复位
  if(goal->MODE == ALLLEGS_RESET)
  {
    
  }
  
  //get maxpoints
  if( goal->MODE == MAXPOINT_REQUEST )
  {   
    if(pointsBuf[0].size()<2500)
    {
      result_.freespace = 500;
      result_.maxpoints = 500;
      result_.minimumBufferFreeBytes = 500;
      result_.status = 1;  
    }
    else
    {
      result_.freespace = 0;
      result_.maxpoints = 0;
      result_.minimumBufferFreeBytes = 0;
      result_.status = 1;  
    }

    result_.motionActive = motionActive;
    if(result_.status == 1)
    {
      as_.setSucceeded(result_);
    }
    else
    {
      as_.setAborted(result_);
    }
  }
  
  //读取所有电机编码器反馈
  if( goal->MODE == READ_ALL_LEGS )
  {
    for(int i = 0; i < 24; i++)
    {
      smAppendSMCommandToQueue(bushandle, SM_SET_WRITE_ADDRESS, SMP_RETURN_PARAM_ADDR);
      smAppendSMCommandToQueue(bushandle, SM_WRITE_VALUE_24B, SMP_ACTUAL_POSITION_FB);
      smExecuteCommandQueue(bushandle, i+1);
      smGetQueuedSMCommandReturnValue(bushandle, &Temp);
      smGetQueuedSMCommandReturnValue(bushandle, &pulsefb_[i]);
      std::cout<<"motor"<<i<<" "<<pulsefb_[i]<<std::endl;
    }
    for(int leg_index = 0; leg_index < 6; leg_index++)
    {
      result_.ALLLEGS_fdbk.leg[leg_index].coxa = pulsefb_[4*leg_index]*360.0/4096.0/(3005640.0/1300.0);
      result_.ALLLEGS_fdbk.leg[leg_index].femur = pulsefb_[4*leg_index+1]*360.0/4096.0/(3005640.0/1300.0);
      result_.ALLLEGS_fdbk.leg[leg_index].tibia = pulsefb_[4*leg_index+2]*360.0/4096.0/(3005640.0/1300.0);
      result_.ALLLEGS_fdbk.leg[leg_index].tarsus = pulsefb_[4*leg_index+3]*360.0/4096.0/(3005640.0/1300.0);
    }
    result_.status = getCumulativeStatus(bushandle);
    if(result_.status == 1)
    {
      result_.result = "Read all motor succeeded.";
      as_.setSucceeded(result_);
    }
    else
    {
      result_.result = "Read all motor failed.";
      as_.setAborted(result_);
    }
  }
  
}

void Hexapodservice::spinOnce()
{
  smint32 positions[24][64];
  smint32 readData[24][64];
  smint32 readDataAmount[24];
  int maxpoints = 0;
      
  //填充24个电机buffer
  if(pointsBuf[0].size()>0)
  {
    smint32 freeSpace;
    smBufferedGetFree(&axis[0], &freeSpace);
    maxpoints = smBufferedGetMaxFillSize(&axis[0], freeSpace);
    int minimumBufferFreeBytes = axis[0].bufferLength - 0.9 * axis[0].bufferLength;
    int32_t smStatus = getCumulativeStatus(bushandle);
    
    if(pointsBuf[0].size()< maxpoints)
    {
      maxpoints = pointsBuf[0].size();
    }
    
    for ( int leg_index = 0; leg_index < 6; leg_index++ )
    {
      for ( int j = 0; j < maxpoints; j++ )
      {
	positions[leg_index*4][j] = pointsBuf[leg_index*4][j];
	positions[leg_index*4+1][j] = pointsBuf[leg_index*4+1][j];
	positions[leg_index*4+2][j] = pointsBuf[leg_index*4+2][j];
	positions[leg_index*4+3][j] = pointsBuf[leg_index*4+3][j];
      }   
    }
    
    for(int i=0; i<24; i++)
    {
      pointsBuf[i].erase(pointsBuf[i].begin(),pointsBuf[i].begin()+maxpoints);
    }
    
    //将buffer发给总线
    smint32 bytesFilled;
    for(int i=0; i<24; i++)
    {
      smint32 Temp;
      //smBufferedFillAndReceive(&axis[i], maxpoints, positions[i], &readDataAmount[i], readData[i], &bytesFilled);
      smBufferedFillAndReceive(&axis[i], maxpoints, positions[i], &smPosFbAmount[i], smPosFb[i], &bytesFilled);
    }
    
      
    //----synchronize clocks of all devices to the current value of first axis----//
    smBufferedRunAndSyncClocks(&axis[0]);  
    smStatus = getCumulativeStatus(bushandle); 
    if(smStatus!=1)
    {
      motionActive = false;
    }
  }    
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "hexapod_service_node");
  ROS_INFO("instantiating the hexapod service");
  Hexapodservice as_object;
  ROS_INFO("going in to spin");
  ros::Rate loop_rate(50);
  while(ros::ok())
  {
    as_object.spinOnce();
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
