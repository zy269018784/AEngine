#include "VulkanAPI.h"
#include "VulkanRHI/VulkanObjects//Instance/VulkanInstance.h"
static VulkanAPI *VulkanAPIInstance = nullptr;

VulkanAPI::VulkanAPI(VulkanInstance *InInstance)
    : Instance(InInstance)
{
    LoadSurfaceAPI();
    LoadCommandBufferAPI();
    LoadRayTracingAPI();
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
#if RHI_USE_WIN32_KHR
    //vkCreateWin32SurfaceKHR_1 = reinterpret_cast<PFN_vkCreateWin32SurfaceKHR>(vkGetInstanceProcAddr(Instance->GetHandle(), "vkCreateWin32SurfaceKHR"));
    vkCreateWin32SurfaceKHR = reinterpret_cast<PFN_vkCreateWin32SurfaceKHR>(Instance->GetInstanceProcAddr("vkCreateWin32SurfaceKHR"));
#endif

#if RHI_USE_WAYLAND_KHR
    vkCreateWaylandSurfaceKHR = reinterpret_cast<PFN_vkCreateWin32SurfaceKHR>(Instance->GetInstanceProcAddr("vkCreateWaylandSurfaceKHR"));
#endif
}

void VulkanAPI::LoadCommandBufferAPI()
{
    vkCmdPipelineBarrier2KHR = reinterpret_cast<PFN_vkCmdPipelineBarrier2KHR>(Instance->GetInstanceProcAddr("vkCmdPipelineBarrier2KHR"));
}

void VulkanAPI::LoadRayTracingAPI()
{
#if 1
    vkCmdTraceRaysKHR = reinterpret_cast<PFN_vkCmdTraceRaysKHR>(Instance->GetInstanceProcAddr("vkCmdTraceRaysKHR"));
    vkCreateRayTracingPipelinesKHR = reinterpret_cast<PFN_vkCreateRayTracingPipelinesKHR>(Instance->GetInstanceProcAddr("vkCreateRayTracingPipelinesKHR"));
    vkGetRayTracingCaptureReplayShaderGroupHandlesKHR = reinterpret_cast<PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR>(Instance->GetInstanceProcAddr("vkGetRayTracingCaptureReplayShaderGroupHandlesKHR"));
    vkCmdTraceRaysIndirectKHR = reinterpret_cast<PFN_vkCmdTraceRaysIndirectKHR>(Instance->GetInstanceProcAddr("vkCmdTraceRaysIndirectKHR"));
    vkGetRayTracingShaderGroupStackSizeKHR = reinterpret_cast<PFN_vkGetRayTracingShaderGroupStackSizeKHR>(Instance->GetInstanceProcAddr("vkGetRayTracingShaderGroupStackSizeKHR"));
    vkCmdSetRayTracingPipelineStackSizeKHR = reinterpret_cast<PFN_vkCmdSetRayTracingPipelineStackSizeKHR>(Instance->GetInstanceProcAddr("vkCmdSetRayTracingPipelineStackSizeKHR"));
#endif
}