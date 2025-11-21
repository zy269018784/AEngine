#include "VulkanObjects/SwapChain/VulkanSwapChain.h"
#include "VulkanObjects/Surface/VulkanSurface.h"
#include "VulkanObjects/Device/VulkanDevice.h"
#include "VulkanObjects/FrameBuffer/VulkanFrameBuffer.h"
#include <iostream>
#include <limits>
#include <stdexcept>
 
VulkanSwapChain::VulkanSwapChain(VulkanDevice* InDevice, VulkanSurface* InSurface)
    : Device(InDevice), Surface(InSurface)
{ 
    SwapChainImageFormat    = Surface->CurrentFormat.format;
    SwapChainClorSpace      = Surface->CurrentFormat.colorSpace;
    SwapChainExtent         = Surface->CurrentExtent;
    SwapChainPresentMode    = Surface->CurrentPresentMode;

    uint32_t ImageCount = Surface->Capabilities.minImageCount + 1;
    if (Surface->Capabilities.maxImageCount > 0 && ImageCount > Surface->Capabilities.maxImageCount)
    {
        ImageCount = Surface->Capabilities.maxImageCount;
    }
    std::cout << "VulkanSwapChain SwapChainImageFormat " << SwapChainImageFormat << std::endl;
    CreateSwapChain();
    GetSwapchainImagesKHR(&ImageCount, nullptr);
    SwapChainImages.resize(ImageCount);
    GetSwapchainImagesKHR(&ImageCount, SwapChainImages.data());
    std::cout << "ImageCount " << ImageCount << std::endl;

    //SwapChainImageViews.resize(SwapChainImages.size());
    //for (size_t i = 0; i < SwapChainImages.size(); i++) 
    //{
    //    VkImageViewCreateInfo CreateInfo{};
    //    CreateInfo.sType                            = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    //    CreateInfo.image                            = SwapChainImages[i];
    //    CreateInfo.viewType                         = VK_IMAGE_VIEW_TYPE_2D;
    //    CreateInfo.format                           = SwapChainImageFormat;
    //    CreateInfo.components.r                     = VK_COMPONENT_SWIZZLE_IDENTITY;
    //    CreateInfo.components.g                     = VK_COMPONENT_SWIZZLE_IDENTITY;
    //    CreateInfo.components.b                     = VK_COMPONENT_SWIZZLE_IDENTITY;
    //    CreateInfo.components.a                     = VK_COMPONENT_SWIZZLE_IDENTITY;
    //    CreateInfo.subresourceRange.aspectMask      = VK_IMAGE_ASPECT_COLOR_BIT;
    //    CreateInfo.subresourceRange.baseMipLevel    = 0;
    //    CreateInfo.subresourceRange.levelCount      = 1;
    //    CreateInfo.subresourceRange.baseArrayLayer  = 0;
    //    CreateInfo.subresourceRange.layerCount      = 1;
    //    if (Device->CreateImageView(&CreateInfo, nullptr, &SwapChainImageViews[i]) != VK_SUCCESS) 
    //    {
    //        throw std::runtime_error("failed to create image views!");
    //    }
    //}

    CreateImageViews();

    /*
        创建Render Pass
    */
    RenderPass = new VulkanRenderPass(Device, GetFormat());

    /*
        创建Frame Buffer
    */
    auto ImageViews = GetImageViews();
    FrameBuffers.resize(GetImageCount());
    for (int i = 0; i < FrameBuffers.size(); i++)
    {
        auto Handle = ImageViews[i];
        FrameBuffers[i] = new VulkanFrameBuffer(Device, RenderPass, { GetWidth(), GetHeight() }, Handle);
    }
}

VulkanSwapChain::~VulkanSwapChain()
{ 
    /*
        释放Frame Buffer
    */
    for (int FrameBufferIndex = 0; FrameBufferIndex < FrameBuffers.size(); FrameBufferIndex++)
    {
        delete FrameBuffers[FrameBufferIndex];
    }

    /*
        释放交换链
    */
    Device->DestroySwapchainKHR(Handle, nullptr);

    /*
    
    */
    delete RenderPass;

    /*
        释放Image View
    */
    for (int i = 0; i < SwapChainImageViews.size(); i++)
    {
        Device->DestroyImageView(SwapChainImageViews[i], nullptr);
    }
}

VkSwapchainKHR VulkanSwapChain::GetHandle() const
{
    return Handle;
}

VkFormat VulkanSwapChain::GetFormat() const
{
    return SwapChainImageFormat;
}

std::uint32_t VulkanSwapChain::GetWidth() const
{
    return SwapChainExtent.width;
}

std::uint32_t VulkanSwapChain::GetHeight() const
{
    return SwapChainExtent.height;
}

