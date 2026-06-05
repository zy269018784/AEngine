#include "VulkanRHI/VulkanObjects/PhysicalDevice/VulkanPhysicalDeviceExtensions.h"
#include "VulkanRHI/VulkanObjects/PhysicalDevice/VulkanPhysicalDevice.h"
#include <set>
#include <string>
#include <iostream>
VulkanPhysicalDeviceExtensions::VulkanPhysicalDeviceExtensions(VulkanPhysicalDevice *InPhysicalDevice)
    : PhysicalDevice(InPhysicalDevice)
{
    std::uint32_t Count = 0;
    PhysicalDevice->EnumerateDeviceExtensionProperties(nullptr, &Count, nullptr);
    Extensions.resize(Count);
    PhysicalDevice->EnumerateDeviceExtensionProperties(nullptr, &Count, Extensions.data());
}

VulkanPhysicalDeviceExtensions::~VulkanPhysicalDeviceExtensions()
{

}

void VulkanPhysicalDeviceExtensions::Print(int Tabs)
{
    std::cout << "\t\tPhysical Device Extensions " << std::endl;
    uint32_t Count = static_cast<uint32_t>(Extensions.size());
    for (uint32_t i = 0; i < Count; i++)
    {
        std::cout
            << "\t\t\t"
            << Extensions[i].extensionName << " "
            //	<< ExtensionPropertyHandles[i].specVersion << " "
            << std::endl;
    }
}

bool VulkanPhysicalDeviceExtensions::CheckExtensionSupport(std::vector<const char*> RequiredExtensions)
{
    /*
        检查释放支持所有的扩展
    */
    std::set<std::string> AllRequiredExtensions(RequiredExtensions.begin(), RequiredExtensions.end());
    for (const auto& Extension : Extensions)
    {
        AllRequiredExtensions.erase(Extension.extensionName);
    }

    return AllRequiredExtensions.empty();
}