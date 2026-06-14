#pragma once

class D3D12Device
{
public:
    ID3D12Device* GetHandle() const;
private:
    ID3D12Device* Handle = nullptr;
};



