#include "MultiMedia/AudioFile/MP3FileFormat.h"
#include "MultiMedia/AudioFile/FlacFileFormat.h"
#include "MultiMedia/AudioFile/OggFileFormat.h"
#include "MultiMedia/AudioFile/PCM.h"
void TestMP3()
{
    PCM pPCM;
    pPCM.SetSampleRate(48000);
    pPCM.SetChannels(2);
    pPCM.SetBytesPerSample(2);
    pPCM.ReadFromRawFile("1.pcm");

    MP3FileFormat mp3;
    mp3.LameEncoder(&pPCM, "test3.mp3");
}

void TestAudioFormat()
{
    PCM pPCM;
    pPCM.SetSampleRate(48000);
    pPCM.SetChannels(2);
    pPCM.SetBytesPerSample(2);
   // pPCM.SetBitRate(317);
    pPCM.SetBitRate(320);
    pPCM.ReadFromRawFile("1.pcm");
    pPCM.Write("test222.mp2");
    return;
    pPCM.Write("test222.aac");
    pPCM.Write("test222.mp3");
    pPCM.Write("test222.ogg");
    pPCM.Write("test222.flac");
}


int main4()
{
    TestAudioFormat();
    return 0;
}