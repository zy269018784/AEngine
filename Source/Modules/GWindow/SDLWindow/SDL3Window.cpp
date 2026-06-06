#include "SDL3Window.h"
#include <iostream>

extern "C"
{
    #include <xcb/xcb.h>
    #include <X11/Xlib-xcb.h>
    #include <X11/Xutil.h>
}

SDL3Window::SDL3Window(GraphicsAPI API, IWindow *Parent)
    : IWindow(Parent)
{
    Handle = SDL_CreateWindow("", 800, 600, SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_RESIZABLE );
    Renderer = SDL_CreateRenderer(Handle, "");
    /*
     * 设置标题
     */
    SetTitle("SDL3Window");
    /*
     * 设置几何
     */
    SetGeometry(0, 0, 800, 600);
    /*
     * 显示
     */
    Show();
}

SDL3Window::~SDL3Window()
{
    SDL_DestroyWindow(Handle);
}


SDL_Window* SDL3Window::GetHandle()
{
    return Handle;
}

void SDL3Window::MakeContextCurrent(void)
{

}

void SDL3Window::Run()
{
   // while (1)  SDL_Delay(10000);
    SDL_Event event;
    bool running = true;
    while (running)
    {
        if (1 == SDL_WaitEvent(&event))
        {
            switch (event.type)
            {
            case SDL_EVENT_QUIT:
                running = false;
                std::cout << "SDL_EVENT_QUIT" << std::endl;
                break;
            }

        }
        SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
        SDL_RenderClear(Renderer);
        SDL_RenderPresent(Renderer);
    }
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

#if  OS_IS_LINUX
xcb_connection_t *SDL3Window::GetXCBConnection()
{
    return nullptr;
}

xcb_window_t SDL3Window::GetXCBWindow()
{
    return 0;
}

Display* SDL3Window::GetXlibDisplay()
{
    return nullptr;
}

Window SDL3Window::GetXlibWindow()
{
    return 0;
}
#endif

void SDL3Window::SetTitle(const char *Title)
{
    SDL_SetWindowTitle(Handle, Title);
}

void SDL3Window::SetGeometry(int X, int Y, int W, int H)
{
    this->X = X;
    this->Y = Y;
    this->Width = W;
    this->Height = H;

    SDL_SetWindowSize(Handle, W, H);
    SDL_SetWindowPosition(Handle, X, Y);
}

void SDL3Window::Resize(int W, int H)
{
    this->Width = W;
    this->Height = H;
    SDL_SetWindowSize(Handle, W, H);
}

void SDL3Window::SetWidth(int arg)
{
    Width = arg;
}

void SDL3Window::SetHeight(int arg)
{
    Height = arg;
}

void SDL3Window::SetPosition(int X, int Y)
{
    this->X = X;
    this->Y = Y;
}

void SDL3Window::Show()
{
    SDL_ShowWindow(Handle);
}

void SDL3Window::SetVisible(bool Visible)
{
    if (Visible)
        SDL_ShowWindow(Handle);
    else
        SDL_HideWindow(Handle);
}

