cmake_minimum_required(VERSION 3.20)
project (RHITest)
#[[
	语言
#]]
enable_language(C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


list (APPEND INCLUDE_PATH   ${PROJECT_SOURCE_DIR}/Source)

file(GLOB_RECURSE SRC_LIST  ${PROJECT_SOURCE_DIR}/Source/*.cpp
                            ${PROJECT_SOURCE_DIR}/Source/*.c
                            ${PROJECT_SOURCE_DIR}/Source/*.h)

message (STATUS "RHITest CMAKE_SOURCE_DIR            ${CMAKE_SOURCE_DIR}")
message (STATUS "RHITest PROJECT_SOURCE_DIR          ${PROJECT_SOURCE_DIR}")
message (STATUS "RHITest CMAKE_CURRENT_SOURCE_DIR 	 ${CMAKE_CURRENT_SOURCE_DIR}")
message (STATUS "RHITest CMAKE_CURRENT_BINARY_DIR    ${CMAKE_CURRENT_BINARY_DIR}")
message (STATUS "RHITest LIBRARY_PATH                ${LIBRARY_PATH}")

if(NOT TARGET RHI)
    add_subdirectory(${CMAKE_SOURCE_DIR}/../Modules/RHI ${CMAKE_CURRENT_BINARY_DIR}/Modules/RHI)
endif ()

if(NOT TARGET Window)
    add_subdirectory(${CMAKE_SOURCE_DIR}/../Modules/Window ${CMAKE_CURRENT_BINARY_DIR}/Modules/Window)
endif ()

# 依赖库
list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/glfw/3.3.10/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/glfw/3.3.10/lib)
list (APPEND LIBRARYS		glfw3)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_include_directories (${PROJECT_NAME}	PUBLIC ${INCLUDE_PATH})
target_link_directories (${PROJECT_NAME}	PUBLIC ${LINK_PATH})
target_link_libraries (${PROJECT_NAME} PUBLIC ${LIBRARYS} RHI Window)