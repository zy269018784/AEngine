#pragma once
#include "RHI/RHIPlatform.h"
#include "RHI/RHIObjects/Surface/RHISurface.h"
#include "VulkanRHI/Vulkan.h"
#include <vector>

class VulkanPhysicalDevice;
class VulkanInstance;
class VulkanSurface : public RHISurface
{
public:
	VulkanSurface();
	VulkanSurface(VulkanInstance* InInstance, VkSurfaceKHR Surface);

#if RHI_USE_WIN32_KHR
	VulkanSurface(VulkanInstance* InInstance, HINSTANCE Hinstance, HWND Hwnd);
#endif

#if RHI_USE_XCB_KHR
	VulkanSurface(VulkanInstance* InInstance, xcb_connection_t* connection, xcb_window_t window);
#endif

#if RHI_USE_Xlib_KHR
	VulkanSurface(VulkanInstance* InInstance, Display* Disp, Window Win);
#endif

#if RHI_USE_WAYLAND_KHR
	VulkanSurface(VulkanInstance* InInstance,   struct wl_display* display, struct wl_surface* surface);
#endif

#if RHI_USE_ANDROID_KHR
	VulkanSurface(VulkanInstance* InInstance, struct ANativeWindow* Win);
#endif

#if RHI_USE_DirectFB_EXT
	VulkanSurface(VulkanInstance* InInstance, DirectFB*  dfb, IDirectFBSurface*  surface);
#endif

#if RHI_USE_IOS_MVK
	VulkanSurface(VulkanInstance* InInstance, const void* pView);
#endif

#if RHI_USE_MacOS_MVK
	VulkanSurface(VulkanInstance* InInstance, const void* pView);
#endif

#if RHI_USE_Metal_EXT
	VulkanSurface(VulkanInstance* InInstance, const CAMetalLayer* Layer);
#endif

#if RHI_USE_QNX
	VulkanSurface(VulkanInstance* InInstance, struct _screen_context* context, struct _screen_window* window);
#endif

#if RHI_USE_VI_NN
	VulkanSurface(VulkanInstance* InInstance, void* window);
#endif

#if RHI_USE_FUCHSIA
	VulkanSurface(VulkanInstance* InInstance, zx_handle_t imagePipeHandle);
#endif

#if RHI_USE_GGP
	VulkanSurface(VulkanInstance* InInstance, GgpStreamDescriptor StreamDescriptor);
#endif

#if RHI_USE_OHOS
	VulkanSurface(VulkanInstance* InInstance, OHNativeWindow* window);
#endif

	~VulkanSurface();
	VkSurfaceKHR GetHandle() const;
	void Query(VulkanPhysicalDevice& PhysicalDevice);
private:
	/*
		Vulkan API Wrapper
	*/
	void DestroySurfaceKHR(const VkAllocationCallbacks* Allocator);
public:
	/*
		句柄
	*/
	VkSurfaceKHR Handle;
	/*
		Vulkan Instance
	*/
	VulkanInstance* Instance = nullptr;
	/*
		能力
	*/
	VkSurfaceCapabilitiesKHR				Capabilities;
	/*
		所有支持的像素格式和色彩空间
	*/
	std::vector<VkSurfaceFormatKHR>			Formats;
	/*
		像素格式和色彩空间
	*/
	VkSurfaceFormatKHR						CurrentFormat;
	/*
		所有Present Mode
	*/
	std::vector<VkPresentModeKHR>			PresentModes;
	/*
		当前Present Mode
	*/
	VkPresentModeKHR						CurrentPresentMode;
	/*
		宽和高
	*/
	VkExtent2D								CurrentExtent;
};