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


file(GLOB_RECURSE SRC_LIST_ModeuleTest  ${PROJECT_SOURCE_DIR}/Source/ModeuleTest/*.cpp
										${PROJECT_SOURCE_DIR}/Source/ModeuleTest/*.c
										${PROJECT_SOURCE_DIR}/Source/ModeuleTest/*.h)

list(APPEND ModeuleTest_SRC_LIST
		${SRC_LIST_ModeuleTest}
		${SRC_LIST}
)

message (STATUS "PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}")

add_subdirectory(${PROJECT_SOURCE_DIR}/Source/Modules/RHI)

add_executable(${PROJECT_NAME} ${ModeuleTest_SRC_LIST})
target_include_directories (${PROJECT_NAME}	PUBLIC ${INCLUDE_PATH})
target_link_directories (${PROJECT_NAME}	PUBLIC ${LINK_PATH})
target_link_libraries (${PROJECT_NAME} PUBLIC ${LIBRARYS} RHI)