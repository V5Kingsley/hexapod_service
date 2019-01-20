;; Auto-generated. Do not edit!


(when (boundp 'link_com::hexcom)
  (if (not (find-package "LINK_COM"))
    (make-package "LINK_COM"))
  (shadow 'hexcom (find-package "LINK_COM")))
(unless (find-package "LINK_COM::HEXCOM")
  (make-package "LINK_COM::HEXCOM"))
(unless (find-package "LINK_COM::HEXCOMREQUEST")
  (make-package "LINK_COM::HEXCOMREQUEST"))
(unless (find-package "LINK_COM::HEXCOMRESPONSE")
  (make-package "LINK_COM::HEXCOMRESPONSE"))

(in-package "ROS")





(defclass link_com::hexcomRequest
  :super ros::object
  :slots (_chose _pwm _io ))

(defmethod link_com::hexcomRequest
  (:init
   (&key
    ((:chose __chose) 0)
    ((:pwm __pwm) 0)
    ((:io __io) (make-array 7 :initial-element 0 :element-type :char))
    )
   (send-super :init)
   (setq _chose (round __chose))
   (setq _pwm (round __pwm))
   (setq _io __io)
   self)
  (:chose
   (&optional __chose)
   (if __chose (setq _chose __chose)) _chose)
  (:pwm
   (&optional __pwm)
   (if __pwm (setq _pwm __pwm)) _pwm)
  (:io
   (&optional __io)
   (if __io (setq _io __io)) _io)
  (:serialization-length
   ()
   (+
    ;; uint8 _chose
    1
    ;; uint8 _pwm
    1
    ;; uint8[7] _io
    (* 1    7)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _chose
       (write-byte _chose s)
     ;; uint8 _pwm
       (write-byte _pwm s)
     ;; uint8[7] _io
     (princ _io s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _chose
     (setq _chose (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _pwm
     (setq _pwm (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8[7] _io
   (setq _io (make-array 7 :element-type :char))
   (replace _io buf :start2 ptr-) (incf ptr- 7)
   ;;
   self)
  )

(defclass link_com::hexcomResponse
  :super ros::object
  :slots (_back ))

(defmethod link_com::hexcomResponse
  (:init
   (&key
    ((:back __back) "")
    )
   (send-super :init)
   (setq _back (string __back))
   self)
  (:back
   (&optional __back)
   (if __back (setq _back __back)) _back)
  (:serialization-length
   ()
   (+
    ;; string _back
    4 (length _back)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _back
       (write-long (length _back) s) (princ _back s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _back
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _back (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass link_com::hexcom
  :super ros::object
  :slots ())

(setf (get link_com::hexcom :md5sum-) "4c6bf6a56b94d0854641b3cbd40fb9db")
(setf (get link_com::hexcom :datatype-) "link_com/hexcom")
(setf (get link_com::hexcom :request) link_com::hexcomRequest)
(setf (get link_com::hexcom :response) link_com::hexcomResponse)

(defmethod link_com::hexcomRequest
  (:response () (instance link_com::hexcomResponse :init)))

(setf (get link_com::hexcomRequest :md5sum-) "4c6bf6a56b94d0854641b3cbd40fb9db")
(setf (get link_com::hexcomRequest :datatype-) "link_com/hexcomRequest")
(setf (get link_com::hexcomRequest :definition-)
      "


uint8 chose
uint8 pwm
uint8[7] io
---
string back

")

(setf (get link_com::hexcomResponse :md5sum-) "4c6bf6a56b94d0854641b3cbd40fb9db")
(setf (get link_com::hexcomResponse :datatype-) "link_com/hexcomResponse")
(setf (get link_com::hexcomResponse :definition-)
      "


uint8 chose
uint8 pwm
uint8[7] io
---
string back

")



(provide :link_com/hexcom "4c6bf6a56b94d0854641b3cbd40fb9db")


