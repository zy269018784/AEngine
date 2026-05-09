#pragma once
#include "RHI/RHIExport.h"
#include "RHI/RHIObjects/Core/RHICore.h"
#include <cstdint>
#include <cstdlib> 
class RHIEXPORT RHIShader
{
public:
	RHIShader() = delete;
	RHIShader(RHIShaderType InType, std::uint32_t* InCode, size_t InSize);
	virtual ~RHIShader();
	std::uint32_t* GetCode() const;
	size_t GetSize() const;
	RHIShaderType GetType() const;
private:
	std::uint32_t* Code;
	size_t Size;
	RHIShaderType Type;
};