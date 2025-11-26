

file(GLOB_RECURSE SRC_LIST_Applications     ${SRC_PREFIX}/Applications/*.cpp ${SRC_PREFIX}/Applications/*.c ${SRC_PREFIX}/Applications/*.h)
file(GLOB_RECURSE SRC_LIST_Audio            ${SRC_PREFIX}/Modules/Audio/*.cpp ${SRC_PREFIX}/Modules/Audio/*.c ${SRC_PREFIX}/Modules/Audio/*.h)
file(GLOB_RECURSE SRC_LIST_AudioPlayer      ${SRC_PREFIX}/Modules/AudioPlayer/*.cpp ${SRC_PREFIX}/Modules/AudioPlayer/*.c ${SRC_PREFIX}/Modules/AudioPlayer/*.h)
file(GLOB_RECURSE SRC_LIST_MultiMedia       ${SRC_PREFIX}/Modules/MultiMedia/*.cpp ${SRC_PREFIX}/Modules/MultiMedia/*.c ${SRC_PREFIX}/Modules/MultiMedia/*.h)
file(GLOB_RECURSE SRC_LIST_Network $        ${SRC_PREFIX}/Modules/Network/*.cpp ${SRC_PREFIX}/Modules/Network/*.c ${SRC_PREFIX}/Modules/Network/*.h)
file(GLOB_RECURSE SRC_LIST_Type             ${SRC_PREFIX}/Modules/Type/*.cpp ${SRC_PREFIX}/Modules/Type/*.c ${SRC_PREFIX}/Modules/Type/*.h)
file(GLOB_RECURSE SRC_LIST_RHI              ${SRC_PREFIX}/Modules/RHI/RHI/*.cpp ${SRC_PREFIX}/Modules/RHI/RHI/*.c ${SRC_PREFIX}/Modules/RHI/RHI/*.h)
file(GLOB_RECURSE SRC_LIST_VulkanRHI        ${SRC_PREFIX}/Modules/RHI/VulkanRHI/*.cpp ${SRC_PREFIX}/Modules/RHI/VulkanRHI/*.c ${SRC_PREFIX}/Modules/RHI/VulkanRHI/*.h)
file(GLOB_RECURSE SRC_LIST_ES32RHI          ${SRC_PREFIX}/Modules/RHI/ES32RHI/*.cpp ${SRC_PREFIX}/Modules/RHI/ES32RHI/*.c ${SRC_PREFIX}/Modules/RHI/ES32RHI/*.h)
file(GLOB_RECURSE SRC_LIST_OpenGL330RHI     ${SRC_PREFIX}/Modules/RHI/OpenGL330RHI/*.cpp ${SRC_PREFIX}/Modules/RHI/OpenGL330RHI/*.c ${SRC_PREFIX}/Modules/RHI/OpenGL330RHI/*.h)
file(GLOB_RECURSE SRC_LIST_D3D12RHI         ${SRC_PREFIX}/Modules/RHI/D3D12RHI/*.cpp ${SRC_PREFIX}/Modules/RHI/D3D12RHI/*.c ${SRC_PREFIX}/Modules/RHI/D3D12RHI/*.h)
file(GLOB_RECURSE SRC_LIST_GLAD             ${SRC_PREFIX}/Modules/glad/*.cpp ${SRC_PREFIX}/Modules/glad/*.c ${SRC_PREFIX}/Modules/glad/*.h)
file(GLOB_RECURSE SRC_LIST_RHIExamples      ${SRC_PREFIX}/Modules/RHIExamples/*.cpp ${SRC_PREFIX}/Modules/RHIExamples/*.c ${SRC_PREFIX}/Modules/RHIExamples/*.h)
file(GLOB_RECURSE SRC_LIST_Model            ${SRC_PREFIX}/Modules/Model/*.cpp ${SRC_PREFIX}/Modules/Model/*.c ${SRC_PREFIX}/Modules/Model/*.h)
file(GLOB_RECURSE SRC_LIST_Window           ${SRC_PREFIX}/Modules/Window/*.cpp ${SRC_PREFIX}/Modules/Window/*.c ${SRC_PREFIX}/Modules/Window/*.h)



#message(STATUS "SRC_LIST_Applications ${SRC_LIST_Applications}")
#message(STATUS "SRC_LIST_Audio ${SRC_LIST_Audio}")
#message(STATUS "SRC_LIST_MultiMedia ${SRC_LIST_MultiMedia}")
#message(STATUS "SRC_LIST_Network ${SRC_LIST_Network}")
#message(STATUS "SRC_LIST_Window ${SRC_LIST_Window}")

list (APPEND SRC_LIST
        ${SRC_LIST_Applications}
        ${SRC_LIST_Audio}
        ${SRC_LIST_AudioPlayer}
        ${SRC_LIST_MultiMedia}
        ${SRC_LIST_Network}
        ${SRC_LIST_Type}
        ${SRC_LIST_RHI}
        ${SRC_LIST_VulkanRHI}
        ${SRC_LIST_ES32RHI}
        #${SRC_LIST_OpenGL330RHI}
        ${SRC_LIST_GLAD}
        ${SRC_LIST_RHIExamples}
        ${SRC_LIST_Model}
        ${SRC_LIST_Window}
)
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    list (APPEND SRC_LIST ${SRC_LIST_D3D12RHI})
endif ()

list (APPEND SRC_LIST ${SRC_PREFIX}/main.cpp ${SRC_PREFIX}/stb_image.cpp ${SRC_PREFIX}/Modules/ModuleTest.cpp)

list (APPEND INCLUDE_PATH ${SRC_PREFIX} ${SRC_PREFIX}/Applications ${SRC_PREFIX}/Modules)

list (APPEND INCLUDE_PATH ${SRC_PREFIX}/Modules/RHI/RHI)
list (APPEND INCLUDE_PATH ${SRC_PREFIX}/Modules/RHI/VulkanRHI)
list (APPEND INCLUDE_PATH ${SRC_PREFIX}/Modules/RHI/ES32RHI)
list (APPEND INCLUDE_PATH ${SRC_PREFIX}/Modules/RHI/OpenGL330RHI)
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    list (APPEND INCLUDE_PATH ${SRC_PREFIX}/Modules/RHI/D3D12RHI)
endif ()

list (APPEND INCLUDE_PATH ${SRC_PREFIX}/Modules/glad)
list (APPEND INCLUDE_PATH ${SRC_PREFIX}/Modules/RHIExamples)
list (APPEND INCLUDE_PATH ${SRC_PREFIX}/Modules/Model)
list (APPEND INCLUDE_PATH ${SRC_PREFIX}/Modules/Window)

message(STATUS "SRC_LIST ${SRC_LIST}")