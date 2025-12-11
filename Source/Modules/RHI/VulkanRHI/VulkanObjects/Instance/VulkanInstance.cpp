#include "VulkanObjects/Instance/VulkanInstance.h"
#include "VulkanObjects/PhysicalDevice/VulkanPhysicalDevice.h"
#include <iostream>
#include <cstring>

VulkanInstance::VulkanInstance()
{
    VkApplicationInfo AppInfo{};
    AppInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    AppInfo.pApplicationName = "Hello Triangle";
    AppInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    AppInfo.pEngineName = "No Engine";
    AppInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    AppInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo CreateInfo{};
    CreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    CreateInfo.pApplicationInfo = &AppInfo;
    CreateInfo.enabledExtensionCount = 0;
    CreateInfo.ppEnabledExtensionNames = nullptr;
    CreateInfo.enabledLayerCount = 0;
    CreateInfo.ppEnabledLayerNames = nullptr;
    CreateInfo.pNext = nullptr;

    if (vkCreateInstance(&CreateInfo, nullptr, &Handle) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create instance!");
    }
}

VulkanInstance::VulkanInstance(std::vector<const char*> Extensions, std::vector<const char*> Layers)
{
    std::uint32_t LayerCount = 0;
    EnumerateInstanceLayerProperties(&LayerCount, nullptr);

    std::vector<VkLayerProperties> AvailableLayers(LayerCount);
    vkEnumerateInstanceLayerProperties(&LayerCount, AvailableLayers.data());
    std::cout << "Instance Layers:" << std::endl;
    for (int i = 0; i < AvailableLayers.size(); i++)
    {
        std::cout << "\t" << AvailableLayers[i].layerName << " " << AvailableLayers[i].description << std::endl;
        if (strcmp("VK_LAYER_KHRONOS_validation", AvailableLayers[i].layerName) == 0)
        {
            SupportValidationLayer = true;
        }
    }

    std::cout << "SupportValidationLayer " << SupportValidationLayer << std::endl;
    if (!SupportValidationLayer)
        Layers.clear();

    VkApplicationInfo AppInfo{};
    AppInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    AppInfo.pApplicationName = "Hello Triangle";
    AppInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    AppInfo.pEngineName = "No Engine";
    AppInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
   // AppInfo.apiVersion = VK_API_VERSION_1_0;
    /*
        1.3 动态状态
        https://vulkan.lunarg.com/doc/view/1.4.321.1/windows/antora/spec/latest/chapters/pipelines.html#VUID-VkGraphicsPipelineCreateInfo-pDynamicStates-03378
    */
    AppInfo.apiVersion = VK_MAKE_API_VERSION(0, 1, 3, 0);
    std::cout << "VulkanInstance " << std::endl;
    VkInstanceCreateInfo CreateInfo{};
    CreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    CreateInfo.pApplicationInfo = &AppInfo;
    CreateInfo.enabledExtensionCount = Extensions.size();
    CreateInfo.ppEnabledExtensionNames = Extensions.data();
    CreateInfo.enabledLayerCount = Layers.size();
    CreateInfo.ppEnabledLayerNames = Layers.data();
    CreateInfo.pNext = nullptr;

    std::cout << "VulkanInstance " << std::endl;
    VkResult ret = vkCreateInstance(&CreateInfo, nullptr, &Handle);
    if (ret != VK_SUCCESS)
    {
        std::cout << "vkCreateInstance ret " << ret << std::endl;
        throw std::runtime_error("failed to create instance!");
    }
    std::cout << "vkCreateInstance " << Handle << std::endl;
}

VulkanInstance::~VulkanInstance()
{
    for (int i = 0; i < PhysicalDevices.size(); i++)
    {
        delete PhysicalDevices[i];
    }

    std::cout << "vkDestroyInstance " << Handle << std::endl;
    if (VK_NULL_HANDLE != Handle)
        vkDestroyInstance(Handle, nullptr);
}

