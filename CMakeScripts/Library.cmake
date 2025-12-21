set (LIBRARY_PATH ${PROJECT_SOURCE_DIR}/../Library)

#[[
        QT
#]]
if (${USE_QT})
	set (CMAKE_AUTOMOC ON)
	set (CMAKE_AUTOUIC ON)
	set (CMAKE_AUTORCC ON)
	message (STATUS "CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH}")
	if (USE_QT6)
		find_package(Qt6 COMPONENTS Widgets Qml Quick QuickControls2 QuickWidgets SerialBus REQUIRED)
		set (QT_LIBS
				Qt6::Widgets
				Qt6::QuickWidgets
				Qt6::Quick
				Qt6::Qml
				Qt6::QuickControls2
				Qt6::SerialBus
		)
	else ()
		find_package(Qt5 COMPONENTS Widgets Qml Quick QuickControls2 QuickWidgets SerialBus REQUIRED)
		set (QT_LIBS Qt5::Widgets
				Qt5::QuickWidgets
				Qt5::Quick
				Qt5::Qml
				Qt5::QuickControls2
				Qt5::SerialBus
		)
	endif ()
	list(APPEND LIBRARYS ${QT_LIBS})
endif ()



if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
	list (APPEND LIBRARYS		asound)
	list (APPEND LIBRARYS		X11 X11-xcb Xcursor Xrandr Xinerama Xfixes)
	list (APPEND LIBRARYS		pango-1.0 pangocairo-1.0 pangoft2-1.0 pangoxft-1.0)
	list (APPEND LIBRARYS		gtk-3)
	list (APPEND LINK_PATH 		/usr/lib/x86_64-linux-gnu/)

	if (${USE_Xlib})
		list(APPEND LIBRARYS X11 X11-xcb)
	endif ()

	if (${USE_XCB})
		list(APPEND LIBRARYS xcb)
	endif ()
endif ()


if (${USE_D3D12})
	list(APPEND INCLUDE_PATH ${LIBRARY_PATH}/Direct3D/12/include)
	list(APPEND LINK_PATH    ${LIBRARY_PATH}/Direct3D/12/lib)
	list(APPEND LIBRARYS d3d12 d3dcompiler d3dcsx)
endif ()

if (${USE_FFMPEG})
	list(APPEND INCLUDE_PATH ${LIBRARY_PATH}/ffmpeg/8.0.1/include)
	list(APPEND LINK_PATH    ${LIBRARY_PATH}/ffmpeg/8.0.1/lib)
	list(APPEND LIBRARYS avcodec avdevice  avfilter  avformat  avutil  swscale swresample)
	if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
		list(APPEND LIBRARYS z bz2 lzma)
	endif()
endif ()


if (${USE_SFML})
	list(APPEND INCLUDE_PATH ${LIBRARY_PATH}/SFML/3.0.2/include)
	list(APPEND LINK_PATH    ${LIBRARY_PATH}/SFML/3.0.2/lib)
	list(APPEND LIBRARYS sfml-audio sfml-window sfml-graphics sfml-system)
if (CMAKE_SYSTEM_NAME STREQUAL "Window")
	list(APPEND LIBRARYS sfml-main)
endif ()
endif ()

if (${USE_FDKAAC})
	list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/fdk-aac/2.0.3/include
								${LIBRARY_PATH}/fdk-aac/2.0.3/fdk-aac
	)

	list (APPEND LINK_PATH      ${LIBRARY_PATH}/fdk-aac/2.0.3/lib)
	list (APPEND LIBRARYS		fdk-aac)
endif ()

if (${USE_IrrKlang})
	list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/irrKlang/1.6/include)
	list (APPEND LINK_PATH      ${LIBRARY_PATH}/irrKlang/1.6/lib)
	list (APPEND LIBRARYS		IrrKlang)
endif ()

if (${USE_OPUS})
	list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/opus/1.5.2/include)
	list (APPEND LINK_PATH      ${LIBRARY_PATH}/opus/1.5.2/lib)
	list (APPEND LIBRARYS		opus)
endif ()

if (${USE_OGG})
	list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/ogg/1.3.6/include)
	list (APPEND LINK_PATH      ${LIBRARY_PATH}/ogg/1.3.6/lib)
	list (APPEND LIBRARYS		ogg)
endif ()

if (${USE_PORTAUDIO})
	list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/PortAudio/v190700_20210406/include)
	list (APPEND LINK_PATH      ${LIBRARY_PATH}/PortAudio/v190700_20210406/lib)
	list (APPEND LIBRARYS		portaudio)
endif ()

