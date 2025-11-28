#pragma once
#include "D3D12_Includes.h"
#include "D3D12Objects/Device/D3D12Device.h"
#include "RHIObjects/Shader/RHIShader.h"
#include <cstddef>
class D3D12Shader : public RHIShader
{
public:
	D3D12Shader(D3D12Device* InDevice, RHIShaderType type, std::uint32_t* Code, std::size_t CodeSize);
	~D3D12Shader();
	ID3DBlob *GetHandle();
private:
private:
	ID3DBlob *Handle;
	D3D12Device* Device;
};