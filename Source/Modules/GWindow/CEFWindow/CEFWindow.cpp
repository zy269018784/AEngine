#include "CEFWindow.h"

CEFWindow::CEFWindow(IWindow::GraphicsAPI API, IWindow *Parent)
    : IWindow(Parent)
{

    /*
     * 设置标题
     */
    SetTitle("CEFWindow");
    /*
     * 设置几何
     */
    SetGeometry(0, 0, 800, 600);
    /*
     * 显示
     */
    Show();
}

CEFWindow::~CEFWindow()
{

}


::CEFWindow* CEFWindow::GetHandle()
{
    return nullptr;
}

#if OS_IS_WINDOWS
HWND CEFWindow::GetHWND()
{

}

HINSTANCE CEFWindow::GetHINSTANCE()
{

}
#endif

#if  OS_IS_LINUX
xcb_connection_t *CEFWindow::GetXCBConnection()
{
    return nullptr;
}

xcb_window_t CEFWindow::GetXCBWindow()
{
    return 0;
}

Display* CEFWindow::GetXlibDisplay()
{
    return nullptr;
}

Window CEFWindow::GetXlibWindow()
{
    return 0;
}

#endif


void CEFWindow::MakeContextCurrent(void)
{

}


void CEFWindow::Run()
{

}

void CEFWindow::SetTitle(const char *Title)
{

}

void CEFWindow::SetGeometry(int X, int Y, int W, int H)
{
    SetPosition(X, Y);
    Resize(W, H);
}

void CEFWindow::Resize(int W, int H)
{
    Width  = W;
    Height = H;
}

void CEFWindow::SetWidth(int arg)
{
    Width = arg;
}

void CEFWindow::SetHeight(int arg)
{
    Height = arg;
}

void CEFWindow::SetPosition(int X, int Y)
{
    this->X = X;
    this->Y = Y;
}

void CEFWindow::Show()
{
}

void CEFWindow::SetVisible(bool Visible)
{

}



