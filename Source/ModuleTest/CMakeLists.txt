cmake_minimum_required(VERSION 3.20)
project (ModuleTest)
#[[
	语言
#]]
enable_language(C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message (STATUS "ModuleTest CMAKE_SOURCE_DIR            ${CMAKE_SOURCE_DIR}")
message (STATUS "ModuleTest PROJECT_SOURCE_DIR          ${PROJECT_SOURCE_DIR}")
message (STATUS "ModuleTest CMAKE_CURRENT_SOURCE_DIR 	${CMAKE_CURRENT_SOURCE_DIR}")
message (STATUS "ModuleTest CMAKE_CURRENT_BINARY_DIR    ${CMAKE_CURRENT_BINARY_DIR}")
message (STATUS "ModuleTest LIBRARY_PATH                ${LIBRARY_PATH}")

add_subdirectory(${PROJECT_SOURCE_DIR}/RHITest)
add_subdirectory(${PROJECT_SOURCE_DIR}/HelloWorld)
