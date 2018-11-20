# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "hexapod_msgs: 6 messages, 0 services")

set(MSG_I_FLAGS "-Ihexapod_msgs:/home/quan/hexapod_service_ws/src/hexapod_msgs/msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/indigo/share/geometry_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(hexapod_msgs_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/Pose.msg" NAME_WE)
add_custom_target(_hexapod_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "hexapod_msgs" "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/Pose.msg" "hexapod_msgs/RPY:geometry_msgs/Point"
)

get_filename_component(_filename "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/Sounds.msg" NAME_WE)
add_custom_target(_hexapod_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "hexapod_msgs" "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/Sounds.msg" ""
)

get_filename_component(_filename "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/LegJoints.msg" NAME_WE)
add_custom_target(_hexapod_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "hexapod_msgs" "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/LegJoints.msg" ""
)

get_filename_component(_filename "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/LegsJoints.msg" NAME_WE)
add_custom_target(_hexapod_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "hexapod_msgs" "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/LegsJoints.msg" "hexapod_msgs/LegJoints"
)

get_filename_component(_filename "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/RPY.msg" NAME_WE)
add_custom_target(_hexapod_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "hexapod_msgs" "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/RPY.msg" ""
)

get_filename_component(_filename "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/FeetPositions.msg" NAME_WE)
add_custom_target(_hexapod_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "hexapod_msgs" "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/FeetPositions.msg" "hexapod_msgs/Pose:geometry_msgs/Point:hexapod_msgs/RPY"
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(hexapod_msgs
  "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/Pose.msg"
  "${MSG_I_FLAGS}"
  "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/RPY.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hexapod_msgs
)
_generate_msg_cpp(hexapod_msgs
  "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/Sounds.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hexapod_msgs
)
_generate_msg_cpp(hexapod_msgs
  "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/LegJoints.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hexapod_msgs
)
_generate_msg_cpp(hexapod_msgs
  "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/LegsJoints.msg"
  "${MSG_I_FLAGS}"
  "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/LegJoints.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hexapod_msgs
)
_generate_msg_cpp(hexapod_msgs
  "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/RPY.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hexapod_msgs
)
_generate_msg_cpp(hexapod_msgs
  "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/FeetPositions.msg"
  "${MSG_I_FLAGS}"
  "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/Pose.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/RPY.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hexapod_msgs
)

### Generating Services

### Generating Module File
_generate_module_cpp(hexapod_msgs
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hexapod_msgs
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(hexapod_msgs_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(hexapod_msgs_generate_messages hexapod_msgs_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/Pose.msg" NAME_WE)
add_dependencies(hexapod_msgs_generate_messages_cpp _hexapod_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/Sounds.msg" NAME_WE)
add_dependencies(hexapod_msgs_generate_messages_cpp _hexapod_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/LegJoints.msg" NAME_WE)
add_dependencies(hexapod_msgs_generate_messages_cpp _hexapod_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/LegsJoints.msg" NAME_WE)
add_dependencies(hexapod_msgs_generate_messages_cpp _hexapod_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/RPY.msg" NAME_WE)
add_dependencies(hexapod_msgs_generate_messages_cpp _hexapod_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/FeetPositions.msg" NAME_WE)
add_dependencies(hexapod_msgs_generate_messages_cpp _hexapod_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(hexapod_msgs_gencpp)
add_dependencies(hexapod_msgs_gencpp hexapod_msgs_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS hexapod_msgs_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(hexapod_msgs
  "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/Pose.msg"
  "${MSG_I_FLAGS}"
  "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/RPY.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hexapod_msgs
)
_generate_msg_lisp(hexapod_msgs
  "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/Sounds.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hexapod_msgs
)
_generate_msg_lisp(hexapod_msgs
  "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/LegJoints.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hexapod_msgs
)
_generate_msg_lisp(hexapod_msgs
  "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/LegsJoints.msg"
  "${MSG_I_FLAGS}"
  "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/LegJoints.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hexapod_msgs
)
_generate_msg_lisp(hexapod_msgs
  "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/RPY.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hexapod_msgs
)
_generate_msg_lisp(hexapod_msgs
  "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/FeetPositions.msg"
  "${MSG_I_FLAGS}"
  "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/Pose.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/RPY.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hexapod_msgs
)

### Generating Services

### Generating Module File
_generate_module_lisp(hexapod_msgs
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hexapod_msgs
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(hexapod_msgs_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(hexapod_msgs_generate_messages hexapod_msgs_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/Pose.msg" NAME_WE)
add_dependencies(hexapod_msgs_generate_messages_lisp _hexapod_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/Sounds.msg" NAME_WE)
add_dependencies(hexapod_msgs_generate_messages_lisp _hexapod_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/LegJoints.msg" NAME_WE)
add_dependencies(hexapod_msgs_generate_messages_lisp _hexapod_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/LegsJoints.msg" NAME_WE)
add_dependencies(hexapod_msgs_generate_messages_lisp _hexapod_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/RPY.msg" NAME_WE)
add_dependencies(hexapod_msgs_generate_messages_lisp _hexapod_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/FeetPositions.msg" NAME_WE)
add_dependencies(hexapod_msgs_generate_messages_lisp _hexapod_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(hexapod_msgs_genlisp)
add_dependencies(hexapod_msgs_genlisp hexapod_msgs_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS hexapod_msgs_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(hexapod_msgs
  "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/Pose.msg"
  "${MSG_I_FLAGS}"
  "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/RPY.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hexapod_msgs
)
_generate_msg_py(hexapod_msgs
  "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/Sounds.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hexapod_msgs
)
_generate_msg_py(hexapod_msgs
  "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/LegJoints.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hexapod_msgs
)
_generate_msg_py(hexapod_msgs
  "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/LegsJoints.msg"
  "${MSG_I_FLAGS}"
  "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/LegJoints.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hexapod_msgs
)
_generate_msg_py(hexapod_msgs
  "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/RPY.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hexapod_msgs
)
_generate_msg_py(hexapod_msgs
  "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/FeetPositions.msg"
  "${MSG_I_FLAGS}"
  "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/Pose.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/RPY.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hexapod_msgs
)

### Generating Services

### Generating Module File
_generate_module_py(hexapod_msgs
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hexapod_msgs
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(hexapod_msgs_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(hexapod_msgs_generate_messages hexapod_msgs_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/Pose.msg" NAME_WE)
add_dependencies(hexapod_msgs_generate_messages_py _hexapod_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/Sounds.msg" NAME_WE)
add_dependencies(hexapod_msgs_generate_messages_py _hexapod_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/LegJoints.msg" NAME_WE)
add_dependencies(hexapod_msgs_generate_messages_py _hexapod_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/LegsJoints.msg" NAME_WE)
add_dependencies(hexapod_msgs_generate_messages_py _hexapod_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/RPY.msg" NAME_WE)
add_dependencies(hexapod_msgs_generate_messages_py _hexapod_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/quan/hexapod_service_ws/src/hexapod_msgs/msg/FeetPositions.msg" NAME_WE)
add_dependencies(hexapod_msgs_generate_messages_py _hexapod_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(hexapod_msgs_genpy)
add_dependencies(hexapod_msgs_genpy hexapod_msgs_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS hexapod_msgs_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hexapod_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hexapod_msgs
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(hexapod_msgs_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(hexapod_msgs_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hexapod_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hexapod_msgs
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(hexapod_msgs_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(hexapod_msgs_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hexapod_msgs)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hexapod_msgs\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hexapod_msgs
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(hexapod_msgs_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(hexapod_msgs_generate_messages_py geometry_msgs_generate_messages_py)
endif()
