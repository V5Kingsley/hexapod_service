;; Auto-generated. Do not edit!


(when (boundp 'hexapod_msgs::FeetPositions)
  (if (not (find-package "HEXAPOD_MSGS"))
    (make-package "HEXAPOD_MSGS"))
  (shadow 'FeetPositions (find-package "HEXAPOD_MSGS")))
(unless (find-package "HEXAPOD_MSGS::FEETPOSITIONS")
  (make-package "HEXAPOD_MSGS::FEETPOSITIONS"))

(in-package "ROS")
;;//! \htmlinclude FeetPositions.msg.html


(defclass hexapod_msgs::FeetPositions
  :super ros::object
  :slots (_foot ))

(defmethod hexapod_msgs::FeetPositions
  (:init
   (&key
    ((:foot __foot) (let (r) (dotimes (i 6) (push (instance hexapod_msgs::Pose :init) r)) r))
    )
   (send-super :init)
   (setq _foot __foot)
   self)
  (:foot
   (&rest __foot)
   (if (keywordp (car __foot))
       (send* _foot __foot)
     (progn
       (if __foot (setq _foot (car __foot)))
       _foot)))
  (:serialization-length
   ()
   (+
    ;; hexapod_msgs/Pose[6] _foot
    (apply #'+ (send-all _foot :serialization-length))
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; hexapod_msgs/Pose[6] _foot
     (dolist (elem _foot)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; hexapod_msgs/Pose[6] _foot
   (dotimes (i 6)
     (send (elt _foot i) :deserialize buf ptr-) (incf ptr- (send (elt _foot i) :serialization-length))
     )
   ;;
   self)
  )

(setf (get hexapod_msgs::FeetPositions :md5sum-) "d12724c3b1519cfb275eb5b1d0e25de2")
(setf (get hexapod_msgs::FeetPositions :datatype-) "hexapod_msgs/FeetPositions")
(setf (get hexapod_msgs::FeetPositions :definition-)
      "hexapod_msgs/Pose[6] foot

================================================================================
MSG: hexapod_msgs/Pose
geometry_msgs/Point position
hexapod_msgs/RPY orientation

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

================================================================================
MSG: hexapod_msgs/RPY
float64 roll
float64 pitch
float64 yaw

")



(provide :hexapod_msgs/FeetPositions "d12724c3b1519cfb275eb5b1d0e25de2")


