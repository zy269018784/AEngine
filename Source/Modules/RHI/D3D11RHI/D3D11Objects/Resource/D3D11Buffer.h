#pragma once
#include "D3D11Objects/Device/D3D11Device.h"
#include "RHIObjects/Resource/RHIBuffer.h"
#include <cstdint>

class D3D11Buffer : public RHIBuffer
{
public:
    D3D11Buffer();
    D3D11Buffer(D3D11Device* InDevice, RHIBuffer::RHIBufferType InType, RHIBuffer::RHIBufferUsageFlag InUsage, std::uint32_t InSize, const void* InData);
    ~D3D11Buffer();
    ID3D11Buffer* GetHandle() const;
    virtual void Update(std::uint32_t InSize, const void* InData) final override;
private:
    ID3D11Buffer* Handle;
    D3D11Device* Device;
};