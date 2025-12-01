#include <iostream>

#ifdef PROJECT_USE_SFML
    #include <SFML/Audio.hpp>
    #include <SFML/Graphics.hpp>
    #include <SFML/Audio/Music.hpp>
#endif

#ifdef PROJECT_USE_CEF1
#include "cef_app.h"
#include "cef_client.h"
#include "cef_render_handler.h"
#endif
int cef_main(int argc, char **argv);

int RHIExample();
int main(int argc, char **argv)
{
    std::cout << "hello world" << std::endl;

#ifdef PROJECT_USE_SFML
    auto Music = new sf::Music("ikutaerika.mp3");
#endif
    std::cout << "play start" << std::endl;
#ifdef PROJECT_USE_SFML
    Music->setLooping(true);
    Music->play();
#endif
   // return cef_main(argc, argv);
    return RHIExample();
}

#if 0
class MinimalClient : public CefClient
{
public:
    IMPLEMENT_REFCOUNTING(MinimalClient);
};

int cef_main(int argc, char **argv) {
    CefMainArgs main_args(argc, argv);
    CefSettings settings;
    CefInitialize(main_args, settings, nullptr, nullptr);

    CefWindowInfo window_info;
    CefBrowserSettings browser_settings;

#ifdef _WIN32
    window_info.SetAsPopup(NULL, "CEF Window");
#else
    window_info.SetAsWindowless(0); // Linux/Mac alternative
#endif

    CefRefPtr<MinimalClient> client(new MinimalClient());
    CefBrowserHost::CreateBrowser(window_info, client, "https://example.com", browser_settings, nullptr, nullptr);

    CefRunMessageLoop();
    CefShutdown();
    return 0;
}
#endif