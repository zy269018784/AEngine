#include "D3D12Shader.h"
#include <iostream>
#include <intsafe.h>
D3D12Shader::D3D12Shader(D3D12Device* InDevice, RHIShaderType InType, std::uint32_t* Code, std::size_t CodeSize)
    : Device(InDevice)
{

    UINT compileFlags = 0;
    ID3DBlob* error = nullptr;
#if 1
    const char *Target = nullptr;
    if (InType == RHIShaderType::Fragment)
        Target = "ps_5_0";
    else if (InType == RHIShaderType::Vertex)
        Target = "vs_5_0";

    if (FAILED(D3DCompile((const char *)Code, CodeSize, nullptr, nullptr, nullptr, "main", Target, compileFlags, 0, &Handle, &error)))
    {
        std::cerr << "Shader compile failed: " << (char*)error->GetBufferPointer() << std::endl;
    }
#endif
}

D3D12Shader::~D3D12Shader()
{
    Handle->Release();
}

ID3DBlob* D3D12Shader::GetHandle()
{
	return Handle;
}