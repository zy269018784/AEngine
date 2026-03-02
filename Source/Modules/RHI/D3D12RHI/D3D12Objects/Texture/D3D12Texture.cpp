#include "D3D12Objects/Texture/D3D12Texture.h"
#include "D3D12Objects/Core/D3D12Core.h"
#include "D3D12Objects/Device/D3D12Device.h"
D3D12Texture::D3D12Texture(D3D12Device *InDevice, RHITextureType InType, RHIPixelFormat InFormat, std::uint32_t InNumMips, std::uint32_t InX, std::uint32_t InY, std::uint32_t InZ, std::uint32_t InArraySize, void *InData)
    : RHITexture(InType, InFormat, InX, InY, InZ, InNumMips, InArraySize, InData), Device(InDevice)
{
    // 1. 定义纹理的属性
    D3D12_RESOURCE_DESC textureDesc = {};
    textureDesc.Dimension = ToD3D12ResourceDimension(GetType()); // 指定为2D纹理
    textureDesc.Width  = GetX();          // 纹理宽度（像素）
    textureDesc.Height = GetY();         // 纹理高度（像素）
    textureDesc.DepthOrArraySize = GetZ(); // 对于非纹理数组，设为1
    textureDesc.MipLevels = GetNumMips();        // 不使用mipmap则设为1
    textureDesc.Format = ToD3D12Format(GetFormat()); // 常用格式，每个像素4个8位分量
    textureDesc.SampleDesc.Count = 1; // 多重采样计数，1表示不开启
    textureDesc.Flags = D3D12_RESOURCE_FLAG_NONE;    // 默认标志

    textureDesc.MipLevels = 1;
    textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    textureDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
    textureDesc.DepthOrArraySize = 1;
    textureDesc.SampleDesc.Count = 1;
    textureDesc.SampleDesc.Quality = 0;
    textureDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;

    CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_DEFAULT);

    Device->CreateCommittedResource(&heapProps, // 默认堆
                           D3D12_HEAP_FLAG_NONE,
                                    &textureDesc,
                                    D3D12_RESOURCE_STATE_COPY_DEST,                     // 初始状态为拷贝目标
                                    nullptr,
                                    IID_PPV_ARGS(&Handle));

    return;
    D3D12_RESOURCE_DESC uploadDesc = {};
    uploadDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER; // 上传资源是缓冲区
    uploadDesc.Width = GetX() * GetY();                       // 缓冲区大小

    D3D12_HEAP_PROPERTIES* pHeapUploadProperties;
    Device->CreateCommittedResource(
        pHeapUploadProperties,
        D3D12_HEAP_FLAG_NONE,
        &uploadDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&pUploadBuffer));
}


D3D12Texture::~D3D12Texture()
{

}

void D3D12Texture::Update(int MipmapLevel, int XOffset, int YOffset, int ZOffset, int Width, int Height, int Depth, const void* InData)
{
    // 2. 将图片数据映射到上传缓冲区
    void* pMappedData = nullptr;
    pUploadBuffer->Map(0, nullptr, &pMappedData);
    memcpy(pMappedData, InData, Width * Height);
    pUploadBuffer->Unmap(0, nullptr);

    // 3. 使用命令列表将数据从上传缓冲区拷贝到纹理资源
    //commandList->CopyResource(Handle, pUploadBuffer);
}