int VulkanSwapChain::GetImageCount() const
{
    return SwapChainImages.size();
}

std::vector<VkImageView> VulkanSwapChain::GetImageViews() const
{
    return SwapChainImageViews;
}

void VulkanSwapChain::CreateSwapChain()
{
    std::cout << "CreateSwapChain 1" << std::endl;
    uint32_t ImageCount = Surface->Capabilities.minImageCount + 1;
    if (Surface->Capabilities.maxImageCount > 0 && ImageCount > Surface->Capabilities.maxImageCount)
    {
        ImageCount = Surface->Capabilities.maxImageCount;
    }
    std::cout << "CreateSwapChain 2" << std::endl;
    VkSwapchainCreateInfoKHR CreateInfo = {};
    CreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    CreateInfo.surface = Surface->GetHandle();
    CreateInfo.minImageCount = ImageCount;
    CreateInfo.imageFormat = SwapChainImageFormat;
    CreateInfo.imageColorSpace = SwapChainClorSpace;
    CreateInfo.imageExtent = SwapChainExtent;
    CreateInfo.presentMode = SwapChainPresentMode;
    CreateInfo.imageArrayLayers = 1;
    CreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
    CreateInfo.preTransform = Surface->Capabilities.currentTransform;
    CreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    CreateInfo.clipped = VK_TRUE;

    if (false)
    {
        uint32_t QueueFamilyIndices[] = { 0, 0 };
        CreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        CreateInfo.queueFamilyIndexCount = 2;
        CreateInfo.pQueueFamilyIndices = QueueFamilyIndices;
    }
    else {
        CreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    }
    std::cout << "CreateSwapChain 3 " << Device << std::endl;
    VkResult Result = Device->CreateSwapchainKHR(&CreateInfo, nullptr, &Handle);
    if (VK_SUCCESS != Result)
    {
        std::cout << "vkCreateSwapchainKHR failed " << Result << std::endl;
        throw std::runtime_error("failed to create swap chain!");
    }
    std::cout << "CreateSwapChain 4" << std::endl;
    std::cout << "vkCreateSwapchainKHR ok " << Handle << std::endl;

}

void VulkanSwapChain::CreateImageViews()
{
    SwapChainImageViews.resize(SwapChainImages.size());
   
    for (size_t i = 0; i < SwapChainImages.size(); i++) 
    {
        VkImageViewCreateInfo CreateInfo{};
        CreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        CreateInfo.image = SwapChainImages[i];
        CreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        CreateInfo.format = SwapChainImageFormat;
        CreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        CreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        CreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        CreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        CreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        CreateInfo.subresourceRange.baseMipLevel = 0;
        CreateInfo.subresourceRange.levelCount = 1;
        CreateInfo.subresourceRange.baseArrayLayer = 0;
        CreateInfo.subresourceRange.layerCount = 1;
           
        VkResult Result = Device->CreateImageView(&CreateInfo, nullptr, &SwapChainImageViews[i]);
        if (VK_SUCCESS != Result)
        {
            throw std::runtime_error("failed to create image views!");
        }
    }
}

void VulkanSwapChain::Resize(float Width, float Height)
{
    Cleanup();
}

void VulkanSwapChain::Cleanup()
{
    /*
        释放Frame Buffer
    */
    for (int FrameBufferIndex = 0; FrameBufferIndex < FrameBuffers.size(); FrameBufferIndex++)
    {
        delete FrameBuffers[FrameBufferIndex];
    }

    /*
        释放交换链
    */
    Device->DestroySwapchainKHR(Handle, nullptr);

    /*

    */
    delete RenderPass;

    /*
        释放Image View
    */
    for (int i = 0; i < SwapChainImageViews.size(); i++)
    {
        Device->DestroyImageView(SwapChainImageViews[i], nullptr);
    }
}

VkSurfaceFormatKHR VulkanSwapChain::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) 
{
    for (const auto& availableFormat : availableFormats) {
        if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
            return availableFormat;
        }
    }

    return availableFormats[0];
}

VkPresentModeKHR VulkanSwapChain::chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
{
    for (const auto& availablePresentMode : availablePresentModes) {
        if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
            return availablePresentMode;
        }
    }

    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D VulkanSwapChain::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
{
    if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
        return capabilities.currentExtent;
    } 
    else 
    {
        int width = 0, height = 0;
        //glfwGetFramebufferSize(window, &width, &height);

        VkExtent2D actualExtent = {
            static_cast<uint32_t>(width),
            static_cast<uint32_t>(height)
        };

        //actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
        //actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

        return actualExtent;
    }
}
