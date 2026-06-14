#include "D3D12Device.h"


ID3D12Device* D3D12Device::GetHandle() const
{
    return Handle;
}