#include "VulkanObjects/Resource/VulkanImageView.h"
#include "VulkanPixelFormat.h"
#include "VulkanObjects/Core/VulkanCore.h"

#include <stdexcept>
#include <iostream>


VulkanImageView::VulkanImageView()
{

}

VulkanImageView::VulkanImageView(VulkanDevice* InDevice, VulkanImage* InImage, RHITextureType InType,  VkImageAspectFlags InaspectFlags,
	RHIPixelFormat InPixelFormat, std::uint32_t InNumMips, std::uint32_t InArraySize)
	: Device(InDevice)
{
	VkImageViewType InResourceType = ToVulkanImageViewType(InType);

	VkImageViewCreateInfo CreateInfo{};
	CreateInfo.sType								= VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	CreateInfo.flags;
	CreateInfo.image								= InImage->GetHandle();
	CreateInfo.viewType								= InResourceType;
	CreateInfo.format								= ToVkFormat(InPixelFormat);
	CreateInfo.components.r							= VK_COMPONENT_SWIZZLE_R;
	CreateInfo.components.g							= VK_COMPONENT_SWIZZLE_G;
	CreateInfo.components.b							= VK_COMPONENT_SWIZZLE_B;
	CreateInfo.components.a							= VK_COMPONENT_SWIZZLE_A;
	CreateInfo.subresourceRange.aspectMask			= InaspectFlags;
	CreateInfo.subresourceRange.baseMipLevel		= 0;
	CreateInfo.subresourceRange.levelCount			= InNumMips;
	CreateInfo.subresourceRange.baseArrayLayer		= 0;
	CreateInfo.subresourceRange.layerCount			= InArraySize;

	if (CreateImageView(&CreateInfo, nullptr) != VK_SUCCESS) 
	{
		throw std::runtime_error("Failed to create texture image view!");
	}
	std::cout << "CreateImageView ok "  << Handle << " InNumMips " << InNumMips << " InArraySize " << InArraySize << std::endl;
}

VulkanImageView::~VulkanImageView()
{
	DestroyImageView(nullptr);
}

VkImageView VulkanImageView::GetHandle()
{
	return Handle;
}