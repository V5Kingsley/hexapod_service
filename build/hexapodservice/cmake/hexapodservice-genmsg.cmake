# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "hexapodservice: 11 messages, 0 services")

set(MSG_I_FLAGS "-Ihexapodservice:/home/sun/hexapod_service_ws/src/hexapodservice/msg;-Ihexapodservice:/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg;-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg;-Iactionlib_msgs:/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(hexapodservice_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionFeedback.msg" NAME_WE)
add_custom_target(_hexapodservice_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "hexapodservice" "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionFeedback.msg" "hexapodservice/leg:std_msgs/Header:hexapodservice/legjoint:actionlib_msgs/GoalID:hexapodservice/hexapodserviceFeedback:actionlib_msgs/GoalStatus"
)

get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceAction.msg" NAME_WE)
add_custom_target(_hexapodservice_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "hexapodservice" "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceAction.msg" "hexapodservice/hexapodserviceActionFeedback:hexapodservice/hexapodserviceActionResult:hexapodservice/legjoint:std_msgs/Header:hexapodservice/legjoints:hexapodservice/leg:hexapodservice/hexapodserviceActionGoal:hexapodservice/legs:hexapodservice/hexapodserviceGoal:hexapodservice/hexapodserviceResult:actionlib_msgs/GoalID:hexapodservice/hexapodserviceFeedback:actionlib_msgs/GoalStatus"
)

get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceGoal.msg" NAME_WE)
add_custom_target(_hexapodservice_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "hexapodservice" "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceGoal.msg" "hexapodservice/legjoints:hexapodservice/legs"
)

get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionGoal.msg" NAME_WE)
add_custom_target(_hexapodservice_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "hexapodservice" "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionGoal.msg" "hexapodservice/legs:hexapodservice/legjoints:actionlib_msgs/GoalID:std_msgs/Header:hexapodservice/hexapodserviceGoal"
)

get_filename_component(_filename "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoints.msg" NAME_WE)
add_custom_target(_hexapodservice_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "hexapodservice" "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoints.msg" ""
)

get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceFeedback.msg" NAME_WE)
add_custom_target(_hexapodservice_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "hexapodservice" "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceFeedback.msg" "hexapodservice/legjoint:hexapodservice/leg"
)

get_filename_component(_filename "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoint.msg" NAME_WE)
add_custom_target(_hexapodservice_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "hexapodservice" "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoint.msg" ""
)

get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionResult.msg" NAME_WE)
add_custom_target(_hexapodservice_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "hexapodservice" "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionResult.msg" "hexapodservice/hexapodserviceResult:actionlib_msgs/GoalID:std_msgs/Header:actionlib_msgs/GoalStatus"
)

get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceResult.msg" NAME_WE)
add_custom_target(_hexapodservice_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "hexapodservice" "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceResult.msg" ""
)

get_filename_component(_filename "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legs.msg" NAME_WE)
add_custom_target(_hexapodservice_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "hexapodservice" "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legs.msg" "hexapodservice/legjoints"
)

