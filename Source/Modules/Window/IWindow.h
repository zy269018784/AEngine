#pragma once
#include "WindowExport.h"
#if  PROJECT_USE_Xlib
   #include <X11/Xlib.h>
#include <X11/Xlib-xcb.h>
#endif

#if  PROJECT_USE_XCB
    #include <xcb/xcb.h>
#endif

#include <windows.h>

class WINDOWEXPORT IWindow
{
public:
    enum class Framework {
        GLFW,
        QT,
        MFC,
        SFML,
        X11,
        FLTK,
        wxWidget,
    };
    enum GraphicsAPI {
        OpenGL33,
        OpenGL46,
        ES20,
        ES31,
        ES32,
        Vulkan,
        D3D9,
        D3D10,
        D3D11,
        D3D12,
        Metal
    };
public:
    IWindow(IWindow *Parent = nullptr);
    virtual ~IWindow();
public:
    virtual void Run() =0;
public:
    virtual void SetTitle(const char *Title) =0;
    virtual void Resize(int W, int H) =0;
    virtual void SetWidth(int arg) =0;
    virtual void SetHeight(int arg) =0;
    virtual void SetPosition(int X, int Y) =0;
#if  PROJECT_USE_XCB
    virtual xcb_connection_t *GetXCBConnection() =0;
    virtual xcb_window_t GetXCBWindow() =0;
#endif
#if  PROJECT_USE_Xlib
    virtual Display* GetXlibDisplay() =0;
    virtual Window GetXlibWindow() =0;
#endif

    virtual HWND GetHWND() =0;
    virtual HINSTANCE GetHINSTANCE() =0;

protected:
    IWindow  *Parent;
    int Width;
    int Height;
    int X;
    int Y;
};

//WINDOWEXPORT IWindow *CreateGLFWWindow(IWindow::GraphicsAPI API);
__declspec(dllexport) IWindow *CreateGLFWWindow(IWindow::GraphicsAPI API);