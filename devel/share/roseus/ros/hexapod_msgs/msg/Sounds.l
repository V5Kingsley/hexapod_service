;; Auto-generated. Do not edit!


(when (boundp 'hexapod_msgs::Sounds)
  (if (not (find-package "HEXAPOD_MSGS"))
    (make-package "HEXAPOD_MSGS"))
  (shadow 'Sounds (find-package "HEXAPOD_MSGS")))
(unless (find-package "HEXAPOD_MSGS::SOUNDS")
  (make-package "HEXAPOD_MSGS::SOUNDS"))

(in-package "ROS")
;;//! \htmlinclude Sounds.msg.html


(defclass hexapod_msgs::Sounds
  :super ros::object
  :slots (_torque _battery _auto_level _stand _waiting _shut_down ))

(defmethod hexapod_msgs::Sounds
  (:init
   (&key
    ((:torque __torque) nil)
    ((:battery __battery) nil)
    ((:auto_level __auto_level) nil)
    ((:stand __stand) nil)
    ((:waiting __waiting) nil)
    ((:shut_down __shut_down) nil)
    )
   (send-super :init)
   (setq _torque __torque)
   (setq _battery __battery)
   (setq _auto_level __auto_level)
   (setq _stand __stand)
   (setq _waiting __waiting)
   (setq _shut_down __shut_down)
   self)
  (:torque
   (&optional __torque)
   (if __torque (setq _torque __torque)) _torque)
  (:battery
   (&optional __battery)
   (if __battery (setq _battery __battery)) _battery)
  (:auto_level
   (&optional __auto_level)
   (if __auto_level (setq _auto_level __auto_level)) _auto_level)
  (:stand
   (&optional __stand)
   (if __stand (setq _stand __stand)) _stand)
  (:waiting
   (&optional __waiting)
   (if __waiting (setq _waiting __waiting)) _waiting)
  (:shut_down
   (&optional __shut_down)
   (if __shut_down (setq _shut_down __shut_down)) _shut_down)
  (:serialization-length
   ()
   (+
    ;; bool _torque
    1
    ;; bool _battery
    1
    ;; bool _auto_level
    1
    ;; bool _stand
    1
    ;; bool _waiting
    1
    ;; bool _shut_down
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _torque
       (if _torque (write-byte -1 s) (write-byte 0 s))
     ;; bool _battery
       (if _battery (write-byte -1 s) (write-byte 0 s))
     ;; bool _auto_level
       (if _auto_level (write-byte -1 s) (write-byte 0 s))
     ;; bool _stand
       (if _stand (write-byte -1 s) (write-byte 0 s))
     ;; bool _waiting
       (if _waiting (write-byte -1 s) (write-byte 0 s))
     ;; bool _shut_down
       (if _shut_down (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _torque
     (setq _torque (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _battery
     (setq _battery (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _auto_level
     (setq _auto_level (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _stand
     (setq _stand (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _waiting
     (setq _waiting (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _shut_down
     (setq _shut_down (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get hexapod_msgs::Sounds :md5sum-) "9e277e5433232e212c4281205788a826")
(setf (get hexapod_msgs::Sounds :datatype-) "hexapod_msgs/Sounds")
(setf (get hexapod_msgs::Sounds :definition-)
      "bool torque
bool battery
bool auto_level
bool stand
bool waiting
bool shut_down

")



(provide :hexapod_msgs/Sounds "9e277e5433232e212c4281205788a826")


