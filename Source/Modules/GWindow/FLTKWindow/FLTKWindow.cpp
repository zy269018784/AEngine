#include "GWindow/FLTKWindow/FLTKWindow.h"

FLTKWindow::FLTKWindow(IWindow::GraphicsAPI API, IWindow *Parent)
    : IWindow(Parent)
{
    Handle = new Fl_Window(800, 600, "FLTKWindow");
    /*
     * 设置标题
     */
    SetTitle("FLTKWindow");
    /*
     * 设置几何
     */
    SetGeometry(0, 0, 800, 600);
    /*
     * 显示
     */
    Show();
}

FLTKWindow::~FLTKWindow()
{
   delete Handle;
}

Fl_Window *FLTKWindow::GetHandle() const
{
    return Handle;
}

void FLTKWindow::Run()
{
    Fl::run();
}

#if OS_IS_WINDOWS
HWND FLTKWindow::GetHWND()
{
    return fl_xid(Handle);
}

HINSTANCE FLTKWindow::GetHINSTANCE()
{
    HWND hwnd = GetHWND();
    if (hwnd)
    {
        return (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);
    }
}
#endif

#if  OS_IS_LINUX
xcb_connection_t *FLTKWindow::GetXCBConnection()
{
    Display* display = GetXlibDisplay();
    if (display)
    {
        return XGetXCBConnection(display);
    }
}

xcb_window_t FLTKWindow::GetXCBWindow()
{
    return GetXlibWindow();
}

Display* FLTKWindow::GetXlibDisplay()
{
    Display *dpy = fl_x11_display();
    if (!dpy) {
        // 处理错误：可能 FLTK 还没有打开显示连接，或者运行在 Wayland 后端下
        fprintf(stderr, "Error: FLTK X11 display not available. Is the program running under X11?\n");
    }
    return dpy;
}

Window FLTKWindow::GetXlibWindow()
{
    return fl_xid(Handle);
}

#endif

void FLTKWindow::SetTitle(const char *Title)
{
    Handle->label(Title);
}

void FLTKWindow::SetGeometry(int X, int Y, int W, int H)
{
    this->X = X;
    this->Y = Y;
    this->Width = W;
    this->Height = H;
    Handle->resize(X, Y, Width, Height);
}

void FLTKWindow::Resize(int W, int H)
{
    this->Width = W;
    this->Height = H;
    Handle->resize(X, Y, Width, Height);
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

void FLTKWindow::Show()
{
    Handle->show();
}

void FLTKWindow::SetVisible(bool Visible)
{
    if (Visible)
        Handle->show();
    else
        Handle->hide();
}





