#pragma once
#include "IWindow.h"
#ifdef PROJECT_USE_GLFW
#include <GLFW/glfw3.h>
#endif


class GLFWWindow : public IWindow
{
public:
    GLFWWindow(IWindow *Parent = nullptr);
    ~GLFWWindow();
    virtual void Run() override final;
public:
    void SetTitle(const char *Title) override final;
    void Resize(int W, int H) override final;
    void SetWidth(int arg) override final;
    void SetHeight(int arg) override final;
    void SetPosition(int X, int Y) override final;
private:
#ifdef PROJECT_USE_GLFW
    GLFWwindow* Handle;
#endif
};

