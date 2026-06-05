#pragma once
#include "VulkanRHI/Vulkan.h"
#include "VulkanRHI/VulkanObjects/Device/VulkanDevice.h"
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