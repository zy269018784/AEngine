#pragma once
#include "VulkanRHI/Vulkan.h"
#include "RHI/RHIObjects/FrameBuffer/RHIFrameBuffer.h"
#include <vector>

class VulkanDevice;
class VulkanRenderPass;
class VulkanFrameBuffer;
class RHIAttachment;
class VulkanFrameBuffer : public RHIFrameBuffer
{
public:
	VulkanFrameBuffer(VulkanDevice* InDevice, VulkanRenderPass *InRenderPass, VkExtent2D SwapChainExtent,
		std::vector<RHIAttachment *> &InColorAttachments, std::vector<RHIAttachment *> &InDepthAttachments);
	~VulkanFrameBuffer();
	VkFramebuffer GetHandle() const;
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