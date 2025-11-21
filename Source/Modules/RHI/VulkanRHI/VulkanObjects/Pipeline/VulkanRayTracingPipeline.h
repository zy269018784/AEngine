#pragma once
#include "VulkanObjects/Pipeline/VulkanPipeline.h"
#include "VulkanObjects/Device/VulkanDevice.h"
#include "VulkanObjects/RenderPass/VulkanRenderPass.h"
#include "RHIObjects/Pipeline/RHIRayTracingPipeline.h"
#include "RHIObjects/Shader/RHIShader.h"

class VulkanRayTracingPipeline : public RHIRayTracingPipeline, public VulkanPipeline
{
public:
	VulkanRayTracingPipeline(VulkanDevice* InDevice = nullptr);
	~VulkanRayTracingPipeline() = default;
public:
	virtual void Create() final override;
};