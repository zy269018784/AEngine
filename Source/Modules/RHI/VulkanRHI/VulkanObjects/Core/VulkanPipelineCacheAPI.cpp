#include "VulkanObjects/Pipeline/VulkanPipelineCache.h"

void VulkanPipelineCache::DestroyPipelineCache(const VkAllocationCallbacks* Allocator)
{
	Device->DestroyPipelineCache(Handle, nullptr);
}