#include "SFMLAudioPlayer.h"
#ifdef PROJECT_USE_SFML
    #include <SFML/Audio.hpp>
    #include <SFML/Graphics.hpp>
    #include <SFML/Audio/Music.hpp>
#endif
SFMLAudioPlayer::SFMLAudioPlayer()
{

}

SFMLAudioPlayer::~SFMLAudioPlayer()
{

}

int SFMLAudioPlayer::Play(const char *fileName)
{
#ifdef PROJECT_USE_SFML
    auto Music = new sf::Music(fileName);
    Music->play();
#endif
    return 0;
}