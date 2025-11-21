#include "VulkanObjects/Pipeline/VulkanPipelineLayout.h"

VulkanPipelineLayout::VulkanPipelineLayout(VulkanDevice* InDevice)
	: Device(InDevice)
{

}

VulkanPipelineLayout::~VulkanPipelineLayout()
{
	DestroyPipelineLayout(nullptr);
}
