#include  "D3D12Window.h"
D3D12Window::D3D12Window(D3D12PhysicalDevice* InPhysicalDevice, D3D12Device* InDevice, D3D12Surface* InSurface)
    : PhysicalDevice(InPhysicalDevice), Device(InDevice), Surface(InSurface)
{

}

D3D12Window::~D3D12Window()
{

}

void D3D12Window::GetExtent(float& x, float& y, float& w, float& h)
{


}

RHICommandBuffer* D3D12Window::CurrentGraphicsCommandBuffer()
{
    return nullptr;
}

void D3D12Window::RHIBeginFrame()
{

}

void D3D12Window::RHIEndFrame()
{

}

void D3D12Window::RHIBeginRenderPass()
{

}

void D3D12Window::RHIEndRenderPass()
{

}

void D3D12Window::Draw()
{

}

void D3D12Window::WaitDeviceIdle()
{


}
