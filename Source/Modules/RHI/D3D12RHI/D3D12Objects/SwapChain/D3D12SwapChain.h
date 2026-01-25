#pragma once
#include <dxgi1_2.h>
class D3D12Factory;
class D3D12Queue;
class D3D12SwapChain
{
public:
    D3D12SwapChain(D3D12Factory *InFactory, D3D12Queue *InQueue, HWND InHwnd);
    ~D3D12SwapChain();
    IDXGISwapChain1 GetHandle() const;
private:
    IDXGISwapChain1 *Handle = nullptr;
    D3D12Factory *Factory = nullptr;
};
