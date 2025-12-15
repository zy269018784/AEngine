#pragma once
#include <vector>
#include <string>
class PCM
{
public:
	int ReadFromRawFile(std::string InputFile);
	int ReadFromRawFile16Normalized(std::string InputFile);
	void SetSampleRate(int n);
	int GetSampleRate();
	void SetBitRate(int n);
	int GetBitRate();
	void SetChannels(int n);
	int GetChannels();
	void SetSampleCount(int n);
	int GetSampleCount();
	void SetBytesPerSample(int n);
	int GetBytesPerSample();
	const std::vector<short>& GetPCMBuffer();
	const std::vector<int>& GetPCMBuffer32();
public:
	int Write(std::string OutputFile);
	int WriteMP2(std::string OutputFile);
	int WriteMP3(std::string OutputFile);
	int WriteAAC(std::string OutputFile);
	int WriteAC3(std::string OutputFile);
	int WriteOPUS(std::string OutputFile);
	int WriteFLAC(std::string OutputFile);
	int WriteLC3(std::string OutputFile);
	int WriteOGG(std::string OutputFile);
private:
	int BitRate;
	int SampleRate;
	int Channels;
	int BytesPerSample;
	std::vector<short> PCMBuffer;
	std::vector<int>   PCMBuffer32;
};