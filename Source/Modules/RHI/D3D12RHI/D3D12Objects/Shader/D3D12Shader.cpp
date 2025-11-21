#include "D3D12Shader.h"
#include <iostream>
D3D12Shader::D3D12Shader(D3D12Device* InDevice, RHIShaderType type, std::uint32_t* Code, std::size_t CodeSize)
{
    UINT compileFlags = 0;
    ID3DBlob* error = nullptr;
    if (FAILED(D3DCompile(Code, CodeSize, nullptr, nullptr, nullptr, "main", "vs_5_0", compileFlags, 0, &Handle, &error)))
    {
        std::cerr << "VS compile failed: " << (char*)error->GetBufferPointer() << std::endl;
    }
}

D3D12Shader::~D3D12Shader()
{
    Handle->Release();
}

ID3DBlob* D3D12Shader::GetHandle()
{
	return Handle;
}