#include "ALSource.h"

ALSource::ALSource()
{
    alGenSources(1, &Handle);
}

ALSource::~ALSource()
{
    alDeleteSources(1, &Handle);
}

ALuint ALSource::GetHandle() const
{
    return  Handle;
}

void ALSource::SetPitch(float Value)
{
    alSourcef(Handle, AL_PITCH, Value);
}

void ALSource::SetGain(float Value)
{
    alSourcef(Handle, AL_GAIN, Value);
}

void ALSource::SetMinGain(float Value)
{
    alSourcef(Handle, AL_MIN_GAIN, Value);
}

void ALSource::SetMaxGain(float Value)
{
    alSourcef(Handle, AL_MAX_GAIN, Value);
}

void ALSource::SetMaxDistance(float distance)
{
    alSourcef(Handle, AL_MAX_DISTANCE, distance);
}

void ALSource::SetRolloffFactor(float factor)
{
    alSourcef(Handle, AL_ROLLOFF_FACTOR, factor);
}

void ALSource::SetConeOuterGain(float gain)
{
    alSourcef(Handle, AL_CONE_OUTER_GAIN, gain);
}

void ALSource::SetConeInnerAngle(float angle)
{
    alSourcef(Handle, AL_CONE_INNER_ANGLE, angle);
}

void ALSource::SetConeOuterAngle(float angle)
{
    alSourcef(Handle, AL_CONE_OUTER_ANGLE, angle);
}

void ALSource::SetReferenceDistance(float distance)
{
    alSourcef(Handle, AL_REFERENCE_DISTANCE, distance);
}

void ALSource::SetPosition(float x, float y, float z)
{
    alSource3f(Handle, AL_POSITION, x, y, z);
}

void ALSource::SetDirection(float x, float y, float z)
{
    alSource3f(Handle, AL_DIRECTION, x, y, z);
}

void ALSource::SetVelocity(float x, float y, float z)
{
    alSource3f(Handle, AL_VELOCITY, x, y, z);
}

void ALSource::SetLooping(bool On) {
    alSourcei(Handle, AL_LOOPING, On);
}

void ALSource::Play()
{
    alSourcePlay(Handle);
}

void ALSource::Pause()
{
    alSourcePause(Handle);
}
void ALSource::Stop()
{
    alSourceStop(Handle);
}
void ALSource::Rewind()
{
    alSourceRewind(Handle);
}

bool ALSource::IsPlaying() const
{
    ALint state;
    alGetSourcei(Handle, AL_SOURCE_STATE, &state);
    return (state == AL_PLAYING);
}

void ALSource::SetBuffer(ALuint buffer)
{
    alSourcei(Handle, AL_BUFFER, buffer);
}

void ALSource::QueueBuffers(ALsizei n, const ALuint* buffers)
{
    alSourceQueueBuffers(Handle, n, buffers);
}

void ALSource::UnqueueBuffers(ALsizei n, ALuint* buffers)
{
    alSourceUnqueueBuffers(Handle, n, buffers);
}