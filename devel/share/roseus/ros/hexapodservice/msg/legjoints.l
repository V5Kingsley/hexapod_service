;; Auto-generated. Do not edit!


(when (boundp 'hexapodservice::legjoints)
  (if (not (find-package "HEXAPODSERVICE"))
    (make-package "HEXAPODSERVICE"))
  (shadow 'legjoints (find-package "HEXAPODSERVICE")))
(unless (find-package "HEXAPODSERVICE::LEGJOINTS")
  (make-package "HEXAPODSERVICE::LEGJOINTS"))

(in-package "ROS")
;;//! \htmlinclude legjoints.msg.html


(defclass hexapodservice::legjoints
  :super ros::object
  :slots (_coxa _femur _tibia _tarsus ))

(defmethod hexapodservice::legjoints
  (:init
   (&key
    ((:coxa __coxa) (make-array 0 :initial-element 0 :element-type :integer))
    ((:femur __femur) (make-array 0 :initial-element 0 :element-type :integer))
    ((:tibia __tibia) (make-array 0 :initial-element 0 :element-type :integer))
    ((:tarsus __tarsus) (make-array 0 :initial-element 0 :element-type :integer))
    )
   (send-super :init)
   (setq _coxa __coxa)
   (setq _femur __femur)
   (setq _tibia __tibia)
   (setq _tarsus __tarsus)
   self)
  (:coxa
   (&optional __coxa)
   (if __coxa (setq _coxa __coxa)) _coxa)
  (:femur
   (&optional __femur)
   (if __femur (setq _femur __femur)) _femur)
  (:tibia
   (&optional __tibia)
   (if __tibia (setq _tibia __tibia)) _tibia)
  (:tarsus
   (&optional __tarsus)
   (if __tarsus (setq _tarsus __tarsus)) _tarsus)
  (:serialization-length
   ()
   (+
    ;; int64[] _coxa
    (* 8    (length _coxa)) 4
    ;; int64[] _femur
    (* 8    (length _femur)) 4
    ;; int64[] _tibia
    (* 8    (length _tibia)) 4
    ;; int64[] _tarsus
    (* 8    (length _tarsus)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int64[] _coxa
     (write-long (length _coxa) s)
     (dotimes (i (length _coxa))
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke (elt _coxa i) (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class (elt _coxa i)) (= (length ((elt _coxa i) . bv)) 2)) ;; bignum
              (write-long (ash (elt ((elt _coxa i) . bv) 0) 0) s)
              (write-long (ash (elt ((elt _coxa i) . bv) 1) -1) s))
             ((and (class (elt _coxa i)) (= (length ((elt _coxa i) . bv)) 1)) ;; big1
              (write-long (elt ((elt _coxa i) . bv) 0) s)
              (write-long (if (>= (elt _coxa i) 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long (elt _coxa i) s)(write-long (if (>= (elt _coxa i) 0) 0 #xffffffff) s)))
       )
     ;; int64[] _femur
     (write-long (length _femur) s)
     (dotimes (i (length _femur))
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke (elt _femur i) (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class (elt _femur i)) (= (length ((elt _femur i) . bv)) 2)) ;; bignum
              (write-long (ash (elt ((elt _femur i) . bv) 0) 0) s)
              (write-long (ash (elt ((elt _femur i) . bv) 1) -1) s))
             ((and (class (elt _femur i)) (= (length ((elt _femur i) . bv)) 1)) ;; big1
              (write-long (elt ((elt _femur i) . bv) 0) s)
              (write-long (if (>= (elt _femur i) 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long (elt _femur i) s)(write-long (if (>= (elt _femur i) 0) 0 #xffffffff) s)))
       )
     ;; int64[] _tibia
     (write-long (length _tibia) s)
     (dotimes (i (length _tibia))
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke (elt _tibia i) (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class (elt _tibia i)) (= (length ((elt _tibia i) . bv)) 2)) ;; bignum
              (write-long (ash (elt ((elt _tibia i) . bv) 0) 0) s)
              (write-long (ash (elt ((elt _tibia i) . bv) 1) -1) s))
             ((and (class (elt _tibia i)) (= (length ((elt _tibia i) . bv)) 1)) ;; big1
              (write-long (elt ((elt _tibia i) . bv) 0) s)
              (write-long (if (>= (elt _tibia i) 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long (elt _tibia i) s)(write-long (if (>= (elt _tibia i) 0) 0 #xffffffff) s)))
       )
     ;; int64[] _tarsus
     (write-long (length _tarsus) s)
     (dotimes (i (length _tarsus))
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke (elt _tarsus i) (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class (elt _tarsus i)) (= (length ((elt _tarsus i) . bv)) 2)) ;; bignum
              (write-long (ash (elt ((elt _tarsus i) . bv) 0) 0) s)
              (write-long (ash (elt ((elt _tarsus i) . bv) 1) -1) s))
             ((and (class (elt _tarsus i)) (= (length ((elt _tarsus i) . bv)) 1)) ;; big1
              (write-long (elt ((elt _tarsus i) . bv) 0) s)
              (write-long (if (>= (elt _tarsus i) 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long (elt _tarsus i) s)(write-long (if (>= (elt _tarsus i) 0) 0 #xffffffff) s)))
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int64[] _coxa
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _coxa (instantiate integer-vector n))
     (dotimes (i n)
#+(or :alpha :irix6 :x86_64)
      (setf (elt _coxa i) (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf (elt _coxa i) (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
     ))
   ;; int64[] _femur
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _femur (instantiate integer-vector n))
     (dotimes (i n)
#+(or :alpha :irix6 :x86_64)
      (setf (elt _femur i) (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf (elt _femur i) (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
     ))
   ;; int64[] _tibia
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _tibia (instantiate integer-vector n))
     (dotimes (i n)
#+(or :alpha :irix6 :x86_64)
      (setf (elt _tibia i) (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf (elt _tibia i) (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
     ))
   ;; int64[] _tarsus
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _tarsus (instantiate integer-vector n))
     (dotimes (i n)
#+(or :alpha :irix6 :x86_64)
      (setf (elt _tarsus i) (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf (elt _tarsus i) (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
     ))
   ;;
   self)
  )

(setf (get hexapodservice::legjoints :md5sum-) "30491f146cc62d519f29e03cbd6340f7")
(setf (get hexapodservice::legjoints :datatype-) "hexapodservice/legjoints")
(setf (get hexapodservice::legjoints :definition-)
      "int64[] coxa
int64[] femur
int64[] tibia
int64[] tarsus

")



(provide :hexapodservice/legjoints "30491f146cc62d519f29e03cbd6340f7")


