#pragma once
#include "Vulkan.h"
#include "VulkanObjects/Device/VulkanDevice.h"
#include <VulkanObjects/Memory/VulkanDeviceMemory.h>
#include "VulkanObjects/CommandBuffer/VulkanCommandPool.h"
#include "VulkanObjects/CommandBuffer/VulkanCommandBuffer.h"
#include "RHIObjects/Texture/RHITexture.h"
#include <iostream>
class VulkanImage
{
public:
	VulkanImage(VulkanDevice *InDevice, RHITextureType InType, RHIPixelFormat InPixelFormat,
				std::uint32_t InSizeX, std::uint32_t InSizeY, std::uint32_t InSizeZ, std::uint32_t InArraySize, std::uint32_t InNumMips, std::uint32_t InSampleCount, const void* InData = nullptr);
	
	VulkanImage(VulkanDevice* InDevice, VkImage InHandle);
	~VulkanImage();
	VkImage GetHandle();
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
//private:
//	VkImageType ImageViewTypeToImageType(VkImageViewType ResourceType);
//	VkImageCreateFlagBits ImageViewTypeToImageCreateFlagBits(VkImageViewType ResourceType);
//	VkSampleCountFlagBits ToSampleCountFlagBits(std::uint32_t InSampleCount);
	/*
		临时创建staging buffer
	*/
	void CreateBuffer(VkDeviceSize Size, VkBufferUsageFlags Usage, VkMemoryPropertyFlags Properties, VkBuffer& Buffer, VkDeviceMemory& BufferMemory);
public:
	/*
		暂时存放
	*/
	void EndSingleTimeCommands(VulkanCommandBuffer* CommandBuffer) {
		CommandBuffer->EndCommandBuffer();

		auto Handle = CommandBuffer->GetHandle();

		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &Handle;

		vkQueueSubmit(GraphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
		vkQueueWaitIdle(GraphicsQueue);

		delete CommandBuffer;
	}
	void TransitionImageLayout(VkFormat format, VkImageLayout OldLayout, VkImageLayout NewLayout);

	void CopyBufferToImage(VkBuffer buffer, uint32_t width, uint32_t height);

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
		纹理类型2
	*/
	RHITextureType Type;		
public:
	/*
		暂时存放
	*/

	VulkanCommandPool *CommandPool;
	VkQueue GraphicsQueue;	
	VkBuffer StagingBuffer;
	VkDeviceMemory StagingBufferMemory;
};