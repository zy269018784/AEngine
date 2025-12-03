#include "VulkanObjects/Surface/VulkanSurface.h"

#include <iostream>
#include <limits>

#include "VulkanRHI.h"

VulkanSurface::VulkanSurface()
{

}

VulkanSurface::VulkanSurface(VulkanInstance* InInstance, VkSurfaceKHR Surface)
    : Instance(InInstance)
{
    Handle = Surface;
}

#ifdef RHI_USE_WIN32_KHR
VulkanSurface::VulkanSurface(VulkanInstance* InInstance, HINSTANCE Hinstance, HWND Hwnd)
    : Instance(InInstance)
{
    VkWin32SurfaceCreateInfoKHR CreateInfo{};
    CreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    CreateInfo.hwnd = Hwnd;
    CreateInfo.hinstance = Hinstance;
    vkCreateWin32SurfaceKHR_1(Instance->GetHandle(), &CreateInfo, nullptr, &Handle);
}
#endif

#ifdef RHI_USE_XCB_KHR
VulkanSurface::VulkanSurface(VulkanInstance* InInstance, xcb_connection_t* connection, xcb_window_t window)
{
    VkXcbSurfaceCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
    createInfo.connection = connection;
    createInfo.window = window;

    // Create the surface
    VkResult result = vkCreateXcbSurfaceKHR(InInstance->GetHandle(), &createInfo, nullptr, &Handle);
    if (result != VK_SUCCESS) {
        // Handle error
        throw std::runtime_error("Failed to create XCB Vulkan surface!");
    }
}
#endif
#ifdef RHI_USE_Xlib_KHR
VulkanSurface::VulkanSurface(VulkanInstance* InInstance, Display* Disp, Window Win)
{
    VkXlibSurfaceCreateInfoKHR CreateInfo{};
    CreateInfo.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
    CreateInfo.dpy = Disp;
    CreateInfo.window = Win;
    VkResult Result = vkCreateXlibSurfaceKHR(InInstance->GetHandle(), &CreateInfo, nullptr, &Handle);
    if (Result != VK_SUCCESS)
    {
        std::cout << "vkCreateXlibSurfaceKHR faliled " << Result << std::endl;
        throw std::runtime_error("Failed to create XCB Vulkan surface!");
    }
}
#endif

#ifdef RHI_USE_ANDROID_KHR
VulkanSurface::VulkanSurface(VulkanInstance* InInstance, struct ANativeWindow* Win)
{
    VkAndroidSurfaceCreateInfoKHR CreateInfo{};
    CreateInfo.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
    CreateInfo.window = Win;
    VkResult Result = vkCreateAndroidSurfaceKHR(InInstance->GetHandle(), &CreateInfo, nullptr, &Handle);
    if (Result != VK_SUCCESS)
    {
        std::cout << "vkCreateAndroidSurfaceKHR failed " << Result << std::endl;
        throw std::runtime_error("Failed to create Android Vulkan surface!");
    }
}
#endif

#ifdef RHI_USE_DirectFB_EXT
VulkanSurface::VulkanSurface(VulkanInstance* InInstance, DirectFB* dfb, IDirectFBSurface* surface)
{
    VkDirectFBSurfaceCreateInfoEXT CreateInfo{};
    CreateInfo.sType = VK_STRUCTURE_TYPE_DIRECTFB_SURFACE_CREATE_INFO_EXT;
    CreateInfo.dfb = dfb;
    CreateInfo.surface = surface;
    VkResult Result = vkCreateDirectFBSurfaceEXT(InInstance->GetHandle(), &CreateInfo, nullptr, &Handle);
    if (Result != VK_SUCCESS)
    {
        std::cout << "vkCreateDirectFBSurfaceEXT failed " << Result << std::endl;
        throw std::runtime_error("Failed to create DirectFB Vulkan surface!");
    }
}
#endif

#ifdef RHI_USE_IOS_MVK
VulkanSurface::VulkanSurface(VulkanInstance* InInstance, const void* pView)
{
    VkIOSSurfaceCreateInfoMVK CreateInfo{};
    CreateInfo.sType = VK_STRUCTURE_TYPE_IOS_SURFACE_CREATE_INFO_MVK;
    CreateInfo.pView = pView;
    VkResult Result = vkCreateIOSSurfaceMVK(InInstance->GetHandle(), &CreateInfo, nullptr, &Handle);
    if (Result != VK_SUCCESS)
    {
        std::cout << "vkCreateIOSSurfaceMVK failed " << Result << std::endl;
        throw std::runtime_error("Failed to create iOS Vulkan surface!");
    }
}
#endif

#ifdef RHI_USE_MacOS_MVK
VulkanSurface::VulkanSurface(VulkanInstance* InInstance, const void* pView)
{
    VkMacOSSurfaceCreateInfoMVK CreateInfo{};
    CreateInfo.sType = VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK;
    CreateInfo.pView = pView;
    VkResult Result = vkCreateMacOSSurfaceMVK(InInstance->GetHandle(), &CreateInfo, nullptr, &Handle);
    if (Result != VK_SUCCESS)
    {
        std::cout << "vkCreateMacOSSurfaceMVK failed " << Result << std::endl;
        throw std::runtime_error("Failed to create macOS Vulkan surface!");
    }
}
#endif

