#include "VulkanRHI/VulkanObjects/SwapChain/VulkanSwapChain.h"
#include "VulkanRHI/VulkanObjects/Surface/VulkanSurface.h"
#include "VulkanRHI/VulkanObjects/Device/VulkanDevice.h"
#include "VulkanRHI/VulkanObjects/Core/VulkanCore.h"

#include <iostream>
#include <limits>
#include <stdexcept>
 
VulkanSwapChain:: VulkanSwapChain(VulkanDevice* InDevice, VulkanSurface* InSurface)
    : RHISwapChain(InDevice, InSurface)
{
   // SwapChainClorSpace      = ToVkColorSpace(InSurface->GetRHIColorSpace());

    SetRHIPresentMode(InSurface->GetRHIPresentMode());
    SetRHIColorSpace(InSurface->GetRHIColorSpace());
    SetRHIPixelFormat(InSurface->GetRHIPixelFormat());
    SetWidth(InSurface->GetWidth());
    SetHeight(InSurface->GetHeight());


    uint32_t ImageCount = InSurface->Capabilities.minImageCount + 1;
    if (InSurface->Capabilities.maxImageCount > 0 && ImageCount > InSurface->Capabilities.maxImageCount)
    {
        ImageCount = InSurface->Capabilities.maxImageCount;
    }

    CreateSwapChain();
    GetSwapchainImagesKHR(&ImageCount, nullptr);
    SwapChainImages.resize(ImageCount);
    GetSwapchainImagesKHR(&ImageCount, SwapChainImages.data());
    std::cout << "ImageCount " << ImageCount << std::endl;

    CreateImageViews();
}

VulkanSwapChain::~VulkanSwapChain()
{
    /*
        释放交换链
    */
    dynamic_cast<VulkanDevice *>(Device)->DestroySwapchainKHR(Handle, nullptr);

    /*
    
    */
    //delete RenderPass;

    /*
        释放Image View
    */
    for (int i = 0; i < SwapChainImageViews.size(); i++)
    {
        dynamic_cast<VulkanDevice *>(Device)->DestroyImageView(SwapChainImageViews[i], nullptr);
    }
}

VkSwapchainKHR VulkanSwapChain::GetHandle() const
{
    return Handle;
}

VkFormat VulkanSwapChain::GetFormat() const
{
    return ToVkFormat(GetRHIPixelFormat());
}

VkPresentModeKHR VulkanSwapChain::GetPresentMode() const
{
    return ToVkPresentMode(GetRHIPresentMode());
}

VkColorSpaceKHR VulkanSwapChain::GetColorSpace() const
{
    return ToVkColorSpace(GetRHIColorSpace());
}

VkExtent2D VulkanSwapChain::GetImageExtent() const
{
    return { GetWidth(), GetHeight() };
}

VkSurfaceKHR VulkanSwapChain::GetSurface() const
{
    return dynamic_cast<VulkanSurface *>(Surface)->GetHandle();
}

std::uint32_t VulkanSwapChain::GetMaxImageCount() const
{
    std::uint32_t ImageCount = dynamic_cast<VulkanSurface *>(Surface)->Capabilities.minImageCount + 1;
    if (dynamic_cast<VulkanSurface *>(Surface)->Capabilities.maxImageCount > 0 && ImageCount > dynamic_cast<VulkanSurface *>(Surface)->Capabilities.maxImageCount)
    {
        ImageCount = dynamic_cast<VulkanSurface *>(Surface)->Capabilities.maxImageCount;
    }
    return ImageCount;
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
#if 0
    uint32_t ImageCount = dynamic_cast<VulkanSurface *>(Surface)->Capabilities.minImageCount + 1;
    if (dynamic_cast<VulkanSurface *>(Surface)->Capabilities.maxImageCount > 0 && ImageCount > dynamic_cast<VulkanSurface *>(Surface)->Capabilities.maxImageCount)
    {
        ImageCount = dynamic_cast<VulkanSurface *>(Surface)->Capabilities.maxImageCount;
    }
#endif
    VkSwapchainCreateInfoKHR CreateInfo = {};
    CreateInfo.sType            = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    CreateInfo.surface          = GetSurface();
    CreateInfo.minImageCount    = GetMaxImageCount();
    CreateInfo.imageFormat      = GetFormat();
    CreateInfo.imageColorSpace  = GetColorSpace();
    CreateInfo.presentMode      = GetPresentMode();
    CreateInfo.imageExtent      = GetImageExtent();
    CreateInfo.imageArrayLayers = 1;
    CreateInfo.preTransform     = dynamic_cast<VulkanSurface *>(Surface)->Capabilities.currentTransform;
    /*
     * 为什么这样写
     */
    CreateInfo.imageUsage       = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
    CreateInfo.compositeAlpha   = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    CreateInfo.clipped          = VK_TRUE;

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

    VkResult Result = dynamic_cast<VulkanDevice *>(Device)->CreateSwapchainKHR(&CreateInfo, nullptr, &Handle);
    if (VK_SUCCESS != Result)
    {
        std::cout << "vkCreateSwapchainKHR failed " << Result << std::endl;
        throw std::runtime_error("failed to create swap chain!");
    }
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
        CreateInfo.format = GetFormat();
        CreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        CreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        CreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        CreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        CreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        CreateInfo.subresourceRange.baseMipLevel = 0;
        CreateInfo.subresourceRange.levelCount = 1;
        CreateInfo.subresourceRange.baseArrayLayer = 0;
        CreateInfo.subresourceRange.layerCount = 1;
           
        VkResult Result = dynamic_cast<VulkanDevice *>(Device)->CreateImageView(&CreateInfo, nullptr, &SwapChainImageViews[i]);
        if (VK_SUCCESS != Result)
        {
            throw std::runtime_error("failed to create image views!");
        }
    }
}

void VulkanSwapChain::Resize(float InWidth, float InHeight)
{
    Cleanup();

    SetRHIPresentMode(Surface->GetRHIPresentMode());
    SetRHIColorSpace(Surface->GetRHIColorSpace());
    SetRHIPixelFormat(Surface->GetRHIPixelFormat());
    SetWidth(Surface->GetWidth());
    SetHeight(Surface->GetHeight());
#if 0
    uint32_t ImageCount = dynamic_cast<VulkanSurface *>(Surface)->Capabilities.minImageCount + 1;
    if (dynamic_cast<VulkanSurface *>(Surface)->Capabilities.maxImageCount > 0 && ImageCount > dynamic_cast<VulkanSurface *>(Surface)->Capabilities.maxImageCount)
    {
        ImageCount = dynamic_cast<VulkanSurface *>(Surface)->Capabilities.maxImageCount;
    }
#endif
    std::uint32_t ImageCount = GetMaxImageCount();
    CreateSwapChain();
    GetSwapchainImagesKHR(&ImageCount, nullptr);
    SwapChainImages.resize(ImageCount);
    GetSwapchainImagesKHR(&ImageCount, SwapChainImages.data());
    std::cout << "ImageCount " << ImageCount << std::endl;

    CreateImageViews();
}

void VulkanSwapChain::Cleanup()
{
    /*
        释放交换链
    */
    dynamic_cast<VulkanDevice *>(Device)->DestroySwapchainKHR(Handle, nullptr);

    /*
        释放Image View
    */
    for (int i = 0; i < SwapChainImageViews.size(); i++)
    {
        dynamic_cast<VulkanDevice *>(Device)->DestroyImageView(SwapChainImageViews[i], nullptr);
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
