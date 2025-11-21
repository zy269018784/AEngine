#include "VulkanRayTracingPipeline.h"
#include "VulkanObjects/Core/VulkanCore.h"
#include "VulkanObjects/Shader/VulkanShader.h"
#include <stdexcept>
#if 0
VulkanRayTracingPipeline::VulkanRayTracingPipeline(VulkanDevice* InDevice)
	: VulkanPipeline(InDevice)
{

}

void VulkanRayTracingPipeline::Create()
{
	/*
		Shader
	*/
	std::vector<VkPipelineShaderStageCreateInfo> ShaderStageCreateInfos;
	for (int i = 0; i < Shaders.size(); i++)
	{
		VkPipelineShaderStageCreateInfo			ShaderStageCreateInfo{};
		ShaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		ShaderStageCreateInfo.module = ((VulkanShader*)Shaders[i])->GetHandle();
		ShaderStageCreateInfo.pName = "main";
		ShaderStageCreateInfo.stage = ToVkShaderStageFlagBits(Shaders[i]->Type_);
		ShaderStageCreateInfos.push_back(ShaderStageCreateInfo);
	}
#if 0
	std::vector<VkRayTracingShaderGroupCreateInfoNV> ShaderGroupCreateInfos;
	ShaderGroupCreateInfos.resize(0);
	ShaderGroupCreateInfos.shrink_to_fit();

	VkRayTracingPipelineCreateInfoNV CreateInfo{};
	CreateInfo.sType						= VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_CREATE_INFO_NV;
	CreateInfo.pNext						= nullptr;
	CreateInfo.flags						= 0;	
	CreateInfo.stageCount					= ShaderStageCreateInfos.size();
	CreateInfo.pStages						= ShaderStageCreateInfos.data();
	CreateInfo.groupCount					= ShaderGroupCreateInfos.size();
	CreateInfo.pGroups						= ShaderGroupCreateInfos.data();
	CreateInfo.maxRecursionDepth			= 10;
	CreateInfo.layout						= PipelineLayout;
	CreateInfo.basePipelineHandle			= VK_NULL_HANDLE;
	/*
		不是派生管线
	*/
	CreateInfo.basePipelineIndex			= -1;
	VkResult ret = vkCreateRayTracingPipelinesNV(Device->GetHandle(), VK_NULL_HANDLE, 1,  &CreateInfo, nullptr, &Handle);
	if (ret != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create graphics pipeline!");
	}
#endif
#if 1
	std::vector<VkRayTracingShaderGroupCreateInfoKHR> ShaderGroupCreateInfos;
	ShaderGroupCreateInfos.resize(1);
	ShaderGroupCreateInfos.shrink_to_fit();

	ShaderGroupCreateInfos[0].sType								= VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_KHR;
	ShaderGroupCreateInfos[0].pNext								= nullptr;
	ShaderGroupCreateInfos[0].type								= VK_RAY_TRACING_SHADER_GROUP_TYPE_GENERAL_KHR;
	ShaderGroupCreateInfos[0].generalShader						= 0;
	ShaderGroupCreateInfos[0].closestHitShader					= 0;
	ShaderGroupCreateInfos[0].anyHitShader						= 0;
	ShaderGroupCreateInfos[0].intersectionShader				= 0;
	ShaderGroupCreateInfos[0].pShaderGroupCaptureReplayHandle   = nullptr;


	VkRayTracingPipelineCreateInfoKHR  CreateInfo{};
	CreateInfo.sType					    = VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_CREATE_INFO_KHR;
	CreateInfo.pNext						= nullptr;
	CreateInfo.flags						= 0;
	CreateInfo.stageCount					= ShaderStageCreateInfos.size();
	CreateInfo.pStages						= ShaderStageCreateInfos.data();
	/*
		着色器组
	*/
	CreateInfo.groupCount					= ShaderGroupCreateInfos.size();
	CreateInfo.pGroups						= ShaderGroupCreateInfos.data();
	CreateInfo.maxPipelineRayRecursionDepth	= 10;
	/*
		管线库支持(可选)	
	*/
	CreateInfo.pLibraryInfo					= nullptr;
	CreateInfo.pLibraryInterface			= nullptr;
	/*
		动态状态(可选)	
	*/
	CreateInfo.pDynamicState				= nullptr;
	CreateInfo.layout						= PipelineLayout;
	CreateInfo.basePipelineHandle			= VK_NULL_HANDLE;
	CreateInfo.basePipelineIndex			= -1; 

	vkCreateRayTracingPipelinesKHR(Device->GetHandle(), VK_NULL_HANDLE, VK_NULL_HANDLE, 1, &CreateInfo, nullptr, &Handle);
#endif
}
/*
	vkCmdBuildAccelerationStructureNV
	vkBindAccelerationStructureMemoryNV

	vkCmdBuildAccelerationStructuresKHR		:		build acceleration structures
	vkCmdBuildAccelerationStructuresIndirectKHR


	VkBuildAccelerationStructureModeKHR
	VkAccelerationStructureGeometryKHR
	VkAccelerationStructureGeometryDataKHR
	VkAccelerationStructureGeometryTrianglesDataKHR 
    VkAccelerationStructureGeometryAabbsDataKHR 
    VkAccelerationStructureGeometryInstancesDataKHR 

typedef enum VkAccelerationStructureTypeKHR {
	VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR = 0,
	VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR = 1,
	VK_ACCELERATION_STRUCTURE_TYPE_GENERIC_KHR = 2,
	VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_NV = VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR,
	VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_NV = VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
	VK_ACCELERATION_STRUCTURE_TYPE_MAX_ENUM_KHR = 0x7FFFFFFF
} VkAccelerationStructureTypeKHR;

*/

