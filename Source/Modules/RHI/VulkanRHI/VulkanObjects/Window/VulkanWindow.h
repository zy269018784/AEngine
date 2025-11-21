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
class VulkanWindow : public RHIWindow
{
public:
	VulkanWindow() = default;
	VulkanWindow(VulkanPhysicalDevice* InPhysicalDevice, VulkanDevice* InDevice, VulkanSurface* InSurface);
	~VulkanWindow();
#if 0
	void CreateSurface(VulkanInstance* Instance);
	void QuerySurface();
#endif
	void Resize(float Width, float Height);
	void CreateSwapChain();
	void CreateRenderPass();
	void CreateFrameBuffer();
	void CreateCommandBuffer();
	void CreateSyncObject();
	virtual void GetExtent(float& x, float& y, float& w, float& h) final override;
	virtual RHICommandBuffer* CurrentGraphicsCommandBuffer() final override;
	virtual void RHIBeginFrame()  final override;
	virtual void RHIEndFrame() final override;
	virtual void RHIBeginRenderPass() final override;
	virtual void RHIEndRenderPass() final override;
	virtual void Draw() final override;
	virtual void WaitDeviceIdle() final override;
public:
	//VulkanRenderPass* RenderPass;
	/*
		交换链
	*/
	VulkanSwapChain*					SwapChain;
private:
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
	/*
		同步帧
	*/
	std::vector<VulkanFrame*>			Frames;						// SwapChainImages.size()	
	/*
		帧缓冲
	*/
	//std::vector<VulkanFrameBuffer*>		FrameBuffers;				// SwapChainImages.size()
	/*
		用于图像的command buffer
	*/
	std::vector<VulkanCommandBuffer*>	GraphicsCommandBuffers;		// SwapChainImages.size()	
	/*
		用于计算的command buffer
	*/	
	VulkanCommandBuffer*				ComputeCommandBuffer;		// 1个	
	/*
		CurrentImageIndex: [0, 2]
	*/
	std::uint32_t					CurrentImageIndex = 0;
	/*
		当前帧编号
		FrameIndex: [0, 1]
	*/
	std::uint32_t					FrameIndex = 0;
};