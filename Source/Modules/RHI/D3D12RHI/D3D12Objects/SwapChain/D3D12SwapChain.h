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
    IDXGISwapChain3* GetHandle3() const;
public:
    /*
     * D3D12 API Wrapper
     */
    UINT GetCurrentBackBufferIndex( void);

    HRESULT Present(UINT SyncInterval, UINT Flags);

    HRESULT GetBuffer(UINT Buffer, REFIID riid, void **ppSurface);
private:
public:
    IDXGISwapChain1 *Handle = nullptr;
    IDXGISwapChain3 *Handle3 = nullptr;
    ID3D12DescriptorHeap *RTVHeap = nullptr;
    D3D12Factory *Factory = nullptr;
    D3D12Surface *Surface = nullptr;
    D3D12Queue *Queue = nullptr;
};