/*
	BLAS: 底层加速结构
	TLAS: 顶层加速结构
*/
void CreateAccl()
{
	VkDevice Device = VK_NULL_HANDLE;

	VkDeviceOrHostAddressConstKHR InstanceDataDeviceAddress{};

	VkAccelerationStructureGeometryKHR AccelerationStructureGeometry{};
	AccelerationStructureGeometry.sType									= VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR;
	AccelerationStructureGeometry.geometryType							= VK_GEOMETRY_TYPE_INSTANCES_KHR;
	AccelerationStructureGeometry.flags									= VK_GEOMETRY_OPAQUE_BIT_KHR;
	AccelerationStructureGeometry.geometry.instances.sType				= VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_INSTANCES_DATA_KHR;
	AccelerationStructureGeometry.geometry.instances.arrayOfPointers	= VK_FALSE;
	AccelerationStructureGeometry.geometry.instances.data				= InstanceDataDeviceAddress;
}

void BuildBLASFromModel()
{
	VkDevice Device = VK_NULL_HANDLE;

	VkDeviceOrHostAddressConstKHR vertex_data_device_address{};
	VkDeviceOrHostAddressConstKHR index_data_device_address{};
	VkDeviceOrHostAddressConstKHR transform_matrix_device_address{};

	VkAccelerationStructureGeometryTrianglesDataKHR AccelerationStructureGeometryTrianglesData{ };
	AccelerationStructureGeometryTrianglesData.sType			= VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR;
	AccelerationStructureGeometryTrianglesData.vertexFormat		= VK_FORMAT_R32G32B32_SFLOAT;
	AccelerationStructureGeometryTrianglesData.vertexData		= vertex_data_device_address;
	AccelerationStructureGeometryTrianglesData.maxVertex		= 100;
	AccelerationStructureGeometryTrianglesData.vertexStride		= 12;
	AccelerationStructureGeometryTrianglesData.indexType		= VK_INDEX_TYPE_UINT32;
	AccelerationStructureGeometryTrianglesData.indexData		= index_data_device_address;
	AccelerationStructureGeometryTrianglesData.transformData	= transform_matrix_device_address;

	// The bottom level acceleration structure contains one set of triangles as the input geometry
	VkAccelerationStructureGeometryKHR acceleration_structure_geometry{ };
	acceleration_structure_geometry.sType					= VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR;
	acceleration_structure_geometry.geometryType			= VK_GEOMETRY_TYPE_TRIANGLES_KHR;
	acceleration_structure_geometry.flags					= VK_GEOMETRY_OPAQUE_BIT_KHR;
	acceleration_structure_geometry.geometry.triangles		= AccelerationStructureGeometryTrianglesData;

	// Get the size requirements for buffers involved in the acceleration structure build process
	VkAccelerationStructureBuildGeometryInfoKHR acceleration_structure_build_geometry_info{ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR };
	acceleration_structure_build_geometry_info.type = VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR;
	acceleration_structure_build_geometry_info.flags = VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR;
	acceleration_structure_build_geometry_info.geometryCount = 1;
	acceleration_structure_build_geometry_info.pGeometries = &acceleration_structure_geometry;

	const uint32_t triangle_count = 10;

	VkAccelerationStructureBuildSizesInfoKHR acceleration_structure_build_sizes_info{ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR };
	vkGetAccelerationStructureBuildSizesKHR(Device, VK_ACCELERATION_STRUCTURE_BUILD_TYPE_DEVICE_KHR,
		&acceleration_structure_build_geometry_info, &triangle_count, &acceleration_structure_build_sizes_info);

	/*
		加速结构Buffer
	*/
	VkBuffer BLASBuffer;
	VkAccelerationStructureKHR BLASHandle;

	/*
		创建加速结构
	*/
	VkAccelerationStructureCreateInfoKHR acceleration_structure_create_info{ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR };
	acceleration_structure_create_info.buffer			= BLASBuffer;
	acceleration_structure_create_info.size				= acceleration_structure_build_sizes_info.accelerationStructureSize;
	acceleration_structure_create_info.type				= VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR;
	vkCreateAccelerationStructureKHR(Device, &acceleration_structure_create_info, nullptr, &BLASHandle);

	/*
		临时存储加速结构Buffer
	*/
	VkBuffer BASScratchBuffer					= VK_NULL_HANDLE;
	VkDeviceAddress    ScratchDeviceAddress		= 0;

	VkAccelerationStructureBuildGeometryInfoKHR acceleration_build_geometry_info{ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR };
	acceleration_build_geometry_info.type						= VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR;
	acceleration_build_geometry_info.flags						= VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR;
	acceleration_build_geometry_info.mode						= VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR;
	acceleration_build_geometry_info.dstAccelerationStructure	= BLASHandle;
	acceleration_build_geometry_info.geometryCount				= 1;
	acceleration_build_geometry_info.pGeometries				= &acceleration_structure_geometry;
	acceleration_build_geometry_info.scratchData.deviceAddress  = ScratchDeviceAddress;

	/*
		定义顶点范围
	*/
	VkAccelerationStructureBuildRangeInfoKHR acceleration_structure_build_range_info;
	acceleration_structure_build_range_info.primitiveCount		= triangle_count;
	acceleration_structure_build_range_info.primitiveOffset		= 0;
	acceleration_structure_build_range_info.firstVertex			= 0;
	acceleration_structure_build_range_info.transformOffset		= 0;
	std::vector<VkAccelerationStructureBuildRangeInfoKHR*> acceleration_build_structure_range_infos = { &acceleration_structure_build_range_info };

	/*
		创建加速结构
	*/
	// Build the acceleration structure on the device via a one-time command buffer submission
	// Some implementations may support acceleration structure building on the host (VkPhysicalDeviceAccelerationStructureFeaturesKHR->accelerationStructureHostCommands), but we prefer device builds
	VkCommandBuffer command_buffer;
	vkCmdBuildAccelerationStructuresKHR(command_buffer,
		1,
		&acceleration_build_geometry_info,
		acceleration_build_structure_range_infos.data());

}

