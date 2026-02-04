#pragma once
#include "RHIObjects/RHIRenderTarget.h"
#include "Vulkan.h"
#include <vector>
/*
 *  Color Attachments
 *      Image View
 *  Depth Attachments
 *
 *  Render Pass
 *  Framebuffery
 */
class VulkanRenderPass;
class VulkanFrameBuffer;
class VulkanSwapChain;
class VulkanSwapChainRenderTarget
{
public:
    VulkanSwapChainRenderTarget();
    ~VulkanSwapChainRenderTarget();
private:
public:
    /*
        Image
    */
    std::vector<VkImage>					SwapChainImages;
    /*
        Image View
    */
    std::vector<VkImageView>				SwapChainImageViews;

    /*
        Render Pass
    */
    VulkanRenderPass*                       RenderPass;
    /*
        Framebuffers
    */
    std::vector<VulkanFrameBuffer*>		    FrameBuffers;				// SwapChainImages.size()

    VulkanSwapChain *SwapChain;
};