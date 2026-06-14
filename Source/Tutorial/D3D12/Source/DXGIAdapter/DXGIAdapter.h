#pragma once

class DXGIAdapter
{
public:
    IDXGIAdapter* GetHandle() const;
private:
    IDXGIAdapter* Handle = nullptr;
};


