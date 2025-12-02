file(GLOB_RECURSE SRC_LIST_HelloWorld     ${SRC_PREFIX}/Applications/HelloWorld/*.cpp ${SRC_PREFIX}/Applications/HelloWorld/*.c ${SRC_PREFIX}/Applications/HelloWorld/*.h)
file(GLOB_RECURSE SRC_LIST_Test           ${SRC_PREFIX}/Applications/Test/*.cpp ${SRC_PREFIX}/Applications/Test/*.c ${SRC_PREFIX}/Applications/Test/*.h)


list (APPEND HelloWorld_SRC_LIST
        ${SRC_LIST_HelloWorld}
        ${SRC_LIST}
)

set (APP_NAME HelloWorld)
add_executable(${APP_NAME}	 ${HelloWorld_SRC_LIST})
target_include_directories (${APP_NAME}	PUBLIC ${INCLUDE_PATH})
target_link_directories (${APP_NAME}	PUBLIC ${LINK_PATH})
target_link_libraries (${APP_NAME} PUBLIC ${LIBRARYS})

include (CMakeScripts/CompileDefinitions.cmake)

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