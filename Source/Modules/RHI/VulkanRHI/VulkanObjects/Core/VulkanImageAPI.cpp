#include "VulkanObjects/Resource/VulkanImage.h"

VkResult VulkanImage::BindImageMemory(VkDeviceMemory Memory, VkDeviceSize MemoryOffset)
{
    return Device->BindImageMemory(Handle, Memory, MemoryOffset);
}

VkResult VulkanImage::CreateImage(const VkImageCreateInfo* CreateInfo, const VkAllocationCallbacks* pAllocator)
{
    return Device->CreateImage(CreateInfo, pAllocator, &Handle);
}

void VulkanImage::DestroyImage(const VkAllocationCallbacks* Allocator)
{
    Device->DestroyImage(Handle, Allocator);
}

void VulkanImage::GetImageMemoryRequirements(VkMemoryRequirements* MemoryRequirements)
{
    return Device->GetImageMemoryRequirements(Handle, MemoryRequirements);
}