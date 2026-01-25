#pragma once
#include "D3D12_Includes.h"

class D3D12Factory
{
public:
    D3D12Factory();
    ~D3D12Factory();
    IDXGIFactory4 *GetHandle() const;
    HRESULT CreateSwapChainForHwnd(
            /* [annotation][in] */
            _In_  IUnknown *pDevice,
            /* [annotation][in] */
            _In_  HWND hWnd,
            /* [annotation][in] */
            _In_  const DXGI_SWAP_CHAIN_DESC1 *pDesc,
            /* [annotation][in] */
            _In_opt_  const DXGI_SWAP_CHAIN_FULLSCREEN_DESC *pFullscreenDesc,
            /* [annotation][in] */
            _In_opt_  IDXGIOutput *pRestrictToOutput,
            /* [annotation][out] */
            _COM_Outptr_  IDXGISwapChain1 **ppSwapChain);
private:
    IDXGIFactory4 *Handle;
};

