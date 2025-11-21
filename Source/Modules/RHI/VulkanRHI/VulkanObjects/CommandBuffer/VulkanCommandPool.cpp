#include "VulkanObjects/CommandBuffer/VulkanCommandPool.h"
#include "VulkanObjects/CommandBuffer/VulkanCommandBuffer.h"
#include <stdexcept>
#include <iostream>

VulkanCommandPool::VulkanCommandPool(VulkanDevice* InDevice)
{
    Device = InDevice;
    Handle = VK_NULL_HANDLE;
}

VulkanCommandPool::~VulkanCommandPool()
{
    std::cout << __FUNCTION__ << " " << Handle << std::endl;
    DestroyCommandPool(Handle, nullptr);
}

VkCommandPool VulkanCommandPool::GetHandle()
{
    return Handle;
}

void VulkanCommandPool::SetHandle(VkCommandPool InHandle)
{
    Handle = InHandle;
}

void VulkanCommandPool::Create(uint32_t QueueFamilyIndex)
{
    VkCommandPoolCreateInfo PoolInfo{};
    PoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    PoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    PoolInfo.queueFamilyIndex = QueueFamilyIndex;
    if (Device->CreateCommandPool(&PoolInfo, nullptr, &Handle) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create command pool!");
    }
}

VkResult VulkanCommandPool::AllocateOneCommandBuffer(VkCommandBuffer* CommandBuffer)
{
    VkCommandBufferAllocateInfo AllocInfo{};
    AllocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    AllocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    AllocInfo.commandPool = Handle;
    AllocInfo.commandBufferCount = 1;
    return AllocateCommandBuffers(&AllocInfo, CommandBuffer);
}

VulkanCommandBuffer* VulkanCommandPool::BeginSingleTimeCommands()
{
    VulkanCommandBuffer* CommandBuffer = new VulkanCommandBuffer(Device, this);
    CommandBuffer->BeginSingleTime();
    return CommandBuffer;
}

