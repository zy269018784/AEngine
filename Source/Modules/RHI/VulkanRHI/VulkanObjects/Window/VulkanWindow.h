#pragma once
#include "RHIObjects/Window/RHIWindow.h"
#include "VulkanObjects/Instance/VulkanInstance.h"
#include "VulkanObjects/Device/VulkanDevice.h"
#include "VulkanObjects/Surface/VulkanSurface.h"
#include "VulkanObjects/SwapChain/VulkanSwapChain.h"
#include "VulkanObjects/FrameBuffer/VulkanFrameBuffer.h"
#include "VulkanObjects/CommandBuffer/VulkanCommandBuffer.h"
#include "VulkanObjects/PhysicalDevice/VulkanPhysicalDevice.h"
#include "VulkanObjects/Window/VulkanFrame.h"
#include <vector>

class VulkanSwapChainRenderTarget;

class VulkanWindow : public RHIWindow
{
public:
	VulkanWindow() = default;
	VulkanWindow(VulkanPhysicalDevice* InPhysicalDevice, VulkanDevice* InDevice, VulkanSurface* InSurface);
	~VulkanWindow();
	virtual void Resize(float Width, float Height) final override;
	virtual void GetExtent(float& x, float& y, float& w, float& h) final override;
	virtual RHICommandBuffer* CurrentGraphicsCommandBuffer() final override;
	virtual void RHIBeginFrame()  final override;
	virtual void RHIEndFrame() final override;
	virtual void RHIBeginRenderPass() final override;
	virtual void RHIEndRenderPass() final override;
	virtual void Draw() final override;
	virtual void WaitDeviceIdle() final override;
public:
	/*
		物理设备
	*/
	VulkanPhysicalDevice* PhysicalDevice = nullptr;
	/*
		逻辑设备
	*/
	VulkanDevice* Device = nullptr;
	/*
		Surface
	*/
	VulkanSurface* Surface;
public:
	VulkanSwapChainRenderTarget *RenderTarget = nullptr;
};