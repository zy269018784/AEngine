cmake_minimum_required(VERSION 3.20)
project (Tuorial)
#[[
	语言
#]]
enable_language(C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message (STATUS "Tuorial CMAKE_SOURCE_DIR            ${CMAKE_SOURCE_DIR}")
message (STATUS "Tuorial PROJECT_SOURCE_DIR          ${PROJECT_SOURCE_DIR}")
message (STATUS "Tuorial CMAKE_CURRENT_SOURCE_DIR 	${CMAKE_CURRENT_SOURCE_DIR}")
message (STATUS "Tuorial CMAKE_CURRENT_BINARY_DIR    ${CMAKE_CURRENT_BINARY_DIR}")
message (STATUS "Tuorial LIBRARY_PATH                ${LIBRARY_PATH}")

add_subdirectory(${PROJECT_SOURCE_DIR}/OpenGL)
add_subdirectory(${PROJECT_SOURCE_DIR}/Vulkan)
add_subdirectory(${PROJECT_SOURCE_DIR}/Qt)
add_subdirectory(${PROJECT_SOURCE_DIR}/Cegui)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_subdirectory(${PROJECT_SOURCE_DIR}/D3D12)
    add_subdirectory(${PROJECT_SOURCE_DIR}/D3D11)
    add_subdirectory(${PROJECT_SOURCE_DIR}/D3D10)
    add_subdirectory(${PROJECT_SOURCE_DIR}/D3D9)
    add_subdirectory(${PROJECT_SOURCE_DIR}/WinSocket)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_subdirectory(${PROJECT_SOURCE_DIR}/LinuxSocket)
endif ()
