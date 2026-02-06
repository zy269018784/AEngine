#pragma once
#include "Vulkan.h"
#include "RHIObjects/FrameBuffer/RHIFrameBuffer.h"
#include <cstdint>
#include <vector>

class VulkanDevice;
class VulkanRenderPass;
class VulkanFrameBuffer;
class VulkanAttachment;
class VulkanFrameBuffer : public RHIFrameBuffer
{
public:
	VulkanFrameBuffer(VulkanDevice* InDevice, VulkanRenderPass *InRenderPass, VkExtent2D SwapChainExtent, VkImageView ImageView, std::vector<VulkanAttachment> *InAttachments);
	~VulkanFrameBuffer();
	VkFramebuffer GetHandle();
	void CreateDepthBuffer(std::uint32_t Width, std::uint32_t Height);
private:
	/*
		Vulkan API Wrapper
	*/
	VkResult CreateFramebuffer(const VkFramebufferCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator);
	void DestroyFramebuffer(const VkAllocationCallbacks* Allocator);
private:
	VkFramebuffer Handle = VK_NULL_HANDLE;
	VulkanDevice* Device = nullptr;
	VkImageView ImageViewDepthBuffer;
	VkImage depthImage;
	VkDeviceMemory depthImageMemory;
};