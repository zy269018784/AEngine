cmake_minimum_required(VERSION 3.20)
project (CeguiTutorial)
#[[
	语言
#]]
enable_language(C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list (APPEND INCLUDE_PATH   ${PROJECT_SOURCE_DIR}/Source)
list (APPEND INCLUDE_PATH   ${PROJECT_SOURCE_DIR}/Source/glad)

file(GLOB_RECURSE SRC_LIST  ${PROJECT_SOURCE_DIR}/Source/*.cpp
                            ${PROJECT_SOURCE_DIR}/Source/*.c
                            ${PROJECT_SOURCE_DIR}/Source/*.h)

message (STATUS "SRC_LIST ${SRC_LIST}")

# cegui
list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/cegui/0.8.7/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/cegui/0.8.7/lib)
list (APPEND LIBRARYS		CEGUI CEGUIBase-0 CEGUICommonDialogs-0 CEGUIOpenGLRenderer-0)
# glfw
list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/glfw/3.4/include)
list (APPEND LINK_PATH      ${LIBRARY_PATH}/glfw/3.4/lib)
list (APPEND LIBRARYS		glfw3)

# epoxy
list (APPEND LIBRARYS		epoxy)



add_executable(${PROJECT_NAME} ${SRC_LIST})
target_include_directories (${PROJECT_NAME}	PUBLIC ${INCLUDE_PATH})
target_link_directories (${PROJECT_NAME}	PUBLIC ${LINK_PATH})
target_link_libraries (${PROJECT_NAME} PUBLIC ${LIBRARYS})


