#include "Core.h"

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