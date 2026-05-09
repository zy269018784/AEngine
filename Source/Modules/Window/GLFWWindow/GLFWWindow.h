#pragma once
#include "../IWindow.h"

#ifdef PROJECT_USE_XCB
    #define GLFW_EXPOSE_NATIVE_X11
#endif

#include <windows.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#ifdef OS_IS_WINDOWS

#endif

#ifdef PROJECT_USE_XCB
#define GLFW_EXPOSE_NATIVE_X11
#endif





class GLFWWindow : public IWindow
{
public:
    GLFWWindow(IWindow::GraphicsAPI API, IWindow *Parent = nullptr);
    ~GLFWWindow();

    GLFWwindow* GetHandle();
    void MakeContextCurrent(void);

    virtual void Run() override final;
public:
    void SetTitle(const char *Title) override final;
    void Resize(int W, int H) override final;
    void SetWidth(int arg) override final;
    void SetHeight(int arg) override final;
    void SetPosition(int X, int Y) override final;
#ifdef PROJECT_USE_GLFW
#ifdef PROJECT_USE_XCB
    virtual xcb_connection_t *GetXCBConnection() override final;
    virtual xcb_window_t GetXCBWindow() override final;
#endif
#ifdef PROJECT_USE_Xlib
    virtual Display* GetXlibDisplay() override final;
    virtual Window GetXlibWindow() override final;
#endif
#endif

//#ifdef OS_IS_WINDOWS
    virtual HWND GetHWND() override final;
    virtual HINSTANCE GetHINSTANCE() override final;
//#endif

private:
    GLFWwindow* Handle;
};

