#include "Core.h"
#include <cstdint>
VkInstance Instance;
std::vector<VkPhysicalDevice> PhysicalDevices;
std::vector<VkQueueFamilyProperties> QueueFamilyProperties;
void VulkanInit()
{
    Instance = CreateInstance();
    std::cout << "VkInstance " << Instance << std::endl;

    PhysicalDevices = EnumeratePhysicalDevices();

    CreateQueue();
}


std::vector<VkPhysicalDevice> EnumeratePhysicalDevices()
{
    /*
        获取物理设备数量
    */
    std::uint32_t PhysicalDeviceCount = 0;
    vkEnumeratePhysicalDevices(Instance, &PhysicalDeviceCount, nullptr);

    /*
        获取物理设备Handle
    */
    std::vector<VkPhysicalDevice> PhysicalDeviceHandles;
    PhysicalDeviceHandles.resize(PhysicalDeviceCount);
    vkEnumeratePhysicalDevices(Instance, &PhysicalDeviceCount, PhysicalDeviceHandles.data());
    return PhysicalDeviceHandles;
}

void CreateQueue()
{
    std::uint32_t Count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevices[0], &Count, nullptr);
    QueueFamilyProperties.resize(Count);
    vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevices[0], &Count, QueueFamilyProperties.data());
}