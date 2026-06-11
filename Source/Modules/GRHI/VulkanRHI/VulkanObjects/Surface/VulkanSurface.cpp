#include "VulkanRHI/VulkanRHI.h"
#include "VulkanRHI/VulkanObjects/Core/VulkanCore.h"
#include "VulkanRHI/VulkanObjects/Core/VulkanAPI.h"
#include "VulkanRHI/VulkanObjects/Surface/VulkanSurface.h"
#include "VulkanRHI/VulkanObjects/Instance/VulkanInstance.h"
#include "VulkanRHI/VulkanObjects/PhysicalDevice/VulkanPhysicalDevice.h"
#include <iostream>
#include <limits>

#if RHI_USE_WIN32_KHR
VulkanSurface::VulkanSurface(VulkanInstance* InInstance, HINSTANCE Hinstance, HWND Hwnd)
    : Instance(InInstance)
{
    std::cout << "VulkanSurface::VulkanSurface " << std::endl;
    VkWin32SurfaceCreateInfoKHR CreateInfo{};
    CreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    CreateInfo.hwnd = Hwnd;
    CreateInfo.hinstance = Hinstance;
    if (!VulkanAPI::GetInstance()->vkCreateWin32SurfaceKHR)
        std::cout << "vkCreateWin32SurfaceKHR is null" << std::endl;
    VulkanAPI::GetInstance()->vkCreateWin32SurfaceKHR(InInstance->GetHandle(), &CreateInfo, nullptr, &Handle);
}
#endif

#if RHI_USE_XCB_KHR
VulkanSurface::VulkanSurface(VulkanInstance* InInstance, xcb_connection_t* connection, xcb_window_t window)
: Instance(InInstance)
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
#if RHI_USE_Xlib_KHR
VulkanSurface::VulkanSurface(VulkanInstance* InInstance, Display* Disp, Window Win)
: Instance(InInstance)
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

#if RHI_USE_WAYLAND_KHR
VulkanSurface::VulkanSurface(VulkanInstance* InInstance, struct wl_display* display, struct wl_surface* surface)
: Instance(InInstance)
{
    VkWaylandSurfaceCreateInfoKHR CreateInfo{};
    CreateInfo.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
    CreateInfo.display = display;
    CreateInfo.surface = surface;
    VkResult Result = vkCreateWaylandSurfaceKHR(InInstance->GetHandle(), &CreateInfo, nullptr, &Handle);
    if (Result != VK_SUCCESS)
    {
        std::cout << "vkCreateWaylandSurfaceKHR failed " << Result << std::endl;
        throw std::runtime_error("Failed to create Wayland Vulkan surface!");
    }
}
#endif

#if RHI_USE_ANDROID_KHR
VulkanSurface::VulkanSurface(VulkanInstance* InInstance, struct ANativeWindow* Win)
: Instance(InInstance)
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

#if RHI_USE_DirectFB_EXT
VulkanSurface::VulkanSurface(VulkanInstance* InInstance, DirectFB* dfb, IDirectFBSurface* surface)
: Instance(InInstance)
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

#if RHI_USE_IOS_MVK
VulkanSurface::VulkanSurface(VulkanInstance* InInstance, const void* pView)
: Instance(InInstance)
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

#if RHI_USE_MacOS_MVK
VulkanSurface::VulkanSurface(VulkanInstance* InInstance, const void* pView)
: Instance(InInstance)
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

#if RHI_USE_Metal_EXT
VulkanSurface::VulkanSurface(VulkanInstance* InInstance, const CAMetalLayer* Layer)
: Instance(InInstance)
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

#if RHI_USE_QNX
VulkanSurface::VulkanSurface(VulkanInstance* InInstance, struct _screen_context* context, struct _screen_window* window)
: Instance(InInstance)
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

#if RHI_USE_VI_NN
VulkanSurface::VulkanSurface(VulkanInstance* InInstance, void* window)
: Instance(InInstance)
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

