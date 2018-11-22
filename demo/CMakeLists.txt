cmake_minimum_required (VERSION 2.8)

project(TestIndem)

include_directories(../include)

add_definitions(-std=c++11)
add_executable(${PROJECT_NAME} Indem.cpp)
target_link_libraries(${PROJECT_NAME}
${CMAKE_SOURCE_DIR}/../lib/1604/libindem.a
${CMAKE_SOURCE_DIR}/../lib/1604/libslam.so
${CMAKE_SOURCE_DIR}/../lib/1604/libyujing.so
${CMAKE_SOURCE_DIR}/../lib/1604/libslam_imp.so
${CMAKE_SOURCE_DIR}/../lib/1604/libusbdriver.so
${CMAKE_SOURCE_DIR}/../lib/1604/plugin/depthimage/libdepthimage.so
pthread
stdc++fs
z
dl
${CMAKE_SOURCE_DIR}/../lib/1604/libtbb.so.2
${CMAKE_SOURCE_DIR}/../lib/1604/libg3logger.so.1.3.0-0
${CMAKE_SOURCE_DIR}/../lib/1604/libprotobuf.so.14
${CMAKE_SOURCE_DIR}/../lib/1604/libnanomsg.so.5
${CMAKE_SOURCE_DIR}/../lib/1604/libhandle_fuse.so
${CMAKE_SOURCE_DIR}/../lib/1604/libopencv_imgproc.so.3.4
${CMAKE_SOURCE_DIR}/../lib/1604/libopencv_core.so.3.4
${CMAKE_SOURCE_DIR}/../lib/1604/libopencv_imgcodecs.so.3.4
${CMAKE_SOURCE_DIR}/../lib/1604/libopencv_highgui.so.3.4
${CMAKE_SOURCE_DIR}/../lib/1604/libopencv_features2d.so.3.4
${CMAKE_SOURCE_DIR}/../lib/1604/libopencv_videoio.so.3.4
${CMAKE_SOURCE_DIR}/../lib/1604/libboost_system.so.1.68.0
${CMAKE_SOURCE_DIR}/../lib/1604/libboost_filesystem.so.1.68.0
)
