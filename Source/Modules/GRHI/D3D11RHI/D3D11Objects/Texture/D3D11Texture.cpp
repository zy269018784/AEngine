#include "D3D11RHI/D3D11Objects/Texture/D3D11Texture.h"
#include "D3D11RHI/D3D11Objects/Core/D3D11Core.h"
#include "D3D11RHI/D3D11Objects/Device/D3D11Device.h"
D3D11Texture::D3D11Texture(D3D11Device *InDevice, RHITextureType InType, RHIPixelFormat InFormat, std::uint32_t InNumMips, std::uint32_t InX, std::uint32_t InY, std::uint32_t InZ, std::uint32_t InArraySize, void *InData)
    : RHITexture(InType, InFormat, InX, InY, InZ, InNumMips, InArraySize, InData), Device(InDevice)
{
    if (RHITextureType::Texture2D == InType)
    {
        D3D11_TEXTURE2D_DESC TextureDesc = {};
        TextureDesc.Width               = GetX();
        TextureDesc.Height              = GetY();
        TextureDesc.MipLevels           = GetNumMips();
        TextureDesc.Format              = ToD3D11Format(GetFormat());
        TextureDesc.ArraySize           = 1;
        TextureDesc.SampleDesc.Count    = 1;
        TextureDesc.SampleDesc.Quality  = 0;
        TextureDesc.Usage               = D3D11_USAGE_DEFAULT;
        /*
         *  作为SRV
         */
        TextureDesc.BindFlags           = D3D11_BIND_SHADER_RESOURCE;
        TextureDesc.CPUAccessFlags      = 0;
        TextureDesc.MiscFlags           = 0;

        D3D11_SUBRESOURCE_DATA InitData = {};
        InitData.pSysMem = GetData();
        InitData.SysMemPitch = GetX() * RHIPixelFormatToBytesPerPixel(GetFormat());
        InitData.SysMemSlicePitch = InitData.SysMemPitch * GetY();

     //   ID3D11Texture2D* Texture2DHandle = reinterpret_cast<ID3D11Texture2D *>(&Handle);
        Device->CreateTexture2D(&TextureDesc, &InitData, &Handle);
    }
    else if (RHITextureType::Texture2DArray == InType)
    {
        D3D11_TEXTURE2D_DESC TextureDesc = {};
        TextureDesc.Width               = GetX();
        TextureDesc.Height              = GetY();
        TextureDesc.MipLevels           = GetNumMips();
        TextureDesc.Format              = ToD3D11Format(GetFormat());
        TextureDesc.ArraySize           = GetArraySize();
        TextureDesc.SampleDesc.Count    = 1;
        TextureDesc.SampleDesc.Quality  = 0;
        TextureDesc.Usage               = D3D11_USAGE_DEFAULT;
        /*
         *  作为SRV
         */
        TextureDesc.BindFlags           = D3D11_BIND_SHADER_RESOURCE;
        TextureDesc.CPUAccessFlags      = 0;
        TextureDesc.MiscFlags           = 0;

        std::vector<D3D11_SUBRESOURCE_DATA> InitData(GetArraySize());
        for (UINT i = 0; i < GetArraySize(); ++i) {
            InitData[i].pSysMem = ((std::uint8_t *)GetData()) + (i * GetX() * GetY() * 4);
            InitData[i].SysMemPitch = GetX() * 4;
            InitData[i].SysMemSlicePitch = InitData[i].SysMemPitch * GetY();
        }

        Device->CreateTexture2D(&TextureDesc, InitData.data(), &Handle);
    }
}

D3D11Texture::~D3D11Texture()
{

}

void D3D11Texture::Update(int MipmapLevel, int XOffset, int YOffset, int ZOffset, int Width, int Height, int Depth, const void* InData)
{
#if 0
    // 2. 将图片数据映射到上传缓冲区
    void* pMappedData = nullptr;
    pUploadBuffer->Map(0, nullptr, &pMappedData);
    memcpy(pMappedData, InData, Width * Height);
    pUploadBuffer->Unmap(0, nullptr);
#endif
    // 3. 使用命令列表将数据从上传缓冲区拷贝到纹理资源
    //commandList->CopyResource(Handle, pUploadBuffer);
}

void D3D11Texture::TransitionImageLayout(int dir)
{

}