#include "VulkanObjects/Queue/VulkanQueue.h"
#include "VulkanObjects/Queue/VulkanQueueFamily.h"
#include "VulkanObjects/Device/VulkanDevice.h"
#include <iostream>

VulkanQueue::VulkanQueue()
{
	QueueFamily = nullptr;
	Handle = VK_NULL_HANDLE;
}

//VulkanQueue::VulkanQueue(VulkanQueueFamily* InQueueFamily, VkQueue InQueue)
//{
//	QueueFamily = InQueueFamily;
//	Handle = InQueue;
//}

VulkanQueue::VulkanQueue(VulkanDevice* InDevice, VulkanQueueFamily* InQueueFamily, std::uint32_t QueueIndex)
	: Device(InDevice), QueueFamily(InQueueFamily), QueueIndex(QueueIndex)
{
	QueueFamily->GetDeviceQueue(Device, QueueIndex, &Handle);
}

VulkanQueue::~VulkanQueue()
{
	std::cout << __FUNCTION__  << " " << Handle << " QueueFamliy " << QueueFamily->GetHandle() << std::endl;
}

VkQueue VulkanQueue::GetHandle()
{
	return Handle;
}