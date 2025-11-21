#pragma once
#include "VulkanObjects/Device/VulkanDevice.h"
#include "VulkanObjects/Resource/VulkanImage.h"
#include "RHIObjects/Texture/RHITexture.h"
class VulkanImageView
{
public:
	VulkanImageView();
	VulkanImageView(VulkanDevice* InDevice, VulkanImage *InImage, RHITextureType InType, VkImageAspectFlags InaspectFlags,
		RHIPixelFormat InPixelFormat,  std::uint32_t InNumMips, std::uint32_t InArraySize);
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