#pragma once
#include "VulkanRHI/Vulkan.h"
#include <cstdint>

class VulkanQueueFamily;
class VulkanDevice;
class VulkanCommandBuffer;
class VulkanQueue
{
public:
	VulkanQueue();
	//VulkanQueue(VulkanQueueFamily* InQueueFamily, VkQueue InQueue);
	VulkanQueue(VulkanDevice* InDevice, VulkanQueueFamily* InQueueFamily, std::uint32_t InQueueIndex);
	~VulkanQueue();
	VkQueue GetHandle();
	void EndCommandBuffer(VulkanCommandBuffer* CommandBuffer);
public:
	/*
		Vulkan API Wrapper
	*/
	VkResult QueueSubmit(std::uint32_t SubmitCount, const VkSubmitInfo* Submits, VkFence Fence);
	VkResult QueueSubmit2(std::uint32_t SubmitCount,const VkSubmitInfo2* Submits, VkFence Fence);
	VkResult QueueWaitIdle();
private:
	VulkanDevice* Device = nullptr;
	VkQueue Handle = VK_NULL_HANDLE;
	VulkanQueueFamily* QueueFamily = nullptr;
	std::uint32_t QueueIndex;
};
