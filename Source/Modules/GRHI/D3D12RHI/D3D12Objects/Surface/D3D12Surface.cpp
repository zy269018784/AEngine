#include "D3D12Surface.h"

D3D12Surface::D3D12Surface(HINSTANCE Hinstance, HWND InHwnd)
    : Hwnd(InHwnd)
{
#if 0
    RECT clientRect;
    GetClientRect(Hwnd, &clientRect);

    Width = clientRect.right - clientRect.left;
    Height = clientRect.bottom - clientRect.top;
#endif
    Width  = 800;
    Height = 600;

    Format = DXGI_FORMAT_R8G8B8A8_UNORM;
}

D3D12Surface::~D3D12Surface()
{

}