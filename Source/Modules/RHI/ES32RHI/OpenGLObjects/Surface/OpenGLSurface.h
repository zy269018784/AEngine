#pragma once
#include "RHI/RHIObjects/Surface/RHISurface.h"
#if RHI_USE_WIN32_KHR
	#include <windows.h>
#endif
class OpenGLInstance;
class OpenGLSurface : public RHISurface
{
public:
	OpenGLSurface();

#if RHI_USE_WIN32_KHR
	OpenGLSurface(OpenGLInstance* InInstance, HINSTANCE Hinstance, HWND Hwnd);
#endif

#if RHI_USE_XCB_KHR
	OpenGLSurface(OpenGLInstance* InInstance, xcb_connection_t* connection, xcb_window_t window);
#endif

#if RHI_USE_Xlib_KHR
	OpenGLSurface(OpenGLInstance* InInstance, Display* Disp, Window Win);
#endif

#if RHI_USE_WAYLAND_KHR
	OpenGLSurface(OpenGLInstance* InInstance,   struct wl_display* display, struct wl_surface* surface);
#endif

#if RHI_USE_ANDROID_KHR
	OpenGLSurface(OpenGLInstance* InInstance, struct ANativeWindow* Win);
#endif

#if RHI_USE_DirectFB_EXT
	OpenGLSurface(OpenGLInstance* InInstance, DirectFB*  dfb, IDirectFBSurface*  surface);
#endif

#if RHI_USE_IOS_MVK
	OpenGLSurface(OpenGLInstance* InInstance, const void* pView);
#endif

#if RHI_USE_MacOS_MVK
	OpenGLSurface(OpenGLInstance* InInstance, const void* pView);
#endif

#if RHI_USE_Metal_EXT
	OpenGLSurface(OpenGLInstance* InInstance, const CAMetalLayer* Layer);
#endif

#if RHI_USE_QNX
	OpenGLSurface(OpenGLInstance* InInstance, struct _screen_context* context, struct _screen_window* window);
#endif

#if RHI_USE_VI_NN
	OpenGLSurface(OpenGLInstance* InInstance, void* window);
#endif

#if RHI_USE_FUCHSIA
	OpenGLSurface(OpenGLInstance* InInstance, zx_handle_t imagePipeHandle);
#endif

#if RHI_USE_GGP
	OpenGLSurface(OpenGLInstance* InInstance, GgpStreamDescriptor StreamDescriptor);
#endif

#if RHI_USE_OHOS
	OpenGLSurface(OpenGLInstance* InInstance, OHNativeWindow* window);
#endif

	~OpenGLSurface();
private:
	OpenGLInstance *Instance = nullptr;
};