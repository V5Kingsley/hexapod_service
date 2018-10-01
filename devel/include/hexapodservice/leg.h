// Generated by gencpp from file hexapodservice/leg.msg
// DO NOT EDIT!


#ifndef HEXAPODSERVICE_MESSAGE_LEG_H
#define HEXAPODSERVICE_MESSAGE_LEG_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <hexapodservice/legjoint.h>

namespace hexapodservice
{
template <class ContainerAllocator>
struct leg_
{
  typedef leg_<ContainerAllocator> Type;

  leg_()
    : leg()  {
    }
  leg_(const ContainerAllocator& _alloc)
    : leg()  {
  (void)_alloc;
      leg.assign( ::hexapodservice::legjoint_<ContainerAllocator> (_alloc));
  }



   typedef boost::array< ::hexapodservice::legjoint_<ContainerAllocator> , 6>  _leg_type;
  _leg_type leg;




  typedef boost::shared_ptr< ::hexapodservice::leg_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::hexapodservice::leg_<ContainerAllocator> const> ConstPtr;

}; // struct leg_

typedef ::hexapodservice::leg_<std::allocator<void> > leg;

typedef boost::shared_ptr< ::hexapodservice::leg > legPtr;
typedef boost::shared_ptr< ::hexapodservice::leg const> legConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::hexapodservice::leg_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::hexapodservice::leg_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace hexapodservice

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'hexapodservice': ['/home/quan/hexapod_service_ws/src/hexapodservice/msg', '/home/quan/hexapod_service_ws/devel/share/hexapodservice/msg'], 'actionlib_msgs': ['/opt/ros/indigo/share/actionlib_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::hexapodservice::leg_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::hexapodservice::leg_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::hexapodservice::leg_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::hexapodservice::leg_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::hexapodservice::leg_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::hexapodservice::leg_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::hexapodservice::leg_<ContainerAllocator> >
{
  static const char* value()
  {
    return "77281f1f9c4cd29d21908d690db99185";
  }

  static const char* value(const ::hexapodservice::leg_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x77281f1f9c4cd29dULL;
  static const uint64_t static_value2 = 0x21908d690db99185ULL;
};

template<class ContainerAllocator>
struct DataType< ::hexapodservice::leg_<ContainerAllocator> >
{
  static const char* value()
  {
    return "hexapodservice/leg";
  }

  static const char* value(const ::hexapodservice::leg_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::hexapodservice::leg_<ContainerAllocator> >
{
  static const char* value()
  {
    return "hexapodservice/legjoint[6] leg\n\
\n\
================================================================================\n\
MSG: hexapodservice/legjoint\n\
float64 coxa\n\
float64 femur\n\
float64 tibia\n\
float64 tarsus\n\
";
  }

  static const char* value(const ::hexapodservice::leg_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::hexapodservice::leg_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.leg);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct leg_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::hexapodservice::leg_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::hexapodservice::leg_<ContainerAllocator>& v)
  {
    s << indent << "leg[]" << std::endl;
    for (size_t i = 0; i < v.leg.size(); ++i)
    {
      s << indent << "  leg[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::hexapodservice::legjoint_<ContainerAllocator> >::stream(s, indent + "    ", v.leg[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // HEXAPODSERVICE_MESSAGE_LEG_H
