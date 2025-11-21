#pragma once
#include "Vulkan.h"
#include "VulkanObjects/Device/VulkanDevice.h"

class VulkanCommandBuffer;
class VulkanCommandPool
{
public:
    VulkanCommandPool(VulkanDevice* InDevice);
    ~VulkanCommandPool();
    VkCommandPool GetHandle();
    void SetHandle(VkCommandPool InHandle);
    void Create(uint32_t QueueFamilyIndex); 
    
    VkResult AllocateOneCommandBuffer(VkCommandBuffer* CommandBuffer);
public:
    /*
        Vulkan API Wrapper
    */
    VkResult AllocateCommandBuffers(const VkCommandBufferAllocateInfo* AllocateInfo, VkCommandBuffer* CommandBuffers);
    void FreeCommandBuffers(std::uint32_t CommandBufferCount, const VkCommandBuffer* CommandBuffers);
    VulkanCommandBuffer* BeginSingleTimeCommands();
private:
    VkResult CreateCommandPool(const VkCommandPoolCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator);
    void DestroyCommandPool(VkCommandPool CommandPool, const VkAllocationCallbacks* Allocator);
private:
    VkCommandPool Handle;
    VulkanDevice* Device = nullptr;
};