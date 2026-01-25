#include "D3D12SwapChain.h"

#include "D3D12Objects/Queue/D3D12Queue.h"

D3D12SwapChain::D3D12SwapChain(D3D12Factory *InFactory, D3D12Queue *InQueue, HWND InHwnd)
    : Factory(InFactory)
{
    if (FAILED(Factory->CreateSwapChainForHwnd(InQueue->GetHandle(), InHwnd, &swapChainDesc, nullptr, nullptr, &Handle)))
    {

    }
}

D3D12SwapChain::~D3D12SwapChain()
{

}

IDXGISwapChain1 GetHandle() const
{
    return Handle;
}