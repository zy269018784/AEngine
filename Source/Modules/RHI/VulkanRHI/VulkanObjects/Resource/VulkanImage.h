#pragma once
#include "VulkanRHI/Vulkan.h"
#include "VulkanRHI/VulkanObjects//Device/VulkanDevice.h"
#include "VulkanRHI/VulkanObjects/Memory/VulkanDeviceMemory.h"
#include "VulkanRHI/VulkanObjects//CommandBuffer/VulkanCommandPool.h"
#include "VulkanRHI/VulkanObjects//CommandBuffer/VulkanCommandBuffer.h"
#include "VulkanRHI/VulkanObjects//Queue/VulkanQueue.h"
#include "RHI/RHIObjects/Texture/RHITexture.h"
#include <iostream>


class VulkanImage
{
public:
	VulkanImage(VulkanDevice *InDevice,
				RHITextureType InType,
				RHIPixelFormat InPixelFormat,
				RHITextureUsageFlag InUsage,
				RHIImageLayout InLayout,
				std::uint32_t InSizeX, std::uint32_t InSizeY, std::uint32_t InSizeZ,
				std::uint32_t InArraySize, std::uint32_t InNumMips, std::uint32_t InSampleCount,
				const void* InData = nullptr);
	
	VulkanImage(VulkanDevice* InDevice, VkImage InHandle);
	~VulkanImage();
	VkImage GetHandle() const;
	VkImageCreateInfo GetCreateInfo() const;
	void Update(const void* InData, std::uint32_t InSize);
	//void Update(int MipmapLevel, int XOffset, int YOffset, int ZOffset, int Width, int Height, int Depth, const void* InData);
public:
	/*
		Vulkan API Wrapper
	*/
	VkResult BindImageMemory(VkDeviceMemory Memory, VkDeviceSize MemoryOffset);

	VkResult CreateImage(const VkImageCreateInfo* CreateInfo, const VkAllocationCallbacks* pAllocator);

	void DestroyImage(const VkAllocationCallbacks* Allocator);

	void GetImageMemoryRequirements(VkMemoryRequirements* MemoryRequirements);
public:
	/*
		临时创建staging buffer
	*/
	void CreateBuffer(VkDeviceSize Size, VkBufferUsageFlags Usage, VkMemoryPropertyFlags Properties, VkBuffer& Buffer, VkDeviceMemory& BufferMemory);

	void TransitionImageLayout(RHIImageLayout OldLayout, RHIImageLayout NewLayout);

	//void CopyBufferToImage(VkBuffer buffer, uint32_t width, uint32_t height);

	void CopyBufferToImage(VkBuffer buffer, uint32_t mipLevel, int XOffset, int YOffset, int ZOffset, uint32_t Width, uint32_t Height, uint32_t Depth);

	//virtual void Update(int MipmapLevel, int XOffset, int YOffset, int ZOffset, int Width, int Height, int Depth, const void* InData) = 0;

private:
	VkImage Handle;
	VkMemoryRequirements MemoryRequirements;
	VulkanDeviceMemory *DeviceMemory;
	VulkanDevice* Device;
	/*
		纹理数组大小
	*/
	std::uint32_t ArraySize;
	/*
		纹理类型
	*/
	RHITextureType Type;

	VkImageCreateInfo CreateInfo;

	RHIImageLayout Layout;
public:
	/*
		暂时存放
	*/
	VkBuffer StagingBuffer = VK_NULL_HANDLE;
	VkDeviceMemory StagingBufferMemory = VK_NULL_HANDLE;
};
