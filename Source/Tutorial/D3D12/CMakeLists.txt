cmake_minimum_required(VERSION 3.20)
project (D3D12Tutorial)
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

file(GLOB_RECURSE SRC_LIST  ${PROJECT_SOURCE_DIR}/Source/*.cpp
                            ${PROJECT_SOURCE_DIR}/Source/*.c
                            ${PROJECT_SOURCE_DIR}/Source/*.h)

list (APPEND LIBRARYS		glfw3)


add_executable(${PROJECT_NAME} ${SRC_LIST})
target_include_directories (${PROJECT_NAME}	PUBLIC ${INCLUDE_PATH})
target_link_directories (${PROJECT_NAME}	PUBLIC ${LINK_PATH})
target_link_libraries (${PROJECT_NAME} PUBLIC ${LIBRARYS})


