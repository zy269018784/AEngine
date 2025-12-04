#include "SFMLWindow.h"

SFMLWindow::SFMLWindow(IWindow *Parent)
    : IWindow(Parent)
{
#ifdef PROJECT_USE_SFML
    Handle = new sf::RenderWindow(sf::VideoMode({800, 600}), "SFML window");
#endif
}

SFMLWindow::~SFMLWindow()
{
#ifdef PROJECT_USE_SFML
    delete Handle;
#endif
}

void SFMLWindow::Run() {
#ifdef PROJECT_USE_SFML
    while (Handle->isOpen())
        {
        while (const std::optional event = Handle->pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                Handle->close();
        }
    }
#endif
}

void SFMLWindow::SetTitle(const char *Title)
{
#ifdef PROJECT_USE_SFML
    Handle->setTitle(Title);
#endif
}

void SFMLWindow::Resize(int W, int H)
{
#ifdef PROJECT_USE_SFML
    sf::Vector2u Size;
    Size.x = Width;
    Size.x = Height;
    Handle->setSize(Size);
#endif
}

void SFMLWindow::SetWidth(int arg)
{
#ifdef PROJECT_USE_SFML
    sf::Vector2u Size;
    Size.x = Width;
    Size.x = Height;
    Handle->setSize(Size);
#endif
}

void SFMLWindow::SetHeight(int arg)
{
#ifdef PROJECT_USE_SFML
    sf::Vector2u Size;
    Size.x = Width;
    Size.x = Height;
    Handle->setSize(Size);
#endif
}

void SFMLWindow::SetPosition(int X, int Y)
{
#ifdef PROJECT_USE_SFML
    this->X = X;
    this->Y = Y;
    sf::Vector2i Pos(this->X, this->Y);
    Handle->setPosition(Pos);
#endif
}

#ifdef PROJECT_USE_XCB
xcb_connection_t *SFMLWindow::GetXCBConnection()
{
    return nullptr;
}

xcb_window_t SFMLWindow::GetXCBWindow()
{
    return 0;
}
#endif
#ifdef PROJECT_USE_Xlib
Display* SFMLWindow::GetXlibDisplay()
{
    return nullptr;
}

Window SFMLWindow::GetXlibWindow()
{
    return 0;
}
#endif