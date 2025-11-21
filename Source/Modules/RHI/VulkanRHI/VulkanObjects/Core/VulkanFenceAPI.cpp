#include "VulkanObjects/Synchronization/VulkanFence.h"
#include "VulkanObjects/Device/VulkanDevice.h"
VkResult VulkanFence::CreateFence(const VkFenceCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator)
{
	return Device->CreateFence(CreateInfo, Allocator, &Handle);
}

void VulkanFence::DestroyFence(const VkAllocationCallbacks* Allocator)
{
	Device->DestroyFence(Handle, Allocator);
}

VkResult VulkanFence::WaitForFences(uint32_t FenceCount, const VkFence* Fences, VkBool32 WaitAll, uint64_t Timeout)
{
	return Device->WaitForFences(FenceCount, Fences, WaitAll, Timeout);
}

VkResult VulkanFence::ResetFences(uint32_t FenceCount, const VkFence* Fences)
{
	return Device->ResetFences(FenceCount, Fences);
}