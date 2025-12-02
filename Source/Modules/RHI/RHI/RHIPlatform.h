#pragma once
#ifdef OS_IS_WINDOWS
	#define RHI_USE_WIN32_KHR	1
#endif
#ifdef OS_IS_ANDROID
	#define RHI_USE_PLATFORM_ANDROID_KHR		0
#endif
#ifdef OS_IS_LINUX
	#define RHI_USE_PLATFORM_WAYLAND_KHR	0
#endif
#ifdef PROJECT_USE_X11
	#define RHI_USE_X11			1
#endif

#ifdef RHI_USE_WIN32_KHR
#include <windows.h>               // 主头文件
#include <windef.h>                // 基本类型定义
#include <minwindef.h>
#endif

#ifdef RHI_USE_X11
	#include <xcb/xcb.h>
	#include <X11/Xlib-xcb.h>
	#include <X11/Xutil.h>
#endif