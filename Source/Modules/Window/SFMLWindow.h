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
#ifdef PROJECT_USE_X11
    xcb_connection_t *GetXCBConnection() override final;
    xcb_window_t GetWindow() override final;
#endif
private:
#ifdef PROJECT_USE_SFML
    sf::RenderWindow *Handle;
#endif
};

