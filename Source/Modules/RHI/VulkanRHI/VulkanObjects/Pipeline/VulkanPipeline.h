#pragma once
#include "VulkanRHI/Vulkan.h"
#include <vector>
//#include "VulkanRHI/VulkanObjects/Device/VulkanDevice.h"
//#include "VulkanRHI/VulkanObjects/Descriptor/VulkanDescriptorPool.h"
class VulkanDevice;
class VulkanDescriptorPool;
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
