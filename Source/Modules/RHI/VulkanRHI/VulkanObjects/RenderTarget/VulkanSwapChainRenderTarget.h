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
class VulkanSurface;
class VulkanDevice;
class VulkanSwapChainRenderTarget
{
public:
    VulkanSwapChainRenderTarget(VulkanDevice *InDevice, VulkanSurface* InSurface);
    ~VulkanSwapChainRenderTarget();
private:
    /*
        Surface
    */
    VulkanSurface*							Surface;
    /*
        设备
    */
    VulkanDevice							*Device;
    /*
        分辨率
    */
    VkExtent2D								SwapChainExtent;
    /*
        Format
    */
    VkFormat								SwapChainImageFormat;
    /*
        色彩空间
    */
    VkColorSpaceKHR							SwapChainClorSpace;
    /*
        呈现模式
    */
    VkPresentModeKHR						SwapChainPresentMode;
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