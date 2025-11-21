#pragma once
#include "Vulkan.h"
#include "VulkanObjects/Device/VulkanDevice.h"
#include "VulkanObjects/Descriptor/VulkanDescriptorPool.h"
class VulkanPipeline  
{
public:
	VulkanPipeline();
	VulkanPipeline(VulkanDevice* InDevice);
	VulkanPipeline(VulkanDevice* InDevice, VkPipeline Handle);
	~VulkanPipeline();
	VkPipeline GetHandle();
	VkPipelineLayout GetPipelineLayout();
	//VkDescriptorSetLayout GetDescriptorSetLayout();
	VkPipelineBindPoint GetPipelineBindPoint();
public:
	VkPipeline Handle;
	VkPipelineBindPoint BindPoint;
	VkPipelineLayout		PipelineLayout = VK_NULL_HANDLE;
	VulkanDevice* Device = nullptr;

	std::vector<VkPipelineShaderStageCreateInfo> ShaderStageCreateInfos;
};
