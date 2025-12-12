#include <vector>
#include <iostream>
#include <fstream>


#include "AL/al.h"
#include "AL/alc.h"
#include "ALBuffer.h"
#include "ALSource.h"
#include "ALListener.h"

std::vector<char> ReadFile(const std::string& filename);
int main()
{
    ALCdevice* device = alcOpenDevice(NULL);

    if (!device) {
        printf("Failed to open audio device\n");
        return -1;
    }

    // Create OpenAL context
    ALCcontext* context = alcCreateContext(device, NULL);
    if (!context) {
        printf("Failed to create context\n");
        alcCloseDevice(device);
        return -1;
    }

    // Make context current
    if (!alcMakeContextCurrent(context)) {
        printf("Failed to make context current\n");
        alcDestroyContext(context);
        alcCloseDevice(device);
        return -1;
    }

    std::cout << "hello, world" << std::endl;
    auto Data = ReadFile("output_s16le.pcm");

    ALsizei Size = Data.size();
    ALsizei Freq = 48000;

    std::cout << "Size " << Data.size() << std::endl;
    ALBuffer Buffer;
    ALSource Source;
    ALListener Listener;

    Listener.SetGain(1.0);
    Listener.SetPosition(0, 0, 0);
    Listener.SetOrientation(0, 1, 0, 0, 0, 1);
    Listener.SetVelocity(0, 0, 0);



    Buffer.BufferData(AL_FORMAT_STEREO16, Data.data(), Size, Freq);

    Source.SetBuffer(Buffer.GetHandle());
    Source.SetPosition(0, 1, 0);
    Source.SetGain(0.5);
    Source.SetVelocity(0, 0, 0);
    Source.SetDirection(0, 1, 0);
    Source.SetLooping(true);

    Source.Play();

    while (1);
    return 0;
}