#pragma once
#include "RHIObjects/RHIRenderTarget.h"
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
class VulkanSwapChainRenderTarget : public VulkanRenderTarget
{
public:
    VulkanSwapChainRenderTarget(VulkanDevice *InDevice, VulkanSurface* InSurface);
    ~VulkanSwapChainRenderTarget();
    void RHIBeginFrame();
    void RHIEndFrame();
    void RHIBeginRenderPass();
    void RHIEndRenderPass();
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