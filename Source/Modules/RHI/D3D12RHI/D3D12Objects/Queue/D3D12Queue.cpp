#include "D3D12Queue.h"
#include "D3D12_Includes.h"
D3D12Queue::D3D12Queue(D3D12Device* InDevice)
    : Device(InDevice)
{
    // 创建命令队列
    D3D12_COMMAND_QUEUE_DESC QueueDesc = {};
    QueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    if (FAILED(Device->CreateCommandQueue(&QueueDesc, IID_PPV_ARGS(&Handle))))
    {

    }
}

D3D12Queue::~D3D12Queue()
{

}

ID3D12CommandQueue* D3D12Queue::GetHandle()
{
	return Handle;
}