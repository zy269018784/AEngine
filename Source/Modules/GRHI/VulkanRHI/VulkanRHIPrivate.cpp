#include "VulkanRHI.h"
#include "VulkanRHI/VulkanObjects//Instance/VulkanInstance.h"
#include "VulkanRHI/VulkanObjects//Device/VulkanDevice.h"
#include "VulkanRHI/VulkanObjects//PhysicalDevice/VulkanPhysicalDevice.h"
#include "VulkanRHI/VulkanObjects//Core/VulkanAPI.h"
#include <iostream>

#include "VulkanRHI/VulkanObjects//PhysicalDevice/VulkanPhysicalDeviceQueueFamilyProperties.h"


void VulkanRHI::CreateInstance()
{
    /*
        待修改
    */
    std::vector<const char*> InstanceExtensions =
    {
        "VK_KHR_surface",
    };
#if RHI_USE_XCB_KHR
    InstanceExtensions.emplace_back("VK_KHR_xcb_surface");
#endif

#if RHI_USE_Xlib_KHR
    InstanceExtensions.emplace_back("VK_KHR_xlib_surface");
#endif

#if RHI_USE_WIN32_KHR
    InstanceExtensions.emplace_back("VK_KHR_win32_surface");
#endif
   std::vector<const char*> InstanceLayers = 
   {
        "VK_LAYER_KHRONOS_validation"
   };

    Instance = new VulkanInstance(InstanceExtensions, InstanceLayers);
    Instance->EnumerateExtensions();
    Instance->EnumerateLayers();
    Instance->EnumeratePhysicalDevices();

    VulkanAPI::GetInstance(Instance);
}

void VulkanRHI::CreateDevice()
{
   for (std::uint32_t  i = 0; i < Instance->GetVulkanPhysicalDeviceCount(); i++)
   {
       auto Device = Instance->GetVulkanPhysicalDevice(i)->CreateDevice();
       Devices.push_back(Device);
   }
}

void VulkanRHI::CreateCommandPool()
{
    Devices[GPUIndex]->CreateCommandPoolForAllQueueFamliy(Instance->GetVulkanPhysicalDevice(GPUIndex)->GetQueueFamilyCount());
    std::cout << "Device->Device->CommandPools.size() " << Devices[GPUIndex]->CommandPools.size() << std::endl;

    GraphicsCommandPool = Devices[GPUIndex]->CommandPools[0];
    ComputeCommandPool  = Devices[GPUIndex]->CommandPools[0];
}
