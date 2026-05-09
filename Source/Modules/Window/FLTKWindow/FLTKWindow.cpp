#include "../FLTKWindow.h"

FLTKWindow::FLTKWindow()
{
#if  PROJECT_USE_FTLK
    Handle = new Fl_Window(400, 300, "FLTK Input Example");
    //Handle->end();
#endif
}

FLTKWindow::~FLTKWindow() {
#if  PROJECT_USE_FTLK
   delete Handle;
#endif
}



void FLTKWindow::Run()
{
    
}

void FLTKWindow::SetTitle(const char *Title)
{

}

void FLTKWindow::Resize(int W, int H)
{

}

void FLTKWindow::SetWidth(int arg)
{

}

void FLTKWindow::SetHeight(int arg)
{
}

void FLTKWindow::SetPosition(int X, int Y)
{

}

#if OS_IS_WINDOWS
HWND FLTKWindow::GetHWND()
{
    return 0;
}

HINSTANCE FLTKWindow::GetHINSTANCE()
{
    return 0;
}
#endif

#if  PROJECT_USE_GLFW

#if  PROJECT_USE_XCB
xcb_connection_t *FLTKWindow::GetXCBConnection()
{
    Display* Display = glfwGetX11Display();
    return XGetXCBConnection(Display);
}

xcb_window_t FLTKWindow::GetXCBWindow()
{
    return glfwGetX11Window(Handle);
}
#endif

#if  PROJECT_USE_Xlib
Display* FLTKWindow::GetXlibDisplay()
{
    return glfwGetX11Display();
}

Window FLTKWindow::GetXlibWindow()
{
    return glfwGetX11Window(Handle);
}

#endif

#endif






