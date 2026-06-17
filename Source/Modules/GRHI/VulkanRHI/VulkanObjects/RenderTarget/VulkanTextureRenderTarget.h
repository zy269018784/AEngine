#pragma once
#include "VulkanRenderTarget.h"
#include "RHI/RHIObjects/RenderTarget/RHITextureRenderTarget.h"
#include "VulkanRHI/Vulkan.h"
/*
 *  Image View
 *  Render Pass
 *  Framebuffery
 */
class VulkanTexture;
class VulkanDevice;
class VulkanFrameBuffer;
class VulkanTextureRenderTarget : public RHITextureRenderTarget
{
public:
    VulkanTextureRenderTarget(VulkanDevice *InDevice, std::uint32_t InWidth, std::uint32_t InHeight);
    ~VulkanTextureRenderTarget();
public:
    virtual void Create(std::vector<RHITexture *> InColorAttachments,
                    std::vector<RHITexture *> InDepthAttachments) override final;
    virtual void CreateFramebuffer() override final;
    virtual void CreateRenderPass()  override final;
    virtual void CreateCommandbuffer() override final;
    virtual void RHIBeginRenderPass() override final;
    virtual void RHIEndRenderPass() override final;
    virtual void RHIBeginRenderPass2() override final;
    virtual void RHIEndRenderPass2() override final;
    virtual void RHIBeginFrame() override final;
    virtual void RHIEndFrame() override final;
    virtual void GetExtent(float &x, float &y, float &w, float &h) override final;
    virtual void Resize(float Width, float Height) final override;
    virtual void WaitDeviceIdle() final override;
public:
    VulkanTexture *Texture;
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
    //std::vector<VkImageView>				ImageViews;
    /*
        分辨率
    */
   // VkExtent2D								Resolution;
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