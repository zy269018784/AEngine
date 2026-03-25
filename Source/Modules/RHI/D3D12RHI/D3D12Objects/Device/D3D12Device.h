#pragma once
#include "D3D12_Includes.h"
#include <vector>
class D3D12CommandPool;
class D3D12CommandBuffer;
class D3D12Queue;
class D3D12Device
{
public:
	D3D12Device();
	~D3D12Device();
    ID3D12Device* GetHandle();
    D3D12CommandBuffer* CreateCommandBuffer(D3D12CommandPool* CommandPool);
    void CreateCommandPool();
    void CreateQueue();
public:
    /*
        D3D12 API Wrapper
    */
    HRESULT CreateFence(
            UINT64 InitialValue,
            D3D12_FENCE_FLAGS Flags,
            REFIID riid,
            void **ppFence);

    HRESULT CreateCommittedResource(
        const D3D12_HEAP_PROPERTIES* pHeapProperties,
        D3D12_HEAP_FLAGS HeapFlags,
        const D3D12_RESOURCE_DESC* pDesc,
        D3D12_RESOURCE_STATES InitialResourceState,
        const D3D12_CLEAR_VALUE* pOptimizedClearValue,
        REFIID riidResource,
        void** ppvResource);

    HRESULT CreateRootSignature(
        UINT nodeMask,
        const void* pBlobWithRootSignature,
        SIZE_T blobLengthInBytes,
        REFIID riid,
        void** ppvRootSignature);

    HRESULT CreateCommandAllocator(
        D3D12_COMMAND_LIST_TYPE type,
        REFIID                  riid,
        void** ppCommandAllocator
    );

    HRESULT CreateCommandList(
        UINT                    nodeMask,
        D3D12_COMMAND_LIST_TYPE type,
        ID3D12CommandAllocator* pCommandAllocator,
        ID3D12PipelineState* pInitialState,
        REFIID                  riid,
        void** ppCommandList
    );

    HRESULT CreateCommandQueue(
        const D3D12_COMMAND_QUEUE_DESC* pDesc,
        REFIID                         riid,
        void** ppCommandQueue
    );


    HRESULT  CreateDescriptorHeap(
        const D3D12_DESCRIPTOR_HEAP_DESC* pDescriptorHeapDesc,
        REFIID riid,
        void** ppvHeap);

    UINT  GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeapType);

    void  CreateRenderTargetView(
        ID3D12Resource* pResource,
        const D3D12_RENDER_TARGET_VIEW_DESC* pDesc,
         D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor);

    HRESULT CreateGraphicsPipelineState(
           const D3D12_GRAPHICS_PIPELINE_STATE_DESC *pDesc,
           REFIID riid,
           void **ppPipelineState);
private:
public:
	ID3D12Device* Handle;
public:
    std::vector<D3D12CommandPool*> CommandPools;
    std::vector<D3D12Queue*> Queues;
    ID3D12CommandQueue *CommandQueue = nullptr;
};