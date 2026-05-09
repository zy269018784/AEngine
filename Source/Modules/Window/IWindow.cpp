#include "IWindow.h"
#include "GLFWWindow/GLFWWindow.h"
IWindow::IWindow(IWindow *Parent)
    : Parent(Parent), X(0), Y(0), Width(800), Height(600)
{


}

IWindow::~IWindow()
{

}

IWindow * CreateGLFWWindow(IWindow::GraphicsAPI API) {
    return new GLFWWindow(API);
}