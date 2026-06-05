#pragma once
#include "VulkanRHI/Vulkan.h"
#include <vector>

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
	VkPipelineBindPoint GetPipelineBindPoint();
protected:
	VkPipeline			Handle = VK_NULL_HANDLE;
	VkPipelineBindPoint BindPoint;
	VkPipelineLayout	PipelineLayout = VK_NULL_HANDLE;
	VulkanDevice*		Device = nullptr;
	std::vector<VkPipelineShaderStageCreateInfo> ShaderStageCreateInfos;
};
