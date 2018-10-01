
(cl:in-package :asdf)

(defsystem "link_com-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "heartbag" :depends-on ("_package_heartbag"))
    (:file "_package_heartbag" :depends-on ("_package"))
  ))