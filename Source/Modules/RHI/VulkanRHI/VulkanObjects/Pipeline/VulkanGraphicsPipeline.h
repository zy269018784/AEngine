#pragma once
#include "RHI/RHIObjects/Pipeline/RHIGraphicsPipeline.h"
#include "VulkanRHI/VulkanObjects/Pipeline/VulkanPipeline.h"
class VulkanDevice;
class VulkanRenderPass;
class VulkanGraphicsPipeline : public RHIGraphicsPipeline, public VulkanPipeline
{
public:
	VulkanGraphicsPipeline(VulkanDevice * InDevice = nullptr, VulkanRenderPass *RenderPass = nullptr);
	~VulkanGraphicsPipeline();
public:
	virtual void Create() final override;
};