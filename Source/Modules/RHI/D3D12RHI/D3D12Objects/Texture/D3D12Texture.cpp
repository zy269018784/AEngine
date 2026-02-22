#include "D3D12Objects/Texture/D3D12Texture.h"
#include "D3D12Objects/Device/D3D12Device.h"
D3D12Texture::D3D12Texture(D3D12Device *InDevice, RHITextureType InType, RHIPixelFormat InFormat, std::uint32_t InNumMips, std::uint32_t InX, std::uint32_t InY, std::uint32_t InZ, std::uint32_t InArraySize)
: RHITexture(InType, InFormat, InX, InY, InZ, InNumMips, InArraySize), Device(InDevice)
{

}


D3D12Texture::~D3D12Texture()
{

}