#pragma once
#include "RHIObjects/Core/RHICore.h"
#include "RHIObjects/Texture/RHITexture.h"
class D3D12Device;
class D3D12Texture : public RHITexture
{
public:
    D3D12Texture(D3D12Device *InDevice, RHITextureType InType, RHIPixelFormat InFormat, std::uint32_t InNumMips, std::uint32_t InX, std::uint32_t InY, std::uint32_t InZ, std::uint32_t InArraySize);
    ~D3D12Texture();
public:
    D3D12Device* Device;
};