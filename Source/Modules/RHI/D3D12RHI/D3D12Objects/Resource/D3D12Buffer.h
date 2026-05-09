#pragma once
#include "D3D12RHI/D3D12Objects/Device/D3D12Device.h"
#include "RHI/RHIObjects/Core/RHICore.h"
#include "RHI/RHIObjects/Resource/RHIBuffer.h"
#include <cstdint>

class D3D12Buffer : public RHIBuffer
{
public:
    D3D12Buffer();
    D3D12Buffer(D3D12Device* InDevice, RHIBufferType InType, RHIBufferUsageFlag InUsage, std::uint32_t InSize, const void* InData);
    ~D3D12Buffer();
    ID3D12Resource* GetHandle() const;
    D3D12_GPU_VIRTUAL_ADDRESS GetGPUVirtualAddress( void);
    virtual void Update(std::uint32_t InSize, const void* InData) final override;
private:
    ID3D12Resource* Handle;
    D3D12Device* Device;
};