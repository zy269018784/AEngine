#pragma once
#include "IWindow.h"
#ifdef PROJECT_USE_X11
#include <xcb/xcb.h>
#include <X11/Xlib-xcb.h>
#include <X11/Xutil.h>
#endif
class X11Window : public IWindow
{
public:
    X11Window(IWindow *Parent = nullptr);
    ~X11Window();
    virtual void Run() override final;
public:
    void SetTitle(const char *Title) override final;
    void Resize(int W, int H) override final;
    void SetWidth(int arg) override final;
    void SetHeight(int arg) override final;
    void SetPosition(int X, int Y) override final;
#ifdef PROJECT_USE_X11
    xcb_connection_t *GetXCBConnection() override final;
    xcb_window_t GetWindow() override final;
#endif
private:
public:
#ifdef PROJECT_USE_X11
    Display *X11Display;
    Window  Handle;
    int Screen;
#endif
};
