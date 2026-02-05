#pragma once
#include "Vulkan.h"
#include <vector>
/*
 *  Image
 *  Image View
 *  Render Pass
 *  Framebuffery
 */
class VulkanRenderPass;
class VulkanFrameBuffer;
class VulkanCommandBuffer;
class VulkanRenderTarget
{
public:
    /*
        Image
    */
    std::vector<VkImage>					Images;
    /*
        Image View
    */
    std::vector<VkImageView>				ImageViews;
    /*
        分辨率
    */
    VkExtent2D								Resolution;
    /*
        Format
    */
    VkFormat								ImageFormat;
    /*
        Render Pass
    */
    VulkanRenderPass*                       RenderPass;
    /*
        Framebuffers
    */
    std::vector<VulkanFrameBuffer*>		    FrameBuffers;				// SwapChainImages.size()

    /*
        用于图像的command buffer
    */
    std::vector<VulkanCommandBuffer*>	GraphicsCommandBuffers;		// SwapChainImages.size()
};