#include "VulkanAPI.h"
#include "VulkanObjects/Instance/VulkanInstance.h"
static VulkanAPI *VulkanAPIInstance = nullptr;

VulkanAPI::VulkanAPI(VulkanInstance *InInstance)
    : Instance(InInstance)
{
    LoadSurfaceAPI();
}

VulkanAPI::~VulkanAPI()
{

}

VulkanAPI *VulkanAPI::GetInstance(VulkanInstance *InInstance)
{
    if (InInstance)
    {
        if (!VulkanAPIInstance)
        {
            VulkanAPIInstance = new VulkanAPI(InInstance);
        }
    }
    return VulkanAPIInstance;
}

void VulkanAPI::LoadSurfaceAPI()
{
#ifdef RHI_USE_WIN32_KHR
    //vkCreateWin32SurfaceKHR_1 = reinterpret_cast<PFN_vkCreateWin32SurfaceKHR>(vkGetInstanceProcAddr(Instance->GetHandle(), "vkCreateWin32SurfaceKHR"));
    vkCreateWin32SurfaceKHR = reinterpret_cast<PFN_vkCreateWin32SurfaceKHR>(Instance->GetInstanceProcAddr("vkCreateWin32SurfaceKHR"));
#endif

#if RHI_USE_PLATFORM_WAYLAND_KHR
    vkCreateWaylandSurfaceKHR = reinterpret_cast<PFN_vkCreateWin32SurfaceKHR>(Instance->GetInstanceProcAddr("vkCreateWaylandSurfaceKHR"));
#endif
}

void VulkanAPI::LoadCommandBufferAPI()
{
    vkCmdPipelineBarrier2KHR = reinterpret_cast<PFN_vkCmdPipelineBarrier2KHR>(Instance->GetInstanceProcAddr("vkCmdPipelineBarrier2KHR"));
}