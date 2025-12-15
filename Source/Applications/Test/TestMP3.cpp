#include "MultiMedia/AudioFile/MP3FileFormat.h"
#include "MultiMedia/AudioFile/PCM.h"
void TestMP3() {

    PCM pPCM;
    pPCM.SetSampleRate(48000);
    pPCM.SetChannels(2);
    pPCM.SetBytesPerSample(2);

    pPCM.ReadFromRawFile("1.pcm");
   // pPCM.ReadFromRawFile16Normalized("1.pcm");

    MP3FileFormat mp3;
    mp3.LameEncoder(&pPCM, "test111.mp3");
}

int main() {
    TestMP3();
    return 0;
}