
set (USE_ES32RHI_RHI    true)
set (USE_VULKAN_RHI     true)
set (USE_D3D12_RHI      true)
set (USE_D3D11_RHI      true)
set (USE_D3D10_RHI      true)
set (USE_D3D9_RHI       true)

if (NOT CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set (USE_D3D12_RHI false)
    set (USE_D3D11_RHI false)
    set (USE_D3D10_RHI false)
    set (USE_D3D9_RHI  false)
endif ()

# ffmpeg
set (USE_AVCODEC       false)

