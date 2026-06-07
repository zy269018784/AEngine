#pragma once
#include "IWindow.h"

#include <FL/Fl.H>
#include <FL/platform.H>
#include <FL/Fl_Window.H>

#if OS_IS_WINDOWS
    #include <windows.h>
#endif

class FLTKWindow : public IWindow
{
public:
    FLTKWindow(IWindow::GraphicsAPI API, IWindow *Parent = nullptr);
    ~FLTKWindow();
    Fl_Window *GetHandle() const;
public:
    virtual void Run() override final;
public:
#if  OS_IS_LINUX
    virtual xcb_connection_t *GetXCBConnection() override final;
    virtual xcb_window_t GetXCBWindow() override final;
    virtual Display* GetXlibDisplay() override final;
    virtual Window GetXlibWindow() override final;
    virtual struct wl_display* GetWLDisplay() override final;
    virtual struct wl_surface* GetWLSurface() override final;
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
    Fl_Window *Handle;
};


