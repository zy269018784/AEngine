#include "VulkanQueueFamily.h"
#include "VulkanObjects/Device/VulkanDevice.h"
VulkanQueueFamily::VulkanQueueFamily(std::uint32_t Index, std::uint32_t Count)
{
	Handle = Index;
	QueueCount = Count;
}

std::uint32_t VulkanQueueFamily::GetHandle()
{
	return Handle;
}

void VulkanQueueFamily::GetDeviceQueue(VulkanDevice* Device, std::uint32_t QueueIndex, VkQueue* Queue)
{
	Device->GetDeviceQueue(Handle, QueueIndex, Queue);
}

std::uint32_t VulkanQueueFamily::GetQueueCount()
{
	return QueueCount;
}

void VulkanQueueFamily::SetGraphics()
{
	QueueFlag |= 0x1;
}

void VulkanQueueFamily::SetCompute()
{
	QueueFlag |= 0x2;
}

void VulkanQueueFamily::SetTransfer()
{
	QueueFlag |= 0x4;
}

bool VulkanQueueFamily::SupportGraphics()
{
	bool ret = false;
	if (QueueFlag & 0x1)
		ret = true;
	return ret;
}

bool VulkanQueueFamily::SupportCompute()
{
	bool ret = false;
	if (QueueFlag & 0x2)
		ret = true;
	return ret;
}

bool VulkanQueueFamily::SupportTransfer()
{
	bool ret = false;
	if (QueueFlag & 0x4)
		ret = true;
	return ret;
}