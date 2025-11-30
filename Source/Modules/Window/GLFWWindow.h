#pragma once
#include "IWindow.h"

#ifdef PROJECT_USE_X11
    #define GLFW_EXPOSE_NATIVE_X11
#endif

#ifdef PROJECT_USE_GLFW
    #include <GLFW/glfw3.h>
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
#ifdef PROJECT_USE_X11
    xcb_connection_t *GetXCBConnection() override final;
    xcb_window_t GetWindow() override final;
#endif
#endif
private:
#ifdef PROJECT_USE_GLFW
    GLFWwindow* Handle;
#endif
};

