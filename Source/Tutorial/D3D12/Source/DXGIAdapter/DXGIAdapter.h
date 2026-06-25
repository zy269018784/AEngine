#pragma once
#include <dxgi.h>
class DXGIAdapter
{
public:
    IDXGIAdapter* GetHandle() const;
private:
    IDXGIAdapter* Handle = nullptr;
};


