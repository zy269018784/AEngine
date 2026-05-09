#include "MFCWindow.h"

MFCWindow::MFCWindow(IWindow *Parent)
    : IWindow(Parent)
{
#ifdef PROJECT_USE_MFC
    //Handle = new QWindow(dynamic_cast<MFCWindow *>(Parent)->GetHandle());

#endif
}

MFCWindow::~MFCWindow()
{

}

void MFCWindow::Run()
{
#ifdef PROJECT_USE_MFC

#endif
}

#ifdef PROJECT_USE_MFC

#endif

void MFCWindow::SetTitle(const char *Title)
{
#ifdef PROJECT_USE_MFC

#endif
}

void MFCWindow::Resize(int W, int H)
{
    Width  = W;
    Height = H;
#ifdef PROJECT_USE_MFC

#endif
}

void MFCWindow::SetWidth(int arg)
{
    Width = arg;
#ifdef PROJECT_USE_MFC

#endif
}

void MFCWindow::SetHeight(int arg)
{
    Height = arg;
#ifdef PROJECT_USE_MFC

#endif
}

void MFCWindow::SetPosition(int X, int Y)
{
    this->X = X;
    this->Y = Y;
#ifdef PROJECT_USE_MFC

#endif
}

#ifdef OS_IS_WINDOWS
HWND MFCWindow::GetHWND()
{
    return {};
}

HINSTANCE MFCWindow::GetHINSTANCE()
{
    return {};
}
#endif

#ifdef PROJECT_USE_XCB
xcb_connection_t *MFCWindow::GetXCBConnection()
{
    return nullptr;
}

xcb_window_t MFCWindow::GetXCBWindow()
{
    return 0;
}
#endif
#ifdef PROJECT_USE_Xlib
Display* MFCWindow::GetXlibDisplay()
{
    return nullptr;
}

Window MFCWindow::GetXlibWindow()
{
    return 0;
}
#endif