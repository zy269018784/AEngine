#include "D3D12Objects/Texture/D3D12Texture.h"

#include "D3D12Objects/Core/D3D12Core.h"
#include "D3D12Objects/Device/D3D12Device.h"
D3D12Texture::D3D12Texture(D3D12Device *InDevice, RHITextureType InType, RHIPixelFormat InFormat, std::uint32_t InNumMips, std::uint32_t InX, std::uint32_t InY, std::uint32_t InZ, std::uint32_t InArraySize)
: RHITexture(InType, InFormat, InX, InY, InZ, InNumMips, InArraySize), Device(InDevice)
{
    // 1. 定义纹理的属性
    D3D12_RESOURCE_DESC textureDesc = {};
    textureDesc.Dimension = ToD3D12ResourceDimension(GetType()); // 指定为2D纹理
    textureDesc.Width = GetX();          // 纹理宽度（像素）
    textureDesc.Height = GetY();         // 纹理高度（像素）
    textureDesc.DepthOrArraySize = GetZ(); // 对于非纹理数组，设为1
    if (InArraySize == 1)
    {

    }
    textureDesc.MipLevels = GetNumMips();        // 不使用mipmap则设为1
    textureDesc.Format = ToD3D12Format(GetFormat()); // 常用格式，每个像素4个8位分量
    textureDesc.SampleDesc.Count = 1; // 多重采样计数，1表示不开启
    textureDesc.Flags = D3D12_RESOURCE_FLAG_NONE;    // 默认标志
}


D3D12Texture::~D3D12Texture()
{

}