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

#[[
	宏定义
#]]
if (${USE_FLTK})
    target_compile_definitions (${PROJECT_NAME} PUBLIC PROJECT_USE_FTLK)
endif ()

if (${USE_SFML})
    target_compile_definitions (${PROJECT_NAME} PUBLIC PROJECT_USE_SFML)
endif ()

if (${USE_QT})
    target_compile_definitions (${PROJECT_NAME} PUBLIC PROJECT_USE_QT)
endif ()

if (${USE_X11})
    target_compile_definitions (${PROJECT_NAME} PUBLIC PROJECT_USE_X11)
endif ()

if (${USE_MFC})
    target_compile_definitions (${PROJECT_NAME} PUBLIC PROJECT_USE_MFC)
endif ()

if (${USE_GLFW})
    target_compile_definitions (${PROJECT_NAME} PUBLIC PROJECT_USE_GLFW)
endif ()

if (${USE_wxWidget})
    target_compile_definitions (${PROJECT_NAME} PUBLIC PROJECT_USE_wxWidget)
endif ()

if (${USE_LVGL})
    target_compile_definitions (${PROJECT_NAME} PUBLIC PROJECT_USE_LVGL)
endif ()

if (${USE_CEGUI})
    target_compile_definitions (${PROJECT_NAME} PUBLIC PROJECT_USE_CEGUI)
endif ()

if (${USE_MYGUI})
    target_compile_definitions (${PROJECT_NAME} PUBLIC PROJECT_USE_MYGUI)
endif ()






