#pragma once
#ifdef PROJECT_USE_X11
    #include <xcb/xcb.h>
#endif
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
    enum GraphicsAPI {
        OpenGL33,
        OpenGL46,
        ES20,
        ES31,
        ES32,
        Vulkan,
        D3D9,
        D3D10,
        D3D11,
        D3D12,
        Metal
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
#ifdef PROJECT_USE_X11
    virtual xcb_connection_t *GetXCBConnection() =0;
    virtual xcb_window_t GetWindow() =0;
#endif
protected:
    IWindow  *Parent;
    int Width;
    int Height;
    int X;
    int Y;
};
