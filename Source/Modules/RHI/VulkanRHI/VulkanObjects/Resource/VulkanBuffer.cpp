#include "Vulkan.h"
#include "VulkanObjects/Resource/VulkanBuffer.h"
#include "VulkanObjects/Core/VulkanCore.h"
#include <string>
#include <cstring>
#include <iostream>
VulkanBuffer::VulkanBuffer()
{

}

VulkanBuffer::VulkanBuffer(VulkanDevice* InDevice, RHIBufferType InType, RHIBufferUsageFlag InUsage, std::uint32_t InSize, const void* InData)
    : Device(InDevice), RHIBuffer(InType, InUsage, InSize)
{
    DeviceMemoryHandle = new VulkanDeviceMemory(InDevice);
    
   VkResult Result = VK_SUCCESS;
   
   VkBufferCreateInfo CreateInfo{};
   CreateInfo.sType     = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
   CreateInfo.size      = InSize;
   CreateInfo.usage     = ToVkBufferUsageFlags(InType);
   Result = CreateBuffer(&CreateInfo, nullptr);
   if (VK_SUCCESS != Result)
       std::cout << "CreateBuffer failed : " << Result << std::endl;
   
   std::cout << "CreateBuffer " << Handle << std::endl;

   GetBufferMemoryRequirements(&MemoryRequirements);

   VkMemoryAllocateInfo AllocateInfo = {
       VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
       nullptr,
       MemoryRequirements.size,
       Device->GetPhysicalDevice()->HostVisibleIndex
   };
   Result = DeviceMemoryHandle->AllocateMemory(&AllocateInfo, nullptr);
   if (VK_SUCCESS != Result)
       std::cout << "AllocateMemory failed : " << Result << std::endl;

   Result = BindBufferMemory(DeviceMemoryHandle->GetHandle(), 0);
   if (VK_SUCCESS != Result)
       std::cout << "BindBufferMemory failed : " << Result << std::endl;

   if (InData)
   {
       std::uint8_t* p;
       Result = DeviceMemoryHandle->MapMemory(0, MemoryRequirements.size, 0, reinterpret_cast<void**>(&p));
       if (VK_SUCCESS != Result)
           std::cout << "MapMemory failed : " << Result << std::endl;
       std::memcpy(p, InData, InSize); 
       DeviceMemoryHandle->UnmapMemory();
   }
}

VulkanBuffer::~VulkanBuffer()
{ 
    std::cout << "~VulkanBuffer" << std::endl;
    DeviceMemoryHandle->FreeMemory();
    DestroyBuffer(nullptr);
}

VkBuffer VulkanBuffer::GetHandle() const
{
    return Handle;
}

//VkDeviceMemory VulkanBuffer::GetMemoryHandle() const
//{
//    return DeviceMemoryHandle->GetHandle();
//}

void VulkanBuffer::Update(std::uint32_t InSize, const void* InData)
{
    VkResult Result = VK_SUCCESS;
    std::uint8_t* p;
    Result = DeviceMemoryHandle->MapMemory(0, MemoryRequirements.size, 0, reinterpret_cast<void**>(&p));
    if (VK_SUCCESS != Result)
        std::cout << "MapMemory failed : " << Result << std::endl;
    std::memcpy(p, InData, InSize);
    DeviceMemoryHandle->UnmapMemory();
}