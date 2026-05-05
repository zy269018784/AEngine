#include "VulkanRHI/VulkanObjects/PhysicalDevice/VulkanPhysicalDevice.h"
#include "VulkanRHI/VulkanObjects/PhysicalDevice/VulkanPhysicalDeviceProperties.h"

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

}