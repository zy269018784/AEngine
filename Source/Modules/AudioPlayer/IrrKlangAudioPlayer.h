#pragma once
#include "IAudioPlayer.h"
#ifdef PROJECT_USE_IrrKlang
    #include <irrKlang.h>
#endif
class IrrKlangAudioPlayer : public IAudioPlayer
{
public:
    IrrKlangAudioPlayer();
    virtual ~IrrKlangAudioPlayer();
public:
    virtual int Play(const char *fileName) override final;
private:
#ifdef PROJECT_USE_IrrKlang
    irrklang::ISoundEngine* Engine = nullptr;
#endif
};


