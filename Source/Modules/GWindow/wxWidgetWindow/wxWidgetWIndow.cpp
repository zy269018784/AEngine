#include "GWindow/wxWidgetWindow/wxWidgetWIndow.h"

wxWidgetWIndow::wxWidgetWIndow(IWindow::GraphicsAPI API, IWindow *Parent)
    : IWindow(Parent)
{
    Handle = new wxFrame(nullptr, wxID_ANY, "Hello World");
    /*
     * 设置标题
     */
    SetTitle("wxWidgetWIndow");
    /*
     * 设置几何
     */
    SetGeometry(0, 0, 800, 600);
    /*
     * 显示
     */
    Show();
}

wxWidgetWIndow::~wxWidgetWIndow()
{
   delete Handle;
}

wxFrame *wxWidgetWIndow::GetHandle() const
{
    return Handle;
}

void wxWidgetWIndow::Run()
{

}

#if OS_IS_WINDOWS
HWND wxWidgetWIndow::GetHWND()
{
    return fl_xid(Handle);
}

HINSTANCE wxWidgetWIndow::GetHINSTANCE()
{
    HWND hwnd = GetHWND();
    if (hwnd)
    {
        return (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);
    }
}
#endif

#if  OS_IS_LINUX
xcb_connection_t *wxWidgetWIndow::GetXCBConnection()
{
    return nullptr;
}

xcb_window_t wxWidgetWIndow::GetXCBWindow()
{
    return 0;
}

Display* wxWidgetWIndow::GetXlibDisplay()
{
    return nullptr;
}

Window wxWidgetWIndow::GetXlibWindow()
{
    return 0;
}

#endif

void wxWidgetWIndow::SetTitle(const char *Title)
{

}

void wxWidgetWIndow::SetGeometry(int X, int Y, int W, int H)
{
    this->X = X;
    this->Y = Y;
    this->Width = W;
    this->Height = H;

}

void wxWidgetWIndow::Resize(int W, int H)
{
    this->Width = W;
    this->Height = H;

}

void wxWidgetWIndow::SetWidth(int arg)
{

}

void wxWidgetWIndow::SetHeight(int arg)
{
}

void wxWidgetWIndow::SetPosition(int X, int Y)
{

}

void wxWidgetWIndow::Show()
{

}

void wxWidgetWIndow::SetVisible(bool Visible)
{

}





