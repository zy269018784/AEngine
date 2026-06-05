#include "VulkanRHI/VulkanObjects//Queue/VulkanQueue.h"
#include "VulkanRHI/VulkanObjects//Queue/VulkanQueueFamily.h"
#include "VulkanRHI/VulkanObjects//Device/VulkanDevice.h"
#include "VulkanRHI/VulkanObjects//CommandBuffer/VulkanCommandBuffer.h"
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

void VulkanQueue::EndCommandBuffer(VulkanCommandBuffer* CommandBuffer)
{
	CommandBuffer->EndCommandBuffer();

	auto CommandBufferHandle = CommandBuffer->GetHandle();

	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &CommandBufferHandle;

	vkQueueSubmit(Handle, 1, &submitInfo, VK_NULL_HANDLE);
	vkQueueWaitIdle(Handle);

	delete CommandBuffer;
}