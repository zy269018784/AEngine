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
private:
	VkPipelineRasterizationStateCreateInfo			RasterizationStateCreateInfo{};
	VkPipelineDepthStencilStateCreateInfo			DepthStencilStateCreateInfo{};
	VkPipelineMultisampleStateCreateInfo			MultisampleStateCreateInfo{};
	VkPipelineInputAssemblyStateCreateInfo			InputAssemblyStateCreateInfo{};
	std::vector<VkVertexInputBindingDescription>	VertexInputBindingDescriptions;
	std::vector<VkVertexInputAttributeDescription>	VkVertexInputAttributeDescriptions;
	VkPipelineVertexInputStateCreateInfo			VertexInputStateCreateInfo{};
	VkPipelineColorBlendAttachmentState				ColorBlendAttachment{};
	VkPipelineViewportStateCreateInfo				ViewportStateCreateInfo{};
	VkPipelineTessellationStateCreateInfo			TessellationStateCreateInfo{};
	VkPipelineColorBlendStateCreateInfo				ColorBlendStateCreateInfo{};
	VkPipelineDynamicStateCreateInfo				DynamicStateCreateInfo{};
	VkGraphicsPipelineCreateInfo					CreateInfo{};
};