cmake_minimum_required(VERSION 3.20)
project (Game)

list (APPEND INCLUDE_PATH ${PROJECT_SOURCE_DIR})

message (STATUS "Game CMAKE_SOURCE_DIR            ${CMAKE_SOURCE_DIR}")
message (STATUS "Game PROJECT_SOURCE_DIR          ${PROJECT_SOURCE_DIR}")
message (STATUS "Game CMAKE_CURRENT_SOURCE_DIR 	${CMAKE_CURRENT_SOURCE_DIR}")
message (STATUS "Game CMAKE_CURRENT_BINARY_DIR    ${CMAKE_CURRENT_BINARY_DIR}")
message (STATUS "Game LIBRARY_PATH                ${LIBRARY_PATH}")
message (STATUS "Game USE_VULKAN                  ${USE_VULKAN}")
message (STATUS "Game OS_IS_WINDOWS               ${OS_IS_WINDOWS}")

# 清空SRC_LIST
set (SRC_LIST "")

file(GLOB_RECURSE     CODEC_SRC_LIST                  ${PROJECT_SOURCE_DIR}/Source/*.cpp
                                        ${PROJECT_SOURCE_DIR}/Source/*.c
                                        ${PROJECT_SOURCE_DIR}/Source/*.h)
list (APPEND SRC_LIST ${CODEC_SRC_LIST})
list (APPEND INCLUDE_PATH ${PROJECT_SOURCE_DIR}/Source)


add_library(${PROJECT_NAME}	 SHARED ${SRC_LIST})

target_include_directories (${PROJECT_NAME}	PUBLIC ${INCLUDE_PATH})
target_link_directories (${PROJECT_NAME}	PUBLIC ${LINK_PATH})
target_link_libraries (${PROJECT_NAME} PUBLIC ${LIBRARYS})

add_library(${PROJECT_NAME}-Static	 ${SRC_LIST})
target_include_directories (${PROJECT_NAME}-Static	PUBLIC ${INCLUDE_PATH})
target_link_directories (${PROJECT_NAME}-Static	PUBLIC ${LINK_PATH})
target_link_libraries (${PROJECT_NAME}-Static PUBLIC ${LIBRARYS})

