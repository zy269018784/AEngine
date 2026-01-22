#pragma once
#include "RHIObjects/Shader/RHIShaderResourceBindings.h"
#include "D3D12Objects/Device/D3D12Device.h"

class D3D12ShaderResourceBindings : public RHIShaderResourceBindings {
public:
    D3D12ShaderResourceBindings(D3D12Device *Device);
    ~D3D12ShaderResourceBindings();
    virtual void Create() final override;
};