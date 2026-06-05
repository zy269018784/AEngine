#include "VulkanRHI/VulkanObjects/PhysicalDevice/VulkanPhysicalDeviceFeatures.h"
#include "VulkanRHI/VulkanObjects/PhysicalDevice/VulkanPhysicalDevice.h"
#include <iostream>
VulkanPhysicalDeviceFeatures::VulkanPhysicalDeviceFeatures(VulkanPhysicalDevice *InPhysicalDevice)
    : PhysicalDevice(InPhysicalDevice)
{
    AccelerationStructureFeatures        = {};
    AccelerationStructureFeatures.sType     = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_FEATURES_KHR;
    AccelerationStructureFeatures.pNext     = nullptr;

    Features2                            = {};
    Features2.sType                         = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
    Features2.pNext                         = &AccelerationStructureFeatures;

    //VkPhysicalDeviceDescriptorIndexingFeatures indexing_features{ VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_FEATURES_EXT, nullptr };
    //AccelerationStructureFeatures.pNext = &indexing_features;
    PhysicalDevice->GetPhysicalDeviceFeatures(&Features);
    PhysicalDevice->GetPhysicalDeviceFeatures2(&Features2);

    std::cout << "AccelerationStructureFeatures.accelerationStructure " << AccelerationStructureFeatures.accelerationStructure << std::endl;
}

VulkanPhysicalDeviceFeatures::~VulkanPhysicalDeviceFeatures()
{

}

void VulkanPhysicalDeviceFeatures::Print(int Tabs)
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