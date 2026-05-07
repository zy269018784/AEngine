#pragma once
#include "RHI/RHIObjects/Pipeline/RHIRayTracingPipeline.h"
#include "VulkanRHI/VulkanObjects/Pipeline/VulkanPipeline.h"
#include <vector>
class VulkanDevice;
class VulkanRayTracingPipeline : public RHIRayTracingPipeline, public VulkanPipeline
{
public:
	VulkanRayTracingPipeline(VulkanDevice* InDevice = nullptr);
	~VulkanRayTracingPipeline();
public:
	virtual void Create() final override;
private:
	VkRayTracingPipelineCreateInfoKHR CreateInfos = {};
	std::vector<VkRayTracingShaderGroupCreateInfoKHR> ShaderGroupCreateInfos;
	VkPipelineDynamicStateCreateInfo              DynamicState;
};