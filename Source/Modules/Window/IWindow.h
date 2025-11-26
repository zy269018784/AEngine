#pragma once

class IWindow
{
public:
    enum class Framework {
        GLFW,
        QT,
        MFC,
        SFML,
        X11,
        FLTK,
        wxWidget,
    };
public:
    IWindow(IWindow *Parent = nullptr);
    virtual ~IWindow();
public:
    virtual void Run() =0;
public:
    virtual void SetTitle(const char *Title) =0;
    virtual void Resize(int W, int H) =0;
    virtual void SetWidth(int arg) =0;
    virtual void SetHeight(int arg) =0;
    virtual void SetPosition(int X, int Y) =0;
protected:
    IWindow  *Parent;
    int Width;
    int Height;
    int X;
    int Y;
};
