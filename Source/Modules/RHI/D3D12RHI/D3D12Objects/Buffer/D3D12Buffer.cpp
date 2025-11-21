#include "D3D12Buffer.h"

D3D12Buffer::D3D12Buffer()
{

}

D3D12Buffer::D3D12Buffer(D3D12Device* InDevice, RHIBuffer::RHIBufferType InType, RHIBuffer::RHIBufferUsageFlag InUsage, std::uint32_t InSize, const void* InData)
	: Device(InDevice), RHIBuffer(InType, InUsage, InSize)
{

    // 创建上传堆
    D3D12_HEAP_PROPERTIES HeapProps = {};
    HeapProps.Type = D3D12_HEAP_TYPE_UPLOAD;

    D3D12_RESOURCE_DESC ResourceDesc = {};
    ResourceDesc.Dimension          = D3D12_RESOURCE_DIMENSION_BUFFER;
    ResourceDesc.Width              = InSize;
    ResourceDesc.Height             = 1;
    ResourceDesc.DepthOrArraySize   = 1;
    ResourceDesc.MipLevels          = 1;
    ResourceDesc.SampleDesc.Count   = 1;
    ResourceDesc.Layout             = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

    if (FAILED(InDevice->CreateCommittedResource(&HeapProps, D3D12_HEAP_FLAG_NONE, &ResourceDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&Handle)))) {
        
    }
}

D3D12Buffer::~D3D12Buffer()
{
    Handle->Release();
}

ID3D12Resource* D3D12Buffer::GetHandle() const
{
	return Handle;
}