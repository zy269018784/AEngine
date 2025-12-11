#pragma once
#include "AL/al.h"
class ALBuffer
{
public:
    ALBuffer();
    ~ALBuffer();
    ALuint GetHandle() const;
    void SetFrequency(int Value);
    void SetBits(int Value);
    void SetSize(int Value);
    void SetChannels(int Value);
    void BufferData(ALenum Format, const ALvoid *Data, ALsizei Size, ALsizei Frequency);
private:
    ALuint Handle;
};
