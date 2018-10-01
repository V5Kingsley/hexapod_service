; Auto-generated. Do not edit!


(cl:in-package hexapodservice-msg)


;//! \htmlinclude leg.msg.html

(cl:defclass <leg> (roslisp-msg-protocol:ros-message)
  ((leg
    :reader leg
    :initarg :leg
    :type (cl:vector hexapodservice-msg:legjoint)
   :initform (cl:make-array 6 :element-type 'hexapodservice-msg:legjoint :initial-element (cl:make-instance 'hexapodservice-msg:legjoint))))
)

(cl:defclass leg (<leg>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <leg>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'leg)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name hexapodservice-msg:<leg> is deprecated: use hexapodservice-msg:leg instead.")))

(cl:ensure-generic-function 'leg-val :lambda-list '(m))
(cl:defmethod leg-val ((m <leg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hexapodservice-msg:leg-val is deprecated.  Use hexapodservice-msg:leg instead.")
  (leg m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <leg>) ostream)
  "Serializes a message object of type '<leg>"
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'leg))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <leg>) istream)
  "Deserializes a message object of type '<leg>"
  (cl:setf (cl:slot-value msg 'leg) (cl:make-array 6))
  (cl:let ((vals (cl:slot-value msg 'leg)))
    (cl:dotimes (i 6)
    (cl:setf (cl:aref vals i) (cl:make-instance 'hexapodservice-msg:legjoint))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<leg>)))
  "Returns string type for a message object of type '<leg>"
  "hexapodservice/leg")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'leg)))
  "Returns string type for a message object of type 'leg"
  "hexapodservice/leg")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<leg>)))
  "Returns md5sum for a message object of type '<leg>"
  "77281f1f9c4cd29d21908d690db99185")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'leg)))
  "Returns md5sum for a message object of type 'leg"
  "77281f1f9c4cd29d21908d690db99185")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<leg>)))
  "Returns full string definition for message of type '<leg>"
  (cl:format cl:nil "hexapodservice/legjoint[6] leg~%~%================================================================================~%MSG: hexapodservice/legjoint~%float64 coxa~%float64 femur~%float64 tibia~%float64 tarsus~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'leg)))
  "Returns full string definition for message of type 'leg"
  (cl:format cl:nil "hexapodservice/legjoint[6] leg~%~%================================================================================~%MSG: hexapodservice/legjoint~%float64 coxa~%float64 femur~%float64 tibia~%float64 tarsus~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <leg>))
  (cl:+ 0
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'leg) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <leg>))
  "Converts a ROS message object to a list"
  (cl:list 'leg
    (cl:cons ':leg (leg msg))
))
