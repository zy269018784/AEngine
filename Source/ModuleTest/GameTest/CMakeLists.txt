cmake_minimum_required(VERSION 3.20)
project (GameTest)
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
                            ${PROJECT_SOURCE_DIR}/Source/*.cc
                            ${PROJECT_SOURCE_DIR}/Source/*.h)

message (STATUS "GameTest CMAKE_SOURCE_DIR            ${CMAKE_SOURCE_DIR}")
message (STATUS "GameTest PROJECT_SOURCE_DIR          ${PROJECT_SOURCE_DIR}")
message (STATUS "GameTest CMAKE_CURRENT_SOURCE_DIR 	  ${CMAKE_CURRENT_SOURCE_DIR}")
message (STATUS "GameTest CMAKE_CURRENT_BINARY_DIR    ${CMAKE_CURRENT_BINARY_DIR}")
message (STATUS "GameTest LIBRARY_PATH                ${LIBRARY_PATH}")

# 库
if(NOT TARGET GArch)
    add_subdirectory(${PROJECT_SOURCE_DIR}/../../Modules/GArch ${CMAKE_CURRENT_BINARY_DIR}/Modules/GArch)
endif ()

if(NOT TARGET GCG)
    add_subdirectory(${PROJECT_SOURCE_DIR}/../../Modules/GCG ${CMAKE_CURRENT_BINARY_DIR}/Modules/GCG)
endif ()

if(NOT TARGET GDeviceDriver)
   add_subdirectory(${PROJECT_SOURCE_DIR}/../../Modules/GDeviceDriver ${CMAKE_CURRENT_BINARY_DIR}/Modules/GDeviceDriver)
endif ()

if(NOT TARGET GMath)
    add_subdirectory(${PROJECT_SOURCE_DIR}/../../Modules/GMath ${CMAKE_CURRENT_BINARY_DIR}/Modules/GMath)
endif ()

if(NOT TARGET GNetwork)
    add_subdirectory(${PROJECT_SOURCE_DIR}/../../Modules/GNetwork ${CMAKE_CURRENT_BINARY_DIR}/Modules/GNetwork)
endif ()

if(NOT TARGET GGame)
    add_subdirectory(${PROJECT_SOURCE_DIR}/../../Modules/GGame ${CMAKE_CURRENT_BINARY_DIR}/Modules/GGame)
endif ()

#if(NOT TARGET GRHI)
#    add_subdirectory(${PROJECT_SOURCE_DIR}/../../Modules/GRHI ${CMAKE_CURRENT_BINARY_DIR}/Modules/GRHI)
#endif ()

if(NOT TARGET GWindow)
    add_subdirectory(${PROJECT_SOURCE_DIR}/../../Modules/GWindow ${CMAKE_CURRENT_BINARY_DIR}/Modules/GWindow)
endif ()

if(NOT TARGET GDatabase)
    add_subdirectory(${PROJECT_SOURCE_DIR}/../../Modules/GDatabase ${CMAKE_CURRENT_BINARY_DIR}/Modules/GDatabase)
endif ()

if(NOT TARGET GProgramming)
    add_subdirectory(${PROJECT_SOURCE_DIR}/../../Modules/GProgramming ${CMAKE_CURRENT_BINARY_DIR}/Modules/GProgramming)
endif ()

if(NOT TARGET GMultimedia)
    add_subdirectory(${PROJECT_SOURCE_DIR}/../../Modules/GMultimedia ${CMAKE_CURRENT_BINARY_DIR}/Modules/GMultimedia)
endif ()


if(NOT TARGET GRenderDependencyGraph)
    add_subdirectory(${PROJECT_SOURCE_DIR}/../../Modules/GRenderDependencyGraph ${CMAKE_CURRENT_BINARY_DIR}/Modules/GRenderDependencyGraph)
endif ()

# 头文件路径
#set (INCLUDE_PATH "")
list (APPEND INCLUDE_PATH   ${PROJECT_SOURCE_DIR}/Source)
list (APPEND INCLUDE_PATH   ${PROJECT_SOURCE_DIR}/../../Modules)

# 链接库
set (LIBRARYS "")
list (APPEND LIBRARYS
        GArch
        GCG
        GMath
        GNetwork
        GWindow
        GGame
        GRenderDependencyGraph
        GDeviceDriver
        GDatabase
        GMultimedia
        GProgramming
)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_include_directories (${PROJECT_NAME}	PUBLIC ${INCLUDE_PATH})
target_link_directories (${PROJECT_NAME}	PUBLIC ${LINK_PATH})
target_link_libraries (${PROJECT_NAME} PUBLIC ${LIBRARYS})

target_compile_definitions(${PROJECT_NAME}  PRIVATE
        __STDC_CONSTANT_MACROS
        __STDC_FORMAT_MACROS
        __STDC_LIMIT_MACROS
)

target_compile_options(${PROJECT_NAME}  PRIVATE
        -fPIC
        -Wall
        -Wno-self-move
)
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_definitions (${PROJECT_NAME} PUBLIC OS_IS_WINDOWS=1)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_definitions (${PROJECT_NAME} PUBLIC OS_IS_LINUX=1)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Android")
    target_compile_definitions (${PROJECT_NAME} PUBLIC OS_IS_ANDROIS=1)
elseif (CMAKE_SYSTEM_NAME STREQUAL "iOS")

elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")

elseif (CMAKE_SYSTEM_NAME STREQUAL "QNX")

elseif (CMAKE_SYSTEM_NAME STREQUAL "NintendoSwitch")

elseif (CMAKE_SYSTEM_NAME STREQUAL "Fuchsia")

elseif (CMAKE_SYSTEM_NAME STREQUAL "GGP")

elseif (CMAKE_SYSTEM_NAME STREQUAL "OHOS")

endif ()
