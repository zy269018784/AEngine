#include "D3D12Device.h"
#include <iostream>
D3D12Device::D3D12Device()
{
    // 创建设备
    if (FAILED(D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&Handle))))
    {
        std::cerr << "Failed to create device" << std::endl;
    }
}

D3D12Device::~D3D12Device()
{
	delete Handle;
}

ID3D12Device* D3D12Device::GetHandle()
{
    return Handle;
}