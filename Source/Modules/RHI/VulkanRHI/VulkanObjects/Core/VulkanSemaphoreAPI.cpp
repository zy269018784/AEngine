#include "VulkanObjects/Synchronization/VulkanSemaphore.h"
#include "VulkanObjects/Device/VulkanDevice.h"
VkResult VulkanSemaphore::CreateSemaphore(const VkSemaphoreCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator)
{
	return Device->CreateSemaphore(CreateInfo, nullptr, &Handle);
}

void VulkanSemaphore::DestroySemaphore(const VkAllocationCallbacks* Allocator)
{
	return Device->DestroySemaphore(Handle, Allocator);
}