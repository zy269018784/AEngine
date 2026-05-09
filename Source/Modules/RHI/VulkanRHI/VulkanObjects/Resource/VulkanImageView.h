#pragma once
#include "VulkanRHI/VulkanObjects//Device/VulkanDevice.h"
#include "VulkanRHI/VulkanObjects//Resource/VulkanImage.h"
#include "RHI/RHIObjects/Texture/RHITexture.h"
class VulkanImageView
{
public:
	VulkanImageView();
	VulkanImageView(VulkanDevice* InDevice, VulkanImage *InImage, RHITextureType InType,
					RHIPixelFormat InPixelFormat, RHITextureUsageFlag InUsage,
					std::uint32_t InNumMips, std::uint32_t InArraySize);
	~VulkanImageView();
	VkImageView GetHandle();
	VkImageView Handle;
public:
	/*
		Vulkan API Wrapper
	*/
	VkResult CreateImageView(const VkImageViewCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator);
	void DestroyImageView(const VkAllocationCallbacks* Allocator);
private:
	VulkanDevice* Device;
};