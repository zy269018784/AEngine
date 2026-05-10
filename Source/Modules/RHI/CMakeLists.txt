cmake_minimum_required(VERSION 3.20)
project (RHI)
#set (LIBRARY_PATH C:/Projects/Library)
set (SRC_LIST "")

set (USE_ES32_RHI   true)
set (USE_VULKAN_RHI ${USE_VULKAN})
set (USE_D3D12_RHI  true)
set (USE_D3D11_RHI  true)
set (USE_D3D10_RHI  true)
set (USE_D3D9_RHI   true)
if (NOT CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set (USE_D3D12_RHI  false)
    set (USE_D3D11_RHI  false)
    set (USE_D3D10_RHI  false)
    set (USE_D3D9_RHI   false)
endif ()
set (USE_D3D12_RHI  false)
set (USE_D3D11_RHI  false)
set (USE_D3D10_RHI  false)
set (USE_D3D9_RHI   false)

file(GLOB_RECURSE SRC_LIST_RHI              ${PROJECT_SOURCE_DIR}/RHI/*.cpp
                                            ${PROJECT_SOURCE_DIR}/RHI/*.c
                                            ${PROJECT_SOURCE_DIR}/RHI/*.h)

file(GLOB_RECURSE SRC_LIST_VulkanRHI        ${PROJECT_SOURCE_DIR}/VulkanRHI/*.cpp
                                            ${PROJECT_SOURCE_DIR}/VulkanRHI/*.c
                                            ${PROJECT_SOURCE_DIR}/VulkanRHI/*.h)
file(GLOB_RECURSE SRC_LIST_ES32RHI          ${PROJECT_SOURCE_DIR}/ES32RHI/*.cpp
                                            ${PROJECT_SOURCE_DIR}/ES32RHI/*.c
                                            ${PROJECT_SOURCE_DIR}/ES32RHI/*.h)
file(GLOB_RECURSE SRC_LIST_OpenGL330RHI     ${PROJECT_SOURCE_DIR}/OpenGL330RHI/*.cpp
                                            ${PROJECT_SOURCE_DIR}/OpenGL330RHI/*.c
                                            ${PROJECT_SOURCE_DIR}/OpenGL330RHI/*.h)
file(GLOB_RECURSE SRC_LIST_D3D12RHI         ${PROJECT_SOURCE_DIR}/D3D12RHI/*.cpp
                                            ${PROJECT_SOURCE_DIR}/D3D12RHI/*.c
                                            ${PROJECT_SOURCE_DIR}/D3D12RHI/*.h)
file(GLOB_RECURSE SRC_LIST_D3D11RHI         ${PROJECT_SOURCE_DIR}/D3D11RHI/*.cpp
                                            ${PROJECT_SOURCE_DIR}/D3D11RHI/*.c
                                            ${PROJECT_SOURCE_DIR}/D3D11RHI/*.h)
file(GLOB_RECURSE SRC_LIST_D3D10RHI         ${PROJECT_SOURCE_DIR}/D3D10RHI/*.cpp
                                            ${PROJECT_SOURCE_DIR}/D3D10RHI/*.c
                                            ${PROJECT_SOURCE_DIR}/D3D10RHI/*.h)
file(GLOB_RECURSE SRC_LIST_D3D9RHI          ${PROJECT_SOURCE_DIR}/D3D9RHI/*.cpp
                                            ${PROJECT_SOURCE_DIR}/D3D9RHI/*.c
                                            ${PROJECT_SOURCE_DIR}/D3D9RHI/*.h)
file(GLOB_RECURSE SRC_LIST_GLAD             ${PROJECT_SOURCE_DIR}/glad/*.cpp
                                            ${PROJECT_SOURCE_DIR}/glad/*.c
                                            ${PROJECT_SOURCE_DIR}/glad/*.h)

list (APPEND INCLUDE_PATH ${PROJECT_SOURCE_DIR})

list (APPEND SRC_LIST ${SRC_LIST_GLAD})
list (APPEND INCLUDE_PATH ${PROJECT_SOURCE_DIR}/glad)
list (APPEND INCLUDE_PATH ${PROJECT_SOURCE_DIR}/glad/KHR)

list (APPEND SRC_LIST ${SRC_LIST_RHI})
#list (APPEND INCLUDE_PATH ${PROJECT_SOURCE_DIR}/RHI)

list (APPEND SRC_LIST ${SRC_LIST_ES32RHI})
#list (APPEND INCLUDE_PATH ${PROJECT_SOURCE_DIR}/ES32RHI)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    list (APPEND SRC_LIST ${SRC_LIST_D3D12RHI})
    #list (APPEND INCLUDE_PATH ${PROJECT_SOURCE_DIR}/D3D12RHI)
    list(APPEND INCLUDE_PATH ${LIBRARY_PATH}/Direct3D/12/include)
    list(APPEND LINK_PATH    ${LIBRARY_PATH}/Direct3D/12/lib)
    list(APPEND LIBRARYS d3d12 d3dcompiler d3dcsx dxgi dxguid)

    list (APPEND SRC_LIST ${SRC_LIST_D3D11RHI})
    #list (APPEND INCLUDE_PATH ${PROJECT_SOURCE_DIR}/D3D11RHI)

    list (APPEND SRC_LIST ${SRC_LIST_D3D10RHI})
    #list (APPEND INCLUDE_PATH ${PROJECT_SOURCE_DIR}/D3D10RHI)

    list (APPEND SRC_LIST ${SRC_LIST_D3D9RHI})
    #list (APPEND INCLUDE_PATH ${PROJECT_SOURCE_DIR}/D3D9RHI)
endif ()

if (USE_VULKAN_RHI)
    list (APPEND SRC_LIST ${SRC_LIST_VulkanRHI})
    #list (APPEND INCLUDE_PATH ${SRC_PREFIX}/Modules/RHI/VulkanRHI)
    list (APPEND INCLUDE_PATH   ${LIBRARY_PATH}/Vulkan/include)
    list (APPEND LINK_PATH      ${LIBRARY_PATH}/Vulkan/lib)
    list (APPEND LIBRARYS		vulkan)
endif ()

add_library(${PROJECT_NAME}	 SHARED ${SRC_LIST})

target_include_directories (${PROJECT_NAME}	PUBLIC ${INCLUDE_PATH})
target_link_directories (${PROJECT_NAME}	PUBLIC ${LINK_PATH})
target_link_libraries (${PROJECT_NAME} PUBLIC ${LIBRARYS})

add_library(${PROJECT_NAME}-Static	 ${SRC_LIST})
target_include_directories (${PROJECT_NAME}-Static	PUBLIC ${INCLUDE_PATH})
target_link_directories (${PROJECT_NAME}-Static	PUBLIC ${LINK_PATH})
target_link_libraries (${PROJECT_NAME}-Static PUBLIC ${LIBRARYS})

target_compile_definitions (${PROJECT_NAME} PUBLIC USE_VULKAN_RHI=${USE_VULKAN_RHI})
target_compile_definitions (${PROJECT_NAME} PUBLIC USE_ES32_RHI=${USE_ES32_RHI})
target_compile_definitions (${PROJECT_NAME} PUBLIC USE_D3D12_RHI=${USE_D3D12_RHI})
target_compile_definitions (${PROJECT_NAME} PUBLIC USE_D3D11_RHI=${USE_D3D11_RHI})
target_compile_definitions (${PROJECT_NAME} PUBLIC USE_D3D10_RHI=${USE_D3D10_RHI})
target_compile_definitions (${PROJECT_NAME} PUBLIC USE_D3D9_RHI=${USE_D3D9_RHI})

target_compile_definitions (${PROJECT_NAME} PUBLIC RHI_USE_WIN32_KHR=0)
target_compile_definitions (${PROJECT_NAME} PUBLIC RHI_USE_PLATFORM_WAYLAND_KHR=0)
target_compile_definitions (${PROJECT_NAME} PUBLIC RHI_USE_XCB_KHR=0)
target_compile_definitions (${PROJECT_NAME} PUBLIC RHI_USE_Xlib_KHR=0)
target_compile_definitions (${PROJECT_NAME} PUBLIC RHI_USE_ANDROID_KHR=0)
target_compile_definitions (${PROJECT_NAME} PUBLIC RHI_USE_DirectFB_EXT=0)
target_compile_definitions (${PROJECT_NAME} PUBLIC RHI_USE_IOS_MVK=0)
target_compile_definitions (${PROJECT_NAME} PUBLIC RHI_USE_MacOS_MVK=0)
target_compile_definitions (${PROJECT_NAME} PUBLIC RHI_USE_Metal_EXT=0)
target_compile_definitions (${PROJECT_NAME} PUBLIC RHI_USE_QNX=0)
target_compile_definitions (${PROJECT_NAME} PUBLIC RHI_USE_VI_NN=0)
target_compile_definitions (${PROJECT_NAME} PUBLIC RHI_USE_FUCHSIA=0)
target_compile_definitions (${PROJECT_NAME} PUBLIC RHI_USE_GGP=0)
target_compile_definitions (${PROJECT_NAME} PUBLIC RHI_USE_OHOS=0)
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_definitions (${PROJECT_NAME} PUBLIC OS_IS_WINDOWS=1)
    target_compile_definitions (${PROJECT_NAME} PUBLIC RHI_USE_WIN32_KHR=1)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_definitions (${PROJECT_NAME} PUBLIC OS_IS_LINUX=1)
    target_compile_definitions (${PROJECT_NAME} PUBLIC RHI_USE_PLATFORM_WAYLAND_KHR=1)
    target_compile_definitions (${PROJECT_NAME} PUBLIC RHI_USE_XCB_KHR=1)
    target_compile_definitions (${PROJECT_NAME} PUBLIC RHI_USE_Xlib_KHR=1)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Android")
    target_compile_definitions (${PROJECT_NAME} PUBLIC RHI_USE_ANDROID_KHR=1)
elseif (CMAKE_SYSTEM_NAME STREQUAL "iOS")
    # iOS 平台代码
    target_compile_definitions (${PROJECT_NAME} PUBLIC RHI_USE_IOS_MVK=1)
    target_compile_definitions (${PROJECT_NAME} PUBLIC RHI_USE_Metal_EXT=1)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    # macOS 平台代码
    target_compile_definitions (${PROJECT_NAME} PUBLIC RHI_USE_MacOS_MVK=1)
    target_compile_definitions (${PROJECT_NAME} PUBLIC RHI_USE_Metal_EXT=1)
elseif (CMAKE_SYSTEM_NAME STREQUAL "QNX")
    target_compile_definitions (${PROJECT_NAME} PUBLIC RHI_USE_QNX=1)
elseif (CMAKE_SYSTEM_NAME STREQUAL "NintendoSwitch")
    target_compile_definitions (${PROJECT_NAME} PUBLIC RHI_USE_VI_NN=1)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Fuchsia")
    target_compile_definitions (${PROJECT_NAME} PUBLIC RHI_USE_FUCHSIA=1)
elseif (CMAKE_SYSTEM_NAME STREQUAL "GGP")
    target_compile_definitions (${PROJECT_NAME} PUBLIC RHI_USE_GGP=1)
elseif (CMAKE_SYSTEM_NAME STREQUAL "OHOS")
    target_compile_definitions (${PROJECT_NAME} PUBLIC RHI_USE_OHOS=0)
endif ()
# 屏蔽windows的max宏, std::numeric_limits<uint32_t>::max()
target_compile_definitions(${PROJECT_NAME} PUBLIC NOMINMAX)
target_compile_definitions(${PROJECT_NAME}-Static PUBLIC NOMINMAX)