get_filename_component(_filename "/home/sun/hexapod_service_ws/src/hexapodservice/msg/leg.msg" NAME_WE)
add_custom_target(_hexapodservice_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "hexapodservice" "/home/sun/hexapod_service_ws/src/hexapodservice/msg/leg.msg" "hexapodservice/legjoint"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(hexapodservice
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionFeedback.msg"
  "${MSG_I_FLAGS}"
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/leg.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoint.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceFeedback.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hexapodservice
)
_generate_msg_cpp(hexapodservice
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceAction.msg"
  "${MSG_I_FLAGS}"
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionFeedback.msg;/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionResult.msg;/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoint.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoints.msg;/home/sun/hexapod_service_ws/src/hexapodservice/msg/leg.msg;/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionGoal.msg;/home/sun/hexapod_service_ws/src/hexapodservice/msg/legs.msg;/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceGoal.msg;/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceResult.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceFeedback.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hexapodservice
)
_generate_msg_cpp(hexapodservice
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceGoal.msg"
  "${MSG_I_FLAGS}"
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoints.msg;/home/sun/hexapod_service_ws/src/hexapodservice/msg/legs.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hexapodservice
)
_generate_msg_cpp(hexapodservice
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionGoal.msg"
  "${MSG_I_FLAGS}"
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legs.msg;/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoints.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceGoal.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hexapodservice
)
_generate_msg_cpp(hexapodservice
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoints.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hexapodservice
)
_generate_msg_cpp(hexapodservice
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceFeedback.msg"
  "${MSG_I_FLAGS}"
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoint.msg;/home/sun/hexapod_service_ws/src/hexapodservice/msg/leg.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hexapodservice
)
_generate_msg_cpp(hexapodservice
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoint.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hexapodservice
)
_generate_msg_cpp(hexapodservice
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionResult.msg"
  "${MSG_I_FLAGS}"
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceResult.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hexapodservice
)
_generate_msg_cpp(hexapodservice
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceResult.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hexapodservice
)
_generate_msg_cpp(hexapodservice
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legs.msg"
  "${MSG_I_FLAGS}"
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoints.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hexapodservice
)
_generate_msg_cpp(hexapodservice
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/leg.msg"
  "${MSG_I_FLAGS}"
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoint.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hexapodservice
)

### Generating Services

### Generating Module File
_generate_module_cpp(hexapodservice
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hexapodservice
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(hexapodservice_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(hexapodservice_generate_messages hexapodservice_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionFeedback.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_cpp _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceAction.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_cpp _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceGoal.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_cpp _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionGoal.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_cpp _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoints.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_cpp _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceFeedback.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_cpp _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoint.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_cpp _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionResult.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_cpp _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceResult.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_cpp _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legs.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_cpp _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/src/hexapodservice/msg/leg.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_cpp _hexapodservice_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(hexapodservice_gencpp)
add_dependencies(hexapodservice_gencpp hexapodservice_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS hexapodservice_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(hexapodservice
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionFeedback.msg"
  "${MSG_I_FLAGS}"
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/leg.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoint.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceFeedback.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/hexapodservice
)
_generate_msg_eus(hexapodservice
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceAction.msg"
  "${MSG_I_FLAGS}"
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionFeedback.msg;/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionResult.msg;/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoint.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoints.msg;/home/sun/hexapod_service_ws/src/hexapodservice/msg/leg.msg;/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionGoal.msg;/home/sun/hexapod_service_ws/src/hexapodservice/msg/legs.msg;/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceGoal.msg;/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceResult.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceFeedback.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/hexapodservice
)
_generate_msg_eus(hexapodservice
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceGoal.msg"
  "${MSG_I_FLAGS}"
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoints.msg;/home/sun/hexapod_service_ws/src/hexapodservice/msg/legs.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/hexapodservice
)
_generate_msg_eus(hexapodservice
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionGoal.msg"
  "${MSG_I_FLAGS}"
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legs.msg;/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoints.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceGoal.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/hexapodservice
)
_generate_msg_eus(hexapodservice
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoints.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/hexapodservice
)
_generate_msg_eus(hexapodservice
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceFeedback.msg"
  "${MSG_I_FLAGS}"
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoint.msg;/home/sun/hexapod_service_ws/src/hexapodservice/msg/leg.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/hexapodservice
)
_generate_msg_eus(hexapodservice
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoint.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/hexapodservice
)
_generate_msg_eus(hexapodservice
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionResult.msg"
  "${MSG_I_FLAGS}"
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceResult.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/hexapodservice
)
_generate_msg_eus(hexapodservice
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceResult.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/hexapodservice
)
_generate_msg_eus(hexapodservice
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legs.msg"
  "${MSG_I_FLAGS}"
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoints.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/hexapodservice
)
_generate_msg_eus(hexapodservice
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/leg.msg"
  "${MSG_I_FLAGS}"
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoint.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/hexapodservice
)

### Generating Services

### Generating Module File
_generate_module_eus(hexapodservice
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/hexapodservice
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(hexapodservice_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(hexapodservice_generate_messages hexapodservice_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionFeedback.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_eus _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceAction.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_eus _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceGoal.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_eus _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionGoal.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_eus _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoints.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_eus _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceFeedback.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_eus _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoint.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_eus _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionResult.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_eus _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceResult.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_eus _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legs.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_eus _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/src/hexapodservice/msg/leg.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_eus _hexapodservice_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(hexapodservice_geneus)
add_dependencies(hexapodservice_geneus hexapodservice_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS hexapodservice_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(hexapodservice
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionFeedback.msg"
  "${MSG_I_FLAGS}"
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/leg.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoint.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceFeedback.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hexapodservice
)
_generate_msg_lisp(hexapodservice
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceAction.msg"
  "${MSG_I_FLAGS}"
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionFeedback.msg;/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionResult.msg;/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoint.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoints.msg;/home/sun/hexapod_service_ws/src/hexapodservice/msg/leg.msg;/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionGoal.msg;/home/sun/hexapod_service_ws/src/hexapodservice/msg/legs.msg;/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceGoal.msg;/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceResult.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceFeedback.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hexapodservice
)
_generate_msg_lisp(hexapodservice
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceGoal.msg"
  "${MSG_I_FLAGS}"
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoints.msg;/home/sun/hexapod_service_ws/src/hexapodservice/msg/legs.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hexapodservice
)
_generate_msg_lisp(hexapodservice
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionGoal.msg"
  "${MSG_I_FLAGS}"
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legs.msg;/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoints.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceGoal.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hexapodservice
)
_generate_msg_lisp(hexapodservice
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoints.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hexapodservice
)
_generate_msg_lisp(hexapodservice
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceFeedback.msg"
  "${MSG_I_FLAGS}"
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoint.msg;/home/sun/hexapod_service_ws/src/hexapodservice/msg/leg.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hexapodservice
)
_generate_msg_lisp(hexapodservice
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoint.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hexapodservice
)
_generate_msg_lisp(hexapodservice
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionResult.msg"
  "${MSG_I_FLAGS}"
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceResult.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hexapodservice
)
_generate_msg_lisp(hexapodservice
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceResult.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hexapodservice
)
_generate_msg_lisp(hexapodservice
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legs.msg"
  "${MSG_I_FLAGS}"
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoints.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hexapodservice
)
_generate_msg_lisp(hexapodservice
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/leg.msg"
  "${MSG_I_FLAGS}"
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoint.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hexapodservice
)

### Generating Services

### Generating Module File
_generate_module_lisp(hexapodservice
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hexapodservice
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(hexapodservice_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(hexapodservice_generate_messages hexapodservice_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionFeedback.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_lisp _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceAction.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_lisp _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceGoal.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_lisp _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionGoal.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_lisp _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoints.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_lisp _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceFeedback.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_lisp _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoint.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_lisp _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionResult.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_lisp _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceResult.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_lisp _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legs.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_lisp _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/src/hexapodservice/msg/leg.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_lisp _hexapodservice_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(hexapodservice_genlisp)
add_dependencies(hexapodservice_genlisp hexapodservice_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS hexapodservice_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(hexapodservice
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionFeedback.msg"
  "${MSG_I_FLAGS}"
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/leg.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoint.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceFeedback.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/hexapodservice
)
_generate_msg_nodejs(hexapodservice
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceAction.msg"
  "${MSG_I_FLAGS}"
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionFeedback.msg;/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionResult.msg;/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoint.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoints.msg;/home/sun/hexapod_service_ws/src/hexapodservice/msg/leg.msg;/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionGoal.msg;/home/sun/hexapod_service_ws/src/hexapodservice/msg/legs.msg;/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceGoal.msg;/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceResult.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceFeedback.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/hexapodservice
)
_generate_msg_nodejs(hexapodservice
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceGoal.msg"
  "${MSG_I_FLAGS}"
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoints.msg;/home/sun/hexapod_service_ws/src/hexapodservice/msg/legs.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/hexapodservice
)
_generate_msg_nodejs(hexapodservice
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionGoal.msg"
  "${MSG_I_FLAGS}"
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legs.msg;/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoints.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceGoal.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/hexapodservice
)
_generate_msg_nodejs(hexapodservice
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoints.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/hexapodservice
)
_generate_msg_nodejs(hexapodservice
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceFeedback.msg"
  "${MSG_I_FLAGS}"
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoint.msg;/home/sun/hexapod_service_ws/src/hexapodservice/msg/leg.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/hexapodservice
)
_generate_msg_nodejs(hexapodservice
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoint.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/hexapodservice
)
_generate_msg_nodejs(hexapodservice
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionResult.msg"
  "${MSG_I_FLAGS}"
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceResult.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/hexapodservice
)
_generate_msg_nodejs(hexapodservice
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceResult.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/hexapodservice
)
_generate_msg_nodejs(hexapodservice
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legs.msg"
  "${MSG_I_FLAGS}"
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoints.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/hexapodservice
)
_generate_msg_nodejs(hexapodservice
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/leg.msg"
  "${MSG_I_FLAGS}"
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoint.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/hexapodservice
)

### Generating Services

### Generating Module File
_generate_module_nodejs(hexapodservice
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/hexapodservice
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(hexapodservice_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(hexapodservice_generate_messages hexapodservice_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionFeedback.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_nodejs _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceAction.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_nodejs _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceGoal.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_nodejs _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionGoal.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_nodejs _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoints.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_nodejs _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceFeedback.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_nodejs _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoint.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_nodejs _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionResult.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_nodejs _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceResult.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_nodejs _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legs.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_nodejs _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/src/hexapodservice/msg/leg.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_nodejs _hexapodservice_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(hexapodservice_gennodejs)
add_dependencies(hexapodservice_gennodejs hexapodservice_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS hexapodservice_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(hexapodservice
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionFeedback.msg"
  "${MSG_I_FLAGS}"
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/leg.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoint.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceFeedback.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hexapodservice
)
_generate_msg_py(hexapodservice
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceAction.msg"
  "${MSG_I_FLAGS}"
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionFeedback.msg;/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionResult.msg;/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoint.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoints.msg;/home/sun/hexapod_service_ws/src/hexapodservice/msg/leg.msg;/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionGoal.msg;/home/sun/hexapod_service_ws/src/hexapodservice/msg/legs.msg;/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceGoal.msg;/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceResult.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceFeedback.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hexapodservice
)
_generate_msg_py(hexapodservice
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceGoal.msg"
  "${MSG_I_FLAGS}"
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoints.msg;/home/sun/hexapod_service_ws/src/hexapodservice/msg/legs.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hexapodservice
)
_generate_msg_py(hexapodservice
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionGoal.msg"
  "${MSG_I_FLAGS}"
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legs.msg;/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoints.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceGoal.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hexapodservice
)
_generate_msg_py(hexapodservice
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoints.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hexapodservice
)
_generate_msg_py(hexapodservice
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceFeedback.msg"
  "${MSG_I_FLAGS}"
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoint.msg;/home/sun/hexapod_service_ws/src/hexapodservice/msg/leg.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hexapodservice
)
_generate_msg_py(hexapodservice
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoint.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hexapodservice
)
_generate_msg_py(hexapodservice
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionResult.msg"
  "${MSG_I_FLAGS}"
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceResult.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hexapodservice
)
_generate_msg_py(hexapodservice
  "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceResult.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hexapodservice
)
_generate_msg_py(hexapodservice
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legs.msg"
  "${MSG_I_FLAGS}"
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoints.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hexapodservice
)
_generate_msg_py(hexapodservice
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/leg.msg"
  "${MSG_I_FLAGS}"
  "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoint.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hexapodservice
)

### Generating Services

### Generating Module File
_generate_module_py(hexapodservice
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hexapodservice
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(hexapodservice_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(hexapodservice_generate_messages hexapodservice_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionFeedback.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_py _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceAction.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_py _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceGoal.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_py _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionGoal.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_py _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoints.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_py _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceFeedback.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_py _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoint.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_py _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionResult.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_py _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceResult.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_py _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legs.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_py _hexapodservice_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sun/hexapod_service_ws/src/hexapodservice/msg/leg.msg" NAME_WE)
add_dependencies(hexapodservice_generate_messages_py _hexapodservice_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(hexapodservice_genpy)
add_dependencies(hexapodservice_genpy hexapodservice_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS hexapodservice_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hexapodservice)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hexapodservice
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(hexapodservice_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET actionlib_msgs_generate_messages_cpp)
  add_dependencies(hexapodservice_generate_messages_cpp actionlib_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/hexapodservice)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/hexapodservice
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(hexapodservice_generate_messages_eus std_msgs_generate_messages_eus)
endif()
if(TARGET actionlib_msgs_generate_messages_eus)
  add_dependencies(hexapodservice_generate_messages_eus actionlib_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hexapodservice)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hexapodservice
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(hexapodservice_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET actionlib_msgs_generate_messages_lisp)
  add_dependencies(hexapodservice_generate_messages_lisp actionlib_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/hexapodservice)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/hexapodservice
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(hexapodservice_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()
if(TARGET actionlib_msgs_generate_messages_nodejs)
  add_dependencies(hexapodservice_generate_messages_nodejs actionlib_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hexapodservice)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hexapodservice\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hexapodservice
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(hexapodservice_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET actionlib_msgs_generate_messages_py)
  add_dependencies(hexapodservice_generate_messages_py actionlib_msgs_generate_messages_py)
endif()
