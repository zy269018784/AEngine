#pragma once
#include "Vulkan.h"
class VulkanDevice;
class VulkanSemaphore
{
public:
	VulkanSemaphore(VulkanDevice* InDevice); 
	 ~VulkanSemaphore();
	 VkSemaphore GetHandle();
	 void Create(bool Signaled = false);
public:
	/*
		Vulkan API Wrapper
	*/
	VkResult CreateSemaphore(const VkSemaphoreCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator);
	void DestroySemaphore(const VkAllocationCallbacks* Allocator);
private: 
	VkSemaphore Handle; 
	VulkanDevice* Device;
};