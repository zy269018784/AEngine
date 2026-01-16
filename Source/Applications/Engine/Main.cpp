#include <iostream>
#include <memory>
#include "Engine.h"
#include "Engine2.h"
#include "../Window/GLFWWindow.h"
int RHIExample();
int main(int argc, char **argv)
{
   // return RHIExample();
#ifdef PROJECT_USE_GLFW
    glfwInit();
#endif

#if USE_RHI_VULKAN
	GLFWWindow *Window = new GLFWWindow(IWindow::Vulkan);
#else
    GLFWWindow *Window = new GLFWWindow(IWindow::OpenGL46);
    Window->MakeContextCurrent();
#endif

    Engine *pEngine = new Engine(Window);
    pEngine->Run();

#ifdef PROJECT_USE_GLFW
    glfwTerminate();
#endif
    return 0;
}