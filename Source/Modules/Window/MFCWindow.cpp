#include "MFCWindow.h"

MFCWindow::MFCWindow(IWindow *Parent)
    : IWindow(Parent)
{
#ifdef PROJECT_USE_MFC
    //Handle = new QWindow(dynamic_cast<MFCWindow *>(Parent)->GetHandle());
    Handle = new QWindow();
#endif
}

MFCWindow::~MFCWindow()
{

}

void MFCWindow::Run()
{
#ifdef PROJECT_USE_MFC
    Handle->show();
#endif
}

#ifdef PROJECT_USE_MFC
QWindow *MFCWindow::GetHandle()
{
    return Handle;
}
#endif

void MFCWindow::SetTitle(const char *Title)
{
#ifdef PROJECT_USE_MFC
    Handle->setTitle(Title);
#endif
}

void MFCWindow::Resize(int W, int H)
{
    Width  = W;
    Height = H;
#ifdef PROJECT_USE_MFC
    Handle->resize(W, H);
#endif
}

void MFCWindow::SetWidth(int arg)
{
    Width = arg;
#ifdef PROJECT_USE_MFC
    Handle->setWidth(Width);
#endif
}

void MFCWindow::SetHeight(int arg)
{
    Height = arg;
#ifdef PROJECT_USE_MFC
    Handle->setHeight(Height);
#endif
}

void MFCWindow::SetPosition(int X, int Y)
{
    this->X = X;
    this->Y = Y;
#ifdef PROJECT_USE_MFC
    Handle->setPosition(this->X, this->Y);
#endif
}

#ifdef PROJECT_USE_X11
xcb_connection_t *MFCWindow::GetXCBConnection()
{
    return nullptr;
}

xcb_window_t MFCWindow::GetWindow()
{
    return 0;
}
#endif