#pragma once
#ifdef PROJECT_USE_SFML
    #include <SFML/Graphics.hpp>
#endif


#include "IWindow.h"


class SFMLWindow : public IWindow
{
public:
    SFMLWindow(IWindow *Parent = nullptr);
    ~SFMLWindow();
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
#ifdef PROJECT_USE_SFML
    sf::RenderWindow *Handle;
#endif
};

