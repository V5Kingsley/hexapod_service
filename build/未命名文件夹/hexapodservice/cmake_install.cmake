# Install script for directory: /home/quan/hexapod_service_ws/src/未命名文件夹/hexapodservice

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/quan/hexapod_service_ws/install")
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

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/hexapodservice/msg" TYPE FILE FILES
    "/home/quan/hexapod_service_ws/src/未命名文件夹/hexapodservice/msg/legjoints.msg"
    "/home/quan/hexapod_service_ws/src/未命名文件夹/hexapodservice/msg/legjoint.msg"
    "/home/quan/hexapod_service_ws/src/未命名文件夹/hexapodservice/msg/legs.msg"
    "/home/quan/hexapod_service_ws/src/未命名文件夹/hexapodservice/msg/leg.msg"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/hexapodservice/action" TYPE FILE FILES "/home/quan/hexapod_service_ws/src/未命名文件夹/hexapodservice/action/hexapodservice.action")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/hexapodservice/msg" TYPE FILE FILES
    "/home/quan/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceAction.msg"
    "/home/quan/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionGoal.msg"
    "/home/quan/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionResult.msg"
    "/home/quan/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceActionFeedback.msg"
    "/home/quan/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceGoal.msg"
    "/home/quan/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceResult.msg"
    "/home/quan/hexapod_service_ws/devel/share/hexapodservice/msg/hexapodserviceFeedback.msg"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/hexapodservice/cmake" TYPE FILE FILES "/home/quan/hexapod_service_ws/build/未命名文件夹/hexapodservice/catkin_generated/installspace/hexapodservice-msg-paths.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/quan/hexapod_service_ws/devel/include/hexapodservice")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/quan/hexapod_service_ws/devel/share/common-lisp/ros/hexapodservice")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND "/usr/bin/python" -m compileall "/home/quan/hexapod_service_ws/devel/lib/python2.7/dist-packages/hexapodservice")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/quan/hexapod_service_ws/devel/lib/python2.7/dist-packages/hexapodservice")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/quan/hexapod_service_ws/build/未命名文件夹/hexapodservice/catkin_generated/installspace/hexapodservice.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/hexapodservice/cmake" TYPE FILE FILES "/home/quan/hexapod_service_ws/build/未命名文件夹/hexapodservice/catkin_generated/installspace/hexapodservice-msg-extras.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/hexapodservice/cmake" TYPE FILE FILES
    "/home/quan/hexapod_service_ws/build/未命名文件夹/hexapodservice/catkin_generated/installspace/hexapodserviceConfig.cmake"
    "/home/quan/hexapod_service_ws/build/未命名文件夹/hexapodservice/catkin_generated/installspace/hexapodserviceConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/hexapodservice" TYPE FILE FILES "/home/quan/hexapod_service_ws/src/未命名文件夹/hexapodservice/package.xml")
endif()

