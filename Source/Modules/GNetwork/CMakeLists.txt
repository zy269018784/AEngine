cmake_minimum_required(VERSION 3.20)
project (GNetwork)

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

# 库
set (LIBRARYS "")

message (STATUS "GNetwork LIBRARY_PATH ${LIBRARY_PATH}")
# 三方库
# mqtt
list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/mqtt/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/mqtt/lib)
list (APPEND LIBRARYS		mqtt)
# curl
list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/curl/8.17.0/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/curl/8.17.0/lib)
list (APPEND LIBRARYS		curl)

# openssl
list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/openssl/3.2.0/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/openssl/3.2.0/lib)
list (APPEND LIBRARYS		ssl crypto)
# curl
list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/httplib/0.48.0/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/httplib/0.48.0/lib)

# 自定义库
# GCore
if(NOT TARGET GCore)
    add_subdirectory(${PROJECT_SOURCE_DIR}/../GCore ${CMAKE_CURRENT_BINARY_DIR}/Modules/GCore)
endif ()
list (APPEND LIBRARYS GCore)

# 模块源码文件
file(GLOB_RECURSE MODULE_SRC_LIST       ${PROJECT_SOURCE_DIR}/*.cpp
                                        ${PROJECT_SOURCE_DIR}/*.c
                                        ${PROJECT_SOURCE_DIR}/*.h)

# 源码文件
set (SRC_LIST "")
list (APPEND SRC_LIST ${MODULE_SRC_LIST})

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

