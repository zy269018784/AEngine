#include "../SDL3Window.h"
#include <iostream>

#if  PROJECT_USE_XCB
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
#if  PROJECT_USE_SDL3
    Handle = SDL_CreateWindow("SDL3 Hello World", 800, 600, 0);
    if (!Handle) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }
    SDL_CreateRenderer(Handle, nullptr);

    Uint32 windowID = SDL_GetWindowID(Handle);
#if  PROJECT_USE_XCB
    X11Window = static_cast<xcb_window_t>(windowID);
    X11Connection = xcb_connect(nullptr, nullptr);
#endif

#endif

}

SDL3Window::~SDL3Window()
{
#if  PROJECT_USE_SDL3

#endif

}

#if  PROJECT_USE_SDL3
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
#if  PROJECT_USE_SDL3

#endif
}

void SDL3Window::SetTitle(const char *Title)
{
#if  PROJECT_USE_SDL3

#endif

}

void SDL3Window::Resize(int W, int H)
{
    Width  = W;
    Height = H;
#if  PROJECT_USE_SDL3

#endif

}

void SDL3Window::SetWidth(int arg)
{
    Width = arg;
#if  PROJECT_USE_SDL3

#endif

}

void SDL3Window::SetHeight(int arg)
{
    Height = arg;
#if  PROJECT_USE_SDL3

#endif

}

void SDL3Window::SetPosition(int X, int Y)
{
    this->X = X;
    this->Y = Y;
#if  PROJECT_USE_SDL3

#endif

}

#if OS_IS_WINDOWS
HWND SDL3Window::GetHWND()
{
    return {};
}

HINSTANCE SDL3Window::GetHINSTANCE()
{
    return {};
}
#endif

#if  PROJECT_USE_XCB
xcb_connection_t *SDL3Window::GetXCBConnection()
{
    return X11Connection;
}

xcb_window_t SDL3Window::GetXCBWindow()
{
    return X11Window;
}
#endif
#if  PROJECT_USE_Xlib
Display* SDL3Window::GetXlibDisplay()
{
    return nullptr;
}

Window SDL3Window::GetXlibWindow()
{
    return 0;
}
#endif