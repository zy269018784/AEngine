#include "VulkanRHI/VulkanObjects/Surface/VulkanSurface.h"
#include "VulkanRHI/VulkanObjects/Instance/VulkanInstance.h"

void VulkanSurface::DestroySurfaceKHR(const VkAllocationCallbacks* Allocator)
{
	Instance->DestroySurfaceKHR(Handle, Allocator);
}