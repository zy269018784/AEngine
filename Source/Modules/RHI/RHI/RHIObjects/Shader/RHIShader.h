#pragma once
#include "RHIResource.h"
#include "RHIObjects/Core/RHICore.h"
#include <cstdint>
#include <cstdlib> 
class RHIShader 
{
public:
	RHIShader();
	RHIShader(RHIShaderType type, std::uint32_t* Code, size_t Size);
	virtual ~RHIShader();
public:
	std::uint32_t* CodePtr;
	size_t CodeSize;
	RHIShaderType Type_;
};