#include "VulkanObjects/Descriptor/VulkanDescriptorPool.h"

VkResult VulkanDescriptorPool::AllocateDescriptorSets(const VkDescriptorSetAllocateInfo* AllocateInfo, VkDescriptorSet* DescriptorSets)
{
	//VkDescriptorSetAllocateInfo AllocateInfo2 = *AllocateInfo;
	//AllocateInfo->descriptorPool = Handle;
	return Device->AllocateDescriptorSets(AllocateInfo, DescriptorSets);
}

VkResult VulkanDescriptorPool::FreeDescriptorSets(uint32_t DescriptorSetCount, const VkDescriptorSet* DescriptorSets)
{
	return Device->FreeDescriptorSets(Handle, DescriptorSetCount, DescriptorSets);
}

VkResult VulkanDescriptorPool::CreateDescriptorPool(const VkDescriptorPoolCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator)
{
	return Device->CreateDescriptorPool(CreateInfo, Allocator, &Handle);
}

void VulkanDescriptorPool::DestroyDescriptorPool(const VkAllocationCallbacks* Allocator)
{
	Device->DestroyDescriptorPool(Handle, Allocator);
}