#pragma once
#include "IWindow.h"
#ifdef PROJECT_USE_SFML
#include <SFML/Graphics.hpp>
#endif
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
private:
#ifdef PROJECT_USE_SFML
    sf::RenderWindow *Handle;
#endif
};

