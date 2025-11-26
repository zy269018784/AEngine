#pragma once
class IAudioPlayer
{
public:
    IAudioPlayer();
    virtual ~IAudioPlayer();
public:
    virtual int Play(const char *fileName) = 0;
};

