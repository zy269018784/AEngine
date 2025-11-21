#include "VulkanObjects/Queue/VulkanQueue.h"

VkResult VulkanQueue::QueueSubmit(std::uint32_t SubmitCount, const VkSubmitInfo* Submits, VkFence Fence)
{
	return vkQueueSubmit(Handle, SubmitCount, Submits, Fence);
}

VkResult VulkanQueue::QueueSubmit2(std::uint32_t SubmitCount, const VkSubmitInfo2* Submits, VkFence Fence)
{
	return vkQueueSubmit2(Handle, SubmitCount, Submits, Fence);
}

VkResult VulkanQueue::QueueWaitIdle()
{
	return vkQueueWaitIdle(Handle);
}