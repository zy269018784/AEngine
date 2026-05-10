cmake_minimum_required(VERSION 3.20)
project (HelloWorld)
#[[
	语言
#]]
enable_language(C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SRC_LIST  ${PROJECT_SOURCE_DIR}/Source/*.cpp
                            ${PROJECT_SOURCE_DIR}/Source/*.c
                            ${PROJECT_SOURCE_DIR}/Source/*.h)

message (STATUS "HelloWorld CMAKE_SOURCE_DIR            ${CMAKE_SOURCE_DIR}")
message (STATUS "HelloWorld PROJECT_SOURCE_DIR          ${PROJECT_SOURCE_DIR}")
message (STATUS "HelloWorld CMAKE_CURRENT_SOURCE_DIR 	${CMAKE_CURRENT_SOURCE_DIR}")
message (STATUS "HelloWorld CMAKE_CURRENT_BINARY_DIR    ${CMAKE_CURRENT_BINARY_DIR}")
message (STATUS "HelloWorld LIBRARY_PATH                ${LIBRARY_PATH}")

if(NOT TARGET RHI)
    add_subdirectory(${PROJECT_SOURCE_DIR}/../../Modules/RHI ${CMAKE_CURRENT_BINARY_DIR})
endif ()

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_include_directories (${PROJECT_NAME}	PUBLIC ${INCLUDE_PATH})
target_link_directories (${PROJECT_NAME}	PUBLIC ${LINK_PATH})
target_link_libraries (${PROJECT_NAME} PUBLIC ${LIBRARYS} RHI)