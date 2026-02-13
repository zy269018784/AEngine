#include "D3D12Objects/Device/D3D12Device.h"

HRESULT D3D12Device::CreateCommittedResource(
    const D3D12_HEAP_PROPERTIES* pHeapProperties,
    D3D12_HEAP_FLAGS HeapFlags,
    const D3D12_RESOURCE_DESC* pDesc,
    D3D12_RESOURCE_STATES InitialResourceState,
    const D3D12_CLEAR_VALUE* pOptimizedClearValue,
    REFIID riidResource,
    void** ppvResource)
{
    return Handle->CreateCommittedResource(pHeapProperties, HeapFlags, pDesc, InitialResourceState, pOptimizedClearValue, riidResource, ppvResource);
}

HRESULT D3D12Device::CreateFence(
            UINT64 InitialValue,
            D3D12_FENCE_FLAGS Flags,
            REFIID riid,
            void **ppFence)
{
    return Handle->CreateFence(InitialValue, Flags, riid, ppFence);
}

HRESULT D3D12Device::CreateRootSignature(
    UINT nodeMask,
    const void* pBlobWithRootSignature,
    SIZE_T blobLengthInBytes,
    REFIID riid,
    void** ppvRootSignature)
{
    return Handle->CreateRootSignature(nodeMask, pBlobWithRootSignature, blobLengthInBytes, riid, ppvRootSignature);
}

HRESULT D3D12Device::CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE type, REFIID riid, void** ppCommandAllocator)
{
    return Handle->CreateCommandAllocator(type, riid, ppCommandAllocator);
}

HRESULT D3D12Device::CreateCommandList(UINT  nodeMask, D3D12_COMMAND_LIST_TYPE type, ID3D12CommandAllocator* pCommandAllocator, ID3D12PipelineState* pInitialState, REFIID riid, void** ppCommandList)
{
    return Handle->CreateCommandList(nodeMask, type, pCommandAllocator, pInitialState, riid, ppCommandList);
}

HRESULT D3D12Device::CreateCommandQueue(
    const D3D12_COMMAND_QUEUE_DESC* pDesc,
    REFIID                         riid,
    void** ppCommandQueue
)
{
    return Handle->CreateCommandQueue(pDesc, riid, ppCommandQueue);
}

HRESULT D3D12Device::CreateDescriptorHeap(
    const D3D12_DESCRIPTOR_HEAP_DESC* pDescriptorHeapDesc,
    REFIID riid,
    void** ppvHeap)
{
    return Handle->CreateDescriptorHeap(pDescriptorHeapDesc, riid, ppvHeap);
}

UINT D3D12Device::GetDescriptorHandleIncrementSize(
    D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeapType)
{
    return Handle->GetDescriptorHandleIncrementSize(DescriptorHeapType);
}

void D3D12Device::CreateRenderTargetView(
    ID3D12Resource* pResource,
    const D3D12_RENDER_TARGET_VIEW_DESC* pDesc,
    D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor)
{
    return Handle->CreateRenderTargetView(pResource, pDesc, DestDescriptor);
}

HRESULT D3D12Device::CreateGraphicsPipelineState(
          const D3D12_GRAPHICS_PIPELINE_STATE_DESC *pDesc,
          REFIID riid,
          void **ppPipelineState) {
    return Handle->CreateGraphicsPipelineState(pDesc, riid, ppPipelineState);
}