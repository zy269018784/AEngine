#pragma once
#include "Vulkan.h"
#include "RHIObjects/FrameBuffer/RHIFrameBuffer.h"
#include "VulkanObjects/FrameBuffer/VulkanFrameBuffer.h"
#include "VulkanObjects/RenderPass/VulkanRenderPass.h"
class VulkanDevice;
class VulkanRenderPass;
class VulkanFrameBuffer : public RHIFrameBuffer
{
public:
	VulkanFrameBuffer(VulkanDevice* InDevice, VulkanRenderPass *InRenderPass, VkExtent2D SwapChainExtent, VkImageView ImageView);
	~VulkanFrameBuffer();
	VkFramebuffer GetHandle();
private:
	/*
		Vulkan API Wrapper
	*/
	VkResult CreateFramebuffer(const VkFramebufferCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator);
	void DestroyFramebuffer(const VkAllocationCallbacks* Allocator);
private:
	VkFramebuffer Handle = VK_NULL_HANDLE;
	VulkanDevice* Device = nullptr;
};