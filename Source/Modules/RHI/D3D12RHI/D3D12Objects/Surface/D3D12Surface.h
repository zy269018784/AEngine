#pragma once
#include "D3D12_Includes.h"

class D3D12Surface
{
public:
    D3D12Surface(HINSTANCE Hinstance, HWND InHwnd);
    ~D3D12Surface();
public:
    int Width;
    int Height;
    DXGI_FORMAT Format;
    HWND Hwnd;
};