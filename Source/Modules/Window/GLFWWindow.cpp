#include "GLFWWindow.h"

GLFWWindow::GLFWWindow(IWindow *Parent)
    : IWindow(Parent)
{
#ifdef PROJECT_USE_GLFW
    Handle = glfwCreateWindow(800, 600, "aaa", NULL, NULL);
    glfwMakeContextCurrent(Handle);
#endif

}

GLFWWindow::~GLFWWindow()
{
#ifdef PROJECT_USE_GLFW
    glfwDestroyWindow(Handle);
#endif

}

void GLFWWindow::Run()
{
#ifdef PROJECT_USE_GLFW
    while (!glfwWindowShouldClose(Handle)) {
       // glClearColor(1, 1, 1, 1);
       // glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();
    }
#endif
}

void GLFWWindow::SetTitle(const char *Title)
{
#ifdef PROJECT_USE_GLFW
    glfwSetWindowTitle(Handle, Title);
#endif

}

void GLFWWindow::Resize(int W, int H)
{
    Width  = W;
    Height = H;
#ifdef PROJECT_USE_GLFW
    glfwSetWindowSize(Handle, Width, Height);
#endif

}

void GLFWWindow::SetWidth(int arg)
{
    Width = arg;
#ifdef PROJECT_USE_GLFW
    glfwSetWindowSize(Handle, Width, Height);
#endif

}

void GLFWWindow::SetHeight(int arg)
{
    Height = arg;
#ifdef PROJECT_USE_GLFW
    glfwSetWindowSize(Handle, Width, Height);
#endif

}

void GLFWWindow::SetPosition(int X, int Y)
{
    this->X = X;
    this->Y = Y;
#ifdef PROJECT_USE_GLFW
    glfwSetWindowPos(Handle, this->X, this->Y);
#endif

}
