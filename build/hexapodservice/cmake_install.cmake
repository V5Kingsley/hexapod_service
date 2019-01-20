# Install script for directory: /home/sun/hexapod_service_ws/src/hexapodservice

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/sun/hexapod_service_ws/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/hexapodservice/msg" TYPE FILE FILES
    "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoints.msg"
    "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legjoint.msg"
    "/home/sun/hexapod_service_ws/src/hexapodservice/msg/legs.msg"
    "/home/sun/hexapod_service_ws/src/hexapodservice/msg/leg.msg"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/hexapodservice/action" TYPE FILE FILES "/home/sun/hexapod_service_ws/src/hexapodservice/action/hexapodservice.action")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/hexapodservice/msg" TYPE FILE FILES
    "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceAction.msg"
    "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionGoal.msg"
    "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionResult.msg"
    "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionFeedback.msg"
    "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceGoal.msg"
    "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceResult.msg"
    "/home/sun/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceFeedback.msg"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/hexapodservice/cmake" TYPE FILE FILES "/home/sun/hexapod_service_ws/build/hexapodservice/catkin_generated/installspace/hexapodservice-msg-paths.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/sun/hexapod_service_ws/devel/include/hexapodservice")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/sun/hexapod_service_ws/devel/share/roseus/ros/hexapodservice")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/sun/hexapod_service_ws/devel/share/common-lisp/ros/hexapodservice")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gennodejs/ros" TYPE DIRECTORY FILES "/home/sun/hexapod_service_ws/devel/share/gennodejs/ros/hexapodservice")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  execute_process(COMMAND "/usr/bin/python" -m compileall "/home/sun/hexapod_service_ws/devel/lib/python2.7/dist-packages/hexapodservice")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/sun/hexapod_service_ws/devel/lib/python2.7/dist-packages/hexapodservice")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/sun/hexapod_service_ws/build/hexapodservice/catkin_generated/installspace/hexapodservice.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/hexapodservice/cmake" TYPE FILE FILES "/home/sun/hexapod_service_ws/build/hexapodservice/catkin_generated/installspace/hexapodservice-msg-extras.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/hexapodservice/cmake" TYPE FILE FILES
    "/home/sun/hexapod_service_ws/build/hexapodservice/catkin_generated/installspace/hexapodserviceConfig.cmake"
    "/home/sun/hexapod_service_ws/build/hexapodservice/catkin_generated/installspace/hexapodserviceConfig-version.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/hexapodservice" TYPE FILE FILES "/home/sun/hexapod_service_ws/src/hexapodservice/package.xml")
endif()

