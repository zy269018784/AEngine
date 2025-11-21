#pragma once
#include "D3D12Objects/Device/D3D12Device.h"
class D3D12CommandPool
{
public:
	D3D12CommandPool(D3D12Device* InDevice);
	~D3D12CommandPool();
	ID3D12CommandAllocator* GetHandle();
public:
	HRESULT STDMETHODCALLTYPE Reset(void);
private:
	ID3D12CommandAllocator* Handle = nullptr;
	D3D12Device* Device = nullptr;
};