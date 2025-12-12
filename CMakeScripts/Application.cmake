#----------------------------------------------------f
file(GLOB_RECURSE SRC_LIST_HelloWorld     ${SRC_PREFIX}/Applications/HelloWorld/*.cpp ${SRC_PREFIX}/Applications/HelloWorld/*.c ${SRC_PREFIX}/Applications/HelloWorld/*.h)

list(APPEND HelloWorld_SRC_LIST
        ${SRC_LIST_HelloWorld}
        ${SRC_LIST}
)

set(APP_NAME HelloWorld)
add_executable(${APP_NAME} ${HelloWorld_SRC_LIST})
target_include_directories (${APP_NAME}	PUBLIC ${INCLUDE_PATH})
target_link_directories (${APP_NAME}	PUBLIC ${LINK_PATH})
target_link_libraries (${APP_NAME} PUBLIC ${LIBRARYS})

include (CMakeScripts/CompileDefinitions.cmake)

#----------------------------------------------------
file(GLOB_RECURSE SRC_LIST_Test           ${SRC_PREFIX}/Applications/Test/*.cpp ${SRC_PREFIX}/Applications/Test/*.c ${SRC_PREFIX}/Applications/Test/*.h)

list (APPEND Test_SRC_LIST
        ${SRC_LIST_Test}
        ${SRC_LIST}
)

set (APP_NAME Test)
add_executable(${APP_NAME}	 ${Test_SRC_LIST})
target_include_directories (${APP_NAME}	PUBLIC ${INCLUDE_PATH})
target_link_directories (${APP_NAME}	PUBLIC ${LINK_PATH})
target_link_libraries (${APP_NAME} PUBLIC ${LIBRARYS})

include (CMakeScripts/CompileDefinitions.cmake)
#----------------------------------------------------
file(GLOB_RECURSE SRC_LIST_VideoPlayer    ${SRC_PREFIX}/Applications/VideoPlayer/*.cpp ${SRC_PREFIX}/Applications/VideoPlayer/*.c ${SRC_PREFIX}/Applications/VideoPlayer/*.h)

list (APPEND VideoPlayer_SRC_LIST
        ${SRC_LIST_VideoPlayer}
        ${SRC_LIST}
)

set (APP_NAME VideoPlayer)
add_executable(${APP_NAME}	 ${VideoPlayer_SRC_LIST})
target_include_directories (${APP_NAME}	PUBLIC ${INCLUDE_PATH})
target_link_directories (${APP_NAME}	PUBLIC ${LINK_PATH})
target_link_libraries (${APP_NAME} PUBLIC ${LIBRARYS})

include (CMakeScripts/CompileDefinitions.cmake)
#----------------------------------------------------
file(GLOB_RECURSE SRC_LIST_AudioPlayer    ${SRC_PREFIX}/Applications/AudioPlayer/*.cpp ${SRC_PREFIX}/Applications/AudioPlayer/*.c ${SRC_PREFIX}/Applications/AudioPlayer/*.h)

list (APPEND AudioPlayer_SRC_LIST
        ${SRC_LIST_AudioPlayer}
        ${SRC_LIST}
)

set (APP_NAME AudioPlayer)
add_executable(${APP_NAME}	 ${AudioPlayer_SRC_LIST})
target_include_directories (${APP_NAME}	PUBLIC ${INCLUDE_PATH})
target_link_directories (${APP_NAME}	PUBLIC ${LINK_PATH})
target_link_libraries (${APP_NAME} PUBLIC ${LIBRARYS})

include (CMakeScripts/CompileDefinitions.cmake)
#----------------------------------------------------