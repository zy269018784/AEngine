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
		find_package(Qt6 COMPONENTS Widgets Qml Quick QuickControls2 QuickWidgets REQUIRED)
		set (QT_LIBS Qt6::Widgets
				Qt6::QuickWidgets
				Qt6::Quick
				Qt6::Qml
				Qt6::QuickControls2)
	else ()
		find_package(Qt5 COMPONENTS Widgets Qml Quick QuickControls2 QuickWidgets REQUIRED)
		set (QT_LIBS Qt5::Widgets
				Qt5::QuickWidgets
				Qt5::Quick
				Qt5::Qml
				Qt5::QuickControls2)
	endif ()
	list(APPEND LIBRARYS ${QT_LIBS})
endif ()

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
	list (APPEND LIBRARYS		asound)
	list (APPEND LIBRARYS		X11 X11-xcb Xcursor Xrandr Xinerama Xfixes)
	list (APPEND LIBRARYS		pango-1.0 pangocairo-1.0 pangoft2-1.0 pangoxft-1.0)
	list (APPEND LIBRARYS		gtk-3)
	list (APPEND LINK_PATH 		/usr/lib/x86_64-linux-gnu/)
endif ()

if (${USE_SFML})
	list(APPEND INCLUDE_PATH ${LIBRARY_PATH}/SFML/3.0.2/include)
	list(APPEND LINK_PATH    ${LIBRARY_PATH}/SFML/3.0.2/lib)
	list(APPEND LIBRARYS sfml-system sfml-audio sfml-window sfml-graphics)
endif ()

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/fdk-aac/2.0.3/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/fdk-aac/2.0.3/lib)
list (APPEND LIBRARYS		fdk-aac)

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/opus/1.5.2/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/opus/1.5.2/lib)
list (APPEND LIBRARYS		opus)

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/ogg/1.3.6/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/ogg/1.3.6/lib)
list (APPEND LIBRARYS		ogg)

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/libtwolame/0.4.0/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/libtwolame/0.4.0/lib)
list (APPEND LIBRARYS		twolame)

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/libflac/1.5.0/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/libflac/1.5.0/lib)
list (APPEND LIBRARYS		FLAC)

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/libvorbis/1.3.7/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/libvorbis/1.3.7/lib)
list (APPEND LIBRARYS		vorbis	vorbisenc vorbisfile)

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/libmp3lame/3.100.2/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/libmp3lame/3.100.2/lib)
list (APPEND LIBRARYS		mp3lame)

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/FLAC/1.5.0/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/FLAC/1.5.0/lib)
list (APPEND LIBRARYS		FLAC)

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/webp/1.6.0/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/webp/1.6.0/lib)
list (APPEND LIBRARYS		webp webpdecoder webpdemux webpmux sharpyuv)

#list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/giflib/5.2.2/include)
#list (APPEND LINK_PATH      ${LIBRARY_PATH}/giflib/5.2.2/lib)
#list (APPEND LIBRARYS		gif)

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/OpenEXR/3.2.1/include)
list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/OpenEXR/3.2.1/include/OpenEXR)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/OpenEXR/3.2.1/lib)
list (APPEND LIBRARYS		OpenEXR-3_2 OpenEXRCore-3_2 OpenEXRUtil-3_2)

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/Imath/3.1/include)
list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/Imath/3.1/include/Imath)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/Imath/3.1/lib)
list (APPEND LIBRARYS		Iex-3_2 IlmThread-3_2 Imath-3_1)

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/stb/include)

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/boost/1.84/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/boost/1.84/lib)
list (APPEND LIBRARYS		boost_exception boost_filesystem)

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/curl/8.17.0/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/curl/8.17.0/lib)
list (APPEND LIBRARYS		curl)

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/openssl/3.6.0/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/openssl/3.6.0/lib)
list (APPEND LIBRARYS		ssl crypto)

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/dxfrw/1.0.1/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/dxfrw/1.0.1/lib)
list (APPEND LIBRARYS		dxfrw)

if (${USE_GLFW})
	list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/glfw/3.3.10/include)
	list (APPEND LINK_PATH      ${LIBRARY_PATH}/glfw/3.3.10/lib)
	list (APPEND LIBRARYS		glfw3)
endif ()

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/mqtt/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/mqtt/lib)

list (APPEND LIBRARYS		vulkan)

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/assimp/6.0.2/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/assimp/6.0.2/lib)
list (APPEND LIBRARYS		assimp)

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/cef/142.0.15/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/cef/142.0.15/lib)
list (APPEND LIBRARYS		cef cef_dll_wrapper)

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/SDL/3.2.24/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/SDL/3.2.24/lib)
list (APPEND LIBRARYS		SDL3)

if (${USE_wxWidget})
list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/wxWidgets/3.2.6/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/wxWidgets/3.2.6/lib)
list (APPEND LIBRARYS		wx_gtk3u_core-3.2 	wx_baseu-3.2 			wx_gtk3u_aui-3.2	wx_gtk3u_richtext-3.2
							wx_gtk3u_ribbon-3.2 wx_gtk3u_propgrid-3.2 	wx_gtk3u_qa-3.2		wx_gtk3u_html-3.2
							wx_gtk3u_gl-3.2		wx_baseu_xml-3.2		wx_baseu_net-3.2    wx_gtk3u_stc-3.2
							wx_gtk3u_xrc-3.2	wx_gtk3u_adv-3.2)
endif ()

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/nana/1.7/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/nana/1.7/lib)
list (APPEND LIBRARYS		nana)

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/fltk/1.4.4/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/fltk/1.4.4/lib)
list (APPEND LIBRARYS		fltk  fltk_forms  fltk_gl fltk_images
		xkbcommon
		X11
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
