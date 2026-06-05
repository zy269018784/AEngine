#include "D3D12CommandPool.h"

#include <iostream>
#include <ostream>

#include "D3D12RHI/D3D12Objects/Device/D3D12Device.h"
D3D12CommandPool::D3D12CommandPool(D3D12Device* InDevice)
	: Device(InDevice)
{
	// 创建命令分配器和列表
	if (FAILED(Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&Handle)))) 
	{
		std::cout << "CreateCommandAllocator failed " << std::endl;
	}

	std::cout << "CreateCommandAllocator OK " << Handle << std::endl;
}

D3D12CommandPool::~D3D12CommandPool()
{
	Handle->Release();
}

ID3D12CommandAllocator* D3D12CommandPool::GetHandle()
{
	return Handle;
}