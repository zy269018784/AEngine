#pragma once
#include "Vulkan.h"
#include <vector>
#include "RHIObjects/RenderTarget/RHIRenderTarget.h"

/*
 *  Image
 *  Image View
 *  Render Pass
 *  Framebuffery
 */
class VulkanRenderPass;
class VulkanFrameBuffer;
class VulkanCommandBuffer;
class RHIRenderTarget;
class RHICommandBuffer;
class VulkanDevice;
class VulkanRenderTarget : public RHIRenderTarget
{
public:
    VulkanRenderTarget(RHIPixelFormat InPixelFormat, VulkanDevice *InDevice);
    virtual void Resize(float Width, float Height) = 0;
public:
    /*
        设备
    */
    VulkanDevice						*Device;
    /*
        Image
    */
    //std::vector<VkImage>					Images;
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
    //VulkanRenderPass*                       RenderPass;
    /*
        Framebuffers
    */
    std::vector<VulkanFrameBuffer*>		    FrameBuffers;			// SwapChainImages.size()

    /*
        用于图像的command buffer
    */
    //std::vector<VulkanCommandBuffer*>	    GraphicsCommandBuffers;		// SwapChainImages.size()

    /*
        当前帧编号
        FrameIndex: [0, 1]
    */
    std::uint32_t					FrameIndex = 0;
};