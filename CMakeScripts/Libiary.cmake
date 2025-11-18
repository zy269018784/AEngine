set (LIBRARY_PATH ${PROJECT_SOURCE_DIR}/../Library)

list(APPEND INCLUDE_PATH ${LIBRARY_PATH}/SFML/3.0.2/include)
list(APPEND LINK_PATH    ${LIBRARY_PATH}/SFML/3.0.2/lib)
list(APPEND LIBRARYS sfml-system sfml-audio sfml-window sfml-graphics)


list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/fdk-acc/2.0.3/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/fdk-acc/2.0.3/lib)
list (APPEND LIBRARYS		fdk-aac)

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/opus/1.5.2/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/opus/1.5.2/lib)
list (APPEND LIBRARYS		opus)

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/libogg/1.3.6/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/libogg/1.3.6/lib)
list (APPEND LIBRARYS		ogg)

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/libtwolame/0.4.0/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/libtwolame/0.4.0/lib)
list (APPEND LIBRARYS		libtwolame_dll)

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/libflac/1.5.0/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/libflac/1.5.0/lib)
list (APPEND LIBRARYS		FLAC)

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/libvorbis/19/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/libvorbis/19/lib)
list (APPEND LIBRARYS		vorbis	vorbisenc vorbisfile)

list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/libmp3lame/3.100.2/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/libmp3lame/3.100.2/lib)
list (APPEND LIBRARYS		libmp3lame mp3lame)
