#pragma once
#include "Vulkan.h"
#include "VulkanObjects/Device/VulkanDevice.h"
#include "VulkanObjects/Descriptor/VulkanDescriptorSetLayout.h"
#include "RHIObjects/Shader/RHIShaderResourceBindings.h"

class VulkanDescriptorPool
{
public:				
	VulkanDescriptorPool() {};
	VulkanDescriptorPool(VulkanDevice* InDevice, VulkanDescriptorSetLayout* Layout, std::uint32_t MaxSetsAllocations = 1);
	VulkanDescriptorPool(VulkanDevice* InDevice, RHIShaderResourceBindings *SRB);
	~VulkanDescriptorPool();
	VkDescriptorPool GetHandle();
public:
	/*
		Vulkan API Wrapper
	*/
	VkResult AllocateDescriptorSets(const VkDescriptorSetAllocateInfo* AllocateInfo, VkDescriptorSet* DescriptorSets);
	VkResult FreeDescriptorSets(uint32_t DescriptorSetCount, const VkDescriptorSet* DescriptorSets);
	VkResult CreateDescriptorPool(const VkDescriptorPoolCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator);
	void DestroyDescriptorPool(const VkAllocationCallbacks* Allocator);
private:
	VkDescriptorPool Handle;
	VulkanDevice *Device;
	std::uint32_t MaxDescriptorSets;
};