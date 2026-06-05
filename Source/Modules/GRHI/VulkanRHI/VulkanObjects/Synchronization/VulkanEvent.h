#pragma once
#include "VulkanRHI/Vulkan.h"
class VulkanDevice;
class VulkanEvent
{
public:
	VulkanEvent(VulkanDevice* Device);
	~VulkanEvent();
	VkEvent GetHandle();
private:
	VkEvent Handle; 
	VulkanDevice* Device;
};