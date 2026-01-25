#include "D3D12SwapChain.h"

#include "D3D12Objects/Factory/D3D12Factory.h"
#include "D3D12Objects/Queue/D3D12Queue.h"
#include "D3D12Objects/Surface/D3D12Surface.h"

D3D12SwapChain::D3D12SwapChain(D3D12Factory *InFactory, D3D12Queue *InQueue, D3D12Surface *InSurface)
    : Factory(InFactory), Queue(InQueue), Surface(InSurface)
{

    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
    swapChainDesc.BufferCount = 2;
    swapChainDesc.Width  = Surface->Width;
    swapChainDesc.Height = Surface->Height;
    swapChainDesc.Format = Surface->Format;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapChainDesc.SampleDesc.Count = 1;
    if (FAILED(Factory->CreateSwapChainForHwnd(Queue->GetHandle(), Surface->Hwnd, &swapChainDesc, nullptr, nullptr, &Handle)))
    {

    }
}

D3D12SwapChain::~D3D12SwapChain()
{

}

IDXGISwapChain1* D3D12SwapChain::GetHandle() const
{
    return Handle;
}

UINT D3D12SwapChain::GetCurrentBackBufferIndex(void)
{
    return ((IDXGISwapChain3*)Handle)->GetCurrentBackBufferIndex();
}