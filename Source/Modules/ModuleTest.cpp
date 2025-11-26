#ifdef PROJECT_USE_QT
#include <QApplication>
#endif

// QT must before x11
#include "Window/QTWindow.h"
#include "Window/SFMLWindow.h"

#include "Window/X11Window.h"
#include "Window/GLFWWindow.h"


#include <iostream>
#include <memory>
#include <stdio.h>
int HelloFLTK() {
    //FLTKWindow Window;
    //return Fl::run();
    return 0;
}

int HelloX11()
{
    std::unique_ptr<IWindow> Window;
    Window.reset(new X11Window());
    Window->SetTitle("X11 Window");
    //Window->SetWidth(960);
    //Window->SetHeight(600);
    Window->Resize(960, 600);
    Window->SetPosition(960, 0);
    Window->Run();
}

int HelloGLFW()
{
#ifdef PROJECT_USE_GLFW
    glfwInit();
#endif
    std::unique_ptr<IWindow> Window;
    Window.reset(new GLFWWindow());
    Window->SetTitle("GLFW Window");
    Window->SetWidth(960);
    Window->SetHeight(600);
    Window->SetPosition(960, 0);
    Window->Run();
#ifdef PROJECT_USE_GLFW
    glfwTerminate();
#endif
}

int HelloSFML()
{
    std::unique_ptr<IWindow> Window;
    Window.reset(new SFMLWindow());
    Window->SetTitle("SFML Window");
    Window->Resize(960, 600);
    //Window->SetWidth(960);
    //Window->SetHeight(600);
    Window->SetPosition(960, 0);
    Window->Run();
}

int HelloQT(int argc, char **argv)
{
#ifdef PROJECT_USE_QT
    QApplication app(argc, argv);
#endif
    std::unique_ptr<IWindow> Window;
    Window.reset(new QTWindow());
    Window->SetTitle("QT Window");
    Window->SetWidth(960);
    Window->SetHeight(600);
    Window->SetPosition(960, 0);
    Window->Run();
#ifdef PROJECT_USE_QT
    return app.exec();
#else
    return 0;
#endif
}

int HelloIWindow() {

    std::unique_ptr<IWindow> Window;
    Window.reset(new X11Window());
    Window->Run();
    return 0;
}

int ModuleTest(int argc, char **argv)
{
#ifdef PROJECT_USE_FTLK
    std::cout << "PROJECT_USE_FTLK" << std::endl;
#endif
    //HelloX11();
    HelloQT(argc, argv);
    //HelloGLFW();
    //HelloSFML();
    return 0;
}