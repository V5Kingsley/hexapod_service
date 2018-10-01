; Auto-generated. Do not edit!


(cl:in-package hexapodservice-msg)


;//! \htmlinclude hexapodserviceResult.msg.html

(cl:defclass <hexapodserviceResult> (roslisp-msg-protocol:ros-message)
  ((status
    :reader status
    :initarg :status
    :type cl:integer
    :initform 0)
   (freespace
    :reader freespace
    :initarg :freespace
    :type cl:integer
    :initform 0)
   (motionActive
    :reader motionActive
    :initarg :motionActive
    :type cl:boolean
    :initform cl:nil)
   (result
    :reader result
    :initarg :result
    :type cl:string
    :initform ""))
)

(cl:defclass hexapodserviceResult (<hexapodserviceResult>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <hexapodserviceResult>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'hexapodserviceResult)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name hexapodservice-msg:<hexapodserviceResult> is deprecated: use hexapodservice-msg:hexapodserviceResult instead.")))

(cl:ensure-generic-function 'status-val :lambda-list '(m))
(cl:defmethod status-val ((m <hexapodserviceResult>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hexapodservice-msg:status-val is deprecated.  Use hexapodservice-msg:status instead.")
  (status m))

(cl:ensure-generic-function 'freespace-val :lambda-list '(m))
(cl:defmethod freespace-val ((m <hexapodserviceResult>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hexapodservice-msg:freespace-val is deprecated.  Use hexapodservice-msg:freespace instead.")
  (freespace m))

(cl:ensure-generic-function 'motionActive-val :lambda-list '(m))
(cl:defmethod motionActive-val ((m <hexapodserviceResult>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hexapodservice-msg:motionActive-val is deprecated.  Use hexapodservice-msg:motionActive instead.")
  (motionActive m))

(cl:ensure-generic-function 'result-val :lambda-list '(m))
(cl:defmethod result-val ((m <hexapodserviceResult>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hexapodservice-msg:result-val is deprecated.  Use hexapodservice-msg:result instead.")
  (result m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <hexapodserviceResult>) ostream)
  "Serializes a message object of type '<hexapodserviceResult>"
  (cl:let* ((signed (cl:slot-value msg 'status)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'freespace)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'motionActive) 1 0)) ostream)
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'result))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'result))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <hexapodserviceResult>) istream)
  "Deserializes a message object of type '<hexapodserviceResult>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'status) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'freespace) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:setf (cl:slot-value msg 'motionActive) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'result) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'result) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<hexapodserviceResult>)))
  "Returns string type for a message object of type '<hexapodserviceResult>"
  "hexapodservice/hexapodserviceResult")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'hexapodserviceResult)))
  "Returns string type for a message object of type 'hexapodserviceResult"
  "hexapodservice/hexapodserviceResult")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<hexapodserviceResult>)))
  "Returns md5sum for a message object of type '<hexapodserviceResult>"
  "84ae386391a6712ba3f1d0cdfd23bad0")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'hexapodserviceResult)))
  "Returns md5sum for a message object of type 'hexapodserviceResult"
  "84ae386391a6712ba3f1d0cdfd23bad0")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<hexapodserviceResult>)))
  "Returns full string definition for message of type '<hexapodserviceResult>"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%int32 status~%int32 freespace~%bool motionActive~%string result~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'hexapodserviceResult)))
  "Returns full string definition for message of type 'hexapodserviceResult"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%int32 status~%int32 freespace~%bool motionActive~%string result~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <hexapodserviceResult>))
  (cl:+ 0
     4
     4
     1
     4 (cl:length (cl:slot-value msg 'result))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <hexapodserviceResult>))
  "Converts a ROS message object to a list"
  (cl:list 'hexapodserviceResult
    (cl:cons ':status (status msg))
    (cl:cons ':freespace (freespace msg))
    (cl:cons ':motionActive (motionActive msg))
    (cl:cons ':result (result msg))
))
