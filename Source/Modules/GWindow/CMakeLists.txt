cmake_minimum_required(VERSION 3.20)
project (GWindow)


# 配置支持哪些窗口
set (USE_GLFW       true)
set (USE_CEF        false)
set (USE_FLTK       true)
set (USE_QT         true)
set (USE_SDL        true)
set (USE_SFML       false)
set (USE_wxWidget   false)
set (USE_X11        true)
set (USE_MFC        true)
if (NOT CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set (USE_MFC false)
endif ()

#
set (INCLUDE_PATH "")
list (APPEND INCLUDE_PATH ${PROJECT_SOURCE_DIR})
list (APPEND INCLUDE_PATH ${PROJECT_SOURCE_DIR}/..)

message (STATUS "Window CMAKE_SOURCE_DIR            ${CMAKE_SOURCE_DIR}")
message (STATUS "Window PROJECT_SOURCE_DIR          ${PROJECT_SOURCE_DIR}")
message (STATUS "Window CMAKE_CURRENT_SOURCE_DIR 	${CMAKE_CURRENT_SOURCE_DIR}")
message (STATUS "Window CMAKE_CURRENT_BINARY_DIR    ${CMAKE_CURRENT_BINARY_DIR}")
message (STATUS "Window LIBRARY_PATH                ${LIBRARY_PATH}")
message (STATUS "Window USE_VULKAN                  ${USE_VULKAN}")
message (STATUS "Window OS_IS_WINDOWS                  ${OS_IS_WINDOWS}")

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
    list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/glfw/3.4/include)
    list (APPEND LINK_PATH      ${LIBRARY_PATH}/glfw/3.4/lib)
    list (APPEND LIBRARYS		glfw3)
endif ()


