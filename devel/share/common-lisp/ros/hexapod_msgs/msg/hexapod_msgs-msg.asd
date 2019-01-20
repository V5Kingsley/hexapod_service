
(cl:in-package :asdf)

(defsystem "hexapod_msgs-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
)
  :components ((:file "_package")
    (:file "FeetPositions" :depends-on ("_package_FeetPositions"))
    (:file "_package_FeetPositions" :depends-on ("_package"))
    (:file "LegJoints" :depends-on ("_package_LegJoints"))
    (:file "_package_LegJoints" :depends-on ("_package"))
    (:file "LegsJoints" :depends-on ("_package_LegsJoints"))
    (:file "_package_LegsJoints" :depends-on ("_package"))
    (:file "Pose" :depends-on ("_package_Pose"))
    (:file "_package_Pose" :depends-on ("_package"))
    (:file "RPY" :depends-on ("_package_RPY"))
    (:file "_package_RPY" :depends-on ("_package"))
    (:file "Sounds" :depends-on ("_package_Sounds"))
    (:file "_package_Sounds" :depends-on ("_package"))
  ))