#include "VulkanRHI/VulkanObjects//Window/VulkanFrame.h"
#include "VulkanRHI/VulkanObjects//Device/VulkanDevice.h"
#include <iostream>
VulkanFrame::VulkanFrame(VulkanDevice* InDevice, bool InSignaled)
	: Device(InDevice)
{
	ImageFence = Device->CreateFence (InSignaled);
	ImageAvailableSemaphore = Device->CreateSemaphore();
	ImageDrawFinishedSemaphore = Device->CreateSemaphore();
}

VulkanFrame::~VulkanFrame()
{
	std::cout << "VulkanFrame::~VulkanFrame()" << std::endl;
	delete ImageFence;
	delete ImageAvailableSemaphore;
	delete ImageDrawFinishedSemaphore;
}