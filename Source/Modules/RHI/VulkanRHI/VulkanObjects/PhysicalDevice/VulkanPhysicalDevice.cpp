#include "VulkanObjects/PhysicalDevice/VulkanPhysicalDevice.h"
#include "VulkanObjects/PhysicalDevice/VulkanPhysicalDeviceFeatures.h"
#include "VulkanObjects/PhysicalDevice/VulkanPhysicalDeviceProperties.h"
#include "VulkanObjects/PhysicalDevice/VulkanPhysicalDeviceMemoryProperties.h"
#include "VulkanRHI/VulkanObjects/PhysicalDevice/VulkanPhysicalDeviceLayerProperties.h"
#include "VulkanObjects/Surface/VulkanSurface.h"
#include "VulkanObjects/Device/VulkanDevice.h"
#include "VulkanObjects/Queue/VulkanQueueFamily.h"

#include <iostream>
#include <set>

#include "VulkanPhysicalDeviceQueueFamilyProperties.h"

VulkanPhysicalDevice::VulkanPhysicalDevice()
{
	Handle = VK_NULL_HANDLE;
}

VulkanPhysicalDevice::VulkanPhysicalDevice(VkPhysicalDevice h)
{
	Handle = h;
	LayerProperties = new VulkanPhysicalDeviceLayerProperties(this);
	Features = new VulkanPhysicalDeviceFeatures(this);
	Properties = new VulkanPhysicalDeviceProperties(this);
	MemoryProperties = new VulkanPhysicalDeviceMemoryProperties(this);
	QueueFamilyProperties = new VulkanPhysicalDeviceQueueFamilyProperties(this);
	QueueFamilies = QueueFamilyProperties->CreateQueueFamilies();

	std::uint32_t Count;

	/*
		获取Extension属性
	*/
	Count = 0;
	EnumerateDeviceExtensionProperties(nullptr, &Count, nullptr);
	SupportedExtensions.resize(Count);
	EnumerateDeviceExtensionProperties(nullptr, &Count, SupportedExtensions.data());
#if 0
	/*
		获取Queue Famliy属性
	*/
	Count = 0;
	GetPhysicalDeviceQueueFamilyProperties(&Count, nullptr);
	QueueFamilyProperties.resize(Count);
	GetPhysicalDeviceQueueFamilyProperties(&Count, QueueFamilyProperties.data());
#endif
	/*
		获取Feature
	*/

	InitFeatures();

	/*
		获取内存属性
	*/
	//GetPhysicalDeviceMemoryProperties(&MemoryProperties);
	/*
		获取主机可见Memory Type索引
	*/
	for (std::uint32_t MemoryTypeIndex = 0; MemoryTypeIndex < MemoryProperties->MemoryProperties.memoryTypeCount; ++MemoryTypeIndex)
	{
		if ((MemoryProperties->MemoryProperties.memoryTypes[MemoryTypeIndex].propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT))
			HostVisibleMemoryTypeIndices.emplace_back(MemoryTypeIndex);

		if ((MemoryProperties->MemoryProperties.memoryTypes[MemoryTypeIndex].propertyFlags & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT))
			DeviceLocalMemoryTypeIndices.emplace_back(MemoryTypeIndex);
	}
}

VulkanPhysicalDevice::~VulkanPhysicalDevice()
{
	std::cout << __FUNCTION__  << " " << Handle << std::endl;
	delete Features;
	delete Properties;
	delete MemoryProperties;
	delete QueueFamilyProperties;
	delete LayerProperties;
}

