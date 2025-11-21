#pragma once
#include "Vulkan.h"
#include "VulkanObjects/Device/VulkanDevice.h"
#include "VulkanObjects/Descriptor/VulkanDescriptorPool.h"
#include "VulkanObjects/Descriptor/VulkanDescriptorSetLayout.h"
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