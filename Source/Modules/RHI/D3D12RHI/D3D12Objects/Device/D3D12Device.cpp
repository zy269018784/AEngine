#include "D3D12Device.h"
#include "D3D12RHI/D3D12Objects/CommandBuffer/D3D12CommandPool.h"
#include "D3D12RHI/D3D12Objects/CommandBuffer/D3D12CommandBuffer.h"
#include "D3D12RHI/D3D12Objects/Queue/D3D12Queue.h"
#include <iostream>
D3D12Device::D3D12Device()
{
    // 创建设备
    if (FAILED(D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&Handle))))
    {
        std::cerr << "Failed to create device" << std::endl;
    }

    D3D12_COMMAND_QUEUE_DESC QueueDesc = {};
    QueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    QueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    Handle->CreateCommandQueue(&QueueDesc, IID_PPV_ARGS(&CommandQueue));

    std::cout << "create device ok" << std::endl;
}

D3D12Device::~D3D12Device()
{
	delete Handle;
}

ID3D12Device* D3D12Device::GetHandle()
{
    return Handle;
}


D3D12CommandBuffer* D3D12Device::CreateCommandBuffer(D3D12CommandPool* CommandPool)
{
    D3D12CommandBuffer* CommandBuffer = new D3D12CommandBuffer(this, CommandPool);
    return CommandBuffer;

}

void D3D12Device::CreateCommandPool()
{
    D3D12CommandPool* CommandPool = new D3D12CommandPool(this);
    CommandPools.emplace_back(CommandPool);
}

void D3D12Device::CreateQueue()
{
    D3D12Queue *Queue = new D3D12Queue(this);
    Queues.emplace_back(Queue);
}