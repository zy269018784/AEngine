#include "VulkanObjects/Surface/VulkanSurface.h"
#include <iostream>
#include <algorithm>
#include <limits>


VulkanSurface::VulkanSurface()
{

}

VulkanSurface::VulkanSurface(VulkanInstance* InInstance, VkSurfaceKHR Surface)
    : Instance(InInstance)
{
    Handle = Surface;
}

//VulkanSurface::VulkanSurface(VulkanInstance *InInstance, GLFWwindow* InWindow)
//	: GLFWWindow(InWindow), Instance(InInstance)
//{
//    VkResult Result = glfwCreateWindowSurface(Instance->GetHandle(), GLFWWindow, nullptr, &Handle);
//    if (VK_SUCCESS != Result)
//    {
//        std::cout << "glfwCreateWindowSurface failed " << Result << std::endl;
//        throw std::runtime_error("failed to create window surface!");
//    }
//    std::cout << "glfwCreateWindowSurface ok " << Handle << std::endl;
//}

VulkanSurface::~VulkanSurface()
{
    DestroySurfaceKHR(nullptr);
}


VkSurfaceKHR VulkanSurface::GetHandle() const
{
	return Handle;
}

void VulkanSurface::Query(VulkanPhysicalDevice& PhysicalDevice)
{

    PhysicalDevice.GetPhysicalDeviceSurfaceCapabilitiesKHR(Handle, &Capabilities);

    std::uint32_t FormatCount;
    PhysicalDevice.GetPhysicalDeviceSurfaceFormatsKHR(Handle, &FormatCount, nullptr);

    std::cout << "FormatCount " << FormatCount << std::endl;
    if (FormatCount != 0)
    {
        Formats.resize(FormatCount);
        PhysicalDevice.GetPhysicalDeviceSurfaceFormatsKHR(Handle, &FormatCount, Formats.data());
    }
    /*
        format和color space
    */
    for (const auto& availableFormat : Formats) 
    {
        std::cout << "availableFormat " << availableFormat.format  << " colorSpace " << availableFormat.colorSpace << std::endl;
        if (availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
        {
            if (availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
            {
                CurrentFormat = availableFormat;
                break;
            }
            else if (availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
            {
                CurrentFormat = availableFormat;
                break;
            }
        }
    } 
    std::cout << "CurrentFormat " << CurrentFormat.format << std::endl;

    uint32_t PresentModeCount;
    //vkGetPhysicalDeviceSurfacePresentModesKHR(PhysicalDevice.GetHandle(), Handle, &PresentModeCount, nullptr);
    PhysicalDevice.GetPhysicalDeviceSurfacePresentModesKHR(Handle, &PresentModeCount, nullptr);

    if (PresentModeCount != 0) 
    {
        PresentModes.resize(PresentModeCount);
        //vkGetPhysicalDeviceSurfacePresentModesKHR(PhysicalDevice.GetHandle(), Handle, &PresentModeCount, PresentModes.data());
        PhysicalDevice.GetPhysicalDeviceSurfacePresentModesKHR(Handle, &PresentModeCount, PresentModes.data());
    }

    for (const auto& availablePresentMode : PresentModes)
    {
        if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
        {
            CurrentPresentMode = availablePresentMode;
            break;
        }
    }

    std::cout << "PresentModeCount " << PresentModeCount << std::endl;

    std::cout << "Capabilities.currentExtent.width  "  << Capabilities.currentExtent.width  << std::endl;
    std::cout << "Capabilities.currentExtent.height  " << Capabilities.currentExtent.height << std::endl;

    if (Capabilities.currentExtent.width != (uint32_t)std::numeric_limits<uint32_t>::max())
    {
        CurrentExtent = Capabilities.currentExtent;
    }
    //else
    //{
    //    int width, height;
    //    glfwGetFramebufferSize(GLFWWindow, &width, &height);

    //    VkExtent2D actualExtent = {
    //        static_cast<std::uint32_t>(width),
    //        static_cast<std::uint32_t>(height)
    //    };

    //    actualExtent.width  = std::clamp(actualExtent.width, Capabilities.minImageExtent.width, Capabilities.maxImageExtent.width);
    //    actualExtent.height = std::clamp(actualExtent.height, Capabilities.minImageExtent.height, Capabilities.maxImageExtent.height);

    //    CurrentExtent = actualExtent;
    //}
}
