#include "GLFWWindow.h"
#ifdef PROJECT_USE_X11
#include <xcb/xcb.h>
#include <X11/Xlib-xcb.h>
#include <X11/Xutil.h>
#endif


GLFWWindow::GLFWWindow(GraphicsAPI API, IWindow *Parent)
    : IWindow(Parent)
{
#ifdef PROJECT_USE_GLFW
    switch (API)
    {
        case OpenGL33:
            glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            break;
        case OpenGL46:
            glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            break;
        case ES20:
            glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            break;
        case ES31:
            glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            break;
        case ES32:
            glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            break;
        case Vulkan:
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
            break;
        case D3D9:
        case D3D10:
        case D3D11:
        case D3D12:
        case Metal:
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
            break;
        default:
            break;
    }

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

#ifdef PROJECT_USE_GLFW
GLFWwindow* GLFWWindow::GetHandle()
{
    return Handle;
}

void GLFWWindow::MakeContextCurrent(void)
{
    glfwMakeContextCurrent(Handle);
}
#endif

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

#ifdef PROJECT_USE_X11
xcb_connection_t *GLFWWindow::GetXCBConnection()
{
#ifdef PROJECT_USE_X11
    Display* Display = glfwGetX11Display();
    return XGetXCBConnection(Display);
#else
    return nullptr;
#endif
}

xcb_window_t GLFWWindow::GetWindow()
{
#ifdef PROJECT_USE_X11
    return glfwGetX11Window(Handle);
#else
    return 0;
#endif
}
#endif