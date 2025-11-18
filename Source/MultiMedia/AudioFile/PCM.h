#pragma once
#include <vector>
#include <string>
class PCM
{
public:
	int ReadFromRawFile(std::string InputFile);
	int ReadFromRawFile16Normalized(std::string InputFile);
	int ReadFromRawFile32(std::string InputFile);
	void SetSampleRate(int n);
	int GetSampleRate();
	void SetChannels(int n);
	int GetChannels();
	void SetSampleCount(int n);
	int GetSampleCount();
	void SetBytesPerSample(int n);
	int GetBytesPerSample();
	const std::vector<short>& GetPCMBuffer();
	const std::vector<int>& GetPCMBuffer32();
private:
	int SampleRate;
	int Channels;
	int BytesPerSample;
	std::vector<short> PCMBuffer;
	std::vector<int>   PCMBuffer32;
};