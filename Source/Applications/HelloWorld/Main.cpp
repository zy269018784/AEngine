#include <iostream>

#ifdef PROJECT_USE_SFML
    #include <SFML/Audio.hpp>
    #include <SFML/Graphics.hpp>
    #include <SFML/Audio/Music.hpp>
#endif

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

    return RHIExample();
}
