set (LIBRARY_PATH ${PROJECT_SOURCE_DIR}/../Library)
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
	list (APPEND LIBRARYS		asound)
endif ()
list(APPEND INCLUDE_PATH ${LIBRARY_PATH}/SFML/3.0.2/include)
list(APPEND LINK_PATH    ${LIBRARY_PATH}/SFML/3.0.2/lib)
list(APPEND LIBRARYS sfml-system sfml-audio sfml-window sfml-graphics)

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/fdk-acc/2.0.3/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/fdk-acc/2.0.3/lib)
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

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/libmp3lame/3.100/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/libmp3lame/3.100/lib)
list (APPEND LIBRARYS		mp3lame)

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/FLAC/1.5.0/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/FLAC/1.5.0/lib)
list (APPEND LIBRARYS		FLAC)

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/webp/1.6.0/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/webp/1.6.0/lib)
list (APPEND LIBRARYS		webp webpdecoder webpdemux webpmux sharpyuv)

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/giflib/5.2.2/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/giflib/5.2.2/lib)
list (APPEND LIBRARYS		gif)

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/OpenEXR/3.2.1/include)
list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/OpenEXR/3.2.1/include/OpenEXR)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/OpenEXR/3.2.1/lib)
list (APPEND LIBRARYS		Iex-3_2 IlmThread-3_2 Imath-3_1 OpenEXR-3_2 OpenEXRCore-3_2 OpenEXRUtil-3_2)

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/stb/include)
