#include "VulkanObjects/Device/VulkanDevice.h"
#include "VulkanObjects/Queue/VulkanQueue.h"
#include "VulkanObjects/Synchronization/VulkanFence.h"
#include "VulkanObjects/CommandBuffer/VulkanCommandPool.h"
#include "VulkanObjects/CommandBuffer/VulkanCommandBuffer.h"
#include "VulkanObjects/Queue/VulkanQueueFamily.h"
#include "VulkanObjects/Synchronization/VulkanSemaphore.h"
#include <set>
#include <iostream>
#include <cstring>

VulkanDevice::VulkanDevice()
{
	Handle = VK_NULL_HANDLE;
}

VulkanDevice::VulkanDevice(VkDevice h)
{
	Handle = h;
}

VulkanDevice::VulkanDevice(VulkanPhysicalDevice* InPhysicalDevice, VkDevice InDevice)
{
	PhysicalDevice = InPhysicalDevice;
	Handle = InDevice;
}

VulkanDevice::~VulkanDevice()
{	
	for (int i = 0; i < Queues.size(); i++)
	{
		delete Queues[i];
	}

	for (int i = 0; i < CommandPools.size(); i++)
	{
		delete CommandPools[i];
	}

	std::cout << __FUNCTION__ << Handle << std::endl;
	vkDestroyDevice(Handle, nullptr);
}

VkDevice VulkanDevice::GetHandle()
{
	return Handle;
}

VulkanPhysicalDevice* VulkanDevice::GetPhysicalDevice()
{
	return PhysicalDevice;
}

void VulkanDevice::CreateQueue()
{
	if (PhysicalDevice)
	{
		/*
			为每个Queue Family创建Queue
		*/
		auto QueueFamilyCount = PhysicalDevice->GetQueueFamilyCount();
		for (int QueueFamiliyIndex = 0; QueueFamiliyIndex < QueueFamilyCount; QueueFamiliyIndex++)
		{
			auto QueueFamiliy = PhysicalDevice->GetQueueFamily(QueueFamiliyIndex);
			auto QueueCount   = QueueFamiliy->GetQueueCount();
			for (int QueueIndex = 0; QueueIndex < QueueCount; QueueIndex++)
			{
				VulkanQueue* Queue = new VulkanQueue(this, QueueFamiliy, QueueIndex);
				Queues.push_back(Queue);
			}
		}
	}
}

void VulkanDevice::CreateCommandPoolForAllQueueFamliy(const std::vector<VkQueueFamilyProperties>& QueueFamilyProperties)
{
	for (uint32_t QeueFamilyIndex = 0; QeueFamilyIndex < QueueFamilyProperties.size(); QeueFamilyIndex++)
	{
		VulkanCommandPool* CommandPool = new VulkanCommandPool(this);
		CommandPool->Create(QeueFamilyIndex);
		CommandPools.push_back(CommandPool);
	}
}

VulkanCommandPool* VulkanDevice::CreateCommandPool(uint32_t QeueFamilyIndex)
{
	VulkanCommandPool* CommandPool = new VulkanCommandPool(this);
	CommandPool->Create(QeueFamilyIndex);
	return CommandPool;
}

VulkanCommandBuffer* VulkanDevice::CreateCommandBuffer(VulkanCommandPool* CommandPool)
{
	VulkanCommandBuffer* CommandBuffer = new VulkanCommandBuffer(this, CommandPool);
	//CommandBuffer->Create(CommandPool);
	return CommandBuffer;
}

VulkanFence* VulkanDevice::CreateFence(bool Signaled)
{
	VulkanFence *Fence = new VulkanFence(this);
	Fence->Create(Signaled);
	return Fence;
}

VulkanSemaphore* VulkanDevice::CreateSemaphore(bool Signaled)
{
	VulkanSemaphore* Semaphore = new VulkanSemaphore(this);
	Semaphore->Create(Signaled);
	return Semaphore;
}

void VulkanDevice::GetPresentQueue(std::uint32_t QueueFamilyIndex, std::uint32_t QueueIndex)
{
	GetDeviceQueue(QueueFamilyIndex, QueueIndex, &PresentQueue);
}


