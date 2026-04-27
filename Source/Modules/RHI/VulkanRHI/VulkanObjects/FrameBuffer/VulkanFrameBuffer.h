#pragma once
#include "Vulkan.h"
#include "RHIObjects/FrameBuffer/RHIFrameBuffer.h"
#include "RHIObjects/FrameBuffer/RHIColorAttachment.h"
#include "RHIObjects/FrameBuffer/RHIDepthAttachment.h"
#include <cstdint>
#include <vector>

class VulkanDevice;
class VulkanRenderPass;
class VulkanFrameBuffer;
class VulkanAttachment;
class RHIColorAttachment;
class RHIDepthAttachment;
class VulkanFrameBuffer : public RHIFrameBuffer
{
public:
	VulkanFrameBuffer(VulkanDevice* InDevice, VulkanRenderPass *InRenderPass, VkExtent2D SwapChainExtent,
		std::vector<RHIColorAttachment *> &InColorAttachments, std::vector<RHIDepthAttachment *> &InDepthAttachments);
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