#[[
	操作系统宏定义
#]]
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_definitions (${APP_NAME} PUBLIC OS_IS_WINDOWS)
    target_compile_definitions (${APP_NAME} PUBLIC NOMINMAX)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_definitions (${APP_NAME} PUBLIC OS_IS_LINUX)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Android")
    target_compile_definitions (${APP_NAME} PUBLIC OS_IS_ANDROID)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_compile_definitions (${APP_NAME} PUBLIC OS_IS_MACOS)
endif ()

#[[
	宏定义
#]]
if (${USE_FLTK})
    target_compile_definitions (${APP_NAME} PUBLIC PROJECT_USE_FTLK)
endif ()

if (${USE_SFML})
    target_compile_definitions (${APP_NAME} PUBLIC PROJECT_USE_SFML)
endif ()

if (${USE_QT})
    target_compile_definitions (${APP_NAME} PUBLIC PROJECT_USE_QT)
endif ()

if (${USE_Xlib})
    target_compile_definitions (${APP_NAME} PUBLIC PROJECT_USE_Xlib)
endif ()

if (${USE_XCB})
    target_compile_definitions (${APP_NAME} PUBLIC PROJECT_USE_XCB)
endif ()

if (${USE_MFC})
    target_compile_definitions (${APP_NAME} PUBLIC PROJECT_USE_MFC)
endif ()

if (${USE_GLFW})
    target_compile_definitions (${APP_NAME} PUBLIC PROJECT_USE_GLFW)
endif ()

if (${USE_wxWidget})
    target_compile_definitions (${APP_NAME} PUBLIC PROJECT_USE_wxWidget)
endif ()

if (${USE_LVGL})
    target_compile_definitions (${APP_NAME} PUBLIC PROJECT_USE_LVGL)
endif ()

if (${USE_CEGUI})
    target_compile_definitions (${APP_NAME} PUBLIC PROJECT_USE_CEGUI)
endif ()

if (${USE_MYGUI})
    target_compile_definitions (${APP_NAME} PUBLIC PROJECT_USE_MYGUI)
endif ()

if (${USE_DXFRW})
    target_compile_definitions (${APP_NAME} PUBLIC PROJECT_USE_DXFRW)
endif ()

if (${USE_SDL3})
    target_compile_definitions (${APP_NAME} PUBLIC PROJECT_USE_SDL3)
endif ()

if (${USE_BOOST})
    target_compile_definitions (${APP_NAME} PUBLIC PROJECT_USE_BOOST)
endif ()

if (${USE_CURL})
    target_compile_definitions (${APP_NAME} PUBLIC PROJECT_USE_CURL)
endif ()

if (${USE_OGG})
    target_compile_definitions (${APP_NAME} PUBLIC PROJECT_USE_OGG)
endif ()

if (${USE_VORBIS})
    target_compile_definitions (${APP_NAME} PUBLIC PROJECT_USE_VORBIS)
endif ()

if (${USE_LAEM})
    target_compile_definitions (${APP_NAME} PUBLIC PROJECT_USE_LAME)
endif ()

if (${USE_ASSIMP})
    target_compile_definitions (${APP_NAME} PUBLIC PROJECT_USE_ASSIMP)
endif ()

if (${USE_CEF})
    target_compile_definitions (${APP_NAME} PUBLIC PROJECT_USE_CEF)
endif ()

if (${USE_STB})
    target_compile_definitions (${APP_NAME} PUBLIC PROJECT_USE_STB)
endif ()

if (${USE_OPENEXR})
    target_compile_definitions (${APP_NAME} PUBLIC PROJECT_USE_OPENEXR)
endif ()

if (${USE_FLAC})
    target_compile_definitions (${APP_NAME} PUBLIC PROJECT_USE_FLAC)
endif ()

if (${USE_OPUS})
    target_compile_definitions (${APP_NAME} PUBLIC PROJECT_USE_OPUS)
endif ()

if (${USE_ALSA})
    target_compile_definitions (${APP_NAME} PUBLIC PROJECT_USE_ALSA)
endif ()

if (${USE_FDKAAC})
    target_compile_definitions (${APP_NAME} PUBLIC PROJECT_USE_FDKAAC)
endif ()

if (${USE_WEBP})
    target_compile_definitions (${APP_NAME} PUBLIC PROJECT_USE_WEBP)
endif ()

if (${USE_IrrKlang})
    target_compile_definitions (${APP_NAME} PUBLIC PROJECT_USE_IrrKlang)
endif ()

if (${USE_PORTAUDIO})
    target_compile_definitions (${APP_NAME} PUBLIC PROJECT_USE_PORTAUDIO)
endif ()

if (${USE_MP3LAME})
    target_compile_definitions (${APP_NAME} PUBLIC PROJECT_USE_MP3LAME)
endif ()


if (${USE_D3D12})
    target_compile_definitions (${APP_NAME} PUBLIC PROJECT_USE_D3D12)
endif ()


if (${USE_MODBUS})
    target_compile_definitions (${APP_NAME} PUBLIC PROJECT_USE_MODBUS)
endif ()

if (${USE_GLM})
    target_compile_definitions (${APP_NAME} PUBLIC PROJECT_USE_GLM)
endif ()

if (${USE_VULKAN})
    target_compile_definitions (${APP_NAME} PUBLIC PROJECT_USE_VULKAN)
endif ()

if (${USE_BLUEZ})
    target_compile_definitions (${APP_NAME} PUBLIC PROJECT_USE_BLUEZ)
endif ()

if (${USE_LIVE555})
    target_compile_definitions (${APP_NAME} PUBLIC PROJECT_USE_LIVE555)
endif ()

if (${USE_embroidery})
    target_compile_definitions (${APP_NAME} PUBLIC PROJECT_USE_embroidery)
endif ()
