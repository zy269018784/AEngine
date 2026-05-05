#include "VulkanRHI/VulkanObjects/PhysicalDevice/VulkanPhysicalDeviceLayerProperties.h"
#include "VulkanRHI/VulkanObjects/PhysicalDevice/VulkanPhysicalDevice.h"
#include <iostream>

VulkanPhysicalDeviceLayerProperties::VulkanPhysicalDeviceLayerProperties(VulkanPhysicalDevice *InPhysicalDevice)
    : PhysicalDevice(InPhysicalDevice)
{
    std::uint32_t Count = 0;
    PhysicalDevice->EnumerateDeviceLayerProperties(&Count, nullptr);
    LayerProperties.resize(Count);
    PhysicalDevice->EnumerateDeviceLayerProperties(&Count, LayerProperties.data());
}

VulkanPhysicalDeviceLayerProperties::~VulkanPhysicalDeviceLayerProperties()
{

}

void VulkanPhysicalDeviceLayerProperties::Print(int Tabs)
{
    std::cout << "\t\tPhysical Device Layers " << std::endl;
    for (uint32_t i = 0; i < LayerProperties.size(); i++)
    {
        std::cout
            << "\t\t\t"
            << LayerProperties[i].layerName
            << std::endl;

        /*
            获取Extension数量
        */
        uint32_t Count = 0;
        PhysicalDevice->EnumerateDeviceExtensionProperties(LayerProperties[i].layerName, &Count, nullptr);

        /*
            获取Extension
        */
        std::vector<VkExtensionProperties>			ExtensionPropertyHandles;
        ExtensionPropertyHandles.resize(Count);
        PhysicalDevice->EnumerateDeviceExtensionProperties(LayerProperties[i].layerName, &Count, ExtensionPropertyHandles.data());

        if (Count > 0)
            std::cout << "\t\t\t\tLayer Extensions" << std::endl;

        for (uint32_t i = 0; i < Count; i++)
        {
            std::cout
                << "\t\t\t\t\t"
                << ExtensionPropertyHandles[i].extensionName << " "
                << std::endl;
        }
    }
}