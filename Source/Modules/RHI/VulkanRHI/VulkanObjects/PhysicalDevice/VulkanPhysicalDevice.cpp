#include "VulkanObjects/PhysicalDevice/VulkanPhysicalDevice.h"
#include "VulkanObjects/Surface/VulkanSurface.h"
#include "VulkanObjects/Device/VulkanDevice.h"
#include "VulkanObjects/Queue/VulkanQueueFamily.h"

#include <iostream>
#include <set>
VulkanPhysicalDevice::VulkanPhysicalDevice()
{
	Handle = VK_NULL_HANDLE;
}

VulkanPhysicalDevice::VulkanPhysicalDevice(VkPhysicalDevice h)
{
	Handle = h;

	std::uint32_t Count;
	/*
		获取物理设备属性
	*/
	GetPhysicalDeviceProperties(&PhysicalDeviceProperties);
	/*
		获取Layer属性
	*/
	Count = 0;
	EnumerateDeviceLayerProperties(&Count, nullptr);
	LayerProperties.resize(Count);
	EnumerateDeviceLayerProperties(&Count, LayerProperties.data());

	/*
		获取Extension属性
	*/
	Count = 0;
	EnumerateDeviceExtensionProperties(nullptr, &Count, nullptr);
	SupportedExtensions.resize(Count);
	EnumerateDeviceExtensionProperties(nullptr, &Count, SupportedExtensions.data());

	/*
		获取Queue Famliy属性
	*/
	Count = 0;
	GetPhysicalDeviceQueueFamilyProperties(&Count, nullptr);
	QueueFamilyProperties.resize(Count);
	GetPhysicalDeviceQueueFamilyProperties(&Count, QueueFamilyProperties.data());

	/*
		获取Feature
	*/
	GetPhysicalDeviceFeatures(&Features);
	//std::cout << " Features.geometryShader ============================" << " " << Features.geometryShader << std::endl;
	/*
		获取内存属性
	*/
	GetPhysicalDeviceMemoryProperties(&MemoryProperties);
	/*
		获取主机可见Memory Type索引
	*/
	for (std::uint32_t MemoryTypeIndex = 0; MemoryTypeIndex < MemoryProperties.memoryTypeCount; ++MemoryTypeIndex)
	{
		if ((MemoryProperties.memoryTypes[MemoryTypeIndex].propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT))
			HostVisibleMemoryTypeIndices.emplace_back(MemoryTypeIndex);

		if ((MemoryProperties.memoryTypes[MemoryTypeIndex].propertyFlags & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT))
			DeviceLocalMemoryTypeIndices.emplace_back(MemoryTypeIndex);
	}
}

VulkanPhysicalDevice::~VulkanPhysicalDevice()
{
	std::cout << __FUNCTION__  << " " << Handle << std::endl;
}

VkPhysicalDevice VulkanPhysicalDevice::GetHandle()
{
	return Handle;
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
	std::uint32_t MemoryTypeIndex = -1;
	for (MemoryTypeIndex = 0; MemoryTypeIndex < MemoryProperties.memoryTypeCount; MemoryTypeIndex++)
	{
		if ((MemoryTypeFilter & (1 << MemoryTypeIndex)) && ((MemoryProperties.memoryTypes[MemoryTypeIndex].propertyFlags & InMemoryProperties) == InMemoryProperties))
		{
			break;
		}
	}
	return MemoryTypeIndex;
}


void VulkanPhysicalDevice::PrintLayers()
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
		EnumerateDeviceExtensionProperties(LayerProperties[i].layerName, &Count, nullptr);

		/*
			获取Extension
		*/
		std::vector<VkExtensionProperties>			ExtensionPropertyHandles;
		ExtensionPropertyHandles.resize(Count);
		EnumerateDeviceExtensionProperties(LayerProperties[i].layerName, &Count, ExtensionPropertyHandles.data());

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

	std::cout << "\t\tPhysical Device Properties" << std::endl;
	std::cout << "\t\t\tDriver Version " << PhysicalDeviceProperties.driverVersion << std::endl;
	std::cout << "\t\t\tDevice Name " << PhysicalDeviceProperties.deviceName << std::endl;
	std::cout << "\t\t\tDevice Type " << PhysicalDeviceProperties.deviceType << std::endl;
}

