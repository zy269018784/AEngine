#pragma once
#include "RHI/RHIObjects/RenderTarget/RHISwapChainRenderTarget.h"
#include "VulkanRenderTarget.h"
#include "VulkanRHI/Vulkan.h"
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
class VulkanSurface;
class VulkanDevice;
class VulkanFrame;
class VulkanTexture;
class VulkanSwapChainRenderTarget : public RHISwapChainRenderTarget
{
public:
    //VulkanSwapChainRenderTarget(VulkanSwapChain *InSwapChain, VulkanDevice *InDevice);
    VulkanSwapChainRenderTarget(VulkanDevice *InDevice, VulkanSurface* InSurface);
    ~VulkanSwapChainRenderTarget();
    virtual void CreateFramebuffer() override final;
    virtual void CreateRenderPass()  override final;
    virtual void CreateCommandbuffer() override final;
    virtual void RHIBeginRenderPass() override final;
    virtual void RHIEndRenderPass() override final;
    virtual void RHIBeginFrame() override final;
    virtual void RHIEndFrame() override final;
    virtual void GetExtent(float &x, float &y, float &w, float &h) override final;
    virtual void Resize(float Width, float Height) final override;
    virtual void WaitDeviceIdle() final override;
public:
    /*
        Image View
    */
    std::vector<VkImageView>				ImageViews;
    /*
        Framebuffers
    */
    std::vector<VulkanFrameBuffer*>		    FrameBuffers;			// SwapChainImages.size()
    /*
        当前帧编号
        FrameIndex: [0, 1]
    */
    std::uint32_t					FrameIndex = 0;
    /*
     * 深度缓冲纹理
     */
    std::vector<VulkanTexture *> Textures;
    /*
        同步帧
    */
    std::vector<VulkanFrame*>			Frames;						// 2

#if 0
    // AMD Radeon RX580 2048SP
    RHIAttachmentType DepthStencilType = RHIAttachmentType::DepthStencil_D32_S8;
    RHIPixelFormat  DepthStencilPixelFormat = RHIPixelFormat::PF_DepthStencil_D32_S8;
#else
    // 4060 support
    // AMD Radeon RX580 2048SP do not support
    RHIAttachmentType DepthStencilType = RHIAttachmentType::DepthStencil_D24_S8;
    RHIPixelFormat  DepthStencilPixelFormat = RHIPixelFormat::PF_DepthStencil_D24_S8;
#endif
};