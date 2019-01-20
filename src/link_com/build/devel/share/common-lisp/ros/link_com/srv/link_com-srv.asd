
(cl:in-package :asdf)

(defsystem "link_com-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "hexcom" :depends-on ("_package_hexcom"))
    (:file "_package_hexcom" :depends-on ("_package"))
  ))