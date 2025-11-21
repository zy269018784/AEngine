#pragma once
#include "Vulkan.h"
#include "VulkanObjects/Device/VulkanDevice.h"
class VulkanPipelineLayout
{
public:
	VulkanPipelineLayout(VulkanDevice* InDevice = nullptr);
	~VulkanPipelineLayout();
public:
	/*
		Vulkan API Wrapper
	*/
	void DestroyPipelineLayout(const VkAllocationCallbacks* Allocator);
private:
	VkPipelineLayout Handle;
	VulkanDevice* Device;
};