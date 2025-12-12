#include "ALBuffer.h"

ALBuffer::ALBuffer()
{
    alGenBuffers(1, &Handle);
}

ALBuffer::~ALBuffer()
{
    alDeleteBuffers(1, &Handle);
}

ALuint ALBuffer::GetHandle() const
{
    return  Handle;
}

void ALBuffer::SetFrequency(int Value)
{
    alBufferi(Handle, AL_FREQUENCY, Value);
}

void ALBuffer::SetBits(int Value)
{
    alBufferi(Handle, AL_BITS, Value);
}

void ALBuffer::SetSize(int Value)
{
    alBufferi(Handle, AL_SIZE, Value);
}

void ALBuffer::SetChannels(int Value)
{
    alBufferi(Handle, AL_CHANNELS, Value);
}

void ALBuffer::BufferData(ALenum Format, const ALvoid *Data, ALsizei Size, ALsizei Frequency)
{
    alBufferData(Handle, Format, Data, Size, Frequency);
}