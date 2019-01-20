; Auto-generated. Do not edit!


(cl:in-package link_com-msg)


;//! \htmlinclude heartbag.msg.html

(cl:defclass <heartbag> (roslisp-msg-protocol:ros-message)
  ((kpa
    :reader kpa
    :initarg :kpa
    :type cl:float
    :initform 0.0)
   (io
    :reader io
    :initarg :io
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 7 :element-type 'cl:fixnum :initial-element 0)))
)

(cl:defclass heartbag (<heartbag>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <heartbag>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'heartbag)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name link_com-msg:<heartbag> is deprecated: use link_com-msg:heartbag instead.")))

(cl:ensure-generic-function 'kpa-val :lambda-list '(m))
(cl:defmethod kpa-val ((m <heartbag>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader link_com-msg:kpa-val is deprecated.  Use link_com-msg:kpa instead.")
  (kpa m))

(cl:ensure-generic-function 'io-val :lambda-list '(m))
(cl:defmethod io-val ((m <heartbag>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader link_com-msg:io-val is deprecated.  Use link_com-msg:io instead.")
  (io m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <heartbag>) ostream)
  "Serializes a message object of type '<heartbag>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'kpa))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) ele) ostream))
   (cl:slot-value msg 'io))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <heartbag>) istream)
  "Deserializes a message object of type '<heartbag>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'kpa) (roslisp-utils:decode-single-float-bits bits)))
  (cl:setf (cl:slot-value msg 'io) (cl:make-array 7))
  (cl:let ((vals (cl:slot-value msg 'io)))
    (cl:dotimes (i 7)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:aref vals i)) (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<heartbag>)))
  "Returns string type for a message object of type '<heartbag>"
  "link_com/heartbag")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'heartbag)))
  "Returns string type for a message object of type 'heartbag"
  "link_com/heartbag")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<heartbag>)))
  "Returns md5sum for a message object of type '<heartbag>"
  "3975ec5bee3b3f6b04685f86ab5e40e0")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'heartbag)))
  "Returns md5sum for a message object of type 'heartbag"
  "3975ec5bee3b3f6b04685f86ab5e40e0")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<heartbag>)))
  "Returns full string definition for message of type '<heartbag>"
  (cl:format cl:nil "#kpa 真空度(0 ~ -100kpa)~%#io[x] = 0 代表第x腿吸盘与真空泵连通，吸盘与放气端口之间阻塞; io[x] = 1 代表第x腿吸盘与放气端口连通，吸盘与真空泵之间阻塞~%~%float32 kpa~%uint8[7] io~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'heartbag)))
  "Returns full string definition for message of type 'heartbag"
  (cl:format cl:nil "#kpa 真空度(0 ~ -100kpa)~%#io[x] = 0 代表第x腿吸盘与真空泵连通，吸盘与放气端口之间阻塞; io[x] = 1 代表第x腿吸盘与放气端口连通，吸盘与真空泵之间阻塞~%~%float32 kpa~%uint8[7] io~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <heartbag>))
  (cl:+ 0
     4
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'io) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <heartbag>))
  "Converts a ROS message object to a list"
  (cl:list 'heartbag
    (cl:cons ':kpa (kpa msg))
    (cl:cons ':io (io msg))
))
