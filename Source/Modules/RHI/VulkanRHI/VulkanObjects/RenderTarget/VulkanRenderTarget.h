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
};