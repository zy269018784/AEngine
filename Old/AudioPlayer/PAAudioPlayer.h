#pragma once
#include "IAudioPlayer.h"
#if  PROJECT_USE_PORTAUDIO
    #include <portaudio.h>
#endif
class PAAudioPlayer : public IAudioPlayer
{
public:
    PAAudioPlayer();
    virtual ~PAAudioPlayer();
public:
    virtual int Play(const char *fileName) override final;
};


