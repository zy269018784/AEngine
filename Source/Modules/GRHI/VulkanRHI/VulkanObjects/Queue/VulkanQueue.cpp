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

	VkFence fence;
	VkFenceCreateInfo fenceInfo = {};
	fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceInfo.flags = 0;
	Device->CreateFence(&fenceInfo, nullptr, &fence);

	vkQueueSubmit(Handle, 1, &submitInfo, fence);

	// 等待 GPU 完成
	Device->WaitForFences(1, &fence, VK_TRUE, UINT64_MAX);

	// 清理
	Device->DestroyFence(fence, nullptr);

	vkQueueWaitIdle(Handle);

	delete CommandBuffer;
}