void BuildBLASInstance()
{
	VkDevice Device = VK_NULL_HANDLE;

	/*
		底层加速结构(为模型创建的)
	*/
	VkAccelerationStructureKHR BLASHandle = VK_NULL_HANDLE;

	/*
		模型矩阵
	*/
	VkTransformMatrixKHR TransformMatrix;

	/*
		获取BLAS设备地址
	*/
	VkAccelerationStructureDeviceAddressInfoKHR AccelerationStructureDeviceAddressInfo{ };
	AccelerationStructureDeviceAddressInfo.sType						= VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_DEVICE_ADDRESS_INFO_KHR;
	AccelerationStructureDeviceAddressInfo.pNext						= nullptr;
	AccelerationStructureDeviceAddressInfo.accelerationStructure		= BLASHandle;
	VkDeviceAddress BLASDeviceAddress = vkGetAccelerationStructureDeviceAddressKHR(Device, &AccelerationStructureDeviceAddressInfo);

	/*
		禁止实例面剔除
	*/
	VkGeometryInstanceFlagsKHR    Instanceflags;
	Instanceflags = VK_GEOMETRY_INSTANCE_TRIANGLE_FACING_CULL_DISABLE_BIT_KHR;

	VkAccelerationStructureInstanceKHR BLASInstance{};
	BLASInstance.transform												= TransformMatrix;
	BLASInstance.instanceCustomIndex									= 0;
	BLASInstance.mask													= 0xFF;
	BLASInstance.instanceShaderBindingTableRecordOffset					= 0;
	BLASInstance.flags													= Instanceflags;
	BLASInstance.accelerationStructureReference							= BLASDeviceAddress;
}

