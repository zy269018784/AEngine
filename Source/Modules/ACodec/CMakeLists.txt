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


list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/ffmpeg/8.0.1/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/ffmpeg/8.0.1/lib)
list (APPEND LIBRARYS		avcodec avdevice avfilter avformat avutil swresample swscale)
list (APPEND INCLUDE_PATH ${PROJECT_SOURCE_DIR}/Source)

add_library(${PROJECT_NAME}	 SHARED ${SRC_LIST})

target_include_directories (${PROJECT_NAME}	PUBLIC ${INCLUDE_PATH})
target_link_directories (${PROJECT_NAME}	PUBLIC ${LINK_PATH})
target_link_libraries (${PROJECT_NAME} PUBLIC ${LIBRARYS})

add_library(${PROJECT_NAME}-Static	 ${SRC_LIST})
target_include_directories (${PROJECT_NAME}-Static	PUBLIC ${INCLUDE_PATH})
target_link_directories (${PROJECT_NAME}-Static	PUBLIC ${LINK_PATH})
target_link_libraries (${PROJECT_NAME}-Static PUBLIC ${LIBRARYS})

