cmake_minimum_required(VERSION 3.20)
project (WindowTest)
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

# 依赖库
list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/glfw/3.3.10/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/glfw/3.3.10/lib)
list (APPEND LIBRARYS		glfw3)

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/fltk/1.4.4/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/fltk/1.4.4/lib)
list (APPEND LIBRARYS		fltk fltk_forms fltk_gl fltk_images fltk_jpeg fltk_png fltk_z )
# fltk 链接了gdi+
list (APPEND LIBRARYS		gdiplus ws2_32 comctl32 user32)


list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/stb/include)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_include_directories (${PROJECT_NAME}	PUBLIC ${INCLUDE_PATH})
target_link_directories (${PROJECT_NAME}	PUBLIC ${LINK_PATH})
target_link_libraries (${PROJECT_NAME} PUBLIC ${LIBRARYS})


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