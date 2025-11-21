#include "VulkanObjects/CommandBuffer/VulkanCommandPool.h"

/*
    Command Pool
*/
VkResult VulkanCommandPool::CreateCommandPool(const VkCommandPoolCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator)
{
    return Device->CreateCommandPool(CreateInfo, Allocator, &Handle);
}

void VulkanCommandPool::DestroyCommandPool(VkCommandPool CommandPool, const VkAllocationCallbacks* Allocator)
{
    Device->DestroyCommandPool(CommandPool, Allocator);
}

/*
    Command Buffers
*/
VkResult VulkanCommandPool::AllocateCommandBuffers(const VkCommandBufferAllocateInfo* AllocateInfo, VkCommandBuffer* CommandBuffers)
{
    return Device->AllocateCommandBuffers(AllocateInfo, CommandBuffers);
}

void VulkanCommandPool::FreeCommandBuffers(std::uint32_t CommandBufferCount, const VkCommandBuffer* CommandBuffers)
{
    Device->FreeCommandBuffers(Handle, CommandBufferCount, CommandBuffers);
}

