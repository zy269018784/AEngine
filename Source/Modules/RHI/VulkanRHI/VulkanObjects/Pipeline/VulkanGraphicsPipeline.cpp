#include "VulkanObjects/Pipeline/VulkanGraphicsPipeline.h"
#include "VulkanObjects/RenderPass/VulkanRenderPass.h"
#include "VulkanObjects/Shader/VulkanShader.h"
#include "VulkanObjects/Core/VulkanCore.h"

#include "VulkanObjects/Shader/VulkanShaderResourceBindings.h"
#include <iostream>
#include <stdexcept>
VulkanGraphicsPipeline::VulkanGraphicsPipeline(VulkanDevice* InDevice, VulkanRenderPass* InRenderPass)
	: VulkanPipeline(InDevice)
{
	RenderPass = InRenderPass;
	BindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
}

VulkanGraphicsPipeline::~VulkanGraphicsPipeline()
{
	std::cout << "~VulkanGraphicsPipeline()" << std::endl;
}

void VulkanGraphicsPipeline::Create()
{
	/*
		Rasterization
	*/
	VkPipelineRasterizationStateCreateInfo	RasterizationStateCreateInfo{};
	RasterizationStateCreateInfo.sType						= VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	RasterizationStateCreateInfo.polygonMode				= ToVkPolygonMode(PolygonMode);
	RasterizationStateCreateInfo.cullMode					= ToVkCullModeFlags(CullMode);
	RasterizationStateCreateInfo.frontFace					= ToVkFrontFace(FrontFace);
	RasterizationStateCreateInfo.lineWidth					= LineWidth;
	RasterizationStateCreateInfo.depthBiasEnable			= VK_FALSE;
	RasterizationStateCreateInfo.depthClampEnable			= VK_FALSE;
	RasterizationStateCreateInfo.rasterizerDiscardEnable	= VK_FALSE;

	/*
		Depth Test && Stencil Test
	*/
	VkPipelineDepthStencilStateCreateInfo	DepthStencilStateCreateInfo{};
	DepthStencilStateCreateInfo.sType					= VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	DepthStencilStateCreateInfo.depthTestEnable			= DepthTestEnable;
	DepthStencilStateCreateInfo.depthWriteEnable		= DepthWriteEnable;
	DepthStencilStateCreateInfo.depthCompareOp			= ToVkCompareOp(DepthCompareOp);
	DepthStencilStateCreateInfo.depthBoundsTestEnable	= VK_FALSE;
	DepthStencilStateCreateInfo.stencilTestEnable		= VK_FALSE;
	DepthStencilStateCreateInfo.back;
	DepthStencilStateCreateInfo.front;
	DepthStencilStateCreateInfo.minDepthBounds;
	DepthStencilStateCreateInfo.maxDepthBounds;

	/*
		Multisample
	*/
	VkSampleMask SampleMask = { 0xFFFFFFFF };

	VkPipelineMultisampleStateCreateInfo	MultisampleStateCreateInfo{};
	MultisampleStateCreateInfo.sType					= VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	MultisampleStateCreateInfo.rasterizationSamples		= ToVkSampleCountFlagBits(SampleCount);
	MultisampleStateCreateInfo.pSampleMask				= &SampleMask;
	MultisampleStateCreateInfo.sampleShadingEnable		= VK_FALSE;
	MultisampleStateCreateInfo.minSampleShading;
	MultisampleStateCreateInfo.alphaToCoverageEnable	= VK_FALSE;
	MultisampleStateCreateInfo.alphaToOneEnable			= VK_FALSE;

	/*
		Input Assembly
	*/
	VkPipelineInputAssemblyStateCreateInfo InputAssemblyStateCreateInfo{};
	InputAssemblyStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	InputAssemblyStateCreateInfo.topology = ToVkPrimitiveTopology(Topology);

	/*
		Dynamic State
	*/
	VkDynamicState DynamicStates[] = {
		/*
			Depth Test
		*/
		VK_DYNAMIC_STATE_DEPTH_TEST_ENABLE,
		VK_DYNAMIC_STATE_DEPTH_WRITE_ENABLE,
		VK_DYNAMIC_STATE_DEPTH_COMPARE_OP,
		VK_DYNAMIC_STATE_DEPTH_BOUNDS_TEST_ENABLE,
		/*
			Stencil Test
		*/
		VK_DYNAMIC_STATE_STENCIL_TEST_ENABLE,
		VK_DYNAMIC_STATE_STENCIL_OP,
		/*
			Viewport
		*/
		VK_DYNAMIC_STATE_VIEWPORT,
		/*
			Scissor
		*/
		VK_DYNAMIC_STATE_SCISSOR,
		/*
			VK_DYNAMIC_STATE_DEPTH_BOUNDS_TEST_ENABLE specifies that the depthBoundsTestEnable state in VkPipelineDepthStencilStateCreateInfo 
			will be ignored and must be set dynamically with vkCmdSetDepthBoundsTestEnable before any draw call.
		*/
		//VK_DYNAMIC_STATE_DEPTH_BOUNDS_TEST_ENABLE,
	};

	VkPipelineDynamicStateCreateInfo		DynamicStateCreateInfo{};
	DynamicStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	DynamicStateCreateInfo.pDynamicStates = DynamicStates;
	DynamicStateCreateInfo.dynamicStateCount = sizeof(DynamicStates) / sizeof(DynamicStates[0]);

	/*
		Shader
	*/
	std::vector<VkPipelineShaderStageCreateInfo> ShaderStageCreateInfos;
	for (int i = 0; i < Shaders.size(); i++)
	{
		VkPipelineShaderStageCreateInfo			ShaderStageCreateInfo{};
		ShaderStageCreateInfo.sType			= VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		ShaderStageCreateInfo.module		= ((VulkanShader *)Shaders[i])->GetHandle();
		ShaderStageCreateInfo.pName			= "main";
		ShaderStageCreateInfo.stage			= ToVkShaderStageFlagBits(Shaders[i]->Type_);
		ShaderStageCreateInfos.push_back(ShaderStageCreateInfo);
	}

	/*
		Vertex Input
	*/

	/*
		1. Vertex Input Bindings
	*/
	std::vector<VkVertexInputBindingDescription> VertexInputBindingDescriptions;
	for (int i = 0; i < VertexInputLayout.Bindings.size(); i++)
	{
		VkVertexInputBindingDescription VertexInputBindingDescription;
		VertexInputBindingDescription.binding = i;
		VertexInputBindingDescription.stride = VertexInputLayout.Bindings[i].GetStride();
		VertexInputBindingDescription.inputRate = ToVkVertexInputRate(VertexInputLayout.Bindings[i].GetInstanceStepRate());

		std::cout << "binding " << i << " " << "stride " << VertexInputBindingDescription.stride << " " << VertexInputBindingDescription.inputRate << std::endl;
		VertexInputBindingDescriptions.push_back(VertexInputBindingDescription);
	}

	/*
		2. Vertex Input Attributes
	*/
	std::vector<VkVertexInputAttributeDescription> VkVertexInputAttributeDescriptions;
	for (int i = 0; i < VertexInputLayout.Attributes.size(); i++)
	{
		VkVertexInputAttributeDescription VertexInputAttributeDescription;
		VertexInputAttributeDescription.binding = VertexInputLayout.Attributes[i].GetBinding();
		VertexInputAttributeDescription.format = ToVkFormat(VertexInputLayout.Attributes[i].GetFormat());
		VertexInputAttributeDescription.location = VertexInputLayout.Attributes[i].GetLocation();
		VertexInputAttributeDescription.offset = VertexInputLayout.Attributes[i].GetOffset();
		VkVertexInputAttributeDescriptions.push_back(VertexInputAttributeDescription);

		std::cout << "i " << i << " "
			<< "binding " << VertexInputAttributeDescription.binding << " "
			<< "format " << VertexInputAttributeDescription.format << " "
			<< "location " << VertexInputAttributeDescription.location << " "
			<< "offset " << VertexInputAttributeDescription.offset << " "
			<< std::endl;
	}

	/*
		3. Vertex Input State Create Info
	*/
	VkPipelineVertexInputStateCreateInfo	VertexInputStateCreateInfo{};
	VertexInputStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	VertexInputStateCreateInfo.pVertexAttributeDescriptions = VkVertexInputAttributeDescriptions.data();
	VertexInputStateCreateInfo.vertexAttributeDescriptionCount = VkVertexInputAttributeDescriptions.size();
	VertexInputStateCreateInfo.pVertexBindingDescriptions = VertexInputBindingDescriptions.data();
	VertexInputStateCreateInfo.vertexBindingDescriptionCount = VertexInputBindingDescriptions.size();

	/*
		Viewport
	*/
	VkPipelineViewportStateCreateInfo		ViewportStateCreateInfo{};
	ViewportStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	ViewportStateCreateInfo.viewportCount = 1;
	ViewportStateCreateInfo.scissorCount = 1;

	/*
		Tessellation
	*/
	//VkPipelineTessellationStateCreateInfo	TessellationStateCreateInfo{};
	//TessellationStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;

	/*
		Blend
	*/
	VkPipelineColorBlendAttachmentState ColorBlendAttachment{};
	ColorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	ColorBlendAttachment .blendEnable = VK_FALSE;

	VkPipelineColorBlendStateCreateInfo		ColorBlendStateCreateInfo{};
	ColorBlendStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	ColorBlendStateCreateInfo.logicOpEnable = VK_FALSE;
	ColorBlendStateCreateInfo.logicOp = VK_LOGIC_OP_COPY;
	ColorBlendStateCreateInfo.attachmentCount = 1;
	ColorBlendStateCreateInfo.pAttachments = &ColorBlendAttachment;
	ColorBlendStateCreateInfo.blendConstants[0] = 0.0f;
	ColorBlendStateCreateInfo.blendConstants[1] = 0.0f;
	ColorBlendStateCreateInfo.blendConstants[2] = 0.0f;
	ColorBlendStateCreateInfo.blendConstants[3] = 0.0f;

	/*
		PipelineLayout
	*/	
	VkResult ret;
	//if (ShaderResourceBindings)
	{
		
		VkPipelineLayoutCreateInfo LayoutCreateInfo{};
		LayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		LayoutCreateInfo.pushConstantRangeCount = 0; // Or your push constant ranges
		LayoutCreateInfo.pPushConstantRanges = nullptr;
		LayoutCreateInfo.setLayoutCount = 0;
		LayoutCreateInfo.pSetLayouts = nullptr;
		if (ShaderResourceBindings)
		{
			auto DescSetLayout = ((VulkanShaderResourceBindings*)ShaderResourceBindings)->GetDescriptorSetLayout()->GetHandle();
			LayoutCreateInfo.setLayoutCount = 1;
			LayoutCreateInfo.pSetLayouts = &DescSetLayout;
			std::cout << "ShaderResourceBindings is " << LayoutCreateInfo.setLayoutCount << std::endl;
		}
		else {
			std::cout << "ShaderResourceBindings is nullptr ==============" << std::endl;
		}

		ret = Device->CreatePipelineLayout(&LayoutCreateInfo, nullptr, &PipelineLayout);
		if (ret != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create pipeline layout!");
		}
	}

	VkGraphicsPipelineCreateInfo CreateInfo{};
	CreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	CreateInfo.stageCount = ShaderStageCreateInfos.size();
	CreateInfo.pStages = ShaderStageCreateInfos.data();
	CreateInfo.pVertexInputState = &VertexInputStateCreateInfo;
	CreateInfo.pInputAssemblyState = &InputAssemblyStateCreateInfo;
	//CreateInfo.pTessellationState = &TessellationStateCreateInfo;
	CreateInfo.pViewportState = &ViewportStateCreateInfo;
	CreateInfo.pRasterizationState = &RasterizationStateCreateInfo;
	CreateInfo.pMultisampleState = &MultisampleStateCreateInfo;
	CreateInfo.pDepthStencilState = &DepthStencilStateCreateInfo;
	CreateInfo.pColorBlendState = &ColorBlendStateCreateInfo;
	CreateInfo.pDynamicState = &DynamicStateCreateInfo;
	CreateInfo.renderPass = static_cast<VulkanRenderPass *>(RenderPass)->GetHandle();
	CreateInfo.layout = PipelineLayout;
	CreateInfo.basePipelineHandle = VK_NULL_HANDLE;

    ret = Device->CreateGraphicsPipelines(VK_NULL_HANDLE, 1, &CreateInfo, nullptr, &Handle);
	if (ret != VK_SUCCESS) 
	{
		throw std::runtime_error("failed to create graphics pipeline!");
	}
	std::cout << "vkCreateGraphicsPipelines ok AAAA " << GraphicsPipeline << std::endl;
}

