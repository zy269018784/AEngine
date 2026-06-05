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

list (APPEND INCLUDE_PATH ../..)

# 清空SRC_LIST
set (SRC_LIST "")

file(GLOB_RECURSE MODULE_SRC_LIST       ${PROJECT_SOURCE_DIR}/Source/*.cpp
                                        ${PROJECT_SOURCE_DIR}/Source/*.c
                                        ${PROJECT_SOURCE_DIR}/Source/*.h)
list (APPEND SRC_LIST ${MODULE_SRC_LIST})
list (APPEND INCLUDE_PATH ../../Source)

add_library(${PROJECT_NAME}	 SHARED ${SRC_LIST})

target_include_directories (${PROJECT_NAME}	PUBLIC ${INCLUDE_PATH})
target_link_directories (${PROJECT_NAME}	PUBLIC ${LINK_PATH})
target_link_libraries (${PROJECT_NAME} PUBLIC ${LIBRARYS})

add_library(${PROJECT_NAME}-Static	 ${SRC_LIST})
target_include_directories (${PROJECT_NAME}-Static	PUBLIC ${INCLUDE_PATH})
target_link_directories (${PROJECT_NAME}-Static	PUBLIC ${LINK_PATH})
target_link_libraries (${PROJECT_NAME}-Static PUBLIC ${LIBRARYS})