#ifdef RHI_USE_Metal_EXT
VulkanSurface::VulkanSurface(VulkanInstance* InInstance, const CAMetalLayer* Layer)
{
    VkMetalSurfaceCreateInfoEXT CreateInfo{};
    CreateInfo.sType = VK_STRUCTURE_TYPE_METAL_SURFACE_CREATE_INFO_EXT;
    CreateInfo.pLayer = Layer;
    VkResult Result = vkCreateMetalSurfaceEXT(InInstance->GetHandle(), &CreateInfo, nullptr, &Handle);
    if (Result != VK_SUCCESS)
    {
        std::cout << "vkCreateMetalSurfaceEXT failed " << Result << std::endl;
        throw std::runtime_error("Failed to create Metal Vulkan surface!");
    }
}
#endif

#ifdef RHI_USE_QNX
VulkanSurface::VulkanSurface(VulkanInstance* InInstance, struct _screen_context* context, struct _screen_window* window)
{
    VkScreenSurfaceCreateInfoQNX CreateInfo{};
    CreateInfo.sType = VK_STRUCTURE_TYPE_SCREEN_SURFACE_CREATE_INFO_QNX;
    CreateInfo.context = context;
    CreateInfo.window = window;
    VkResult Result = vkCreateScreenSurfaceQNX(InInstance->GetHandle(), &CreateInfo, nullptr, &Handle);
    if (Result != VK_SUCCESS)
    {
        std::cout << "vkCreateScreenSurfaceQNX failed " << Result << std::endl;
        throw std::runtime_error("Failed to create QNX Vulkan surface!");
    }
}
#endif

#ifdef RHI_USE_VI_NN
VulkanSurface::VulkanSurface(VulkanInstance* InInstance, void* window)
{
    VkViSurfaceCreateInfoNN CreateInfo{};
    CreateInfo.sType = VK_STRUCTURE_TYPE_VI_SURFACE_CREATE_INFO_NN;
    CreateInfo.window = window;
    VkResult Result = vkCreateViSurfaceNN(InInstance->GetHandle(), &CreateInfo, nullptr, &Handle);
    if (Result != VK_SUCCESS)
    {
        std::cout << "vkCreateViSurfaceNN failed " << Result << std::endl;
        throw std::runtime_error("Failed to create VI_NN Vulkan surface!");
    }
}
#endif

#ifdef RHI_USE_FUCHSIA
VulkanSurface::VulkanSurface(VulkanInstance* InInstance, zx_handle_t imagePipeHandle)
{
    VkImagePipeSurfaceCreateInfoFUCHSIA CreateInfo{};
    CreateInfo.sType = VK_STRUCTURE_TYPE_IMAGEPIPE_SURFACE_CREATE_INFO_FUCHSIA;
    CreateInfo.imagePipeHandle = imagePipeHandle;
    VkResult Result = vkCreateImagePipeSurfaceFUCHSIA(InInstance->GetHandle(), &CreateInfo, nullptr, &Handle);
    if (Result != VK_SUCCESS)
    {
        std::cout << "vkCreateImagePipeSurfaceFUCHSIA failed " << Result << std::endl;
        throw std::runtime_error("Failed to create Fuchsia Vulkan surface!");
    }
}
#endif

#ifdef RHI_USE_GGP
VulkanSurface::VulkanSurface(VulkanInstance* InInstance, GgpStreamDescriptor StreamDescriptor)
{
    VkStreamDescriptorSurfaceCreateInfoGGP CreateInfo{};
    CreateInfo.sType = VK_STRUCTURE_TYPE_STREAM_DESCRIPTOR_SURFACE_CREATE_INFO_GGP;
    CreateInfo.streamDescriptor = StreamDescriptor;
    VkResult Result = vkCreateStreamDescriptorSurfaceGGP(InInstance->GetHandle(), &CreateInfo, nullptr, &Handle);
    if (Result != VK_SUCCESS)
    {
        std::cout << "vkCreateStreamDescriptorSurfaceGGP failed " << Result << std::endl;
        throw std::runtime_error("Failed to create GGP Vulkan surface!");
    }
}
#endif

#ifdef RHI_USE_OHOS
VulkanSurface::VulkanSurface(VulkanInstance* InInstance, OHNativeWindow* window)
{
    VkOHOSSurfaceCreateInfoOHOS CreateInfo{};
    CreateInfo.sType = VK_STRUCTURE_TYPE_OHOS_SURFACE_CREATE_INFO_OHOS;
    CreateInfo.window = window;
    VkResult Result = vkCreateOHOSSurfaceOHOS(InInstance->GetHandle(), &CreateInfo, nullptr, &Handle);
    if (Result != VK_SUCCESS)
    {
        std::cout << "vkCreateOHOSSurfaceOHOS failed " << Result << std::endl;
        throw std::runtime_error("Failed to create OHOS Vulkan surface!");
    }
}
#endif

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