#if 0
/*
	Image
*/ 
void VulkanDevice::MapFormatSupport(RHIPixelFormat UserFormat, VkFormat InFormat, const VkComponentMapping& ComponentMapping)
{
	GPixelFormats[UserFormat].PlatformFormat = InFormat;
	//ComponentMapping todo...
}
#endif
void VulkanDevice::SetupFormats()
{
	//for (uint32_t i = 0; i < VK_FORMAT_RANGE_SIZE; ++i)
	//{
	//	const VkFormat Format = (VkFormat)i;
	//	FMemory::Memzero(FormatProperties[i]);
	//	VulkanRHI::vkGetPhysicalDeviceFormatProperties(Gpu, Format, &FormatProperties[i]);
	//}

	//static_assert(sizeof(VkFormat) <= sizeof(GPixelFormats[0].PlatformFormat), "PlatformFormat must be increased!");

	// Create shortcuts for the possible component mappings
	const VkComponentMapping ComponentMappingRGBA = { VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A };
	const VkComponentMapping ComponentMappingRGB1 = { VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_ONE };
	const VkComponentMapping ComponentMappingRG01 = { VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_ZERO, VK_COMPONENT_SWIZZLE_ONE };
	const VkComponentMapping ComponentMappingR001 = { VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_ZERO, VK_COMPONENT_SWIZZLE_ZERO, VK_COMPONENT_SWIZZLE_ONE };
	const VkComponentMapping ComponentMappingRIII = { VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY };
	const VkComponentMapping ComponentMapping000R = { VK_COMPONENT_SWIZZLE_ZERO, VK_COMPONENT_SWIZZLE_ZERO, VK_COMPONENT_SWIZZLE_ZERO, VK_COMPONENT_SWIZZLE_R };
	const VkComponentMapping ComponentMappingR000 = { VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_ZERO, VK_COMPONENT_SWIZZLE_ZERO, VK_COMPONENT_SWIZZLE_ZERO };
	const VkComponentMapping ComponentMappingRR01 = { VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_ZERO, VK_COMPONENT_SWIZZLE_ONE };

#if 0
	// Initialize the platform pixel format map.
	for (int32_t i = 0; i < PF_MAX; ++i)
	{
		GPixelFormats[i].PlatformFormat = VK_FORMAT_UNDEFINED;
		//GPixelFormats[i].Supported = false;
		//GVulkanBufferFormat[Index] = VK_FORMAT_UNDEFINED;

		//// Set default component mapping
		//PixelFormatComponentMapping[Index] = ComponentMappingRGBA;
	}

	//const EPixelFormatCapabilities ColorRenderTargetRequiredCapabilities = (EPixelFormatCapabilities::TextureSample | EPixelFormatCapabilities::RenderTarget);

	// Default formats
	//PixelFormatInfo.PlatformFormat = VulkanFormat;

	MapFormatSupport(RHIPixelFormat::PF_R8_SBYTE, VK_FORMAT_R8_SNORM, ComponentMappingR001);
	MapFormatSupport(RHIPixelFormat::PF_R8_UBYTE, VK_FORMAT_R8_UNORM, ComponentMappingR001);
	MapFormatSupport(RHIPixelFormat::PF_R16_SINT, VK_FORMAT_R16_SINT, ComponentMappingR001);
	MapFormatSupport(RHIPixelFormat::PF_R16_UINT, VK_FORMAT_R16_UINT, ComponentMappingR001);
	MapFormatSupport(RHIPixelFormat::PF_R32_SINT, VK_FORMAT_R32_SINT, ComponentMappingR001);
	MapFormatSupport(RHIPixelFormat::PF_R32_UINT, VK_FORMAT_R32_UINT, ComponentMappingR001);
	MapFormatSupport(RHIPixelFormat::PF_R16_FLOAT, VK_FORMAT_R16_SFLOAT, ComponentMappingR001);
	MapFormatSupport(RHIPixelFormat::PF_R32_FLOAT, VK_FORMAT_R32_SFLOAT, ComponentMappingR001);

	MapFormatSupport(RHIPixelFormat::PF_R8G8_SBYTE, VK_FORMAT_R8G8_SNORM, ComponentMappingRG01);
	MapFormatSupport(RHIPixelFormat::PF_R8G8_UBYTE, VK_FORMAT_R8G8_UNORM, ComponentMappingRG01);
	MapFormatSupport(RHIPixelFormat::PF_R16G16_SINT, VK_FORMAT_R16G16_SINT, ComponentMappingRG01);
	MapFormatSupport(RHIPixelFormat::PF_R16G16_UINT, VK_FORMAT_R16G16_UINT, ComponentMappingRG01);
	MapFormatSupport(RHIPixelFormat::PF_R32G32_SINT, VK_FORMAT_R32G32_SINT, ComponentMappingRG01);
	MapFormatSupport(RHIPixelFormat::PF_R32G32_UINT, VK_FORMAT_R32G32_UINT, ComponentMappingRG01);
	MapFormatSupport(RHIPixelFormat::PF_R16G16_FLOAT, VK_FORMAT_R16G16_SFLOAT, ComponentMappingRG01);
	MapFormatSupport(RHIPixelFormat::PF_R32G32_FLOAT, VK_FORMAT_R32G32_SFLOAT, ComponentMappingRG01); // Requirement for GPU particles

	MapFormatSupport(RHIPixelFormat::PF_R8G8B8_SBYTE, VK_FORMAT_R8G8B8_SNORM, ComponentMappingRGB1);
	MapFormatSupport(RHIPixelFormat::PF_R8G8B8_UBYTE, VK_FORMAT_R8G8B8_UNORM, ComponentMappingRGB1);
	MapFormatSupport(RHIPixelFormat::PF_R16G16B16_SINT, VK_FORMAT_R16G16B16_SINT, ComponentMappingRGB1);
	MapFormatSupport(RHIPixelFormat::PF_R16G16B16_UINT, VK_FORMAT_R16G16B16_UINT, ComponentMappingRGB1);
	MapFormatSupport(RHIPixelFormat::PF_R32G32B32_SINT, VK_FORMAT_R32G32B32_SINT, ComponentMappingRGB1);
	MapFormatSupport(RHIPixelFormat::PF_R32G32B32_UINT, VK_FORMAT_R32G32B32_UINT, ComponentMappingRGB1);
	MapFormatSupport(RHIPixelFormat::PF_R16G16B16_FLOAT, VK_FORMAT_R16G16B16_SFLOAT, ComponentMappingRGB1);
	MapFormatSupport(RHIPixelFormat::PF_R32G32B32_FLOAT, VK_FORMAT_R32G32B32_SFLOAT, ComponentMappingRGB1);

	MapFormatSupport(RHIPixelFormat::PF_R8G8B8A8_SBYTE, VK_FORMAT_R8G8B8A8_SNORM, ComponentMappingRGBA);
	MapFormatSupport(RHIPixelFormat::PF_R8G8B8A8_UBYTE, VK_FORMAT_R8G8B8A8_UNORM, ComponentMappingRGBA);
	MapFormatSupport(RHIPixelFormat::PF_R16G16B16A16_SINT, VK_FORMAT_R16G16B16A16_SINT, ComponentMappingRGBA);
	MapFormatSupport(RHIPixelFormat::PF_R16G16B16A16_UINT, VK_FORMAT_R16G16B16A16_UINT, ComponentMappingRGBA);
	MapFormatSupport(RHIPixelFormat::PF_R32G32B32A32_SINT, VK_FORMAT_R32G32B32A32_SINT, ComponentMappingRGBA);
	MapFormatSupport(RHIPixelFormat::PF_R32G32B32A32_UINT, VK_FORMAT_R32G32B32A32_UINT, ComponentMappingRGBA);
	MapFormatSupport(RHIPixelFormat::PF_R16G16B16A16_FLOAT, VK_FORMAT_R16G16B16A16_SFLOAT, ComponentMappingRGBA);
	MapFormatSupport(RHIPixelFormat::PF_R32G32B32A32_FLOAT, VK_FORMAT_R32G32B32A32_SFLOAT, ComponentMappingRGBA);
#endif

}







