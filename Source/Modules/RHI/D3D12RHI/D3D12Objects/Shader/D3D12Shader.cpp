#include "D3D12Shader.h"
#include <iostream>
#include <intsafe.h>
D3D12Shader::D3D12Shader(D3D12Device* InDevice, RHIShaderType type, std::uint32_t* Code, std::size_t CodeSize)
    : Device(InDevice)
{

    UINT compileFlags = 0;
    ID3DBlob* error = nullptr;
#if 0
    if (FAILED(D3DCompile(Code, CodeSize, nullptr, nullptr, nullptr, "main", "vs_5_0", compileFlags, 0, &Handle, &error)))
    {
      //  std::cerr << "VS compile failed: " << (char*)error->GetBufferPointer() << std::endl;
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