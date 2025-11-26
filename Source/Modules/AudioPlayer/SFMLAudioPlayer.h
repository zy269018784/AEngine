#pragma once
#include "IAudioPlayer.h"
class SFMLAudioPlayer : public IAudioPlayer
{
public:
    SFMLAudioPlayer();
    virtual ~SFMLAudioPlayer();
public:
    virtual int Play(const char *fileName) override final;
};


