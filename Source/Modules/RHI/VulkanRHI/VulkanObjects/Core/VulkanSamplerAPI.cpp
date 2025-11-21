#include "VulkanObjects/Resource/VulkanSampler.h"

VkResult VulkanSampler::CreateSampler(const VkSamplerCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator)
{
	return Device->CreateSampler(CreateInfo, Allocator, &Handle);
}

void VulkanSampler::DestroySampler(const VkAllocationCallbacks* Allocator)
{
	Device->DestroySampler(Handle, Allocator);
}