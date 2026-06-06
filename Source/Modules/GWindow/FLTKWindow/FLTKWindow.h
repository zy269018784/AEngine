#pragma once
#include "IWindow.h"

#include <FL/Fl.H>
#include <FL/platform.H>
#include <FL/Fl_Window.H>

#if OS_IS_WINDOWS
    #include <windows.h>
#endif

class FLTKWindow : public IWindow {
public:
    FLTKWindow();
    ~FLTKWindow();
    virtual void Run() override final;
public:
    void SetTitle(const char *Title) override final;
    void Resize(int W, int H) override final;
    void SetWidth(int arg) override final;
    void SetHeight(int arg) override final;
    void SetPosition(int X, int Y) override final;

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
private:
    Fl_Window *Handle;
};


