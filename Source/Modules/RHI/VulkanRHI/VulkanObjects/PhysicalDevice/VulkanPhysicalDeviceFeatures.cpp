#include "VulkanRHI/VulkanObjects/PhysicalDevice/VulkanPhysicalDeviceFeatures.h"
#include "VulkanRHI/VulkanObjects/PhysicalDevice/VulkanPhysicalDevice.h"
#include <iostream>
VulkanPhysicalDeviceFeatures::VulkanPhysicalDeviceFeatures(VulkanPhysicalDevice *InPhysicalDevice)
    : PhysicalDevice(InPhysicalDevice)
{
    AccelerationStructureFeatures        = {};
    AccelerationStructureFeatures.sType     = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_FEATURES_KHR;
    AccelerationStructureFeatures.pNext     = nullptr;

    Features2                            = {};
    Features2.sType                         = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
    Features2.pNext                         = &AccelerationStructureFeatures;

    //VkPhysicalDeviceDescriptorIndexingFeatures indexing_features{ VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_FEATURES_EXT, nullptr };
    //AccelerationStructureFeatures.pNext = &indexing_features;

    PhysicalDevice->GetPhysicalDeviceFeatures2(&Features2);

    std::cout << "AccelerationStructureFeatures.accelerationStructure " << AccelerationStructureFeatures.accelerationStructure << std::endl;
}

VulkanPhysicalDeviceFeatures::~VulkanPhysicalDeviceFeatures()
{

}