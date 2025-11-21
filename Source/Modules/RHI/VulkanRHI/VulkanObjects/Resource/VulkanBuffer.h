#pragma once
#include "VulkanObjects/Device/VulkanDevice.h"
#include <VulkanObjects/Memory/VulkanDeviceMemory.h>
#include "RHIObjects/Resource/RHIBuffer.h"
#include <cstdint>

class VulkanBuffer : public RHIBuffer
{
public:
	VulkanBuffer();
	VulkanBuffer(VulkanDevice* Device, RHIBuffer::RHIBufferType InType, RHIBuffer::RHIBufferUsageFlag InUsage, std::uint32_t InSize, const void* InData);
	~VulkanBuffer();
	VkBuffer GetHandle() const;
private:
	/*
		Vulkan API Wrapper
	*/
	void GetBufferMemoryRequirements(VkMemoryRequirements* MemoryRequirements);
	VkResult BindBufferMemory(VkDeviceMemory Memory, VkDeviceSize MemoryOffset);
	VkResult CreateBuffer(const VkBufferCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator);
	void DestroyBuffer(const VkAllocationCallbacks* Allocator);
private:
	VkBuffer Handle;
	VulkanDeviceMemory *DeviceMemoryHandle;
	VkMemoryRequirements MemoryRequirements;
	VulkanDevice* Device;
};