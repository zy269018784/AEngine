#include "D3D11Device.h"

D3D11Device::D3D11Device() {

}

D3D11Device::~D3D11Device() {

}

ID3D11Device* D3D11Device::GetHandle()
{
    return Handle;
}

D3D11CommandBuffer* D3D11Device::CreateCommandBuffer(D3D11CommandPool* CommandPool)
{
    return nullptr;
}

void D3D11Device::CreateCommandPool()
{

}

void D3D11Device::CreateQueue()
{

}
