#ifndef GAI_H_
#define GAI_H_

#include <cmath>
#include <algorithm>
#include <ros/ros.h>
#include <hexapod_msgs/FeetPositions.h>
#include <geometry_msgs/Pose2D.h>
#include <geometry_msgs/Twist.h>

class Gait
{
public:
  Gait(void);
  void gaitCycle(const geometry_msgs::Twist &cmd_vel, hexapod_msgs::FeetPositions *feet); //摆动腿和支撑腿切换
  int cycle_period_;
  std::vector<int> cycle_leg_number_;
  bool start_cycle;
  bool is_travelling_;
  geometry_msgs::Pose2D smooth_base_;
  bool hexapod_stop_flag;

private:
  void cyclePeriod(const geometry_msgs::Pose2D &base, hexapod_msgs::FeetPositions *feet); //每条摆动腿和支撑腿一个周期内的步幅控制
  int CYCLE_LENGTH_ORIGIN;
  int CYCLE_LENGTH;
  int LIFT_LENGTH;
  int MOVE_LENGTH;
  int DROP_LENGTH;
  int NUMBER_OF_LEGS;
  double LEG_LIFT_HEIGHT;
  bool stop_cycle_;
  geometry_msgs::Pose2D base;
  double period_seg;
  double linear_x_max;
  double linear_y_max;
  double angular_z_max;
};

#endif
