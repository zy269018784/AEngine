#pragma once
#include "RHIObjects/Window/RHIWindow.h"
#include <D3D12_Includes.h>
class D3D12PhysicalDevice;
class D3D12Device;
class D3D12Surface;
class D3D12CommandBuffer;
class D3D12SwapChain;
class D3D12Factory;
class D3D12Window : public RHIWindow {
public:
    D3D12Window() = default;
    D3D12Window(D3D12PhysicalDevice* InPhysicalDevice, D3D12Device* InDevice, D3D12Surface* InSurface);
    ~D3D12Window();
    void CreateFactory();
    void CreateSwapChain();
    void CreateCommandBuffer();
    virtual void GetExtent(float& x, float& y, float& w, float& h) final override;
    virtual RHICommandBuffer* CurrentGraphicsCommandBuffer() final override;
    virtual void RHIBeginFrame()  final override;
    virtual void RHIEndFrame() final override;
    virtual void RHIBeginRenderPass() final override;
    virtual void RHIEndRenderPass() final override;
    virtual void Draw() final override;
    virtual void WaitDeviceIdle() final override;
    virtual void Resize(float Width, float Height) final override;
private:
    /*
        物理设备
    */
    D3D12PhysicalDevice* PhysicalDevice = nullptr;
    /*
        逻辑设备
    */
    D3D12Device* Device = nullptr;
    /*
        Surface
    */
    D3D12Surface* Surface;

    std::vector<D3D12CommandBuffer*>	GraphicsCommandBuffers;
public:
    D3D12SwapChain *SwapChain = nullptr;
    ID3D12DescriptorHeap *RTVHeap = nullptr;
    ID3D12Resource* RenderTargets[2];
    SIZE_T rtvDescriptorSize;
    D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;
    D3D12Factory *Factory = nullptr;
    uint32_t g_FrameIndex = 0;
};