#include "QTWindow.h"

QTWindow::QTWindow(IWindow::GraphicsAPI API, IWindow *Parent)
    : IWindow(Parent)
{
    Handle = new QWidget();
    Handle->setWindowFlags(Handle->windowFlags() & ~Qt::WindowMaximizeButtonHint);
    /*
     * 设置标题
     */
    SetTitle("GLFWWindow");
    /*
     * 设置几何
     */
    SetGeometry(0, 0, 800, 600);
    /*
     * 显示
     */
    Show();
}

QTWindow::~QTWindow()
{

}


#if OS_IS_WINDOWS
HWND QTWindow::GetHWND()
{
    return glfwGetWin32Window(Handle);
}

HINSTANCE QTWindow::GetHINSTANCE()
{

    HWND hwnd = glfwGetWin32Window(Handle);

    HINSTANCE instacne = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);

    return instacne;
}
#endif

#if  OS_IS_LINUX
xcb_connection_t *QTWindow::GetXCBConnection()
{
    return nullptr;
}

xcb_window_t QTWindow::GetXCBWindow()
{
    return 0;
}

Display* QTWindow::GetXlibDisplay()
{
    return nullptr;
}

Window QTWindow::GetXlibWindow()
{
    return 0;
}

struct wl_display* QTWindow::GetWLDisplay()
{
    return nullptr;
}

struct wl_surface* QTWindow::GetWLSurface()
{
    return nullptr;
}

#endif

void QTWindow::Run()
{
    Handle->show();
}


QWidget *QTWindow::GetHandle()
{
    return Handle;
}


void QTWindow::SetTitle(const char *Title)
{

}

void QTWindow::SetGeometry(int X, int Y, int W, int H)
{
    Handle->setGeometry(X, Y, W, H);
    Handle->resize(W, H);
    Handle->move(X, Y);
}

void QTWindow::Resize(int W, int H)
{
    Width  = W;
    Height = H;
    Handle->resize(W, H);
}

void QTWindow::SetWidth(int arg)
{
    Width = arg;

}

void QTWindow::SetHeight(int arg)
{
    Height = arg;

}

void QTWindow::SetPosition(int X, int Y)
{
    this->X = X;
    this->Y = Y;

}
void QTWindow::Show()
{
    Handle->show();
}

void QTWindow::SetVisible(bool Visible)
{
    Handle->setVisible(Visible);
}
