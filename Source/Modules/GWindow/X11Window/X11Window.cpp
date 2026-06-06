#include "X11Window.h"
#include <iostream>

X11Window::X11Window(IWindow::GraphicsAPI API, IWindow *Parent)
    : IWindow(Parent)
{

     X11Display = XOpenDisplay(NULL);

     Screen = DefaultScreen(X11Display);
     Handle = XCreateSimpleWindow(X11Display,
                            RootWindow(X11Display, Screen),
                            0, 0,  // x, y position
                            400, 300,  // width, height
                            2,         // border width
                            BlackPixel(X11Display, Screen),
                            WhitePixel(X11Display, Screen));
    XCBHandle = Handle;
    XStoreName(X11Display, Handle, "X11 Hello World");
    XSelectInput(X11Display, Handle, ExposureMask | KeyPressMask);
    XMapWindow(X11Display, Handle);
}

X11Window::~X11Window()
{
    XDestroyWindow(X11Display, Handle);
    XCloseDisplay(X11Display);
}

void X11Window::Run()
{
    XEvent event;
    while (1)
    {
        XNextEvent(X11Display, &event);
        if (event.type == ClientMessage) {
            break;  // Exit on any key press
        }
    }
}

#if OS_IS_WINDOWS
HWND X11Window::GetHWND()
{
    return {};
}

HINSTANCE X11Window::GetHINSTANCE()
{
    return {};
}
#endif

#if  OS_IS_LINUX
xcb_connection_t *X11Window::GetXCBConnection()
{
    return XGetXCBConnection(X11Display);
}

xcb_window_t X11Window::GetXCBWindow()
{
    return XCBHandle;
}

Display* X11Window::GetXlibDisplay()
{
    return X11Display;
}

Window X11Window::GetXlibWindow()
{
    return Handle;
}
#endif

void X11Window::SetTitle(const char *Title)
{
    XTextProperty WindowTitle;
    XStringListToTextProperty((char **)&Title, 1, &WindowTitle);
    XSetWMName(X11Display, Handle, &WindowTitle);
}

void X11Window::SetGeometry(int X, int Y, int W, int H)
{
    this->X = X;
    this->Y = Y;
    this->Width = W;
    this->Height = H;
    XMoveResizeWindow(X11Display, Handle, X, Y, W, H);
    XFlush(X11Display);
}

void X11Window::Resize(int W, int H)
{
    Width  = W;
    Height = H;
    //XResizeWindow(X11Display, Handle, Width, Height);
    XWindowChanges changes;
    changes.width = Width;
    changes.height = Height;
    XConfigureWindow(X11Display, Handle, CWWidth | CWHeight, &changes);
    XMapWindow(X11Display, Handle);
    XFlush(X11Display);
}

void X11Window::SetWidth(int arg)
{
    Width  = arg;
    //XResizeWindow(X11Display, Handle, Width, Height);

    XWindowChanges changes;
    changes.width = Width;
    XConfigureWindow(X11Display, Handle, CWWidth, &changes);
    XMapWindow(X11Display, Handle);
    XFlush(X11Display);
}

void X11Window::SetHeight(int arg)
{
    Height = arg;
    //XResizeWindow(X11Display, Handle, Width, Height);
    XWindowChanges changes;
    changes.height = Height;
    XConfigureWindow(X11Display, Handle, CWHeight, &changes);
    XMapWindow(X11Display, Handle);
    XFlush(X11Display);
}

void X11Window::SetPosition(int X, int Y)
{
    this->X = X;
    this->Y = Y;
    //XMoveWindow(X11Display, Handle, this->X, this->Y);
    XWindowChanges changes;
    changes.x = this->X;
    changes.y = this->Y;
    XConfigureWindow(X11Display, Handle, CWX | CWY, &changes);
    XMapWindow(X11Display, Handle);
    XFlush(X11Display);
}


void X11Window::Show()
{
    XMapWindow(X11Display, Handle);
    XFlush(X11Display);
}

void X11Window::SetVisible(bool Visible)
{
    if (Visible)
        XMapWindow(X11Display, Handle);
    else
        XUnmapWindow(X11Display, Handle);
}