void BuildTLAS(std::vector<VkAccelerationStructureInstanceKHR>& BLASInstances)
{
	VkDevice Device = VK_NULL_HANDLE;

	VkDeviceOrHostAddressConstKHR instance_data_device_address{};

	// The top level acceleration structure contains (bottom level) instance as the input geometry
	VkAccelerationStructureGeometryKHR AccelerationStructureGeometry{ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR };
	AccelerationStructureGeometry.geometryType = VK_GEOMETRY_TYPE_INSTANCES_KHR;
	AccelerationStructureGeometry.flags = VK_GEOMETRY_OPAQUE_BIT_KHR;
	AccelerationStructureGeometry.geometry.instances.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_INSTANCES_DATA_KHR;
	AccelerationStructureGeometry.geometry.instances.arrayOfPointers = VK_FALSE;
	AccelerationStructureGeometry.geometry.instances.data = instance_data_device_address;

	// Get the size requirements for buffers involved in the acceleration structure build process
	VkAccelerationStructureBuildGeometryInfoKHR AccelerationStructureBuildGeometryInfo{};
	AccelerationStructureBuildGeometryInfo.sType			= VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR;
	AccelerationStructureBuildGeometryInfo.type				= VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR;
	AccelerationStructureBuildGeometryInfo.flags			= VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR;
	AccelerationStructureBuildGeometryInfo.geometryCount	= 1;
	AccelerationStructureBuildGeometryInfo.pGeometries		= &AccelerationStructureGeometry;

	const uint32_t primitive_count = 100;

	/*
		获取构建所需内存大小
	*/
	VkAccelerationStructureBuildSizesInfoKHR AccelerationStructureBuildSizesInfo{};
	AccelerationStructureBuildSizesInfo.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR;
	vkGetAccelerationStructureBuildSizesKHR(Device, VK_ACCELERATION_STRUCTURE_BUILD_TYPE_DEVICE_KHR, &AccelerationStructureBuildGeometryInfo, &primitive_count, &AccelerationStructureBuildSizesInfo);

	/*
		加速结构大小
	*/
	VkDeviceSize TLASSize = AccelerationStructureBuildSizesInfo.accelerationStructureSize;

	/*
		TLAS加速结构Buffer
	*/
	VkBuffer	 TLASBuffer;



	/*
		创建加速结构
	*/
	// Create the acceleration structure
	VkAccelerationStructureCreateInfoKHR AccelerationStructureCreateInfo{};
	AccelerationStructureCreateInfo.sType					= VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR;
	AccelerationStructureCreateInfo.buffer					= TLASBuffer;
	AccelerationStructureCreateInfo.size					= TLASSize;
	AccelerationStructureCreateInfo.type					= VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR;
	VkAccelerationStructureKHR Handle;
	vkCreateAccelerationStructureKHR(Device, &AccelerationStructureCreateInfo, nullptr, &Handle);

	/*
		构造加速结构
	*/
	//vkCmdBuildAccelerationStructuresKHR();
}
#endif