;; Auto-generated. Do not edit!


(when (boundp 'link_com::heartbag)
  (if (not (find-package "LINK_COM"))
    (make-package "LINK_COM"))
  (shadow 'heartbag (find-package "LINK_COM")))
(unless (find-package "LINK_COM::HEARTBAG")
  (make-package "LINK_COM::HEARTBAG"))

(in-package "ROS")
;;//! \htmlinclude heartbag.msg.html


(defclass link_com::heartbag
  :super ros::object
  :slots (_kpa _io ))

(defmethod link_com::heartbag
  (:init
   (&key
    ((:kpa __kpa) 0.0)
    ((:io __io) (make-array 7 :initial-element 0 :element-type :char))
    )
   (send-super :init)
   (setq _kpa (float __kpa))
   (setq _io __io)
   self)
  (:kpa
   (&optional __kpa)
   (if __kpa (setq _kpa __kpa)) _kpa)
  (:io
   (&optional __io)
   (if __io (setq _io __io)) _io)
  (:serialization-length
   ()
   (+
    ;; float32 _kpa
    4
    ;; uint8[7] _io
    (* 1    7)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _kpa
       (sys::poke _kpa (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; uint8[7] _io
     (princ _io s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _kpa
     (setq _kpa (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; uint8[7] _io
   (setq _io (make-array 7 :element-type :char))
   (replace _io buf :start2 ptr-) (incf ptr- 7)
   ;;
   self)
  )

(setf (get link_com::heartbag :md5sum-) "3975ec5bee3b3f6b04685f86ab5e40e0")
(setf (get link_com::heartbag :datatype-) "link_com/heartbag")
(setf (get link_com::heartbag :definition-)
      "#kpa 真空度(0 ~ -100kpa)
#io[x] = 0 代表第x腿吸盘与真空泵连通，吸盘与放气端口之间阻塞; io[x] = 1 代表第x腿吸盘与放气端口连通，吸盘与真空泵之间阻塞

float32 kpa
uint8[7] io

")



(provide :link_com/heartbag "3975ec5bee3b3f6b04685f86ab5e40e0")