#if RHI_USE_FUCHSIA
VulkanSurface::VulkanSurface(VulkanInstance* InInstance, zx_handle_t imagePipeHandle)
: Instance(InInstance)
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

#if RHI_USE_GGP
VulkanSurface::VulkanSurface(VulkanInstance* InInstance, GgpStreamDescriptor StreamDescriptor)
: Instance(InInstance)
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

#if RHI_USE_OHOS
VulkanSurface::VulkanSurface(VulkanInstance* InInstance, OHNativeWindow* window)
: Instance(InInstance)
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

VkPresentModeKHR VulkanSurface::GetPresentMode() const
{
    return ToVkPresentMode(GetRHIPresentMode());
}

void VulkanSurface::Query(VulkanPhysicalDevice& PhysicalDevice)
{
    /*
        typedef struct VkSurfaceCapabilitiesKHR {
            uint32_t                         minImageCount;
            uint32_t                         maxImageCount;
            VkExtent2D                       currentExtent;
            VkExtent2D                       minImageExtent;
            VkExtent2D                       maxImageExtent;
            uint32_t                         maxImageArrayLayers;
            VkSurfaceTransformFlagsKHR       supportedTransforms;
            VkSurfaceTransformFlagBitsKHR    currentTransform;
            VkCompositeAlphaFlagsKHR         supportedCompositeAlpha;
            VkImageUsageFlags                supportedUsageFlags;
        } VkSurfaceCapabilitiesKHR;
     */
    PhysicalDevice.GetPhysicalDeviceSurfaceCapabilitiesKHR(Handle, &Capabilities);

    /*
     * 获取Surface支持的交换链格式
     */
    std::uint32_t FormatCount;
    PhysicalDevice.GetPhysicalDeviceSurfaceFormatsKHR(Handle, &FormatCount, nullptr);
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
        SetRHIPixelFormat(ToRHIPixelFormat(availableFormat.format));
        if (availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
        {
            SetRHIColorSpace(ToRHIColorSpace(availableFormat.colorSpace));
            break;
        }
        else if (availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
        {
            SetRHIColorSpace(ToRHIColorSpace(availableFormat.colorSpace));
            break;
        }
    }

    /*
     * 获取Surface支持的呈现模式
     */
    uint32_t PresentModeCount;
    PhysicalDevice.GetPhysicalDeviceSurfacePresentModesKHR(Handle, &PresentModeCount, nullptr);
    if (PresentModeCount != 0) 
    {
        PresentModes.resize(PresentModeCount);
        PhysicalDevice.GetPhysicalDeviceSurfacePresentModesKHR(Handle, &PresentModeCount, PresentModes.data());
    }

    /*
     * 获取呈现模式
     */
    for (const auto& availablePresentMode : PresentModes)
    {
        std::cout << "availablePresentMode " << availablePresentMode << std::endl;
        if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
        {
            SetRHIPresentMode(ToRHIPresentMode(availablePresentMode));
            break;
        }

        else if (availablePresentMode == VK_PRESENT_MODE_FIFO_KHR)
        {
            SetRHIPresentMode(ToRHIPresentMode(availablePresentMode));
            break;
        }
        else if (availablePresentMode == VK_PRESENT_MODE_FIFO_RELAXED_KHR)
        {
            SetRHIPresentMode(ToRHIPresentMode(availablePresentMode));
            break;
        }
        else if (availablePresentMode == VK_PRESENT_MODE_IMMEDIATE_KHR)
        {
            SetRHIPresentMode(ToRHIPresentMode(availablePresentMode));
            break;
        }
    }


    /*
     * 获取Surface size
     */
    if ((Capabilities.currentExtent.width  <= (uint32_t)std::numeric_limits<uint32_t>::max()) &&
        (Capabilities.currentExtent.height <= (uint32_t)std::numeric_limits<uint32_t>::max()))
    {
        SetWidth(Capabilities.currentExtent.width);
        SetHeight(Capabilities.currentExtent.height);
        std::cout << "AAA Surface size " << GetWidth() << " " << GetHeight() << std::endl;
    }
}
