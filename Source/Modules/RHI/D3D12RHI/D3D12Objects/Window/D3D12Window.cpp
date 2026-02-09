#include  "D3D12Window.h"
#include "D3D12Objects/SwapChain/D3D12SwapChain.h"
#include "D3D12Objects/Instance/D3D12Instance.h"
#include "D3D12Objects/Device/D3D12Device.h"
#include "D3D12Objects/Surface/D3D12Surface.h"
#include "D3D12Objects/FrameBuffer/D3D12FrameBuffer.h"
#include "D3D12Objects/CommandBuffer/D3D12CommandBuffer.h"
#include "D3D12Objects/CommandBuffer/D3D12CommandPool.h"
#include "D3D12Objects/PhysicalDevice/D3D12PhysicalDevice.h"
#include "D3D12Objects/Factory/D3D12Factory.h"
#include "D3D12Objects/Queue/D3D12Queue.h"

D3D12Window::D3D12Window(D3D12PhysicalDevice* InPhysicalDevice, D3D12Device* InDevice, D3D12Surface* InSurface)
    : PhysicalDevice(InPhysicalDevice), Device(InDevice), Surface(InSurface)
{
    // 创建RTV堆
    D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
    rtvHeapDesc.NumDescriptors = 2;
    rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    if (FAILED(Device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&RTVHeap)))) {
        return;
    }
}

D3D12Window::~D3D12Window()
{

}

void D3D12Window::GetExtent(float& x, float& y, float& w, float& h)
{

}

void D3D12Window::CreateFactory()
{
    Factory = new D3D12Factory();
}

void D3D12Window::CreateSwapChain()
{
    D3D12Queue *Queue = Device->Queues[0];
    SwapChain = new D3D12SwapChain(Factory, Queue, Surface);

    // 创建RTV
    SIZE_T rtvDescriptorSize = Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = RTVHeap->GetCPUDescriptorHandleForHeapStart();

    for (UINT i = 0; i < 2; i++) {
        if (FAILED(SwapChain->GetBuffer(i, IID_PPV_ARGS(&RenderTargets[i])))) {

        }
        Device->CreateRenderTargetView(RenderTargets[i], nullptr, rtvHandle);
        rtvHandle.ptr += rtvDescriptorSize;
    }
}

void D3D12Window::CreateCommandBuffer()
{
    auto pCB = Device->CreateCommandBuffer(Device->CommandPools[0]);
    GraphicsCommandBuffers.emplace_back(pCB);
}

RHICommandBuffer* D3D12Window::CurrentGraphicsCommandBuffer()
{
    return GraphicsCommandBuffers[0];
}

void D3D12Window::RHIBeginFrame()
{
    // 重置命令
    auto CommandPool = Device->CommandPools[0]->GetHandle();
   // CommandPool->Reset();
   // GraphicsCommandBuffers[0]->GetHandle()->Reset(CommandPool, g_PipelineState.Get());mmandBuffers[0]->GetHandle()->ResourceBarrier(1, &barrier);

    // 资源屏障：Present -> Render Target
    D3D12_RESOURCE_BARRIER barrier = {};
    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Transition.pResource = RenderTargets[g_FrameIndex];
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    GraphicsCommandBuffers[0]->ResourceBarrier(1, &barrier);
}

void D3D12Window::RHIEndFrame()
{
#if 1
    D3D12_RESOURCE_BARRIER barrier = {};
    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Transition.pResource = RenderTargets[g_FrameIndex];
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

    // 资源屏障：Render Target -> Present
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
    GraphicsCommandBuffers[0]->ResourceBarrier(1, &barrier);
#endif
    GraphicsCommandBuffers[0]->Close();
    ID3D12CommandList* CmdLists[] = { GraphicsCommandBuffers[0]->GetHandle() };
    Device->Queues[0]->ExecuteCommandLists(1, CmdLists);
    // 呈现
    SwapChain->Present(1, 0);
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

void D3D12Window::Resize(float Width, float Height)
{

}