#pragma once
#include "RHI/RHIObjects/Pipeline/RHIRayTracingPipeline.h"
#include "VulkanRHI/VulkanObjects/Pipeline/VulkanPipeline.h"
class VulkanDevice;
class VulkanRayTracingPipeline : public RHIRayTracingPipeline, public VulkanPipeline
{
public:
	VulkanRayTracingPipeline(VulkanDevice* InDevice = nullptr);
	~VulkanRayTracingPipeline();
public:
	virtual void Create() final override;
};