; Auto-generated. Do not edit!


(cl:in-package link_com-srv)


;//! \htmlinclude hexcom-request.msg.html

(cl:defclass <hexcom-request> (roslisp-msg-protocol:ros-message)
  ((chose
    :reader chose
    :initarg :chose
    :type cl:fixnum
    :initform 0)
   (pwm
    :reader pwm
    :initarg :pwm
    :type cl:fixnum
    :initform 0)
   (io
    :reader io
    :initarg :io
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 7 :element-type 'cl:fixnum :initial-element 0)))
)

(cl:defclass hexcom-request (<hexcom-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <hexcom-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'hexcom-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name link_com-srv:<hexcom-request> is deprecated: use link_com-srv:hexcom-request instead.")))

(cl:ensure-generic-function 'chose-val :lambda-list '(m))
(cl:defmethod chose-val ((m <hexcom-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader link_com-srv:chose-val is deprecated.  Use link_com-srv:chose instead.")
  (chose m))

(cl:ensure-generic-function 'pwm-val :lambda-list '(m))
(cl:defmethod pwm-val ((m <hexcom-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader link_com-srv:pwm-val is deprecated.  Use link_com-srv:pwm instead.")
  (pwm m))

(cl:ensure-generic-function 'io-val :lambda-list '(m))
(cl:defmethod io-val ((m <hexcom-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader link_com-srv:io-val is deprecated.  Use link_com-srv:io instead.")
  (io m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <hexcom-request>) ostream)
  "Serializes a message object of type '<hexcom-request>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'chose)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'pwm)) ostream)
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) ele) ostream))
   (cl:slot-value msg 'io))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <hexcom-request>) istream)
  "Deserializes a message object of type '<hexcom-request>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'chose)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'pwm)) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'io) (cl:make-array 7))
  (cl:let ((vals (cl:slot-value msg 'io)))
    (cl:dotimes (i 7)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:aref vals i)) (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<hexcom-request>)))
  "Returns string type for a service object of type '<hexcom-request>"
  "link_com/hexcomRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'hexcom-request)))
  "Returns string type for a service object of type 'hexcom-request"
  "link_com/hexcomRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<hexcom-request>)))
  "Returns md5sum for a message object of type '<hexcom-request>"
  "4c6bf6a56b94d0854641b3cbd40fb9db")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'hexcom-request)))
  "Returns md5sum for a message object of type 'hexcom-request"
  "4c6bf6a56b94d0854641b3cbd40fb9db")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<hexcom-request>)))
  "Returns full string definition for message of type '<hexcom-request>"
  (cl:format cl:nil "~%~%~%uint8 chose~%uint8 pwm~%uint8[7] io~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'hexcom-request)))
  "Returns full string definition for message of type 'hexcom-request"
  (cl:format cl:nil "~%~%~%uint8 chose~%uint8 pwm~%uint8[7] io~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <hexcom-request>))
  (cl:+ 0
     1
     1
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'io) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <hexcom-request>))
  "Converts a ROS message object to a list"
  (cl:list 'hexcom-request
    (cl:cons ':chose (chose msg))
    (cl:cons ':pwm (pwm msg))
    (cl:cons ':io (io msg))
))
;//! \htmlinclude hexcom-response.msg.html

(cl:defclass <hexcom-response> (roslisp-msg-protocol:ros-message)
  ((back
    :reader back
    :initarg :back
    :type cl:string
    :initform ""))
)

(cl:defclass hexcom-response (<hexcom-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <hexcom-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'hexcom-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name link_com-srv:<hexcom-response> is deprecated: use link_com-srv:hexcom-response instead.")))

(cl:ensure-generic-function 'back-val :lambda-list '(m))
(cl:defmethod back-val ((m <hexcom-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader link_com-srv:back-val is deprecated.  Use link_com-srv:back instead.")
  (back m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <hexcom-response>) ostream)
  "Serializes a message object of type '<hexcom-response>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'back))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'back))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <hexcom-response>) istream)
  "Deserializes a message object of type '<hexcom-response>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'back) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'back) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<hexcom-response>)))
  "Returns string type for a service object of type '<hexcom-response>"
  "link_com/hexcomResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'hexcom-response)))
  "Returns string type for a service object of type 'hexcom-response"
  "link_com/hexcomResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<hexcom-response>)))
  "Returns md5sum for a message object of type '<hexcom-response>"
  "4c6bf6a56b94d0854641b3cbd40fb9db")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'hexcom-response)))
  "Returns md5sum for a message object of type 'hexcom-response"
  "4c6bf6a56b94d0854641b3cbd40fb9db")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<hexcom-response>)))
  "Returns full string definition for message of type '<hexcom-response>"
  (cl:format cl:nil "string back~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'hexcom-response)))
  "Returns full string definition for message of type 'hexcom-response"
  (cl:format cl:nil "string back~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <hexcom-response>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'back))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <hexcom-response>))
  "Converts a ROS message object to a list"
  (cl:list 'hexcom-response
    (cl:cons ':back (back msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'hexcom)))
  'hexcom-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'hexcom)))
  'hexcom-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'hexcom)))
  "Returns string type for a service object of type '<hexcom>"
  "link_com/hexcom")