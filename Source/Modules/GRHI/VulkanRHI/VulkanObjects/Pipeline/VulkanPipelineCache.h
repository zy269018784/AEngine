#pragma once
#include "VulkanRHI/Vulkan.h"
#include "VulkanRHI/VulkanObjects/Device/VulkanDevice.h"

class VulkanPipelineCache
{
public:
	VulkanPipelineCache();
	VulkanPipelineCache(VulkanDevice* InDevice);
	~VulkanPipelineCache();
public:
	/*
		Vulkan API Wrapper
	*/
	void DestroyPipelineCache(const VkAllocationCallbacks* Allocator);
private:
	VkPipelineCache Handle = VK_NULL_HANDLE;
	VulkanDevice* Device;
};