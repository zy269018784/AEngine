#pragma once
#include "IWindow.h"

#include <xcb/xcb.h>
#include <X11/Xlib-xcb.h>
#include <X11/Xutil.h>

class X11Window : public IWindow
{
public:
    X11Window(IWindow::GraphicsAPI API, IWindow *Parent = nullptr);
    ~X11Window();
public:
    virtual void Run() override final;
public:
#if  OS_IS_LINUX
    virtual xcb_connection_t *GetXCBConnection() override final;
    virtual xcb_window_t GetXCBWindow() override final;
    virtual Display* GetXlibDisplay() override final;
    virtual Window GetXlibWindow() override final;
#endif
#if OS_IS_WINDOWS
    virtual HWND GetHWND() override final;
    virtual HINSTANCE GetHINSTANCE() override final;
#endif
    void SetTitle(const char *Title) override final;
    void SetGeometry(int X, int Y, int W, int H) override final;
    void Resize(int W, int H) override final;
    void SetWidth(int arg) override final;
    void SetHeight(int arg) override final;
    void SetPosition(int X, int Y) override final;
    void Show() override final;
    void SetVisible(bool Visible) override final;
private:
    Display *X11Display = nullptr;
    Window Handle;
    xcb_window_t XCBHandle;
    int Screen;
};