void VulkanPhysicalDevice::PrintQueueFamilyProperties()
{
	std::cout << "\t\tQueue Family Properties" << std::endl;
	for (uint32_t i = 0; i < QueueFamilyProperties.size(); i++)
	{
		VulkanQueueFamily* QueueFamily = new VulkanQueueFamily(i, QueueFamilyProperties[i].queueCount);

		if (QueueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			QueueFamily->SetGraphics();
		}

		if (QueueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			QueueFamily->SetCompute();
		}

		if (QueueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			QueueFamily->SetTransfer();
		}

		QueueFamilies.push_back(QueueFamily);


		std::cout
			<< "\t\t\tQueue Count " << QueueFamilyProperties[i].queueCount << " "
			<< "\t\t\tQueue Flags " << QueueFamilyProperties[i].queueFlags << " ";
		if (QueueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
			std::cout << "\t\tVK_QUEUE_GRAPHICS_BIT" << " ";
		if (QueueFamilyProperties[i].queueFlags & VK_QUEUE_COMPUTE_BIT)
			std::cout << "\t\tVK_QUEUE_COMPUTE_BIT" << " ";
		if (QueueFamilyProperties[i].queueFlags & VK_QUEUE_TRANSFER_BIT)
			std::cout << "\t\tVK_QUEUE_TRANSFER_BIT" << " ";
		if (QueueFamilyProperties[i].queueFlags & VK_QUEUE_SPARSE_BINDING_BIT)
			std::cout << "\t\tVK_QUEUE_SPARSE_BINDING_BIT" << " ";
		if (QueueFamilyProperties[i].queueFlags & VK_QUEUE_PROTECTED_BIT)
			std::cout << "\t\tVK_QUEUE_PROTECTED_BIT" << " ";
		if (QueueFamilyProperties[i].queueFlags & VK_QUEUE_OPTICAL_FLOW_BIT_NV)
			std::cout << "\t\tVK_QUEUE_OPTICAL_FLOW_BIT_NV" << " ";
		if (QueueFamilyProperties[i].queueFlags & VK_QUEUE_VIDEO_DECODE_BIT_KHR)
			std::cout << "\t\tVK_QUEUE_VIDEO_DECODE_BIT_KHR" << " ";
		if (QueueFamilyProperties[i].queueFlags & VK_QUEUE_VIDEO_ENCODE_BIT_KHR)
			std::cout << "\t\tVK_QUEUE_VIDEO_ENCODE_BIT_KHR" << " ";

		std::cout << std::endl;
	}
}

void VulkanPhysicalDevice::PrintMemoryProperties()
{
	std::cout << "\t\tMemory Properties " << std::endl;

	std::cout
		<< "\t\t\tMemory Type Count " << MemoryProperties.memoryTypeCount << " "
		<< std::endl;

	for (uint32_t i = 0; i < MemoryProperties.memoryTypeCount; i++)
	{
		std::cout
			<< "\t\t\t\t" << "[" << i << "]" << "Heap Index " << MemoryProperties.memoryTypes[i].heapIndex << " "
			<< "\t\t\t\t" << "Property Flags " << MemoryProperties.memoryTypes[i].propertyFlags << " ";

	
		if (MemoryProperties.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
		{
			std::cout << "VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT" << " ";
		}
		if (MemoryProperties.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
		{
			std::cout << "VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT" << " ";
		}
		if (MemoryProperties.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
		{
			std::cout << "VK_MEMORY_PROPERTY_HOST_COHERENT_BIT" << " ";
		}
		if (MemoryProperties.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_HOST_CACHED_BIT)
		{
			std::cout << "VK_MEMORY_PROPERTY_HOST_CACHED_BIT" << " ";
		}
		if (MemoryProperties.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT)
		{
			std::cout << "VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT" << " ";
		}
		if (MemoryProperties.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_PROTECTED_BIT)
		{
			std::cout << "VK_MEMORY_PROPERTY_PROTECTED_BIT" << " ";
		}
		if (MemoryProperties.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD)
		{
			std::cout << "VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD" << " ";
		}
		if (MemoryProperties.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD)
		{
			std::cout << "VK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD" << " ";
		}
		if (MemoryProperties.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_RDMA_CAPABLE_BIT_NV)
		{
			std::cout << "VK_MEMORY_PROPERTY_RDMA_CAPABLE_BIT_NV" << " ";
		}

		if (MemoryProperties.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
		{
			//HostVisibleIndex = i;

			std::cout << "\t\t\t\tHostVisibleIndex = Memory Type Index " << i << " ";
		}

		std::cout << std::endl;
	}

	std::cout
		<< "\t\t\tMemory Heap Count " << MemoryProperties.memoryHeapCount << " "
		<< std::endl;
	for (uint32_t i = 0; i < MemoryProperties.memoryHeapCount; i++)
	{
		std::cout
			<< "\t\t\t\tSize " << MemoryProperties.memoryHeaps[i].size << " "
			<< "\t\t\t\tFlags " << MemoryProperties.memoryHeaps[i].flags << " "
			<< std::endl;
	}
}

void VulkanPhysicalDevice::PrintFeatures()
{
	std::cout
		<< "\t\tFeatures" << " "
		<< std::endl;

	std::cout
		<< "\t\t" << "\trobustBufferAccess " << Features.robustBufferAccess << "\n"
		<< "\t\t" << "\tfullDrawIndexUint32 " << Features.fullDrawIndexUint32 << "\n"
		<< "\t\t" << "\timageCubeArray " << Features.imageCubeArray << "\n"
		<< "\t\t" << "\tindependentBlend " << Features.independentBlend << "\n"
		<< "\t\t" << "\tgeometryShader " << Features.geometryShader << "\n"
		<< "\t\t" << "\ttessellationShader " << Features.tessellationShader << "\n"
		<< "\t\t" << "\tsampleRateShading " << Features.sampleRateShading << "\n"
		<< "\t\t" << "\tdualSrcBlend " << Features.dualSrcBlend << "\n"
		<< "\t\t" << "\tlogicOp " << Features.logicOp << "\n"
		<< "\t\t" << "\tmultiDrawIndirect " << Features.multiDrawIndirect << "\n"
		<< "\t\t" << "\tdrawIndirectFirstInstance " << Features.drawIndirectFirstInstance << "\n"
		<< "\t\t" << "\tdepthClamp " << Features.depthClamp << "\n"
		<< "\t\t" << "\tdepthBiasClamp " << Features.depthBiasClamp << "\n"
		<< "\t\t" << "\tfillModeNonSolid " << Features.fillModeNonSolid << "\n"
		<< "\t\t" << "\tdepthBounds " << Features.depthBounds << "\n"
		<< "\t\t" << "\twideLines " << Features.wideLines << "\n"
		<< "\t\t" << "\tlargePoints " << Features.largePoints << "\n"
		<< "\t\t" << "\talphaToOne " << Features.alphaToOne << "\n"
		<< "\t\t" << "\tmultiViewport " << Features.multiViewport << "\n"
		<< "\t\t" << "\tsamplerAnisotropy " << Features.samplerAnisotropy << "\n"
		<< "\t\t" << "\ttextureCompressionETC2 " << Features.textureCompressionETC2 << "\n"
		<< "\t\t" << "\ttextureCompressionASTC_LDR " << Features.textureCompressionASTC_LDR << "\n"
		<< "\t\t" << "\ttextureCompressionBC " << Features.textureCompressionBC << "\n"
		<< "\t\t" << "\tocclusionQueryPrecise " << Features.occlusionQueryPrecise << "\n"
		<< "\t\t" << "\tpipelineStatisticsQuery " << Features.pipelineStatisticsQuery << "\n"
		<< "\t\t" << "\tvertexPipelineStoresAndAtomics " << Features.vertexPipelineStoresAndAtomics << "\n"
		<< "\t\t" << "\tfragmentStoresAndAtomics " << Features.fragmentStoresAndAtomics << "\n"
		<< "\t\t" << "\tshaderTessellationAndGeometryPointSize " << Features.shaderTessellationAndGeometryPointSize << "\n"
		<< "\t\t" << "\tshaderImageGatherExtended " << Features.shaderImageGatherExtended << "\n"
		<< "\t\t" << "\tshaderStorageImageExtendedFormats " << Features.shaderStorageImageExtendedFormats << "\n"
		<< "\t\t" << "\tshaderStorageImageMultisample " << Features.shaderStorageImageMultisample << "\n"
		<< "\t\t" << "\tshaderStorageImageReadWithoutFormat " << Features.shaderStorageImageReadWithoutFormat << "\n"
		<< "\t\t" << "\tshaderStorageImageWriteWithoutFormat " << Features.shaderStorageImageWriteWithoutFormat << "\n"
		<< "\t\t" << "\tshaderUniformBufferArrayDynamicIndexing " << Features.shaderUniformBufferArrayDynamicIndexing << "\n"
		<< "\t\t" << "\tshaderSampledImageArrayDynamicIndexing " << Features.shaderSampledImageArrayDynamicIndexing << "\n"
		<< "\t\t" << "\tshaderStorageBufferArrayDynamicIndexing " << Features.shaderStorageBufferArrayDynamicIndexing << "\n"
		<< "\t\t" << "\tshaderStorageImageArrayDynamicIndexing " << Features.shaderStorageImageArrayDynamicIndexing << "\n"
		<< "\t\t" << "\tshaderClipDistance " << Features.shaderClipDistance << "\n"
		<< "\t\t" << "\tshaderCullDistance " << Features.shaderCullDistance << "\n"
		<< "\t\t" << "\tshaderFloat64 " << Features.shaderFloat64 << "\n"
		<< "\t\t" << "\tshaderInt64 " << Features.shaderInt64 << "\n"
		<< "\t\t" << "\tshaderInt16 " << Features.shaderInt16 << "\n"
		<< "\t\t" << "\tshaderResourceResidency " << Features.shaderResourceResidency << "\n"
		<< "\t\t" << "\tshaderResourceMinLod " << Features.shaderResourceMinLod << "\n"
		<< "\t\t" << "\tsparseBinding " << Features.sparseBinding << "\n"
		<< "\t\t" << "\tsparseResidencyBuffer " << Features.sparseResidencyBuffer << "\n"
		<< "\t\t" << "\tsparseResidencyImage2D " << Features.sparseResidencyImage2D << "\n"
		<< "\t\t" << "\tsparseResidencyImage3D " << Features.sparseResidencyImage3D << "\n"
		<< "\t\t" << "\tsparseResidency2Samples " << Features.sparseResidency2Samples << "\n"
		<< "\t\t" << "\tsparseResidency4Samples " << Features.sparseResidency4Samples << "\n"
		<< "\t\t" << "\tsparseResidency8Samples " << Features.sparseResidency8Samples << "\n"
		<< "\t\t" << "\tsparseResidency16Samples " << Features.sparseResidency16Samples << "\n"
		<< "\t\t" << "\tsparseResidencyAliased " << Features.sparseResidencyAliased << "\n"
		<< "\t\t" << "\tvariableMultisampleRate " << Features.variableMultisampleRate << "\n"
		<< "\t\t" << "\tinheritedQueries " << Features.inheritedQueries << "\n"
		<< std::endl;
}

VulkanDevice* VulkanPhysicalDevice::CreateDevice()
{
	/*
		改为为每个Queue Family创建Queue
	*/
	std::vector<VkDeviceQueueCreateInfo> QueueCreateInfos;
	std::vector<std::vector<float>> QueuePriorityForEachQueueFamily;
	for (int QueueFamilyIndex = 0; QueueFamilyIndex < QueueFamilyProperties.size(); QueueFamilyIndex++)
	{
		std::cout << "CreateDevice QueueFamilyIndex " << QueueFamilyIndex << " queueCount " << QueueFamilyProperties[QueueFamilyIndex].queueCount << std::endl;
		std::vector<float> QueuePriority;
		QueuePriority.resize(QueueFamilyProperties[QueueFamilyIndex].queueCount);
		for (int i = 0; i < QueuePriority.size(); i++)
			QueuePriority[i] = 1.f;
		QueuePriorityForEachQueueFamily.emplace_back(QueuePriority);

		VkDeviceQueueCreateInfo QueueCreateInfo = {};
		QueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		QueueCreateInfo.pNext = nullptr;
		QueueCreateInfo.flags = 0;
		QueueCreateInfo.queueFamilyIndex = QueueFamilyIndex;
		QueueCreateInfo.queueCount = QueueFamilyProperties[QueueFamilyIndex].queueCount;
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
	DeviceCreateInfo.pEnabledFeatures = &Features;

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
	if (PresentQueueFamilyIndices.size() == 0)
		std::cout << "No Queue Famliy support present" << std::endl;

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
	
	std::cout << "Query ----------------- QueueFamilyProperties " << QueueFamilyProperties.size() << std::endl;
	for (std::uint32_t QueueFamilyIndex = 0; QueueFamilyIndex < QueueFamilyProperties.size(); QueueFamilyIndex++)
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
