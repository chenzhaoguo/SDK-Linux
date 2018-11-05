cmake_minimum_required (VERSION 2.8)

project(TestIndem)

include_directories(../include)
add_executable(${PROJECT_NAME} Indem.cpp)
target_link_libraries(${PROJECT_NAME}
pthread
${CMAKE_SOURCE_DIR}/../lib/libindem.a
stdc++fs
${CMAKE_SOURCE_DIR}/../lib/libboost_system.so.1.68.0
${CMAKE_SOURCE_DIR}/../lib/libboost_filesystem.so.1.68.0
${CMAKE_SOURCE_DIR}/../lib/libz.so
${CMAKE_SOURCE_DIR}/../lib/libdl.so
${CMAKE_SOURCE_DIR}/../lib/libtbb.so.2
${CMAKE_SOURCE_DIR}/../lib/libslam_imp.so
${CMAKE_SOURCE_DIR}/../lib/libg3logger.so.1.3.0-0
${CMAKE_SOURCE_DIR}/../lib/libDBoW2.so
${CMAKE_SOURCE_DIR}/../lib/libDLib.so
${CMAKE_SOURCE_DIR}/../lib/libprotobuf.so.14
${CMAKE_SOURCE_DIR}/../lib/libnanomsg.so.5
${CMAKE_SOURCE_DIR}/../lib/libslam.so
${CMAKE_SOURCE_DIR}/../lib/libusbdriver.so
${CMAKE_SOURCE_DIR}/../lib/libhandle_fuse.so
${CMAKE_SOURCE_DIR}/../lib/libopencv_imgproc.so.3.4
${CMAKE_SOURCE_DIR}/../lib/libopencv_core.so.3.4
${CMAKE_SOURCE_DIR}/../lib/libopencv_imgcodecs.so.3.4
${CMAKE_SOURCE_DIR}/../lib/libopencv_highgui.so.3.4
${CMAKE_SOURCE_DIR}/../lib/libopencv_features2d.so.3.4
${CMAKE_SOURCE_DIR}/../lib/libopencv_videoio.so.3.4
${CMAKE_SOURCE_DIR}/../lib/libyujing.so
${CMAKE_SOURCE_DIR}/../lib/plugin/depthimage/libdepthimage.so
)
