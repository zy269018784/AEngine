#pragma once
#include "Vulkan.h"

class VulkanDescriptorPool;
class VulkanDescriptorSetLayout;
class VulkanDevice;
class VulkanDescriptorSet
{
public:
	VulkanDescriptorSet(VulkanDevice *Device, VulkanDescriptorPool* InDescriptorPool, VulkanDescriptorSetLayout * DescriptorSetLayout);
	~VulkanDescriptorSet();
	VkDescriptorSet GetHandle();
private:
	/*
		Vulkan API Wrapper
	*/
	VkResult AllocateDescriptorSets(const VkDescriptorSetAllocateInfo* AllocateInfo);
	VkResult FreeDescriptorSets();
private:
	VulkanDevice* Device;
	VkDescriptorSet Handle;
	VulkanDescriptorPool* DescriptorPool;
};