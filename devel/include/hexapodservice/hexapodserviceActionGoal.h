// Generated by gencpp from file hexapodservice/hexapodserviceActionGoal.msg
// DO NOT EDIT!


#ifndef HEXAPODSERVICE_MESSAGE_HEXAPODSERVICEACTIONGOAL_H
#define HEXAPODSERVICE_MESSAGE_HEXAPODSERVICEACTIONGOAL_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>
#include <actionlib_msgs/GoalID.h>
#include <hexapodservice/hexapodserviceGoal.h>

namespace hexapodservice
{
template <class ContainerAllocator>
struct hexapodserviceActionGoal_
{
  typedef hexapodserviceActionGoal_<ContainerAllocator> Type;

  hexapodserviceActionGoal_()
    : header()
    , goal_id()
    , goal()  {
    }
  hexapodserviceActionGoal_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , goal_id(_alloc)
    , goal(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef  ::actionlib_msgs::GoalID_<ContainerAllocator>  _goal_id_type;
  _goal_id_type goal_id;

   typedef  ::hexapodservice::hexapodserviceGoal_<ContainerAllocator>  _goal_type;
  _goal_type goal;





  typedef boost::shared_ptr< ::hexapodservice::hexapodserviceActionGoal_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::hexapodservice::hexapodserviceActionGoal_<ContainerAllocator> const> ConstPtr;

}; // struct hexapodserviceActionGoal_

typedef ::hexapodservice::hexapodserviceActionGoal_<std::allocator<void> > hexapodserviceActionGoal;

typedef boost::shared_ptr< ::hexapodservice::hexapodserviceActionGoal > hexapodserviceActionGoalPtr;
typedef boost::shared_ptr< ::hexapodservice::hexapodserviceActionGoal const> hexapodserviceActionGoalConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::hexapodservice::hexapodserviceActionGoal_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::hexapodservice::hexapodserviceActionGoal_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace hexapodservice

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'hexapodservice': ['/home/sun/hexapod_service_ws/src/hexapodservice/msg', '/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg'], 'actionlib_msgs': ['/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::hexapodservice::hexapodserviceActionGoal_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::hexapodservice::hexapodserviceActionGoal_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::hexapodservice::hexapodserviceActionGoal_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::hexapodservice::hexapodserviceActionGoal_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::hexapodservice::hexapodserviceActionGoal_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::hexapodservice::hexapodserviceActionGoal_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::hexapodservice::hexapodserviceActionGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "cc03a023749cee818edcce65f3a89798";
  }

  static const char* value(const ::hexapodservice::hexapodserviceActionGoal_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xcc03a023749cee81ULL;
  static const uint64_t static_value2 = 0x8edcce65f3a89798ULL;
};

template<class ContainerAllocator>
struct DataType< ::hexapodservice::hexapodserviceActionGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "hexapodservice/hexapodserviceActionGoal";
  }

  static const char* value(const ::hexapodservice::hexapodserviceActionGoal_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::hexapodservice::hexapodserviceActionGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
\n\
Header header\n\
actionlib_msgs/GoalID goal_id\n\
hexapodserviceGoal goal\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n\
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
\n\
================================================================================\n\
MSG: actionlib_msgs/GoalID\n\
# The stamp should store the time at which this goal was requested.\n\
# It is used by an action server when it tries to preempt all\n\
# goals that were requested before a certain time\n\
time stamp\n\
\n\
# The id provides a way to associate feedback and\n\
# result message with specific goal requests. The id\n\
# specified must be unique.\n\
string id\n\
\n\
\n\
================================================================================\n\
MSG: hexapodservice/hexapodserviceGoal\n\
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
int32 MODE \n\
int32 SIMPLEMOTION_MODE\n\
int32 MAXPOINTS\n\
int32 LEG_INDEX\n\
hexapodservice/legjoints ONELEG\n\
hexapodservice/legs ALLLEGS\n\
\n\
================================================================================\n\
MSG: hexapodservice/legjoints\n\
int64[] coxa\n\
int64[] femur\n\
int64[] tibia\n\
int64[] tarsus\n\
\n\
================================================================================\n\
MSG: hexapodservice/legs\n\
hexapodservice/legjoints[6] leg\n\
";
  }

  static const char* value(const ::hexapodservice::hexapodserviceActionGoal_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::hexapodservice::hexapodserviceActionGoal_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.goal_id);
      stream.next(m.goal);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct hexapodserviceActionGoal_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::hexapodservice::hexapodserviceActionGoal_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::hexapodservice::hexapodserviceActionGoal_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "goal_id: ";
    s << std::endl;
    Printer< ::actionlib_msgs::GoalID_<ContainerAllocator> >::stream(s, indent + "  ", v.goal_id);
    s << indent << "goal: ";
    s << std::endl;
    Printer< ::hexapodservice::hexapodserviceGoal_<ContainerAllocator> >::stream(s, indent + "  ", v.goal);
  }
};

} // namespace message_operations
} // namespace ros

#endif // HEXAPODSERVICE_MESSAGE_HEXAPODSERVICEACTIONGOAL_H
