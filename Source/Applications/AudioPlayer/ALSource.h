#pragma once
#include "AL/al.h"
class ALSource {
public:
    ALSource();
    ~ALSource();
    ALuint GetHandle() const;
    void SetPitch(float Value);
    void SetGain(float Value);
    void SetMinGain(float Value);
    void SetMaxGain(float Value);
    void SetMaxDistance(float distance);
    void SetRolloffFactor(float factor);
    void SetConeOuterGain(float gain);
    void SetConeInnerAngle(float angle);
    void SetConeOuterAngle(float angle);
    void SetReferenceDistance(float distance);
    void SetPosition(float x, float y, float z);
    void SetDirection(float x, float y, float z);
    void SetVelocity(float x, float y, float z);
    void Play();
    void Pause();
    void Stop();
    void Rewind();
    bool IsPlaying() const;
    void SetBuffer(ALuint buffer);
    void QueueBuffers(ALsizei n, const ALuint* buffers);
    void UnqueueBuffers(ALsizei n, ALuint* buffers);
private:
    ALuint Handle;
};
