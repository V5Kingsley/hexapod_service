; Auto-generated. Do not edit!


(cl:in-package hexapod_msgs-msg)


;//! \htmlinclude Sounds.msg.html

(cl:defclass <Sounds> (roslisp-msg-protocol:ros-message)
  ((torque
    :reader torque
    :initarg :torque
    :type cl:boolean
    :initform cl:nil)
   (battery
    :reader battery
    :initarg :battery
    :type cl:boolean
    :initform cl:nil)
   (auto_level
    :reader auto_level
    :initarg :auto_level
    :type cl:boolean
    :initform cl:nil)
   (stand
    :reader stand
    :initarg :stand
    :type cl:boolean
    :initform cl:nil)
   (waiting
    :reader waiting
    :initarg :waiting
    :type cl:boolean
    :initform cl:nil)
   (shut_down
    :reader shut_down
    :initarg :shut_down
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass Sounds (<Sounds>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Sounds>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Sounds)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name hexapod_msgs-msg:<Sounds> is deprecated: use hexapod_msgs-msg:Sounds instead.")))

(cl:ensure-generic-function 'torque-val :lambda-list '(m))
(cl:defmethod torque-val ((m <Sounds>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hexapod_msgs-msg:torque-val is deprecated.  Use hexapod_msgs-msg:torque instead.")
  (torque m))

(cl:ensure-generic-function 'battery-val :lambda-list '(m))
(cl:defmethod battery-val ((m <Sounds>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hexapod_msgs-msg:battery-val is deprecated.  Use hexapod_msgs-msg:battery instead.")
  (battery m))

(cl:ensure-generic-function 'auto_level-val :lambda-list '(m))
(cl:defmethod auto_level-val ((m <Sounds>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hexapod_msgs-msg:auto_level-val is deprecated.  Use hexapod_msgs-msg:auto_level instead.")
  (auto_level m))

(cl:ensure-generic-function 'stand-val :lambda-list '(m))
(cl:defmethod stand-val ((m <Sounds>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hexapod_msgs-msg:stand-val is deprecated.  Use hexapod_msgs-msg:stand instead.")
  (stand m))

(cl:ensure-generic-function 'waiting-val :lambda-list '(m))
(cl:defmethod waiting-val ((m <Sounds>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hexapod_msgs-msg:waiting-val is deprecated.  Use hexapod_msgs-msg:waiting instead.")
  (waiting m))

(cl:ensure-generic-function 'shut_down-val :lambda-list '(m))
(cl:defmethod shut_down-val ((m <Sounds>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hexapod_msgs-msg:shut_down-val is deprecated.  Use hexapod_msgs-msg:shut_down instead.")
  (shut_down m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Sounds>) ostream)
  "Serializes a message object of type '<Sounds>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'torque) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'battery) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'auto_level) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'stand) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'waiting) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'shut_down) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Sounds>) istream)
  "Deserializes a message object of type '<Sounds>"
    (cl:setf (cl:slot-value msg 'torque) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'battery) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'auto_level) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'stand) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'waiting) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'shut_down) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Sounds>)))
  "Returns string type for a message object of type '<Sounds>"
  "hexapod_msgs/Sounds")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Sounds)))
  "Returns string type for a message object of type 'Sounds"
  "hexapod_msgs/Sounds")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Sounds>)))
  "Returns md5sum for a message object of type '<Sounds>"
  "9e277e5433232e212c4281205788a826")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Sounds)))
  "Returns md5sum for a message object of type 'Sounds"
  "9e277e5433232e212c4281205788a826")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Sounds>)))
  "Returns full string definition for message of type '<Sounds>"
  (cl:format cl:nil "bool torque~%bool battery~%bool auto_level~%bool stand~%bool waiting~%bool shut_down~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Sounds)))
  "Returns full string definition for message of type 'Sounds"
  (cl:format cl:nil "bool torque~%bool battery~%bool auto_level~%bool stand~%bool waiting~%bool shut_down~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Sounds>))
  (cl:+ 0
     1
     1
     1
     1
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Sounds>))
  "Converts a ROS message object to a list"
  (cl:list 'Sounds
    (cl:cons ':torque (torque msg))
    (cl:cons ':battery (battery msg))
    (cl:cons ':auto_level (auto_level msg))
    (cl:cons ':stand (stand msg))
    (cl:cons ':waiting (waiting msg))
    (cl:cons ':shut_down (shut_down msg))
))
