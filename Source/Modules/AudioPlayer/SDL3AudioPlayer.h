#pragma once
#include "IAudioPlayer.h"
class SDL3AudioPlayer : public IAudioPlayer
{
public:
    SDL3AudioPlayer();
    virtual ~SDL3AudioPlayer();
public:
    virtual int Play(const char *fileName) override final;
};


