// Generated by gencpp from file hexapodservice/hexapodserviceResult.msg
// DO NOT EDIT!


#ifndef HEXAPODSERVICE_MESSAGE_HEXAPODSERVICERESULT_H
#define HEXAPODSERVICE_MESSAGE_HEXAPODSERVICERESULT_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <hexapodservice/legjoint.h>
#include <hexapodservice/leg.h>

namespace hexapodservice
{
template <class ContainerAllocator>
struct hexapodserviceResult_
{
  typedef hexapodserviceResult_<ContainerAllocator> Type;

  hexapodserviceResult_()
    : ONELEG_fdbk()
    , ALLLEGS_fdbk()
    , result()
    , status(0)
    , freespace(0)
    , minimumBufferFreeBytes(0)
    , maxpoints(0)
    , motionActive(false)  {
    }
  hexapodserviceResult_(const ContainerAllocator& _alloc)
    : ONELEG_fdbk(_alloc)
    , ALLLEGS_fdbk(_alloc)
    , result(_alloc)
    , status(0)
    , freespace(0)
    , minimumBufferFreeBytes(0)
    , maxpoints(0)
    , motionActive(false)  {
  (void)_alloc;
    }



   typedef  ::hexapodservice::legjoint_<ContainerAllocator>  _ONELEG_fdbk_type;
  _ONELEG_fdbk_type ONELEG_fdbk;

   typedef  ::hexapodservice::leg_<ContainerAllocator>  _ALLLEGS_fdbk_type;
  _ALLLEGS_fdbk_type ALLLEGS_fdbk;

   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _result_type;
  _result_type result;

   typedef int32_t _status_type;
  _status_type status;

   typedef int64_t _freespace_type;
  _freespace_type freespace;

   typedef int64_t _minimumBufferFreeBytes_type;
  _minimumBufferFreeBytes_type minimumBufferFreeBytes;

   typedef int32_t _maxpoints_type;
  _maxpoints_type maxpoints;

   typedef uint8_t _motionActive_type;
  _motionActive_type motionActive;




  typedef boost::shared_ptr< ::hexapodservice::hexapodserviceResult_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::hexapodservice::hexapodserviceResult_<ContainerAllocator> const> ConstPtr;

}; // struct hexapodserviceResult_

typedef ::hexapodservice::hexapodserviceResult_<std::allocator<void> > hexapodserviceResult;

typedef boost::shared_ptr< ::hexapodservice::hexapodserviceResult > hexapodserviceResultPtr;
typedef boost::shared_ptr< ::hexapodservice::hexapodserviceResult const> hexapodserviceResultConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::hexapodservice::hexapodserviceResult_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::hexapodservice::hexapodserviceResult_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace hexapodservice

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'hexapodservice': ['/home/quan/hexapod_service_ws/src/hexapodservice/msg', '/home/quan/hexapod_service_ws/src/hexapodservice/build/devel/share/hexapodservice/msg'], 'actionlib_msgs': ['/opt/ros/indigo/share/actionlib_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::hexapodservice::hexapodserviceResult_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::hexapodservice::hexapodserviceResult_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::hexapodservice::hexapodserviceResult_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::hexapodservice::hexapodserviceResult_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::hexapodservice::hexapodserviceResult_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::hexapodservice::hexapodserviceResult_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::hexapodservice::hexapodserviceResult_<ContainerAllocator> >
{
  static const char* value()
  {
    return "9159b5bfa0e50cc64f02e08ee55d9428";
  }

  static const char* value(const ::hexapodservice::hexapodserviceResult_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x9159b5bfa0e50cc6ULL;
  static const uint64_t static_value2 = 0x4f02e08ee55d9428ULL;
};

template<class ContainerAllocator>
struct DataType< ::hexapodservice::hexapodserviceResult_<ContainerAllocator> >
{
  static const char* value()
  {
    return "hexapodservice/hexapodserviceResult";
  }

  static const char* value(const ::hexapodservice::hexapodserviceResult_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::hexapodservice::hexapodserviceResult_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
hexapodservice/legjoint ONELEG_fdbk\n\
hexapodservice/leg ALLLEGS_fdbk\n\
string result\n\
int32 status\n\
int64 freespace\n\
int64 minimumBufferFreeBytes\n\
int32 maxpoints\n\
bool motionActive\n\
\n\
================================================================================\n\
MSG: hexapodservice/legjoint\n\
float64 coxa\n\
float64 femur\n\
float64 tibia\n\
float64 tarsus\n\
\n\
================================================================================\n\
MSG: hexapodservice/leg\n\
hexapodservice/legjoint[6] leg\n\
";
  }

  static const char* value(const ::hexapodservice::hexapodserviceResult_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::hexapodservice::hexapodserviceResult_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.ONELEG_fdbk);
      stream.next(m.ALLLEGS_fdbk);
      stream.next(m.result);
      stream.next(m.status);
      stream.next(m.freespace);
      stream.next(m.minimumBufferFreeBytes);
      stream.next(m.maxpoints);
      stream.next(m.motionActive);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct hexapodserviceResult_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::hexapodservice::hexapodserviceResult_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::hexapodservice::hexapodserviceResult_<ContainerAllocator>& v)
  {
    s << indent << "ONELEG_fdbk: ";
    s << std::endl;
    Printer< ::hexapodservice::legjoint_<ContainerAllocator> >::stream(s, indent + "  ", v.ONELEG_fdbk);
    s << indent << "ALLLEGS_fdbk: ";
    s << std::endl;
    Printer< ::hexapodservice::leg_<ContainerAllocator> >::stream(s, indent + "  ", v.ALLLEGS_fdbk);
    s << indent << "result: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.result);
    s << indent << "status: ";
    Printer<int32_t>::stream(s, indent + "  ", v.status);
    s << indent << "freespace: ";
    Printer<int64_t>::stream(s, indent + "  ", v.freespace);
    s << indent << "minimumBufferFreeBytes: ";
    Printer<int64_t>::stream(s, indent + "  ", v.minimumBufferFreeBytes);
    s << indent << "maxpoints: ";
    Printer<int32_t>::stream(s, indent + "  ", v.maxpoints);
    s << indent << "motionActive: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.motionActive);
  }
};

} // namespace message_operations
} // namespace ros

#endif // HEXAPODSERVICE_MESSAGE_HEXAPODSERVICERESULT_H
