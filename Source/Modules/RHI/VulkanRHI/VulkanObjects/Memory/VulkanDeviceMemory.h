#pragma once
#include "VulkanObjects/Device/VulkanDevice.h"
class VulkanDeviceMemory
{
public:
	VulkanDeviceMemory(VulkanDevice* InDevice);
	~VulkanDeviceMemory();
	VkDeviceMemory GetHandle();
public:
	/*
		Vulkan API Wrapper
	*/
	VkResult AllocateMemory(const VkMemoryAllocateInfo* AllocateInfo, const VkAllocationCallbacks* Allocator);
	void FreeMemory();
	VkResult MapMemory(VkDeviceSize Offset, VkDeviceSize Size, VkMemoryMapFlags Flags, void** Data);
	void UnmapMemory();
private:
	VkDeviceMemory Handle = VK_NULL_HANDLE;
	VulkanDevice* Device;
};