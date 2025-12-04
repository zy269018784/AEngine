#include "QTWindow.h"

QTWindow::QTWindow(IWindow *Parent)
    : IWindow(Parent)
{
#ifdef PROJECT_USE_QT
    //Handle = new QWindow(dynamic_cast<QTWindow *>(Parent)->GetHandle());
    Handle = new QWindow();
#endif
}

QTWindow::~QTWindow()
{

}

void QTWindow::Run()
{
#ifdef PROJECT_USE_QT
    Handle->show();
#endif
}

#ifdef PROJECT_USE_QT
QWindow *QTWindow::GetHandle()
{
    return Handle;
}
#endif

void QTWindow::SetTitle(const char *Title)
{
#ifdef PROJECT_USE_QT
    Handle->setTitle(Title);
#endif
}

void QTWindow::Resize(int W, int H)
{
    Width  = W;
    Height = H;
#ifdef PROJECT_USE_QT
    Handle->resize(W, H);
#endif
}

void QTWindow::SetWidth(int arg)
{
    Width = arg;
#ifdef PROJECT_USE_QT
    Handle->setWidth(Width);
#endif
}

void QTWindow::SetHeight(int arg)
{
    Height = arg;
#ifdef PROJECT_USE_QT
    Handle->setHeight(Height);
#endif
}

void QTWindow::SetPosition(int X, int Y)
{
    this->X = X;
    this->Y = Y;
#ifdef PROJECT_USE_QT
    Handle->setPosition(this->X, this->Y);
#endif
}


#ifdef PROJECT_USE_XCB
xcb_connection_t *QTWindow::GetXCBConnection()
{
    return nullptr;
}

xcb_window_t QTWindow::GetXCBWindow()
{
    return 0;
}
#endif
#ifdef PROJECT_USE_Xlib
Display* QTWindow::GetXlibDisplay()
{
    return nullptr;
}

Window QTWindow::GetXlibWindow()
{
    return 0;
}

#endif