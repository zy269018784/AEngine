#include "VulkanObjects/Pipeline/VulkanPipelineCache.h"
VulkanPipelineCache::VulkanPipelineCache()
	: Device(nullptr), Handle(VK_NULL_HANDLE)
{

}
VulkanPipelineCache::VulkanPipelineCache(VulkanDevice* InDevice)
	: Device(InDevice), Handle(VK_NULL_HANDLE)
{

}

VulkanPipelineCache::~VulkanPipelineCache()
{
	DestroyPipelineCache(nullptr);
}
