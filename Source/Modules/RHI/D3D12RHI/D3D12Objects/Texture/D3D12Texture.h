#pragma once
#include "D3D12_Includes.h"
#include "RHIObjects/Core/RHICore.h"
#include "RHIObjects/Texture/RHITexture.h"
class D3D12Device;
class D3D12Texture : public RHITexture
{
public:
    D3D12Texture(D3D12Device *InDevice, RHITextureType InType, RHIPixelFormat InFormat, std::uint32_t InNumMips, std::uint32_t InX, std::uint32_t InY, std::uint32_t InZ, std::uint32_t InArraySize, void *InData = nullptr);
    ~D3D12Texture();
    virtual void Update(int MipmapLevel, int XOffset, int YOffset, int ZOffset, int Width, int Height, int Depth, const void* InData) override final;

public:
    D3D12Device* Device;
    ID3D12Resource* Handle = nullptr;
    ID3D12Resource* pUploadBuffer = nullptr;
};