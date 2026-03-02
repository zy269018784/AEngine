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
    ID3D11Device* GetHandle();
    D3D11CommandBuffer* CreateCommandBuffer(D3D11CommandPool* CommandPool);
    void CreateCommandPool();
    void CreateQueue();
public:
	HRESULT CreateTexture2D(const D3D11_TEXTURE2D_DESC *pDesc, const D3D11_SUBRESOURCE_DATA *pInitialData, ID3D11Texture2D **ppTexture2D);
private:
public:
	ID3D11Device* Handle;
public:
    std::vector<D3D11CommandPool*> CommandPools;
    std::vector<D3D11Queue*> Queues;
};