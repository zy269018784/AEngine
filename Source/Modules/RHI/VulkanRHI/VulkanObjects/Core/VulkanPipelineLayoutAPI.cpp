#include "VulkanObjects/Pipeline/VulkanPipelineLayout.h"

void VulkanPipelineLayout::DestroyPipelineLayout(const VkAllocationCallbacks* Allocator)
{
	Device->DestroyPipelineLayout(Handle, nullptr);
}