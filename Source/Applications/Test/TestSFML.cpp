#if PROJECT_USE_SFML
    #include <SFML/Audio.hpp>
    #include <SFML/Graphics.hpp>
    #include <SFML/Audio/Music.hpp>
#endif
#include <iostream>

int SFMLMain(int argc, char **argv)
{
    std::cout << "play start" << std::endl;

#if PROJECT_USE_SFML
 //   auto Music = new sf::Music("ikutaerika.mp3");
    auto Music = new sf::Music("1.ogg");



    Music->play();
#endif
    std::cout << "play end" << std::endl;
    while (1);
    return 0;
}