void VulkanInstance::EnumeratePhysicalDevices()
{
    /*
        获取物理设备数量
    */
    uint32_t PhysicalDeviceCount = 0;
    EnumeratePhysicalDevices(&PhysicalDeviceCount, nullptr);
    std::cout << "GPU Count " << PhysicalDeviceCount << std::endl;

    /*
        获取物理设备Handle
    */
    std::vector<VkPhysicalDevice>			PhysicalDeviceHandles;
    PhysicalDeviceHandles.resize(PhysicalDeviceCount);
    EnumeratePhysicalDevices(&PhysicalDeviceCount, PhysicalDeviceHandles.data());
#if 0
    /*
     *  check format
     *
     */
    VkFormat format = VK_FORMAT_R8G8B8A8_UNORM;
    VkFormatProperties formatProperties;

    vkGetPhysicalDeviceFormatProperties(PhysicalDeviceHandles[0], format, &formatProperties);

    std::cout << "VK_FORMAT_R8G8B8A8_UNORM support:\n";
    std::cout << "Linear tiling features: "
              << formatProperties.linearTilingFeatures << "\n";
    std::cout << "Optimal tiling features: "
              << formatProperties.optimalTilingFeatures << "\n";
    std::cout << "Buffer features: "
              << formatProperties.bufferFeatures << "\n";
#endif
    /*
        创建VulkanPhysicalDevice
    */
    PhysicalDevices.resize(PhysicalDeviceCount);
    for (uint32_t i = 0; i < PhysicalDeviceCount; i++)
    {
        std::cout << "\t==========================\t" << "GPU " << i << "\tBegin" << "\t====================================================" << std::endl;
        PhysicalDevices[i] = new VulkanPhysicalDevice(PhysicalDeviceHandles[i]);

        PhysicalDevices[i]->PrintExtensions();
        PhysicalDevices[i]->PrintLayers();
        PhysicalDevices[i]->PrintProperties();
        PhysicalDevices[i]->PrintQueueFamilyProperties();
        PhysicalDevices[i]->PrintMemoryProperties();
        PhysicalDevices[i]->PrintFeatures();
        std::cout << "\t==========================\t" << "GPU " << i << "\tEnd" << "\t====================================================" << std::endl;
    }
}


void VulkanInstance::EnumerateLayers()
{
    /*
        获取Layer数量
    */
    uint32_t Count = 0;
    EnumerateInstanceLayerProperties(&Count, nullptr);

    /*
        获取Layer Handle
    */
    std::vector<VkLayerProperties>			LayerPropertyHandles;
    LayerPropertyHandles.resize(Count);
    EnumerateInstanceLayerProperties(&Count, LayerPropertyHandles.data());

    std::cout << "\tLayers " << std::endl;
    for (uint32_t i = 0; i < Count; i++)
    {
        std::cout 
            << "\t\t"
            << LayerPropertyHandles[i].layerName             
            << std::endl;
     
        /*
            获取Extension数量
        */
        uint32_t Count = 0;
        EnumerateInstanceExtensionProperties(LayerPropertyHandles[i].layerName, &Count, nullptr);

        /*
            获取Extension
        */
        std::vector<VkExtensionProperties>			ExtensionPropertyHandles;
        ExtensionPropertyHandles.resize(Count);
        EnumerateInstanceExtensionProperties(LayerPropertyHandles[i].layerName, &Count, ExtensionPropertyHandles.data());

        if (Count > 0)
            std::cout << "\t\t\tLayer Extensions" << std::endl;
        for (uint32_t i = 0; i < Count; i++)
        {
            std::cout
                << "\t\t\t\t"
                << ExtensionPropertyHandles[i].extensionName << " "
                << std::endl;
        }
    }
}

void VulkanInstance::EnumerateExtensions()
{
    /*
        获取Extension数量
    */
    uint32_t Count = 0;
    EnumerateInstanceExtensionProperties(nullptr, &Count, nullptr);

    /*
        获取Extension
    */
    std::vector<VkExtensionProperties>			ExtensionPropertyHandles;
    ExtensionPropertyHandles.resize(Count);
    EnumerateInstanceExtensionProperties(nullptr, &Count, ExtensionPropertyHandles.data());

    std::cout << "\tExtensions " << std::endl;
    for (uint32_t i = 0; i < Count; i++)
    {
        std::cout
            << "\t\t"
            << ExtensionPropertyHandles[i].extensionName << " "
           // << ExtensionPropertyHandles[i].specVersion << " "
            << std::endl;
    }
}

VulkanPhysicalDevice* VulkanInstance::GetVulkanPhysicalDevice(uint32_t i) const
{
    return PhysicalDevices[i];
}

std::uint32_t  VulkanInstance::GetVulkanPhysicalDeviceCount()
{
    return PhysicalDevices.size();
}


VkInstance VulkanInstance::GetHandle()
{
    return Handle;
}

void VulkanInstance::SetHandle(VkInstance Instance)
{
    Handle = Instance; 
}
