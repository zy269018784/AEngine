#pragma once
#include "RHIObjects/RenderTarget/RHISwapChainRenderTarget.h"
#include "VulkanRenderTarget.h"
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
class VulkanSurface;
class VulkanDevice;
class VulkanFrame;
class VulkanSwapChainRenderTarget : public VulkanRenderTarget, public RHISwapchainRenderTarget
{
public:
    VulkanSwapChainRenderTarget(VulkanDevice *InDevice, VulkanSurface* InSurface, RHIPixelFormat InPixelFormat);
    ~VulkanSwapChainRenderTarget();
    virtual void RHIBeginRenderPass() override final;
    virtual void RHIEndRenderPass() override final;
    virtual void RHIBeginFrame() override final;
    virtual void RHIEndFrame() override final;
private:
public:
    /*
        Surface
    */
    VulkanSurface*							Surface;
    /*
        设备
    */
    VulkanDevice							*Device;
    /*
        色彩空间
    */
    VkColorSpaceKHR							SwapChainClorSpace;
    /*
        呈现模式
    */
    VkPresentModeKHR						SwapChainPresentMode;
    /*
        同步帧
    */
    std::vector<VulkanFrame*>			Frames;						// SwapChainImages.size()
public:
    VulkanSwapChain *SwapChain;
};