#pragma once
#include "D3D11RHI/D3D11_Includes.h"
#include "RHI/RHIObjects/Texture/RHITexture.h"
class D3D11Device;
class D3D11Texture : public RHITexture
{
public:
    D3D11Texture(D3D11Device *InDevice, RHITextureType InType, RHIPixelFormat InFormat, std::uint32_t InNumMips, std::uint32_t InX, std::uint32_t InY, std::uint32_t InZ, std::uint32_t InArraySize, void *InData = nullptr);
    ~D3D11Texture();
    virtual void Update(int MipmapLevel, int XOffset, int YOffset, int ZOffset, int Width, int Height, int Depth, const void* InData) override final;
    void TransitionImageLayout(int dir) override final;
public:
    D3D11Device* Device;
    //ID3D11Resource* Handle = nullptr;
    ID3D11Texture2D* Handle = nullptr;
    ID3D11Resource* pUploadBuffer = nullptr;
};