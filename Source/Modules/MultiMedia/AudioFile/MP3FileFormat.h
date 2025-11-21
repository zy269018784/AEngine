#pragma once
#include <string>
#include <vector>
class PCM;
class MP3FileFormat
{
public:
	int LameEncoder(class PCM *InPCM, std::string OutputFile);
};