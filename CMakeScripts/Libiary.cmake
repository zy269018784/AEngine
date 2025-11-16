set (LIBRARY_PATH ${PROJECT_SOURCE_DIR}/../Library)
list(APPEND INCLUDE_PATH ${LIBRARY_PATH}/SFML/3.0.2/include)
list(APPEND LINK_PATH    ${LIBRARY_PATH}/SFML/3.0.2/lib)
list(APPEND LIBRARYS sfml-system sfml-audio sfml-window sfml-graphics sfml-main)