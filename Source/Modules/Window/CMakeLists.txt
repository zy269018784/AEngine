cmake_minimum_required(VERSION 3.20)
project (Window)


# 配置支持哪些窗口
set (USE_GLFW       true)
set (USE_CEF        false)
set (USE_FLTK       false)
set (USE_QT         false)
set (USE_SDL        false)
set (USE_SFML       false)
set (USE_wxWidget   false)
set (USE_X11        false)
set (USE_MFC        true)
if (NOT CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set (USE_MFC false)
endif ()

list (APPEND INCLUDE_PATH ${PROJECT_SOURCE_DIR})

message (STATUS "Window CMAKE_SOURCE_DIR            ${CMAKE_SOURCE_DIR}")
message (STATUS "Window PROJECT_SOURCE_DIR          ${PROJECT_SOURCE_DIR}")
message (STATUS "Window CMAKE_CURRENT_SOURCE_DIR 	${CMAKE_CURRENT_SOURCE_DIR}")
message (STATUS "Window CMAKE_CURRENT_BINARY_DIR    ${CMAKE_CURRENT_BINARY_DIR}")
message (STATUS "Window LIBRARY_PATH                ${LIBRARY_PATH}")

# 清空SRC_LIST
set (SRC_LIST "")

file(GLOB IWINDOW_SRC_LIST                  ${PROJECT_SOURCE_DIR}/*.cpp
                                            ${PROJECT_SOURCE_DIR}/*.c
                                            ${PROJECT_SOURCE_DIR}/*.h)
list (APPEND SRC_LIST ${IWINDOW_SRC_LIST})

# glfw
if (USE_GLFW)
    file(GLOB_RECURSE GLFW_SRC_LIST         ${PROJECT_SOURCE_DIR}/GLFWWindow/*.cpp
                                            ${PROJECT_SOURCE_DIR}/GLFWWindow/*.c
                                            ${PROJECT_SOURCE_DIR}/GLFWWindow/*.h)
    list (APPEND SRC_LIST ${GLFW_SRC_LIST})
    # 依赖库
    list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/glfw/3.3.10/include)
    list (APPEND LINK_PATH      ${LIBRARY_PATH}/glfw/3.3.10/lib)
    list (APPEND LIBRARYS		glfw3)
endif ()


# cef
if (USE_CEF)
    file(GLOB_RECURSE CEF_SRC_LIST         ${PROJECT_SOURCE_DIR}/CEFWindow/*.cpp
            ${PROJECT_SOURCE_DIR}/CEFWindow/*.c
            ${PROJECT_SOURCE_DIR}/CEFWindow/*.h)
    list (APPEND SRC_LIST ${CEF_SRC_LIST})
endif ()

# fltk
if (USE_FLTK)
    file(GLOB_RECURSE FLTK_SRC_LIST        ${PROJECT_SOURCE_DIR}/FLTKWindow/*.cpp
            ${PROJECT_SOURCE_DIR}/FLTKWindow/*.c
            ${PROJECT_SOURCE_DIR}/FLTKWindow/*.h)
    list (APPEND SRC_LIST ${FLTK_SRC_LIST})
endif ()

# qt
if (USE_QT)
    file(GLOB_RECURSE QT_SRC_LIST          ${PROJECT_SOURCE_DIR}/QTWindow/*.cpp
            ${PROJECT_SOURCE_DIR}/QTWindow/*.c
            ${PROJECT_SOURCE_DIR}/QTWindow/*.h)
    list (APPEND SRC_LIST ${QT_SRC_LIST})
endif ()

# mfc
if (USE_MFC)
    file(GLOB_RECURSE MFC_SRC_LIST         ${PROJECT_SOURCE_DIR}/MFCWindow/*.cpp
            ${PROJECT_SOURCE_DIR}/MFCWindow/*.c
            ${PROJECT_SOURCE_DIR}/MFCWindow/*.h)
    list (APPEND SRC_LIST ${MFC_SRC_LIST})
endif ()

# sdl
if (USE_SDL)
    file(GLOB_RECURSE SDL_SRC_LIST         ${PROJECT_SOURCE_DIR}/SDLWindow/*.cpp
            ${PROJECT_SOURCE_DIR}/SDLWindow/*.c
            ${PROJECT_SOURCE_DIR}/SDLWindow/*.h)
    list (APPEND SRC_LIST ${SDL_SRC_LIST})
endif ()

# x11
if (USE_X11)
    file(GLOB_RECURSE X11_SRC_LIST         ${PROJECT_SOURCE_DIR}/X11Window/*.cpp
            ${PROJECT_SOURCE_DIR}/X11Window/*.c
            ${PROJECT_SOURCE_DIR}/X11Window/*.h)
    list (APPEND SRC_LIST ${X11_SRC_LIST})
endif ()

# sfml
if (USE_SFML)
    file(GLOB_RECURSE SFML_SRC_LIST        ${PROJECT_SOURCE_DIR}/SFMLWindow/*.cpp
            ${PROJECT_SOURCE_DIR}/SFMLWindow/*.c
            ${PROJECT_SOURCE_DIR}/SFMLWindow/*.h)
    list (APPEND SRC_LIST ${SFML_SRC_LIST})
endif ()

# wxwidget
if (USE_WXWIDGET)
    file(GLOB_RECURSE WXWIDGET_SRC_LIST    ${PROJECT_SOURCE_DIR}/wxWidgetWindow/*.cpp
            ${PROJECT_SOURCE_DIR}/wxWidgetWindow/*.c
            ${PROJECT_SOURCE_DIR}/wxWidgetWindow/*.h)
    list (APPEND SRC_LIST ${WXWIDGET_SRC_LIST})
endif ()

list (APPEND SRC_LIST ${SRC_LIST_RHI})

add_library(${PROJECT_NAME}	 SHARED ${SRC_LIST})

target_include_directories (${PROJECT_NAME}	PUBLIC ${INCLUDE_PATH})
target_link_directories (${PROJECT_NAME}	PUBLIC ${LINK_PATH})
target_link_libraries (${PROJECT_NAME} PUBLIC ${LIBRARYS})

add_library(${PROJECT_NAME}-Static	 ${SRC_LIST})
target_include_directories (${PROJECT_NAME}-Static	PUBLIC ${INCLUDE_PATH})
target_link_directories (${PROJECT_NAME}-Static	PUBLIC ${LINK_PATH})
target_link_libraries (${PROJECT_NAME}-Static PUBLIC ${LIBRARYS})





