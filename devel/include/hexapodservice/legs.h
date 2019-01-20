// Generated by gencpp from file hexapodservice/legs.msg
// DO NOT EDIT!


#ifndef HEXAPODSERVICE_MESSAGE_LEGS_H
#define HEXAPODSERVICE_MESSAGE_LEGS_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <hexapodservice/legjoints.h>

namespace hexapodservice
{
template <class ContainerAllocator>
struct legs_
{
  typedef legs_<ContainerAllocator> Type;

  legs_()
    : leg()  {
    }
  legs_(const ContainerAllocator& _alloc)
    : leg()  {
  (void)_alloc;
      leg.assign( ::hexapodservice::legjoints_<ContainerAllocator> (_alloc));
  }



   typedef boost::array< ::hexapodservice::legjoints_<ContainerAllocator> , 6>  _leg_type;
  _leg_type leg;





  typedef boost::shared_ptr< ::hexapodservice::legs_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::hexapodservice::legs_<ContainerAllocator> const> ConstPtr;

}; // struct legs_

typedef ::hexapodservice::legs_<std::allocator<void> > legs;

typedef boost::shared_ptr< ::hexapodservice::legs > legsPtr;
typedef boost::shared_ptr< ::hexapodservice::legs const> legsConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::hexapodservice::legs_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::hexapodservice::legs_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace hexapodservice

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'hexapodservice': ['/home/sun/hexapod_service_ws/src/hexapodservice/msg', '/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg'], 'actionlib_msgs': ['/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::hexapodservice::legs_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::hexapodservice::legs_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::hexapodservice::legs_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::hexapodservice::legs_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::hexapodservice::legs_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::hexapodservice::legs_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::hexapodservice::legs_<ContainerAllocator> >
{
  static const char* value()
  {
    return "283042c2b49d709689847698830e74a9";
  }

  static const char* value(const ::hexapodservice::legs_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x283042c2b49d7096ULL;
  static const uint64_t static_value2 = 0x89847698830e74a9ULL;
};

template<class ContainerAllocator>
struct DataType< ::hexapodservice::legs_<ContainerAllocator> >
{
  static const char* value()
  {
    return "hexapodservice/legs";
  }

  static const char* value(const ::hexapodservice::legs_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::hexapodservice::legs_<ContainerAllocator> >
{
  static const char* value()
  {
    return "hexapodservice/legjoints[6] leg\n\
\n\
================================================================================\n\
MSG: hexapodservice/legjoints\n\
int64[] coxa\n\
int64[] femur\n\
int64[] tibia\n\
int64[] tarsus\n\
";
  }

  static const char* value(const ::hexapodservice::legs_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::hexapodservice::legs_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.leg);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct legs_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::hexapodservice::legs_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::hexapodservice::legs_<ContainerAllocator>& v)
  {
    s << indent << "leg[]" << std::endl;
    for (size_t i = 0; i < v.leg.size(); ++i)
    {
      s << indent << "  leg[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::hexapodservice::legjoints_<ContainerAllocator> >::stream(s, indent + "    ", v.leg[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // HEXAPODSERVICE_MESSAGE_LEGS_H
