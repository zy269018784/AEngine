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
class VulkanSwapChainRenderTarget : public VulkanRenderTarget
{
public:
    //VulkanSwapChainRenderTarget(VulkanSwapChain *InSwapChain, VulkanDevice *InDevice);
    VulkanSwapChainRenderTarget(VulkanDevice *InDevice, VulkanSurface* InSurface);
    ~VulkanSwapChainRenderTarget();
    virtual void RHIBeginRenderPass() override final;
    virtual void RHIEndRenderPass() override final;
    virtual void RHIBeginFrame() override final;
    virtual void RHIEndFrame() override final;
    virtual void GetExtent(float &x, float &y, float &w, float &h) override final;
    virtual void Resize(float Width, float Height) final override;
public:
    std::vector<VulkanTexture *> Textures;
    /*
        设备
    */
   // VulkanDevice						*Device;
    /*
        交换链
     */
    VulkanSwapChain                     *SwapChain;
    /*
        同步帧
    */
    std::vector<VulkanFrame*>			Frames;						// 2
};