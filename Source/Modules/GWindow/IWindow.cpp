#include "IWindow.h"
#include "GLFWWindow/GLFWWindow.h"
#include <iostream>
IWindow::IWindow(IWindow *Parent)
    : Parent(Parent), X(0), Y(0), Width(800), Height(600)
{


}

IWindow::~IWindow()
{

}

IWindow * CreateGLFWWindow(IWindow::GraphicsAPI API) {

    std::cout << "Creating GLFW window 11111111111111" << std::endl;
    IWindow *IWin = new GLFWWindow(API, nullptr);
    std::cout << "Creating GLFW window 22222222222222" << std::endl;
    return IWin;
}