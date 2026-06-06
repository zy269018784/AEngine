#pragma once


#include "IWindow.h"

class WINDOWEXPORT CEFWindow : public IWindow
{
public:
    CEFWindow(IWindow::GraphicsAPI API, IWindow *Parent = nullptr);
    ~CEFWindow();

    ::CEFWindow* GetHandle();
    void MakeContextCurrent(void);

    virtual void Run() override final;
public:
    void SetTitle(const char *Title) override final;
    void SetGeometry(int X, int Y, int W, int H) override final;
    void Resize(int W, int H) override final;
    void SetWidth(int arg) override final;
    void SetHeight(int arg) override final;
    void SetPosition(int X, int Y) override final;
    void Show() override final;
    void SetVisible(bool Visible) override final;
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

};

