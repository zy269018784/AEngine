#pragma once
#include <string>
#include <vector>
class PCM;
class FlacFileFormat
{
public:
	int FlacEncoder(class PCM* InPCM, std::string OutputFile);
};