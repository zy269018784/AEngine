#pragma once

#if OS_IS_WINDOWS
	#include <windows.h>               // 主头文件
	#include <windef.h>                // 基本类型定义
	#include <minwindef.h>
#endif

#if  OS_IS_ANDROID

#endif

#if  OS_IS_LINUX
	#include <xcb/xcb.h>
	#include <X11/Xlib-xcb.h>
	#include <X11/Xutil.h>
	#include <X11/Xlib.h>
#endif

