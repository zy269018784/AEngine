cmake_minimum_required(VERSION 3.20)
project (GMultimedia)

#[[
	语言
#]]
enable_language(C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 头文件路径
set (INCLUDE_PATH "")
list (APPEND INCLUDE_PATH ${PROJECT_SOURCE_DIR}/..)
list (APPEND INCLUDE_PATH ${PROJECT_SOURCE_DIR})

# 模块源码文件
file(GLOB_RECURSE MODULE_SRC_LIST       ${PROJECT_SOURCE_DIR}/*.cpp
                                        ${PROJECT_SOURCE_DIR}/*.c
                                        ${PROJECT_SOURCE_DIR}/*.h)

# 源码文件
set (SRC_LIST "")
list (APPEND SRC_LIST ${MODULE_SRC_LIST})

# 库
set (LIBRARYS "")
# 三方库
# ffmpeg
list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/ffmpeg/8.0.1/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/ffmpeg/8.0.1/lib)
list (APPEND LIBRARYS		avdevice  avfilter  avformat  avutil  swscale swresample)
# curl
list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/ffmpeg/8.0.1/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/ffmpeg/8.0.1/lib)
list (APPEND LIBRARYS		avdevice  avfilter  avformat  avutil  swscale swresample)
# fdk-aac
list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/fdk-aac/2.0.3/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/fdk-aac/2.0.3/lib)
list (APPEND LIBRARYS		fdk-aac)
# flac
list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/FLAC/1.5.0/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/FLAC/1.5.0/lib)
list (APPEND LIBRARYS		FLAC++ FLAC)
# lame
list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/libmp3lame/3.100.2/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/libmp3lame/3.100.2/lib)
list (APPEND LIBRARYS		mp3lame)
# ogg
list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/ogg/1.3.6/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/ogg/1.3.6/lib)
list (APPEND LIBRARYS		ogg)
# vorbis
list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/libvorbis/1.3.7/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/libvorbis/1.3.7/lib)
list (APPEND LIBRARYS		vorbis vorbisenc vorbisfile)
# opus
list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/opus/1.6.1/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/opus/1.6.1/lib)
list (APPEND LIBRARYS		opus)
# twolame
list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/libtwolame/0.4.0/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/libtwolame/0.4.0/lib)
#list (APPEND LIBRARYS		twolame)


# 链接GCore库
if(NOT TARGET GCore)
    add_subdirectory(${PROJECT_SOURCE_DIR}/../GCore ${CMAKE_CURRENT_BINARY_DIR}/Modules/GCore)
endif ()

list (APPEND LIBRARYS GCore)

# 动态库
add_library(${PROJECT_NAME}	 SHARED ${SRC_LIST})
target_include_directories (${PROJECT_NAME}	PUBLIC ${INCLUDE_PATH})
target_link_directories (${PROJECT_NAME}	PUBLIC ${LINK_PATH})
target_link_libraries (${PROJECT_NAME} PUBLIC ${LIBRARYS})

if (false)
    add_library(${PROJECT_NAME}-Static	 ${SRC_LIST})
    target_include_directories (${PROJECT_NAME}-Static	PUBLIC ${INCLUDE_PATH})
    target_link_directories (${PROJECT_NAME}-Static	PUBLIC ${LINK_PATH})
    target_link_libraries (${PROJECT_NAME}-Static PUBLIC ${LIBRARYS})
endif ()

