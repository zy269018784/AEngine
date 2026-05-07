#pragma once
#include "Vulkan.h"
class VulkanInstance;
class VulkanAPI
{
public:
    VulkanAPI(VulkanInstance *InInstance);
    ~VulkanAPI();
    static VulkanAPI *GetInstance(VulkanInstance *InInstance = nullptr);
private:
    void LoadSurfaceAPI();
    void LoadCommandBufferAPI();
    void LoadRayTracingAPI();
private:
    VulkanInstance *Instance;
public:
#ifdef RHI_USE_WIN32_KHR
    PFN_vkCreateWin32SurfaceKHR vkCreateWin32SurfaceKHR;
#endif
#if RHI_USE_PLATFORM_WAYLAND_KHR
    PFN_vkCreateWaylandSurfaceKHR vkCreateWaylandSurfaceKHR;
#endif
#if 1
    PFN_vkCmdTraceRaysKHR vkCmdTraceRaysKHR;
    PFN_vkCreateRayTracingPipelinesKHR vkCreateRayTracingPipelinesKHR;
    PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR vkGetRayTracingCaptureReplayShaderGroupHandlesKHR;
    PFN_vkCmdTraceRaysIndirectKHR vkCmdTraceRaysIndirectKHR;
    PFN_vkGetRayTracingShaderGroupStackSizeKHR vkGetRayTracingShaderGroupStackSizeKHR;
    PFN_vkCmdSetRayTracingPipelineStackSizeKHR vkCmdSetRayTracingPipelineStackSizeKHR;
#endif
public:
    /*
     * Command Buffer API
     */
    /*
     * Pipeline Barrier         Vulkan 1.1 Core
     */
    PFN_vkCmdPipelineBarrier               vkCmdPipelineBarrier;

    /*
     * Pipeline Barrier         Vulkan 1.3 Core
     */
    PFN_vkCmdPipelineBarrier2               vkCmdPipelineBarrier2;

    /*
     * Pipeline Barrier         Vulkan 1.3 Core     VK_KHR_synchronization2
     */
    PFN_vkCmdPipelineBarrier2KHR            vkCmdPipelineBarrier2KHR;

    /*
     * RenderPass               Vulkan 1.0 Core
     * Render Pass Objects: Superseded via dynamic rendering
     */
    PFN_vkCmdBeginRenderPass                vkCmdBeginRenderPass;
    PFN_vkCmdEndRenderPass                  vkCmdEndRenderPass;
    PFN_vkCmdNextSubpass                    vkCmdNextSubpass;

    /*
     * RenderPass2               Vulkan 1.2 Core    VK_KHR_render_pass2
     */
    PFN_vkCmdBeginRenderPass2KHR            vkCmdBeginRenderPass2KHR;
    PFN_vkCmdEndRenderPass2KHR              vkCmdEndRenderPass2KHR;
    PFN_vkCmdNextSubpass2KHR                vkCmdNextSubpass2KHR;

    /*
     * Dynamic Rendering         Vulkan 1.3 Core
     */
    PFN_vkCmdBeginRendering                 vkCmdBeginRendering;
    PFN_vkCmdEndRendering                   vkCmdEndRendering;

    /*
     * Dynamic Rendering         Vulkan 1.3 Core    VK_KHR_dynamic_rendering
     */
    PFN_vkCmdBeginRenderingKHR              vkCmdBeginRenderingKHR;
    PFN_vkCmdEndRenderingKHR                vkCmdEndRenderingKHR;

    /*
     * Event                    Vulkan 1.3 Core     VK_KHR_synchronization2
     */
    PFN_vkCmdResetEvent2KHR                 vkCmdResetEvent2KHR;
    PFN_vkCmdSetEvent2KHR                   vkCmdSetEvent2KHR;
    PFN_vkCmdWaitEvents2KHR                 vkCmdWaitEvents2KHR;


    /*
     * Copy Commands 2          Vulkan 1.3 Core     VK_KHR_copy_commands2
     */
    PFN_vkCmdCopyBuffer2KHR                 vkCmdCopyBuffer2KHR;
    PFN_vkCmdCopyBufferToImage2KHR          vkCmdCopyBufferToImage2KHR;
    PFN_vkCmdCopyImage2KHR                  vkCmdCopyImage2KHR;
    PFN_vkCmdCopyImageToBuffer2KHR          vkCmdCopyImageToBuffer2KHR;
    PFN_vkCmdBlitImage2KHR                  vkCmdBlitImage2KHR;
    PFN_vkCmdResolveImage2KHR               vkCmdResolveImage2KHR;

    /*
     * Dynamic State            Vulkan 1.3 Core     VK_EXT_extended_dynamic_state,  VK_EXT_shader_object
     */
    PFN_vkCmdSetCullModeEXT                 vkCmdSetCullModeEXT;
    PFN_vkCmdSetFrontFaceEXT                vkCmdSetFrontFaceEXT;
    PFN_vkCmdSetDepthTestEnableEXT          vkCmdSetDepthTestEnableEXT;
    PFN_vkCmdSetDepthWriteEnableEXT         vkCmdSetDepthWriteEnableEXT;
    PFN_vkCmdSetDepthCompareOpEXT           vkCmdSetDepthCompareOpEXT;
    PFN_vkCmdSetDepthBoundsTestEnableEXT    vkCmdSetDepthBoundsTestEnableEXT;
    PFN_vkCmdSetDepthBiasEnableEXT          vkCmdSetDepthBiasEnableEXT;
    PFN_vkCmdSetStencilOpEXT                vkCmdSetStencilOpEXT;
    PFN_vkCmdSetStencilTestEnableEXT        vkCmdSetStencilTestEnableEXT;
    PFN_vkCmdSetScissorWithCountEXT         vkCmdSetScissorWithCountEXT;
    PFN_vkCmdSetPrimitiveTopologyEXT        vkCmdSetPrimitiveTopologyEXT;
};