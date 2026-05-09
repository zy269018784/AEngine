cmake_minimum_required(VERSION 3.20)
project (HelloWorld)
#[[
	语言
#]]
enable_language(C)
set(CMAKE_C_STANDARD 11)        
set(CMAKE_C_STANDARD_REQUIRED ON) 

enable_language(CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


file(GLOB_RECURSE SRC_LIST_HelloWorld  	${PROJECT_SOURCE_DIR}/Source/Applications/HelloWorld/*.cpp
										${PROJECT_SOURCE_DIR}/Source/Applications/HelloWorld/*.c
										${PROJECT_SOURCE_DIR}/Source/Applications/HelloWorld/*.h)

list(APPEND HelloWorld_SRC_LIST
		${SRC_LIST_HelloWorld}
		${SRC_LIST}
)

message (STATUS "PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}")

add_subdirectory(${PROJECT_SOURCE_DIR}/Source/Modules/RHI)

add_executable(${PROJECT_NAME} ${HelloWorld_SRC_LIST})
target_include_directories (${PROJECT_NAME}	PUBLIC ${INCLUDE_PATH})
target_link_directories (${PROJECT_NAME}	PUBLIC ${LINK_PATH} RHI)
target_link_libraries (${PROJECT_NAME} PUBLIC ${LIBRARYS})