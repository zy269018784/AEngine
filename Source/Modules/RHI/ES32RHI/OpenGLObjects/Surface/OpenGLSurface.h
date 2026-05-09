#pragma once
#include "RHI/RHIObjects/Surface/RHISurface.h"

class OpenGLSurface : public RHISurface
{
public:
	OpenGLSurface();

#ifdef RHI_USE_WIN32_KHR
	OpenGLSurface(VulkanInstance* InInstance, HINSTANCE Hinstance, HWND Hwnd);
#endif

#ifdef RHI_USE_XCB_KHR
	OpenGLSurface(VulkanInstance* InInstance, xcb_connection_t* connection, xcb_window_t window);
#endif

#ifdef RHI_USE_Xlib_KHR
	OpenGLSurface(VulkanInstance* InInstance, Display* Disp, Window Win);
#endif

#ifdef RHI_USE_WAYLAND_KHR
	OpenGLSurface(VulkanInstance* InInstance,   struct wl_display* display, struct wl_surface* surface);
#endif

#ifdef RHI_USE_ANDROID_KHR
	OpenGLSurface(VulkanInstance* InInstance, struct ANativeWindow* Win);
#endif

#ifdef RHI_USE_DirectFB_EXT
	OpenGLSurface(VulkanInstance* InInstance, DirectFB*  dfb, IDirectFBSurface*  surface);
#endif

#ifdef RHI_USE_IOS_MVK
	OpenGLSurface(VulkanInstance* InInstance, const void* pView);
#endif

#ifdef RHI_USE_MacOS_MVK
	OpenGLSurface(VulkanInstance* InInstance, const void* pView);
#endif

#ifdef RHI_USE_Metal_EXT
	OpenGLSurface(VulkanInstance* InInstance, const CAMetalLayer* Layer);
#endif

#ifdef RHI_USE_QNX
	OpenGLSurface(VulkanInstance* InInstance, struct _screen_context* context, struct _screen_window* window);
#endif

#ifdef RHI_USE_VI_NN
	OpenGLSurface(VulkanInstance* InInstance, void* window);
#endif

#ifdef RHI_USE_FUCHSIA
	OpenGLSurface(VulkanInstance* InInstance, zx_handle_t imagePipeHandle);
#endif

#ifdef RHI_USE_GGP
	OpenGLSurface(VulkanInstance* InInstance, GgpStreamDescriptor StreamDescriptor);
#endif

#ifdef RHI_USE_OHOS
	OpenGLSurface(VulkanInstance* InInstance, OHNativeWindow* window);
#endif

	~OpenGLSurface();
};