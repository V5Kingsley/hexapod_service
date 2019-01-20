;; Auto-generated. Do not edit!


(when (boundp 'hexapodservice::legs)
  (if (not (find-package "HEXAPODSERVICE"))
    (make-package "HEXAPODSERVICE"))
  (shadow 'legs (find-package "HEXAPODSERVICE")))
(unless (find-package "HEXAPODSERVICE::LEGS")
  (make-package "HEXAPODSERVICE::LEGS"))

(in-package "ROS")
;;//! \htmlinclude legs.msg.html


(defclass hexapodservice::legs
  :super ros::object
  :slots (_leg ))

(defmethod hexapodservice::legs
  (:init
   (&key
    ((:leg __leg) (let (r) (dotimes (i 6) (push (instance hexapodservice::legjoints :init) r)) r))
    )
   (send-super :init)
   (setq _leg __leg)
   self)
  (:leg
   (&rest __leg)
   (if (keywordp (car __leg))
       (send* _leg __leg)
     (progn
       (if __leg (setq _leg (car __leg)))
       _leg)))
  (:serialization-length
   ()
   (+
    ;; hexapodservice/legjoints[6] _leg
    (apply #'+ (send-all _leg :serialization-length))
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; hexapodservice/legjoints[6] _leg
     (dolist (elem _leg)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; hexapodservice/legjoints[6] _leg
   (dotimes (i 6)
     (send (elt _leg i) :deserialize buf ptr-) (incf ptr- (send (elt _leg i) :serialization-length))
     )
   ;;
   self)
  )

(setf (get hexapodservice::legs :md5sum-) "283042c2b49d709689847698830e74a9")
(setf (get hexapodservice::legs :datatype-) "hexapodservice/legs")
(setf (get hexapodservice::legs :definition-)
      "hexapodservice/legjoints[6] leg

================================================================================
MSG: hexapodservice/legjoints
int64[] coxa
int64[] femur
int64[] tibia
int64[] tarsus

")



(provide :hexapodservice/legs "283042c2b49d709689847698830e74a9")


