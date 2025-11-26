set (USE_FLTK       false)
set (USE_SFML       false)
set (USE_QT         false)
set (USE_GLFW       true)
set (USE_wxWidget   false)
set (USE_X11        false)
set (USE_MFC        false)
set (USE_CEGUI      false)
set (USE_MYGUI      false)
set (USE_LVGL       false)

if (NOT CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set (USE_X11    false)
endif ()

if (CMAKE_SYSTEM_NAME STREQUAL "Window")
    set (USE_MFC    false)
endif ()




