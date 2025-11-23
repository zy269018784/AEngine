set (LIBRARY_PATH ${PROJECT_SOURCE_DIR}/../Library)

#[[
        QT
#]]
set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTOUIC ON)
set (CMAKE_AUTORCC ON)
message (STATUS "USE_QT6 ${USE_QT6}")
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

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
	list (APPEND LIBRARYS		asound)
endif ()

list(APPEND INCLUDE_PATH ${LIBRARY_PATH}/SFML/3.0.2/include)
list(APPEND LINK_PATH    ${LIBRARY_PATH}/SFML/3.0.2/lib)
list(APPEND LIBRARYS sfml-system sfml-audio sfml-window sfml-graphics)

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

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/glfw/3.3.10/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/glfw/3.3.10/lib)
list (APPEND LIBRARYS		glfw3)

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/mqtt/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/mqtt/lib)

list (APPEND LIBRARYS		vulkan)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
	list (APPEND LIBRARYS		X11 X11-xcb)
endif ()

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/assimp/6.0.2/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/assimp/6.0.2/lib)
list (APPEND LIBRARYS		assimp)

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/cef/142.0.15/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/cef/142.0.15/lib)
list (APPEND LIBRARYS		cef cef_dll_wrapper)

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/SDL/3.2.24/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/SDL/3.2.24/lib)
list (APPEND LIBRARYS		SDL3)