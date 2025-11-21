#include "VulkanObjects/Resource/VulkanBuffer.h"

void VulkanBuffer::GetBufferMemoryRequirements(VkMemoryRequirements* MemoryRequirements)
{
    Device->GetBufferMemoryRequirements(Handle, MemoryRequirements);
}

VkResult VulkanBuffer::BindBufferMemory(VkDeviceMemory Memory, VkDeviceSize MemoryOffset)
{
    return Device->BindBufferMemory(Handle, Memory, MemoryOffset);
}

VkResult VulkanBuffer::CreateBuffer(const VkBufferCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator)
{
    return Device->CreateBuffer(CreateInfo, Allocator, &Handle);
}

void VulkanBuffer::DestroyBuffer(const VkAllocationCallbacks* Allocator)
{
    Device->DestroyBuffer(Handle, Allocator);
}









