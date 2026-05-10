#pragma once
#include "IWindow.h"

#if  PROJECT_USE_XCB
    #define GLFW_EXPOSE_NATIVE_X11
#endif


#include <windows.h>
#if WINDOWS_USE_VULKAN
    #define GLFW_INCLUDE_VULKAN
#endif
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#if OS_IS_WINDOWS

#endif

#if  PROJECT_USE_XCB
#define GLFW_EXPOSE_NATIVE_X11
#endif





class WINDOWEXPORT GLFWWindow : public IWindow
{
public:
    GLFWWindow(IWindow::GraphicsAPI API, IWindow *Parent = nullptr);
    ~GLFWWindow();

    ::GLFWwindow* GetHandle();
    void MakeContextCurrent(void);

    virtual void Run() override final;
public:
    void SetTitle(const char *Title) override final;
    void Resize(int W, int H) override final;
    void SetWidth(int arg) override final;
    void SetHeight(int arg) override final;
    void SetPosition(int X, int Y) override final;
#if  PROJECT_USE_GLFW
#if  PROJECT_USE_XCB
    virtual xcb_connection_t *GetXCBConnection() override final;
    virtual xcb_window_t GetXCBWindow() override final;
#endif
#if  PROJECT_USE_Xlib
    virtual Display* GetXlibDisplay() override final;
    virtual Window GetXlibWindow() override final;
#endif
#endif

//#if OS_IS_WINDOWS
    virtual HWND GetHWND() override final;
    virtual HINSTANCE GetHINSTANCE() override final;
//#endif

private:
    ::GLFWwindow* Handle;
};

