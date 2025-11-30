#include "X11Window.h"
#include <iostream>

X11Window::X11Window(IWindow *Parent)
    : IWindow(Parent)
{
#ifdef PROJECT_USE_X11
     X11Display = XOpenDisplay(NULL);

     Screen = DefaultScreen(X11Display);
     Handle = XCreateSimpleWindow(X11Display,
                            RootWindow(X11Display, Screen),
                            0, 0,  // x, y position
                            400, 300,  // width, height
                            2,         // border width
                            BlackPixel(X11Display, Screen),
                            WhitePixel(X11Display, Screen));
    XStoreName(X11Display, Handle, "X11 Hello World");
    XSelectInput(X11Display, Handle, ExposureMask | KeyPressMask);
    XMapWindow(X11Display, Handle);
#endif
}

X11Window::~X11Window()
{
#ifdef PROJECT_USE_X11
    XDestroyWindow(X11Display, Handle);
    XCloseDisplay(X11Display);
#endif
}

void X11Window::Run()
{
#ifdef PROJECT_USE_X11
    XEvent event;
    while (1)
    {
        XNextEvent(X11Display, &event);
        if (event.type == ClientMessage) {
            break;  // Exit on any key press
        }
    }
#endif
}

void X11Window::SetTitle(const char *Title)
{
#ifdef PROJECT_USE_X11
    XTextProperty WindowTitle;
    XStringListToTextProperty((char **)&Title, 1, &WindowTitle);
    XSetWMName(X11Display, Handle, &WindowTitle);
#endif
}

void X11Window::Resize(int W, int H)
{
#ifdef PROJECT_USE_X11
    Width  = W;
    Height = H;
    //XResizeWindow(X11Display, Handle, Width, Height);
    XWindowChanges changes;
    changes.width = Width;
    changes.height = Height;
    XConfigureWindow(X11Display, Handle, CWWidth | CWHeight, &changes);
    XMapWindow(X11Display, Handle);
    XFlush(X11Display);
#endif
}

void X11Window::SetWidth(int arg)
{
#ifdef PROJECT_USE_X11
    Width  = arg;
    //XResizeWindow(X11Display, Handle, Width, Height);

    XWindowChanges changes;
    changes.width = Width;
    XConfigureWindow(X11Display, Handle, CWWidth, &changes);
    XMapWindow(X11Display, Handle);
    XFlush(X11Display);
#endif
}

void X11Window::SetHeight(int arg)
{
#ifdef PROJECT_USE_X11
    Height = arg;
    //XResizeWindow(X11Display, Handle, Width, Height);
    XWindowChanges changes;
    changes.height = Height;
    XConfigureWindow(X11Display, Handle, CWHeight, &changes);
    XMapWindow(X11Display, Handle);
    XFlush(X11Display);
#endif
}

void X11Window::SetPosition(int X, int Y)
{
#ifdef PROJECT_USE_X11
    this->X = X;
    this->Y = Y;
    //XMoveWindow(X11Display, Handle, this->X, this->Y);
    XWindowChanges changes;
    changes.x = this->X;
    changes.y = this->Y;
    XConfigureWindow(X11Display, Handle, CWX | CWY, &changes);
    XMapWindow(X11Display, Handle);
    XFlush(X11Display);
#endif
}


#ifdef PROJECT_USE_X11
xcb_connection_t *X11Window::GetXCBConnection()
{
    return xcb_connect(NULL, NULL);;
}

xcb_window_t X11Window::GetWindow()
{
    return Handle;
}
#endif