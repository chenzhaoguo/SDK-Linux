cmake_minimum_required(VERSION 2.8.3)
project(indemind_module)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  sensor_msgs
  std_msgs
  geometry_msgs
  cv_bridge
  tf
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES indemind_module
  CATKIN_DEPENDS roscpp rospy sensor_msgs std_msgs geometry_msgs tf
)


include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

 add_executable(module_driver src/camera_driver.cpp)

 add_dependencies(module_driver ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

 target_link_libraries(module_driver
   ${PROJECT_SOURCE_DIR}/../../lib/1604/libindem.so
   ${catkin_LIBRARIES}
   ${PROJECT_SOURCE_DIR}/../../lib/1604/libboost_filesystem.so.1.58.0
   ${PROJECT_SOURCE_DIR}/../../lib/1604/libboost_system.so.1.58.0
   ${PROJECT_SOURCE_DIR}/../../lib/1604/libg3logger.so.1.3.0-0
   ${PROJECT_SOURCE_DIR}/../../lib/1604/libnanomsg.so.5
   ${PROJECT_SOURCE_DIR}/../../lib/1604/libopencv_core.so.3.4
   ${PROJECT_SOURCE_DIR}/../../lib/1604/libopencv_imgproc.so.3.4
   ${PROJECT_SOURCE_DIR}/../../lib/1604/libopencv_videoio.so.3.4
   pthread
   stdc++fs
   dl
 )

