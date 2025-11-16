cmake_minimum_required(VERSION 3.20)
project (Engine)
#[[
	语言
#]]
enable_language(C)
set(CMAKE_C_STANDARD 11)        
set(CMAKE_C_STANDARD_REQUIRED ON) 

enable_language(CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include (CMakeScripts/Libiary.cmake)

message(STATUS "项目名称: ${PROJECT_NAME}")   
message(STATUS "INCLUDE_PATH: ${INCLUDE_PATH}")   
message(STATUS "LINK_PATH: ${LINK_PATH}")   
message(STATUS "LIBRARYS: ${LIBRARYS}")   


add_executable(${PROJECT_NAME} Source/main.cpp)
target_include_directories (${PROJECT_NAME}	PUBLIC ${INCLUDE_PATH})
target_link_directories (${PROJECT_NAME}	PUBLIC ${LINK_PATH})
target_link_libraries (${PROJECT_NAME} PUBLIC ${LIBRARYS})


#[[
	操作系统宏定义
#]]
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
	target_compile_definitions (${PROJECT_NAME} PUBLIC OS_IS_WINDOWS)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
	target_compile_definitions (${PROJECT_NAME} PUBLIC OS_IS_LINUX)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Android")
	target_compile_definitions (${PROJECT_NAME} PUBLIC OS_IS_ANDROID)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
	target_compile_definitions (${PROJECT_NAME} PUBLIC OS_IS_MACOS)
endif ()
