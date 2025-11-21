#include "VulkanObjects/Resource/VulkanImageView.h"

VkResult VulkanImageView::CreateImageView(const VkImageViewCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator)
{
	return Device->CreateImageView(CreateInfo, Allocator, &Handle);
}

void VulkanImageView::DestroyImageView(const VkAllocationCallbacks* Allocator)
{
	Device->DestroyImageView(Handle, Allocator);
}