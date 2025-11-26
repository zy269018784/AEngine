#include "IrrKlangAudioPlayer.h"


IrrKlangAudioPlayer::IrrKlangAudioPlayer()
{
#ifdef PROJECT_USE_IrrKlang
    Engine = irrklang::createIrrKlangDevice();
#endif
}

IrrKlangAudioPlayer::~IrrKlangAudioPlayer()
{
#ifdef PROJECT_USE_IrrKlang
    Engine->drop();
#endif
}

int IrrKlangAudioPlayer::Play(const char *fileName)
{
#ifdef PROJECT_USE_IrrKlang
    Engine->play2D(fileName, true);
#endif
    return 0;
}