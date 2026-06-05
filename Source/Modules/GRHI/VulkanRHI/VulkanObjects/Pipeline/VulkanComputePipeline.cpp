#include "VulkanRHI/VulkanObjects/Pipeline/VulkanComputePipeline.h"

VulkanComputePipeline::VulkanComputePipeline(VulkanDevice* InDevice)
    : VulkanPipeline(InDevice)
{
    BindPoint = VK_PIPELINE_BIND_POINT_COMPUTE;
}

VulkanComputePipeline::~VulkanComputePipeline() {

}

void VulkanComputePipeline::Create()
{}