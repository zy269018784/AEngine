#pragma once
#include "RHIObjects/Window/RHIWindow.h"
#include "D3D12Objects/Instance/D3D12Instance.h"
#include "D3D12Objects/Device/D3D12Device.h"
#include "D3D12Objects/Surface/D3D12Surface.h"
#include "D3D12Objects/FrameBuffer/D3D12FrameBuffer.h"
#include "D3D12Objects/CommandBuffer/D3D12CommandBuffer.h"
#include "D3D12Objects/PhysicalDevice/D3D12PhysicalDevice.h"

class D3D12Window : public RHIWindow {
public:
    D3D12Window() = default;
    D3D12Window(D3D12PhysicalDevice* InPhysicalDevice, D3D12Device* InDevice, D3D12Surface* InSurface);
    ~D3D12Window();
    virtual void GetExtent(float& x, float& y, float& w, float& h) final override;
    virtual RHICommandBuffer* CurrentGraphicsCommandBuffer() final override;
    virtual void RHIBeginFrame()  final override;
    virtual void RHIEndFrame() final override;
    virtual void RHIBeginRenderPass() final override;
    virtual void RHIEndRenderPass() final override;
    virtual void Draw() final override;
    virtual void WaitDeviceIdle() final override;
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
};