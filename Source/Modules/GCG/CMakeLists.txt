cmake_minimum_required(VERSION 3.20)
project (GCG)

#[[
	语言
#]]
enable_language(C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 清空SRC_LIST, INCLUDE_PATH
set (SRC_LIST "")
set (INCLUDE_PATH "")

# 头文件路径
list (APPEND INCLUDE_PATH ${PROJECT_SOURCE_DIR}/..)

# 源码文件
file(GLOB_RECURSE MODULE_SRC_LIST       ${PROJECT_SOURCE_DIR}/*.cpp
                                        ${PROJECT_SOURCE_DIR}/*.c
                                        ${PROJECT_SOURCE_DIR}/*.h)
list (APPEND SRC_LIST ${MODULE_SRC_LIST})


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

