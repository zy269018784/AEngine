#pragma once
#include "IWindow.h"
#include "SDL3/SDL.h"
#include <SDL3/SDL_system.h>
#include <SDL3/SDL_video.h>



class SDL3Window : public IWindow
{
public:
    SDL3Window(IWindow::GraphicsAPI API, IWindow *Parent = nullptr);
    ~SDL3Window();
public:
    SDL_Window* GetHandle();
    void MakeContextCurrent(void);
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
    SDL_Window *Handle = nullptr;
    SDL_Renderer* Renderer = nullptr;
};

