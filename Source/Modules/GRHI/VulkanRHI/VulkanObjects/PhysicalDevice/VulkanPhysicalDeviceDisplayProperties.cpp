#include "VulkanRHI/VulkanObjects/PhysicalDevice/VulkanPhysicalDeviceDisplayProperties.h"
#include "VulkanRHI/VulkanObjects/PhysicalDevice/VulkanPhysicalDevice.h"

VulkanPhysicalDeviceDisplayProperties::VulkanPhysicalDeviceDisplayProperties(VulkanPhysicalDevice *InPhysicalDevice)
    : PhysicalDevice(InPhysicalDevice)
{
#if 0
    std::uint32_t Count = 0;
    PhysicalDevice->GetPhysicalDeviceDis(&Count, nullptr);
    QueueFamilyProperties.resize(Count);
    PhysicalDevice->GetPhysicalDeviceQueueFamilyProperties(&Count, QueueFamilyProperties.data());
#endif
}

VulkanPhysicalDeviceDisplayProperties::~VulkanPhysicalDeviceDisplayProperties()
{

}

void VulkanPhysicalDeviceDisplayProperties::Print(int Tabs)
{

}