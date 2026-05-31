cmake_minimum_required(VERSION 3.20)
project (ACodec)

list (APPEND INCLUDE_PATH ${PROJECT_SOURCE_DIR})

message (STATUS "AVCodec CMAKE_SOURCE_DIR            ${CMAKE_SOURCE_DIR}")
message (STATUS "AVCodec PROJECT_SOURCE_DIR          ${PROJECT_SOURCE_DIR}")
message (STATUS "AVCodec CMAKE_CURRENT_SOURCE_DIR 	${CMAKE_CURRENT_SOURCE_DIR}")
message (STATUS "AVCodec CMAKE_CURRENT_BINARY_DIR    ${CMAKE_CURRENT_BINARY_DIR}")
message (STATUS "AVCodec LIBRARY_PATH                ${LIBRARY_PATH}")
message (STATUS "AVCodec USE_VULKAN                  ${USE_VULKAN}")
message (STATUS "AVCodec OS_IS_WINDOWS               ${OS_IS_WINDOWS}")

# 清空SRC_LIST
set (SRC_LIST "")

file(GLOB_RECURSE     CODEC_SRC_LIST                  ${PROJECT_SOURCE_DIR}/Source/*.cpp
                                        ${PROJECT_SOURCE_DIR}/Source/*.c
                                        ${PROJECT_SOURCE_DIR}/Source/*.h)
list (APPEND SRC_LIST ${CODEC_SRC_LIST})

list (APPEND INCLUDE_PATH ${PROJECT_SOURCE_DIR}/Source)

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/ffmpeg/8.0.1/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/ffmpeg/8.0.1/lib)
list (APPEND LIBRARYS		avcodec avdevice avfilter avformat avutil swresample swscale)

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/gstreamer/include
                            ${LIBRARY_PATH}/gstreamer/include/gstreamer-1.0
                            ${LIBRARY_PATH}/gstreamer/include/glib-2.0
                            ${LIBRARY_PATH}/gstreamer/lib/glib-2.0/include
)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/gstreamer/lib)
list (APPEND LIBRARYS		gobject-2.0
                            gstcodecs-1.0 gsttranscoder-1.0
                            gstvideo-1.0 gstaudio-1.0
                            gstnet-1.0  gstrtp-1.0 gstsdp-1.0
                            gstrtsp-1.0 gstrtspserver-1.0
                            gstwebrtc-1.0
                            gstplay-1.0 gstplayer-1.0
                            gstallocators-1.0
                            gstd3d11-1.0 gstd3d12-1.0 gstcuda-1.0
)

add_library(${PROJECT_NAME}	 SHARED ${SRC_LIST})

target_include_directories (${PROJECT_NAME}	PUBLIC ${INCLUDE_PATH})
target_link_directories (${PROJECT_NAME}	PUBLIC ${LINK_PATH})
target_link_libraries (${PROJECT_NAME} PUBLIC ${LIBRARYS})

add_library(${PROJECT_NAME}-Static	 ${SRC_LIST})
target_include_directories (${PROJECT_NAME}-Static	PUBLIC ${INCLUDE_PATH})
target_link_directories (${PROJECT_NAME}-Static	PUBLIC ${LINK_PATH})
target_link_libraries (${PROJECT_NAME}-Static PUBLIC ${LIBRARYS})

