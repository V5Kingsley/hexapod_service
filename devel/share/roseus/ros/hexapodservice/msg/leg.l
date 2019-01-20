;; Auto-generated. Do not edit!


(when (boundp 'hexapodservice::leg)
  (if (not (find-package "HEXAPODSERVICE"))
    (make-package "HEXAPODSERVICE"))
  (shadow 'leg (find-package "HEXAPODSERVICE")))
(unless (find-package "HEXAPODSERVICE::LEG")
  (make-package "HEXAPODSERVICE::LEG"))

(in-package "ROS")
;;//! \htmlinclude leg.msg.html


(defclass hexapodservice::leg
  :super ros::object
  :slots (_leg ))

(defmethod hexapodservice::leg
  (:init
   (&key
    ((:leg __leg) (let (r) (dotimes (i 6) (push (instance hexapodservice::legjoint :init) r)) r))
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
    ;; hexapodservice/legjoint[6] _leg
    (apply #'+ (send-all _leg :serialization-length))
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; hexapodservice/legjoint[6] _leg
     (dolist (elem _leg)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; hexapodservice/legjoint[6] _leg
   (dotimes (i 6)
     (send (elt _leg i) :deserialize buf ptr-) (incf ptr- (send (elt _leg i) :serialization-length))
     )
   ;;
   self)
  )

(setf (get hexapodservice::leg :md5sum-) "77281f1f9c4cd29d21908d690db99185")
(setf (get hexapodservice::leg :datatype-) "hexapodservice/leg")
(setf (get hexapodservice::leg :definition-)
      "hexapodservice/legjoint[6] leg

================================================================================
MSG: hexapodservice/legjoint
float64 coxa
float64 femur
float64 tibia
float64 tarsus

")



(provide :hexapodservice/leg "77281f1f9c4cd29d21908d690db99185")


