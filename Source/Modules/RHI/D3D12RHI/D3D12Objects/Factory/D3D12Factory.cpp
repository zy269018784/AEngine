#include "D3D12Factory.h"


D3D12Factory::D3D12Factory()
{
    CreateDXGIFactory1(IID_PPV_ARGS(&Handle));
}

D3D12Factory::~D3D12Factory()
{

}

IDXGIFactory4 *D3D12Factory::GetHandle() const
{
    return Handle;
}

HRESULT D3D12Factory::CreateSwapChainForHwnd(
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
            _COM_Outptr_  IDXGISwapChain1 **ppSwapChain) {
    return Handle->CreateSwapChainForHwnd(pDevice, HWND, pDesc, nullptr, pFullscreenDesc, ppSwapChain);
}