#include "VulkanObjects/Surface/VulkanSurface.h"

void VulkanSurface::DestroySurfaceKHR(const VkAllocationCallbacks* Allocator)
{
	Instance->DestroySurfaceKHR(Handle, Allocator);
}