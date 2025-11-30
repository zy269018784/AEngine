#include "SDL3Window.h"
#include <iostream>

#ifdef PROJECT_USE_X11
extern "C"
{
#include <xcb/xcb.h>
#include <X11/Xlib-xcb.h>
#include <X11/Xutil.h>
}
#endif
SDL3Window::SDL3Window(GraphicsAPI API, IWindow *Parent)
    : IWindow(Parent)
{
    Handle = SDL_CreateWindow("SDL3 Hello World", 800, 600, 0);
    if (!Handle) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }
    SDL_CreateRenderer(Handle, nullptr);
#ifdef PROJECT_USE_SDL3
    Uint32 windowID = SDL_GetWindowID(Handle);
    X11Window = static_cast<xcb_window_t>(windowID);
    X11Connection = xcb_connect(nullptr, nullptr);
#endif

}

SDL3Window::~SDL3Window()
{
#ifdef PROJECT_USE_SDL3

#endif

}

#ifdef PROJECT_USE_SDL3
SDL_Window* SDL3Window::GetHandle()
{
    return Handle;
}

void SDL3Window::MakeContextCurrent(void)
{

}
#endif

void SDL3Window::Run()
{
#ifdef PROJECT_USE_SDL3

#endif
}

void SDL3Window::SetTitle(const char *Title)
{
#ifdef PROJECT_USE_SDL3

#endif

}

void SDL3Window::Resize(int W, int H)
{
    Width  = W;
    Height = H;
#ifdef PROJECT_USE_SDL3

#endif

}

void SDL3Window::SetWidth(int arg)
{
    Width = arg;
#ifdef PROJECT_USE_SDL3

#endif

}

void SDL3Window::SetHeight(int arg)
{
    Height = arg;
#ifdef PROJECT_USE_SDL3

#endif

}

void SDL3Window::SetPosition(int X, int Y)
{
    this->X = X;
    this->Y = Y;
#ifdef PROJECT_USE_SDL3

#endif

}

#ifdef PROJECT_USE_X11
xcb_connection_t *SDL3Window::GetXCBConnection()
{
    return X11Connection;
}

xcb_window_t SDL3Window::GetWindow()
{
    return X11Window;
}
#endif