if (${USE_TWOLAME})
	list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/libtwolame/0.4.0/include)
	list (APPEND LINK_PATH      ${LIBRARY_PATH}/libtwolame/0.4.0/lib)
	list (APPEND LIBRARYS		twolame)
endif ()

if (${USE_LC3})
	list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/liblc3/1.1.3/include)
	list (APPEND LINK_PATH      ${LIBRARY_PATH}/liblc3/1.1.3/lib)
	list (APPEND LIBRARYS		lc3)
endif ()


if (${USE_MQTT})
	list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/mqtt/include)
	list (APPEND LINK_PATH      ${LIBRARY_PATH}/mqtt/lib)
	list (APPEND LIBRARYS		mqtt)
endif ()

if (${USE_VORBIS})
	list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/libvorbis/1.3.7/include)
	list (APPEND LINK_PATH      ${LIBRARY_PATH}/libvorbis/1.3.7/lib)
	list (APPEND LIBRARYS		vorbis	vorbisenc vorbisfile)
endif ()

if (${USE_MP3LAME})
	list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/libmp3lame/3.100.2/include)
	list (APPEND LINK_PATH      ${LIBRARY_PATH}/libmp3lame/3.100.2/lib)
	list (APPEND LIBRARYS		mp3lame)
endif ()

if (${USE_FLAC})
		list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/libflac/1.5.0/include)
		list (APPEND LINK_PATH      ${LIBRARY_PATH}/libflac/1.5.0/lib)
		list (APPEND LIBRARYS		FLAC)
endif ()

if (${USE_FLAC})
	list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/FLAC/1.5.0/include)
	list (APPEND LINK_PATH      ${LIBRARY_PATH}/FLAC/1.5.0/lib)
	list (APPEND LIBRARYS		FLAC)
endif ()

if (${USE_WEBP})
	list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/webp/1.6.0/include)
	list (APPEND LINK_PATH      ${LIBRARY_PATH}/webp/1.6.0/lib)
	list (APPEND LIBRARYS		webp webpdecoder webpdemux webpmux sharpyuv)
endif ()

if (${USE_GIF})
	list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/giflib/5.2.2/include)
	list (APPEND LINK_PATH      ${LIBRARY_PATH}/giflib/5.2.2/lib)
	list (APPEND LIBRARYS		gif)
endif ()

if (${USE_OPENEXR})
	list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/OpenEXR/3.2.1/include)
	list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/OpenEXR/3.2.1/include/OpenEXR)
	list (APPEND LINK_PATH      ${LIBRARY_PATH}/OpenEXR/3.2.1/lib)
	list (APPEND LIBRARYS		OpenEXR-3_2 OpenEXRCore-3_2 OpenEXRUtil-3_2)
endif ()

if (${USE_IMATH})
	list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/Imath/3.1/include)
	list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/Imath/3.1/include/Imath)
	list (APPEND LINK_PATH      ${LIBRARY_PATH}/Imath/3.1/lib)
	list (APPEND LIBRARYS		Iex-3_2 IlmThread-3_2 Imath-3_1)
endif ()

if (${USE_STB})
	list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/stb/include)
endif ()

if (${USE_BOOST})
	list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/boost/1.84/include)
	list (APPEND LINK_PATH      ${LIBRARY_PATH}/boost/1.84/lib)
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
	list (APPEND LIBRARYS		boost_exception boost_filesystem)
endif ()
if (CMAKE_SYSTEM_NAME STREQUAL "Window")
	list (APPEND LIBRARYS		boost_exception-vc143-mt-x64-1_84 boost_filesystem-vc143-mt-x64-1_84)
endif ()
endif ()

if (${USE_CURL})
	list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/curl/8.17.0/include)
	list (APPEND LINK_PATH      ${LIBRARY_PATH}/curl/8.17.0/lib)
	list (APPEND LIBRARYS		curl)
endif ()

if (${USE_OPENSSL})
	list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/openssl/3.6.0/include)
	list (APPEND LINK_PATH      ${LIBRARY_PATH}/openssl/3.6.0/lib)
	list (APPEND LIBRARYS		ssl crypto)
endif ()

if (${USE_DXFRW})
	list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/dxfrw/1.0.1/include)
	list (APPEND LINK_PATH      ${LIBRARY_PATH}/dxfrw/1.0.1/lib)
	list (APPEND LIBRARYS		dxfrw)
endif ()

if (${USE_GLFW})
	list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/glfw/3.3.10/include)
	list (APPEND LINK_PATH      ${LIBRARY_PATH}/glfw/3.3.10/lib)
	list (APPEND LIBRARYS		glfw3)
endif ()

if (${USE_GLM})
	list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/glm/1.0.2/include)
	list (APPEND LINK_PATH      ${LIBRARY_PATH}/glm/1.0.2/lib)
