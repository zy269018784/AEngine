#pragma once
#include <string>
#include <vector>
class PCM;
class OggFileFormat
{
public:
	//int OggEncoder(class PCM* InPCM, std::string OutputFile);
	int VorbisEncoder(class PCM* InPCM, std::string OutputFile);
};