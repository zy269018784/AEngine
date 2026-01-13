#include "Vulkan.h"
#include "VulkanObjects/Resource/VulkanBuffer.h"
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

    VkBufferUsageFlags UsageFlags = 0x0;
    switch (InType)
    {
    case VertexBuffer:
        UsageFlags |= VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
        break;
    case IndexBuffer:
        UsageFlags |= VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
        break;
    case UniformBuffer:
        UsageFlags |= VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
        break;
    case StorageBuffer:
        UsageFlags |= VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
        break;
    case IndirectBuffer:
        UsageFlags |= VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT;
        break;
    case TransferSrcBuffer:
        UsageFlags |= VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
        break;
    case TransferDstBuffer:
        UsageFlags |= VK_BUFFER_USAGE_TRANSFER_DST_BIT;
        break;
    }

   VkResult Result = VK_SUCCESS;
   
   VkBufferCreateInfo CreateInfo;
   std::memset(&CreateInfo, 0, sizeof(CreateInfo));
   CreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
   CreateInfo.size = InSize;
   CreateInfo.usage = UsageFlags;
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

}