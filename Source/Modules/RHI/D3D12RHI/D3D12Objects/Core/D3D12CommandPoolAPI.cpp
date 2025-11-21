#include "D3D12Objects/CommandBuffer/D3D12CommandPool.h"

HRESULT STDMETHODCALLTYPE D3D12CommandPool::Reset(void)
{
	return Handle->Reset();
}