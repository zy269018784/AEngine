#include "VulkanRHI/VulkanObjects/PhysicalDevice/VulkanPhysicalDevice.h"
#include "VulkanRHI/VulkanObjects/PhysicalDevice/VulkanPhysicalDeviceProperties.h"
#include <iostream>
VulkanPhysicalDeviceProperties::VulkanPhysicalDeviceProperties(VulkanPhysicalDevice *InPhysicalDevice)
    : PhysicalDevice(InPhysicalDevice)
{
    AccelerationStructureProperties.sType   = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_PROPERTIES_KHR;
    AccelerationStructureProperties.pNext   = nullptr;
    RayTracingPipelineProperties.sType      = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_PROPERTIES_KHR;
    RayTracingPipelineProperties.pNext      = &AccelerationStructureProperties;
    Properties2.sType                       = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
    Properties2.pNext                       = &RayTracingPipelineProperties;

    /*
        获取物理设备属性
    */
    PhysicalDevice->GetPhysicalDeviceProperties(&Properties);
    PhysicalDevice->GetPhysicalDeviceProperties2(&Properties2);
}

VulkanPhysicalDeviceProperties::~VulkanPhysicalDeviceProperties()
{

}

void VulkanPhysicalDeviceProperties::Print(int Tabs)
{
    std::string Head1 = "";
    std::string Head2 = "\t";
    for (int i = 0; i < Tabs; i++)
    {
        Head1 += "\t";
        Head2 += "\t";
    }
    std::cout << Head1 << "Physical Device Properties" << std::endl;
    std::cout << Head2 << "Driver Version "		<< Properties.driverVersion << std::endl;
    std::cout << Head2 << "Device Name "			<< Properties.deviceName << std::endl;
    std::cout << Head2 << "Device Type "			<< Properties.deviceType << std::endl;
}