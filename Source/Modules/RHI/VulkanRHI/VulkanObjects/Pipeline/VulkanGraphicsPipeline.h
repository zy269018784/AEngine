#pragma once
#include <VulkanObjects/Pipeline/VulkanPipeline.h>
#include "VulkanObjects/Device/VulkanDevice.h"
#include "VulkanObjects/RenderPass/VulkanRenderPass.h"
#include "RHIObjects/Pipeline/RHIGraphicsPipeline.h"
#include "RHIObjects/Shader/RHIShader.h"

class VulkanGraphicsPipeline : public RHIGraphicsPipeline, public VulkanPipeline
{
public:
	VulkanGraphicsPipeline(VulkanDevice * InDevice = nullptr, VulkanRenderPass *RenderPass = nullptr);
	~VulkanGraphicsPipeline();
public:
	virtual void Create() final override;
};