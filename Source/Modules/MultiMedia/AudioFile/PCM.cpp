#include "PCM.h"

int PCM::ReadFromRawFile(std::string InputFile)
{
	size_t FileSize = 0;
	FILE* file = fopen(InputFile.c_str(), "rb");
	fseek(file, 0, SEEK_END);
	FileSize = ftell(file);

	SetSampleCount(FileSize / BytesPerSample);

	fseek(file, 0, SEEK_SET);

	fread(PCMBuffer.data(), BytesPerSample, GetSampleCount(), file);

	fclose(file);

	return 0;
}

int PCM::ReadFromRawFile16Normalized(std::string InputFile)
{
	size_t FileSize = 0;
	FILE* file = fopen(InputFile.c_str(), "rb");
	fseek(file, 0, SEEK_END);
	FileSize = ftell(file);

	SetSampleCount(FileSize / BytesPerSample);

	fseek(file, 0, SEEK_SET);

	fread(PCMBuffer.data(), BytesPerSample, GetSampleCount(), file);
	/*
		将 16-bit PCM 转换为浮点 (-1.0 ~ 1.0)
	*/
	for (size_t i = 0; i < PCMBuffer.size(); i++)
	{
		PCMBuffer[i] = PCMBuffer[i] / 32768.0f;
	}

	fclose(file);

	return 0;
}

int PCM::ReadFromRawFile32(std::string InputFile)
{
	size_t FileSize = 0;
	FILE* file = fopen(InputFile.c_str(), "rb");
	fseek(file, 0, SEEK_END);
	FileSize = ftell(file);

	SetSampleCount(FileSize / BytesPerSample);

	fseek(file, 0, SEEK_SET);

	fread(PCMBuffer.data(), BytesPerSample, GetSampleCount(), file);

	PCMBuffer32.resize(FileSize / BytesPerSample);
	for (size_t i = 0; i < PCMBuffer32.size(); i++)
	{
		PCMBuffer32[i] = PCMBuffer[i];
	}

	fclose(file);

	return 0;
}

void PCM::SetSampleRate(int n)
{
	SampleRate = n;
}

int  PCM::GetSampleRate()
{
	return SampleRate;
}

void PCM::SetChannels(int n)
{
	Channels = n;
}

int  PCM::GetChannels()
{
	return Channels;
}

void PCM::SetSampleCount(int n)
{
	PCMBuffer.resize(n);
}

int PCM::GetSampleCount()
{
	return PCMBuffer.size();
}

const std::vector<short>& PCM::GetPCMBuffer()
{
	return PCMBuffer;
}

const std::vector<int>& PCM::GetPCMBuffer32()
{
	return PCMBuffer32;
}

void PCM::SetBytesPerSample(int n)
{
	BytesPerSample = n;
}

int PCM::GetBytesPerSample()
{
	return BytesPerSample;
}