#pragma once
#include "IWindow.h"

#if WINDOWS_USE_VULKAN
    #define GLFW_INCLUDE_VULKAN
#endif
#if OS_IS_LINUX
#define GLFW_INCLUDE_ES32
#endif
#include <glfw/glfw3.h>

#if OS_IS_WINDOWS
    #define GLFW_EXPOSE_NATIVE_WIN32
#endif
#if OS_IS_LINUX
    #define GLFW_EXPOSE_NATIVE_X11
#endif
#include <glfw/glfw3native.h>




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
#if  OS_IS_LINUX
    virtual xcb_connection_t *GetXCBConnection() override final;
    virtual xcb_window_t GetXCBWindow() override final;
    virtual Display* GetXlibDisplay() override final;
    virtual Window GetXlibWindow() override final;
#endif
#if OS_IS_WINDOWS
    virtual HWND GetHWND() override final;
    virtual HINSTANCE GetHINSTANCE() override final;
#endif

private:
    ::GLFWwindow* Handle;
};

