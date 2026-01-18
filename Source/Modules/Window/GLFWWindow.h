#pragma once
#include "IWindow.h"

#ifdef PROJECT_USE_XCB
    #define GLFW_EXPOSE_NATIVE_X11
#endif

#ifdef PROJECT_USE_GLFW
    #include <GLFW/glfw3.h>
#endif

#ifdef OS_IS_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#endif

#ifdef PROJECT_USE_XCB
#define GLFW_EXPOSE_NATIVE_X11
#endif

#include <GLFW/glfw3native.h>


class GLFWWindow : public IWindow
{
public:
    GLFWWindow(IWindow::GraphicsAPI API, IWindow *Parent = nullptr);
    ~GLFWWindow();
#ifdef PROJECT_USE_GLFW
    GLFWwindow* GetHandle();
    void MakeContextCurrent(void);
#endif
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
private:
#ifdef PROJECT_USE_GLFW
    GLFWwindow* Handle;
#endif
};

