#pragma once
#include <D3D12_Includes.h>
class D3D12Factory;
class D3D12Queue;
class D3D12Surface;
class D3D12SwapChain
{
public:
    D3D12SwapChain(D3D12Factory *InFactory, D3D12Queue *InQueue, D3D12Surface *InSurface);
    ~D3D12SwapChain();
    IDXGISwapChain1* GetHandle() const;
public:
    UINT GetCurrentBackBufferIndex( void);
private:
    IDXGISwapChain1 *Handle = nullptr;
    D3D12Factory *Factory = nullptr;
    D3D12Surface *Surface = nullptr;
    D3D12Queue *Queue = nullptr;
};