# cef
if (USE_CEF)
    file(GLOB_RECURSE CEF_SRC_LIST          ${PROJECT_SOURCE_DIR}/CEFWindow/*.cpp
                                            ${PROJECT_SOURCE_DIR}/CEFWindow/*.c
                                            ${PROJECT_SOURCE_DIR}/CEFWindow/*.h)
    list (APPEND SRC_LIST ${CEF_SRC_LIST})
    # 依赖库
    list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/cef/148.0.9)
    list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/cef/148.0.9/include)
    list (APPEND LINK_PATH      ${LIBRARY_PATH}/cef/148.0.9/lib)
    list (APPEND LIBRARYS		cef cef_dll_wrapper)
endif ()

# fltk
if (USE_FLTK)
    file(GLOB_RECURSE FLTK_SRC_LIST         ${PROJECT_SOURCE_DIR}/FLTKWindow/*.cpp
                                            ${PROJECT_SOURCE_DIR}/FLTKWindow/*.c
                                            ${PROJECT_SOURCE_DIR}/FLTKWindow/*.h)
    list (APPEND SRC_LIST ${FLTK_SRC_LIST})
    # 依赖库
    list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/fltk/1.4.4/include)
    list (APPEND LINK_PATH      ${LIBRARY_PATH}/fltk/1.4.4/lib)
    list (APPEND LIBRARYS		fltk fltk_forms  fltk_gl  fltk_images)
    list (APPEND LIBRARYS
                                X11-xcb
                                X11
                                Xext
                                Xrender
                                Xcursor
                                Xfixes
                                Xinerama
                                Xft
                                fontconfig
                                dl
                                m
                                pthread)
endif ()

# qt
if (USE_QT)
    file(GLOB_RECURSE QT_SRC_LIST           ${PROJECT_SOURCE_DIR}/QTWindow/*.cpp
                                            ${PROJECT_SOURCE_DIR}/QTWindow/*.c
                                            ${PROJECT_SOURCE_DIR}/QTWindow/*.h)
    list (APPEND SRC_LIST ${QT_SRC_LIST})

    set(CMAKE_AUTOMOC ON)                         # 自动处理信号槽等元对象编译[citation:9]
    set(CMAKE_AUTORCC ON)                         # 自动处理 .qrc 资源文件[citation:9]
    set(CMAKE_AUTOUIC ON)
    find_package(Qt6 REQUIRED COMPONENTS Widgets)
    list (APPEND LIBRARYS		Qt6::Widgets)
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
    file(GLOB_RECURSE SDL_SRC_LIST          ${PROJECT_SOURCE_DIR}/SDLWindow/*.cpp
                                            ${PROJECT_SOURCE_DIR}/SDLWindow/*.c
                                            ${PROJECT_SOURCE_DIR}/SDLWindow/*.h)
    list (APPEND SRC_LIST ${SDL_SRC_LIST})
    # 依赖库
    list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/SDL/3.2.24/include)
    list (APPEND LINK_PATH      ${LIBRARY_PATH}/SDL/3.2.24/lib)
    list (APPEND LIBRARYS		SDL3)
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
if (USE_wxWidget)
    file(GLOB_RECURSE WXWIDGET_SRC_LIST     ${PROJECT_SOURCE_DIR}/wxWidgetWindow/*.cpp
                                            ${PROJECT_SOURCE_DIR}/wxWidgetWindow/*.c
                                            ${PROJECT_SOURCE_DIR}/wxWidgetWindow/*.h)
    list (APPEND SRC_LIST ${WXWIDGET_SRC_LIST})
    # 依赖库
    list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/wxWidgets/3.3.1/include)
    list (APPEND LINK_PATH      ${LIBRARY_PATH}/wxWidgets/3.3.1/lib)
    list (APPEND LIBRARYS		wx_gtk3u_core-3.3)
endif ()

list (APPEND SRC_LIST ${SRC_LIST_RHI})

if (USE_VULKAN)
    list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/Vulkan/include)
    list (APPEND LINK_PATH      ${LIBRARY_PATH}/Vulkan/lib)
    list (APPEND LIBRARYS		vulkan)
endif ()


add_library(${PROJECT_NAME}	 SHARED ${SRC_LIST})

target_include_directories (${PROJECT_NAME}	PUBLIC ${INCLUDE_PATH})
target_link_directories (${PROJECT_NAME}	PUBLIC ${LINK_PATH})
target_link_libraries (${PROJECT_NAME} PUBLIC ${LIBRARYS})

add_library(${PROJECT_NAME}-Static	 ${SRC_LIST})
target_include_directories (${PROJECT_NAME}-Static	PUBLIC ${INCLUDE_PATH})
target_link_directories (${PROJECT_NAME}-Static	PUBLIC ${LINK_PATH})
target_link_libraries (${PROJECT_NAME}-Static PUBLIC ${LIBRARYS})

# vulkan开关宏定义
target_compile_definitions (${PROJECT_NAME} PUBLIC WINDOWS_USE_VULKAN=${USE_VULKAN})
# OS宏定义
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_definitions (${PROJECT_NAME} PUBLIC OS_IS_WINDOWS=1)
    target_compile_definitions (${PROJECT_NAME}-Static PUBLIC OS_IS_WINDOWS=1)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_definitions (${PROJECT_NAME} PUBLIC OS_IS_LINUX=1)
    target_compile_definitions (${PROJECT_NAME}-Static PUBLIC OS_IS_LINUX=1)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Android")
    target_compile_definitions (${PROJECT_NAME} PUBLIC OS_IS_ANDROIS=1)
    target_compile_definitions (${PROJECT_NAME}-Static PUBLIC OS_IS_ANDROIS=1)
elseif (CMAKE_SYSTEM_NAME STREQUAL "iOS")

elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")

elseif (CMAKE_SYSTEM_NAME STREQUAL "QNX")

elseif (CMAKE_SYSTEM_NAME STREQUAL "NintendoSwitch")

elseif (CMAKE_SYSTEM_NAME STREQUAL "Fuchsia")

elseif (CMAKE_SYSTEM_NAME STREQUAL "GGP")

elseif (CMAKE_SYSTEM_NAME STREQUAL "OHOS")

endif ()
