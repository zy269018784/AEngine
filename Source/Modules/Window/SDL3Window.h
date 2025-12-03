#pragma once
#include "IWindow.h"
#ifdef PROJECT_USE_SDL3
#include "SDL3/SDL.h"
#include <SDL3/SDL_system.h>
#endif


class SDL3Window : public IWindow
{
public:
    SDL3Window(IWindow::GraphicsAPI API, IWindow *Parent = nullptr);
    ~SDL3Window();
#ifdef PROJECT_USE_SDL3
    SDL_Window* GetHandle();
    void MakeContextCurrent(void);
#endif
    virtual void Run() override final;
public:
    void SetTitle(const char *Title) override final;
    void Resize(int W, int H) override final;
    void SetWidth(int arg) override final;
    void SetHeight(int arg) override final;
    void SetPosition(int X, int Y) override final;
#ifdef PROJECT_USE_XCB
    virtual xcb_connection_t *GetXCBConnection() override final;
    virtual xcb_window_t GetXCBWindow() override final;
#endif
#ifdef PROJECT_USE_Xlib
    virtual Display* GetXlibDisplay() override final;
    virtual Window GetXlibWindow() override final;
#endif
private:
#ifdef PROJECT_USE_SDL3
    SDL_Window* Handle;
#endif

#ifdef PROJECT_USE_XCB
    xcb_window_t X11Window;
    xcb_connection_t* X11Connection;
#endif
};

