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

HRESULT STDMETHODCALLTYPE D3D12Device::CreateRootSignature(
    _In_  UINT nodeMask,
    _In_reads_(blobLengthInBytes)  const void* pBlobWithRootSignature,
    _In_  SIZE_T blobLengthInBytes,
    REFIID riid,
    _COM_Outptr_  void** ppvRootSignature)
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

HRESULT STDMETHODCALLTYPE D3D12Device::CreateDescriptorHeap(
    _In_  const D3D12_DESCRIPTOR_HEAP_DESC* pDescriptorHeapDesc,
    REFIID riid,
    _COM_Outptr_  void** ppvHeap)
{
    return Handle->CreateDescriptorHeap(pDescriptorHeapDesc, riid, ppvHeap);
}

UINT STDMETHODCALLTYPE D3D12Device::GetDescriptorHandleIncrementSize(
    _In_  D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeapType)
{
    return Handle->GetDescriptorHandleIncrementSize(DescriptorHeapType);
}

void STDMETHODCALLTYPE D3D12Device::CreateRenderTargetView(
    _In_opt_  ID3D12Resource* pResource,
    _In_opt_  const D3D12_RENDER_TARGET_VIEW_DESC* pDesc,
    _In_  D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor)
{
    return Handle->CreateRenderTargetView(pResource, pDesc, DestDescriptor);
}