void VulkanPhysicalDevice::QuerySupportedPixelFormats() {

	//VkFormat format = VK_FORMAT_D32_SFLOAT_S8_UINT;
	//VkFormatProperties formatProperties;

	std::vector<VkFormat> Candidates = {
		VK_FORMAT_D32_SFLOAT_S8_UINT,  // 32位深度 + 8位模板 (高精度，首选)
		VK_FORMAT_D24_UNORM_S8_UINT,   // 24位深度 + 8位模板 (常见)
		VK_FORMAT_D32_SFLOAT,          // 32位深度，仅深度 (如果不需要模板)
		VK_FORMAT_D16_UNORM            // 16位深度，仅深度 (最低精度)
	};


	VkFormat chosenFormat = VK_FORMAT_UNDEFINED;
	for (VkFormat format : Candidates) {
		VkFormatProperties props;
		vkGetPhysicalDeviceFormatProperties(Handle, format, &props);

		// 检查是否可以作为深度模板附件使用
		if (props.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
		{
			chosenFormat = format;
			std::cout << "optimalTilingFeatures " << format << std::endl;
			//break;
		}
		if (props.linearTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
		{
			chosenFormat = format;
			std::cout << "linearTilingFeatures " << format << std::endl;
			//break;
		}
	}
	//GetPhysicalDeviceFormatProperties(format, &formatProperties);
//
	//std::cout << "VK_FORMAT_R8G8B8A8_UNORM support:\n";
	//std::cout << "Linear tiling features: "
	//		  << formatProperties.linearTilingFeatures << "\n";
	//std::cout << "Optimal tiling features: "
	//		  << formatProperties.optimalTilingFeatures << "\n";
	//std::cout << "Buffer features: "
	//		  << formatProperties.bufferFeatures << "\n";
}

void VulkanPhysicalDevice::InitFeatures()
{
#if 0
	GetPhysicalDeviceFeatures(&VulkanFeatures);

	Vulkan12Features 		= {};
	Vulkan12Features.sType  = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;

	VulkanFeatures2.sType 	= VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
	VulkanFeatures2.pNext 	= &Vulkan12Features;
	GetPhysicalDeviceFeatures2(&VulkanFeatures2);

	Features[static_cast<std::uint32_t>(RHIFeatures::DepthBoundsTest)] = Features->Features.depthBounds;
	Features[static_cast<std::uint32_t>(RHIFeatures::MultiViewport)] = Features->Features.multiViewport;

	std::cout << "imagelessFramebuffer " << Vulkan12Features.imagelessFramebuffer << std::endl;
#endif
}

VkPhysicalDevice VulkanPhysicalDevice::GetHandle()
{
	return Handle;
}

VkPhysicalDeviceFeatures VulkanPhysicalDevice::GetGeatures() const
{
	return Features->Features;
}

std::uint32_t VulkanPhysicalDevice::GetQueueFamilyCount() const
{
	return QueueFamilies.size();
}

VulkanQueueFamily* VulkanPhysicalDevice::GetQueueFamily(std::uint32_t Index) const
{
	return QueueFamilies[Index];
}

std::uint32_t VulkanPhysicalDevice::FindMemoryType(std::uint32_t MemoryTypeFilter, VkMemoryPropertyFlags InMemoryProperties)
{
	return MemoryProperties->FindMemoryType(MemoryTypeFilter, InMemoryProperties);
}


void VulkanPhysicalDevice::PrintLayers()
{
	LayerProperties->Print(3);
}


void VulkanPhysicalDevice::PrintExtensions()
{
	/*
		获取Extension数量
	*/
	uint32_t Count = 0;
	EnumerateDeviceExtensionProperties(nullptr, &Count, nullptr);

	/*
		获取Extension
	*/
	SupportedExtensions.resize(Count);
	EnumerateDeviceExtensionProperties(nullptr, &Count, SupportedExtensions.data());

	std::cout << "\t\tPhysical Device Extensions " << std::endl;
	for (uint32_t i = 0; i < Count; i++)
	{
		std::cout
			<< "\t\t\t"
			<< SupportedExtensions[i].extensionName << " "
			//	<< ExtensionPropertyHandles[i].specVersion << " "
			<< std::endl;
	}
}

void VulkanPhysicalDevice::PrintProperties()
{
	Properties->Print(2);
}

void VulkanPhysicalDevice::PrintQueueFamilyProperties()
{
	QueueFamilyProperties->Print(2);
}

void VulkanPhysicalDevice::PrintMemoryProperties()
{
	MemoryProperties->Print(3);
}

void VulkanPhysicalDevice::PrintFeatures()
{
	Features->Print(3);

}



VulkanDevice* VulkanPhysicalDevice::CreateDevice()
{
	/*
		改为为每个Queue Family创建Queue
	*/
	std::vector<VkDeviceQueueCreateInfo> QueueCreateInfos;
	std::vector<std::vector<float>> QueuePriorityForEachQueueFamily;
	for (int QueueFamilyIndex = 0; QueueFamilyIndex < QueueFamilyProperties->QueueFamilyProperties.size(); QueueFamilyIndex++)
	{
		std::cout << "CreateDevice QueueFamilyIndex " << QueueFamilyIndex << " queueCount " << QueueFamilyProperties->QueueFamilyProperties[QueueFamilyIndex].queueCount << std::endl;
		std::vector<float> QueuePriority;
		QueuePriority.resize(QueueFamilyProperties->QueueFamilyProperties[QueueFamilyIndex].queueCount);
		for (int i = 0; i < QueuePriority.size(); i++)
			QueuePriority[i] = 1.f;
		QueuePriorityForEachQueueFamily.emplace_back(QueuePriority);

		VkDeviceQueueCreateInfo QueueCreateInfo = {};
		QueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		QueueCreateInfo.pNext = nullptr;
		QueueCreateInfo.flags = 0;
		QueueCreateInfo.queueFamilyIndex = QueueFamilyIndex;
		QueueCreateInfo.queueCount = QueueFamilyProperties->QueueFamilyProperties[QueueFamilyIndex].queueCount;
		QueueCreateInfo.pQueuePriorities = QueuePriorityForEachQueueFamily[QueueFamilyIndex].data();
		QueueCreateInfos.push_back(QueueCreateInfo);
	}
	/*
		暂时打开交换链
	*/
	std::vector<const char*> DeviceExtensions = {
		// "VK_KHR_swapchain"
		VK_KHR_SWAPCHAIN_EXTENSION_NAME,

		"VK_EXT_extended_dynamic_state",
		//VK_KHR_DYNAMIC_RENDERING_EXTENSION_NAME
	};
#if 0
	/*
		打开各向异性采样
	*/
	VkPhysicalDeviceFeatures DeviceFeatures{};

	/*
		imageCubeArray specifies whether image views with a VkImageViewType of VK_IMAGE_VIEW_TYPE_CUBE_ARRAY can be created,
		and that the corresponding SampledCubeArray and ImageCubeArray SPIR-V capabilities can be used in shader code.
	*/
	DeviceFeatures.imageCubeArray = Features.imageCubeArray;

	/*
		samplerAnisotropy specifies whether anisotropic filtering is supported. If this feature is not enabled, 
		the anisotropyEnable member of the VkSamplerCreateInfo structure must be VK_FALSE.
	*/
	DeviceFeatures.samplerAnisotropy = Features.samplerAnisotropy;
	/*
		fragmentStoresAndAtomics specifies whether storage buffers and images support stores and atomic operations in the fragment shader stage. 
		If this feature is not enabled, all storage image, storage texel buffer, and storage buffer variables used by the
		fragment stage in shader modules must be decorated with the NonWritable decoration (or the readonly memory qualifier in GLSL).
	*/
	DeviceFeatures.fragmentStoresAndAtomics = Features.fragmentStoresAndAtomics;

	/*
		depthBounds specifies whether depth bounds tests are supported. 
		If this feature is not enabled, the depthBoundsTestEnable member of the VkPipelineDepthStencilStateCreateInfo structure
		must be VK_FALSE unless the VK_DYNAMIC_STATE_DEPTH_BOUNDS_TEST_ENABLE dynamic state is enabled, in which case the depthBoundsTestEnable
		parameter to vkCmdSetDepthBoundsTestEnable must be VK_FALSE. When depthBoundsTestEnable is VK_FALSE, the minDepthBounds and maxDepthBounds
		members of the VkPipelineDepthStencilStateCreateInfo structure are ignored.
	*/
	DeviceFeatures.depthBounds = Features.depthBounds;

	/*
		geometryShader specifies whether geometry shaders are supported. If this feature is not enabled, 
		the VK_SHADER_STAGE_GEOMETRY_BIT and VK_PIPELINE_STAGE_GEOMETRY_SHADER_BIT enum values must not be used. 
		This also specifies whether shader modules can declare the Geometry capability.
	*/
	DeviceFeatures.geometryShader = Features.geometryShader;
#endif
	VkDeviceCreateInfo DeviceCreateInfo{};
	DeviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	DeviceCreateInfo.queueCreateInfoCount = QueueCreateInfos.size();
	DeviceCreateInfo.pQueueCreateInfos = QueueCreateInfos.data();
	DeviceCreateInfo.enabledExtensionCount = DeviceExtensions.size();
	DeviceCreateInfo.ppEnabledExtensionNames = DeviceExtensions.data();
	DeviceCreateInfo.enabledLayerCount = 0;
	DeviceCreateInfo.ppEnabledLayerNames = nullptr;
	DeviceCreateInfo.flags = 0;
	DeviceCreateInfo.pEnabledFeatures = &Features->Features;

	VkDevice DeviceHandle;
	VkResult Result = CreateDevice(&DeviceCreateInfo, nullptr, &DeviceHandle);
	if (VK_SUCCESS != Result)
	{
		std::cout << "vkCreateDevice failed" << std::endl;
		return nullptr;
	}
	std::cout << "vkCreateDevice ok " << Handle << std::endl;


	VulkanDevice* Device = new VulkanDevice(this, DeviceHandle);
	//Device->pPhysicalDevice = this;
	//std::cout << "PresentQueueFamilyIndex " << PresentQueueFamilyIndex << std::endl;
	//if (PresentQueueFamilyIndices.size() == 0)
	//	std::cout << "No Queue Famliy support present" << std::endl;

	/*
		给第一个Present Queue Family创建1个Queue
		FIX 暂时创建prenset 队列
	*/
	//Device->GetPresentQueue(PresentQueueFamilyIndices[0], 0);
	Device->GetPresentQueue(0, 0);
	/*
		为每个Queue Family创建最大数量的Queue
	*/
	Device->CreateQueue();

	return Device;
}

VulkanDevice* VulkanPhysicalDevice::CreateDevice2()
{
	/*
		每个Queue Family创建最大数量的队列
	*/
	std::vector<VkDeviceQueueCreateInfo> QueueCreateInfos;
	float QueuePriority = 1.0f;
	for (auto QueueFamily : QueueFamilies)
	{
		VkDeviceQueueCreateInfo QueueCreateInfo = {};
		QueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		QueueCreateInfo.pNext = nullptr;
		QueueCreateInfo.flags = 0;
		QueueCreateInfo.queueFamilyIndex = QueueFamily->GetHandle();
		QueueCreateInfo.queueCount = QueueFamily->GetQueueCount();
		QueueCreateInfo.pQueuePriorities = &QueuePriority;
		QueueCreateInfos.push_back(QueueCreateInfo);
	}

	/*
		暂时打开交换链
	*/
	std::vector<const char*> PhysicalDeviceExtensions =
	{
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	VkPhysicalDeviceFeatures PhysicalDeviceFeatures{};
	PhysicalDeviceFeatures.samplerAnisotropy = VK_TRUE;

	VkDeviceCreateInfo DeviceCreateInfo{};
	DeviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	DeviceCreateInfo.queueCreateInfoCount = QueueCreateInfos.size();
	DeviceCreateInfo.pQueueCreateInfos = QueueCreateInfos.data();
	DeviceCreateInfo.enabledExtensionCount = PhysicalDeviceExtensions.size();
	DeviceCreateInfo.ppEnabledExtensionNames = PhysicalDeviceExtensions.data();
	DeviceCreateInfo.enabledLayerCount = 0;
	DeviceCreateInfo.ppEnabledLayerNames = nullptr;
	DeviceCreateInfo.flags = 0;
	DeviceCreateInfo.pEnabledFeatures = &PhysicalDeviceFeatures;

	VkDevice DeviceHandle;
	VkResult Result = CreateDevice(&DeviceCreateInfo, nullptr, &DeviceHandle);
	if (VK_SUCCESS != Result)
	{
		std::cout << "vkCreateDevice failed" << std::endl;
		return nullptr;
	}
	std::cout << "vkCreateDevice ok " << Handle << std::endl;
	VulkanDevice* Device = new VulkanDevice(this, DeviceHandle);

	Device->CreateQueue();

	return Device;
}


bool VulkanPhysicalDevice::CheckExtensionSupport(std::vector<const char*> RequiredExtensions)
{
	/*
		检查释放支持所有的扩展
	*/
	std::set<std::string> AllRequiredExtensions(RequiredExtensions.begin(), RequiredExtensions.end());
	for (const auto& Extension : SupportedExtensions)
	{
		AllRequiredExtensions.erase(Extension.extensionName);
	}

	return AllRequiredExtensions.empty();
}

void VulkanPhysicalDevice::Query(const VulkanSurface* Surface)
{
	
	std::cout << "Query ----------------- QueueFamilyProperties " << QueueFamilyProperties->QueueFamilyProperties.size() << std::endl;
	for (std::uint32_t QueueFamilyIndex = 0; QueueFamilyIndex < QueueFamilyProperties->QueueFamilyProperties.size(); QueueFamilyIndex++)
	{
		VkBool32 PresentSupport = false;

		GetPhysicalDeviceSurfaceSupportKHR(QueueFamilyIndex, Surface->GetHandle(), &PresentSupport);

		if (PresentSupport)
		{
			PresentQueueFamilyIndices.push_back(QueueFamilyIndex);
			std::cout << "PresentQueueFamilyIndex AAAAAAAA " << QueueFamilyIndex << std::endl; 
				break;
		}
	}

	for (int i = 0; i < HostVisibleMemoryTypeIndices.size(); i++)
	{
		std::cout << "HostVisibleMemoryTypeIndices " << HostVisibleMemoryTypeIndices[i] << std::endl;
	}

	HostVisibleIndex = -1;
	VkPhysicalDeviceMemoryProperties memProperties;
	GetPhysicalDeviceMemoryProperties(&memProperties);
	for (uint32_t i = 0; i < memProperties.memoryTypeCount; ++i) {
		if ((memProperties.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)) {
			HostVisibleIndex = i;
			break;
		}
	}
	std::cout << "HostVisibleIndex " << HostVisibleIndex << std::endl;
}

VkPhysicalDeviceLimits	VulkanPhysicalDevice::GetPhysicalDeviceLimits() const {
	return Properties->Properties.limits;
}