endif ()

if (${USE_MQTT})
	list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/mqtt/include)
	list (APPEND LINK_PATH      ${LIBRARY_PATH}/mqtt/lib)
endif ()

if (${USE_VULKAN})
	list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/Vulkan/include)
	list (APPEND LINK_PATH      ${LIBRARY_PATH}/Vulkan/lib)
	list (APPEND LIBRARYS		vulkan)
endif ()

if (${USE_ASSIMP})
	list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/assimp/6.0.2/include)
	list (APPEND LINK_PATH      ${LIBRARY_PATH}/assimp/6.0.2/lib)
	list (APPEND LIBRARYS		assimp)
endif ()

if (${USE_CEF})
	list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/cef/142.0.17/include)
	list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/cef/142.0.17/include/include)
	list (APPEND LINK_PATH      ${LIBRARY_PATH}/cef/142.0.17/lib)
	list (APPEND LIBRARYS	 cef cef_dll_wrapper)
endif ()

if (${USE_SDL3})
	list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/SDL/3.2.24/include)
	list (APPEND LINK_PATH      ${LIBRARY_PATH}/SDL/3.2.24/lib)
	list (APPEND LIBRARYS		SDL3)
endif ()

if (${USE_wxWidget})
	list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/wxWidgets/3.2.6/include)
	list (APPEND LINK_PATH      ${LIBRARY_PATH}/wxWidgets/3.2.6/lib)
	list (APPEND LIBRARYS		wx_gtk3u_core-3.2 	wx_baseu-3.2 			wx_gtk3u_aui-3.2	wx_gtk3u_richtext-3.2
								wx_gtk3u_ribbon-3.2 wx_gtk3u_propgrid-3.2 	wx_gtk3u_qa-3.2		wx_gtk3u_html-3.2
								wx_gtk3u_gl-3.2		wx_baseu_xml-3.2		wx_baseu_net-3.2    wx_gtk3u_stc-3.2
								wx_gtk3u_xrc-3.2	wx_gtk3u_adv-3.2)
endif ()

if (${USE_NANA})
	list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/nana/1.7/include)
	list (APPEND LINK_PATH      ${LIBRARY_PATH}/nana/1.7/lib)
	list (APPEND LIBRARYS		nana)
endif ()

if (${USE_MODBUS})
	list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/libmodbus/3.1.11/include)
	list (APPEND LINK_PATH      ${LIBRARY_PATH}/libmodbus/3.1.11/lib)
	list (APPEND LIBRARYS		modbus)
endif ()

if (${USE_embroidery})
	list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/libembroidery/include)
	list (APPEND LINK_PATH      ${LIBRARY_PATH}/libembroidery/lib)
	list (APPEND LIBRARYS		embroidery)
endif ()

if (${USE_BLUEZ})
	list (APPEND LIBRARYS		bluetooth)
endif ()

if (${USE_OpenAL})
	list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/OpenAL/1.24.3/include)
	list (APPEND LINK_PATH      ${LIBRARY_PATH}/OpenAL/1.24.3/lib)
	list (APPEND LIBRARYS		openal)
endif ()

if (${USE_LIVE555})
	list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/live555/include
			${LIBRARY_PATH}/live555/include/BasicUsageEnvironment
			${LIBRARY_PATH}/live555/include/groupsock
			${LIBRARY_PATH}/live555/include/liveMedia
			${LIBRARY_PATH}/live555/include/UsageEnvironment)
	list (APPEND LINK_PATH      ${LIBRARY_PATH}/live555/lib)
	list (APPEND LIBRARYS		BasicUsageEnvironment  groupsock liveMedia UsageEnvironment)
endif ()

if (${USE_LVGL})
	list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/lvgl/9.4.0/include)
	list (APPEND LINK_PATH      ${LIBRARY_PATH}/lvgl/9.4.0/lib)
	list (APPEND LIBRARYS		lvgl LvglWindows)
endif ()

if (${USE_FLTK})
	list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/fltk/1.4.4/include)
	list (APPEND LINK_PATH      ${LIBRARY_PATH}/fltk/1.4.4/lib)
	list (APPEND LIBRARYS		fltk  fltk_forms  fltk_gl fltk_images
			xkbcommon
			pthread
			dl
			m
			dbus-1
			glib-2.0
			wayland-client
			wayland-cursor
			wayland-egl
			cairo
			gobject-2.0
			gio-2.0
		)

	execute_process(
			COMMAND fltk-config --cxxflags
			OUTPUT_VARIABLE FLTK_CXXFLAGS
			OUTPUT_STRIP_TRAILING_WHITESPACE
	)
endif ()