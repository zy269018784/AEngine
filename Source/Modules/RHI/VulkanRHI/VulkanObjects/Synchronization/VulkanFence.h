#pragma once
#include "Vulkan.h"
class VulkanDevice;
class VulkanFence
{
public:
	VulkanFence(VulkanDevice* InDevice);
	~VulkanFence();
	VkFence GetHandle();
public:
	/*
		Vulkan API Wrapper
	*/
	VkResult CreateFence(const VkFenceCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator);
	void DestroyFence(const VkAllocationCallbacks* Allocator);
	VkResult WaitForFences(uint32_t FenceCount, const VkFence* pFences, VkBool32 WaitAll, uint64_t Timeout);
	VkResult ResetFences(uint32_t FenceCount, const VkFence* Fences);
public:
	VkResult Create(bool Signaled);
	VkResult Wait();
	VkResult Reset();
private:
	VkFence Handle; 
	VulkanDevice* Device;
};