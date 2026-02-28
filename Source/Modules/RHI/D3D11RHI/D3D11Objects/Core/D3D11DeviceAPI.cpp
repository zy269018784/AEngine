#include "D3D11Objects/Device/D3D11Device.h"


HRESULT D3D11Device::CreateTexture2D(const D3D11_TEXTURE2D_DESC *pDesc, const D3D11_SUBRESOURCE_DATA *pInitialData, ID3D11Texture2D **ppTexture2D)
{
    return Handle->CreateTexture2D(pDesc, pInitialData, ppTexture2D);
}