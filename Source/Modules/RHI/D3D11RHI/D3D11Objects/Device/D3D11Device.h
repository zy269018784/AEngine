#pragma once
#include "D3D11_Includes.h"
#include <vector>
class D3D11CommandPool;
class D3D11CommandBuffer;
class D3D11Queue;
class D3D11Device
{
public:
	D3D11Device();
	~D3D11Device();
    ID3D11Device* GetHandle() { return Handle; };
    D3D11CommandBuffer* CreateCommandBuffer(D3D11CommandPool* CommandPool);
    void CreateCommandPool();
    void CreateQueue();
public:

private:
	ID3D11Device* Handle;
public:
    std::vector<D3D11CommandPool*> CommandPools;
    std::vector<D3D11Queue*> Queues;
};