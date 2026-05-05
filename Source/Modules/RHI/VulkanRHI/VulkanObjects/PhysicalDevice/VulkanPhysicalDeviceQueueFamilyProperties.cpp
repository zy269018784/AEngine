#include "VulkanRHI/VulkanObjects/PhysicalDevice/VulkanPhysicalDeviceQueueFamilyProperties.h"
#include "VulkanRHI/VulkanObjects/PhysicalDevice/VulkanPhysicalDevice.h"
#include "VulkanRHI/VulkanObjects/Queue/VulkanQueueFamily.h"
#include <string>
#include <iostream>
VulkanPhysicalDeviceQueueFamilyProperties::VulkanPhysicalDeviceQueueFamilyProperties(VulkanPhysicalDevice *InPhysicalDevice)
    : PhysicalDevice(InPhysicalDevice)
{
    std::uint32_t Count = 0;
    PhysicalDevice->GetPhysicalDeviceQueueFamilyProperties(&Count, nullptr);
    QueueFamilyProperties.resize(Count);
    PhysicalDevice->GetPhysicalDeviceQueueFamilyProperties(&Count, QueueFamilyProperties.data());
}

VulkanPhysicalDeviceQueueFamilyProperties::~VulkanPhysicalDeviceQueueFamilyProperties()
{

}

void VulkanPhysicalDeviceQueueFamilyProperties::Print(int Tabs)
{
    std::string Head1 = "\t";
    std::string Head2 = "";
    for (int i = 0; i < Tabs; i++)
    {
        Head1 += "\t";
        Head2 += "\t";
    }

    std::cout << Head2 << "Queue Family Properties" << std::endl;
    for (uint32_t i = 0; i < QueueFamilyProperties.size(); i++)
    {
        std::cout
            << Head1 << "Queue Count " << QueueFamilyProperties[i].queueCount << " "
            << Head1 << "Queue Flags " << QueueFamilyProperties[i].queueFlags << " ";
        if (QueueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
            std::cout << Head2 << "VK_QUEUE_GRAPHICS_BIT" << " ";
        if (QueueFamilyProperties[i].queueFlags & VK_QUEUE_COMPUTE_BIT)
            std::cout << Head2 << "VK_QUEUE_COMPUTE_BIT" << " ";
        if (QueueFamilyProperties[i].queueFlags & VK_QUEUE_TRANSFER_BIT)
            std::cout << Head2 << "VK_QUEUE_TRANSFER_BIT" << " ";
        if (QueueFamilyProperties[i].queueFlags & VK_QUEUE_SPARSE_BINDING_BIT)
            std::cout << Head2 << "VK_QUEUE_SPARSE_BINDING_BIT" << " ";
        if (QueueFamilyProperties[i].queueFlags & VK_QUEUE_PROTECTED_BIT)
            std::cout << Head2 << "VK_QUEUE_PROTECTED_BIT" << " ";
        if (QueueFamilyProperties[i].queueFlags & VK_QUEUE_OPTICAL_FLOW_BIT_NV)
            std::cout << Head2 << "VK_QUEUE_OPTICAL_FLOW_BIT_NV" << " ";
        if (QueueFamilyProperties[i].queueFlags & VK_QUEUE_VIDEO_DECODE_BIT_KHR)
            std::cout << Head2 << "VK_QUEUE_VIDEO_DECODE_BIT_KHR" << " ";
        if (QueueFamilyProperties[i].queueFlags & VK_QUEUE_VIDEO_ENCODE_BIT_KHR)
            std::cout << Head2 << "VK_QUEUE_VIDEO_ENCODE_BIT_KHR" << " ";

        std::cout << std::endl;
    }
}

std::uint32_t VulkanPhysicalDeviceQueueFamilyProperties::GetQueueFamilyCount() const
{
    return static_cast<std::uint32_t>(QueueFamilyProperties.size());
}

std::vector<VulkanQueueFamily *> VulkanPhysicalDeviceQueueFamilyProperties::CreateQueueFamilies() const
{
    std::vector<VulkanQueueFamily*>			QueueFamilies;
    for (uint32_t  QueueFamilyIndex = 0; QueueFamilyIndex < QueueFamilyProperties.size(); QueueFamilyIndex++)
    {
        VulkanQueueFamily* QueueFamily = new VulkanQueueFamily(QueueFamilyIndex, QueueFamilyProperties[QueueFamilyIndex].queueCount);
        VkQueueFlags QueueFlags = QueueFamilyProperties[QueueFamilyIndex].queueFlags;

        if (QueueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            QueueFamily->SetGraphics();
        }

        if (QueueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            QueueFamily->SetCompute();
        }

        if (QueueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            QueueFamily->SetTransfer();
        }

        QueueFamilies.push_back(QueueFamily);
    }
    return QueueFamilies;
}