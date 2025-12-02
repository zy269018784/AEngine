#pragma once
#ifdef PROJECT_USE_VULKAN

#include "RHI/RHI/RHIPlatform.h"

#if RHI_USE_PLATFORM_ANDROID_KHR
#define VK_USE_PLATFORM_ANDROID_KHR
#endif

#ifdef RHI_USE_WIN32_KHR
#define VK_USE_PLATFORM_WIN32_KHR
#endif

#if RHI_USE_PLATFORM_WAYLAND_KHR
#define VK_USE_PLATFORM_WAYLAND_KHR
#endif

#if RHI_USE_PLATFORM_XCB_KHR
#define VK_USE_PLATFORM_XCB_KHR
#endif

#if RHI_USE_PLATFORM_XLIB_KHR
#define VK_USE_PLATFORM_XLIB_KHR
#endif

#if RHI_USE_PLATFORM_WAYLAND_KHR
#define VK_USE_PLATFORM_WAYLAND_KHR
#define VK_ENABLE_BETA_EXTENSIONS
#endif

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>


#if RHI_USE_PLATFORM_WAYLAND_KHR 
#include <vulkan/vulkan_wayland.h>  
#endif

#endif

/*
	1. Instance
	2. Physical Device
	3. Device
	4. Command Buffer
	5. Render Pass
	6. Shaders
	7. Pipeline
	8. Window System Integration
		vkCreateAndroidSurfaceKHR
		vkCreateWaylandSurfaceKHR
		vkCreateWin32SurfaceKHR
		vkCreateXcbSurfaceKHR
		vkCreateXlibSurfaceKHR
		vkCreateDirectFBSurfaceEXT
		vkCreateImagePipeSurfaceFUCHSIA
		vkCreateStreamDescriptorSurfaceGGP
		vkCreateIOSSurfaceMVK
		vkCreateMacOSSurfaceMVK
		vkCreateViSurfaceNN
		vkCreateMetalSurfaceEXT
		vkCreateScreenSurfaceQNX
	9. Ray Tracing
		9.1 https://nvpro-samples.github.io/vk_raytracing_tutorial_KHR/
		9.2
			Closest Hit
			Any Hit
			Miss
		9.3 API
			KHR API
				vkCmdBuildAccelerationStructuresKHR
				vkCmdBuildAccelerationStructuresIndirectKHR
				vkCmdTraceRaysKHR
				vkCmdTraceRaysIndirectKHR
				VkTraceRaysIndirectCommandKHR
				vkCmdTraceRaysIndirect2KHR
			NVidia API
				vkCmdBuildAccelerationStructureNV
		9.4 结构
			typedef struct VkAccelerationStructureGeometryTrianglesDataKHR {
				VkStructureType                  sType;
				const void*                      pNext;
				VkFormat                         vertexFormat;					// 顶点类型
				VkDeviceOrHostAddressConstKHR    vertexData;					// 顶点数据
				VkDeviceSize                     vertexStride;					// 顶点步长
				uint32_t                         maxVertex;						// vertexData中的顶点数量
				VkIndexType                      indexType;						// 索引类型
				VkDeviceOrHostAddressConstKHR    indexData;						// 索引数据
				VkDeviceOrHostAddressConstKHR    transformData;
			} VkAccelerationStructureGeometryTrianglesDataKHR;

			typedef struct VkAccelerationStructureDeviceAddressInfoKHR {
				VkStructureType               sType;
				const void*                   pNext;
				VkAccelerationStructureKHR    accelerationStructure;
			} VkAccelerationStructureDeviceAddressInfoKHR;

			typedef struct VkAccelerationStructureInstanceKHR {
				VkTransformMatrixKHR          transform;
				uint32_t                      instanceCustomIndex:24;
				uint32_t                      mask:8;
				uint32_t                      instanceShaderBindingTableRecordOffset:24;
				VkGeometryInstanceFlagsKHR    flags:8;
				uint64_t                      accelerationStructureReference;
			} VkAccelerationStructureInstanceKHR;

			VkAccelerationStructureGeometryKHR
			VkAccelerationStructureBuildGeometryInfoKHR
			VkAccelerationStructureBuildRangeInfoKHR
			VkAccelerationStructureBuildSizesInfoKHR
			VkAccelerationStructureCreateInfoKHR
			VkGeometryTypeKHR
		9.5
		9.6 Acceleration Structure
			9.6.1 Geometry
				Geometries refer to a triangle or axis-aligned bounding box.
			9.6.2 Top-Level Acceleration Structure
			9.6.3 Bottom-Level Acceleration Structure
			9.6.4 build operation & update operation
			9.6.5 流程
				9.4.5.1 BLAS	
					VkAccelerationStructureGeometryTrianglesDataKHR									设置VBO, EBO结构
					VkAccelerationStructureGeometryKHR	t		三角形几何
						type VK_GEOMETRY_TYPE_TRIANGLES_KHR	
					VkAccelerationStructureBuildGeometryInfoKHR
					VkAccelerationStructureBuildSizesInfoKHR										获取加速结构大小	
					vkGetAccelerationStructureBuildSizesKHR											获取加速结构大小
					vkCreateAccelerationStructureKHR												创建加速结构对象，分配内存资源，但不构建实际的层次结构。
					vkCmdBuildAccelerationStructuresKHR												在命令缓冲区中记录构建命令，实际生成加速结构的层次结构。
					vkGetAccelerationStructureDeviceAddressKHR
					VkAccelerationStructureInstanceKHR
				9.4.5.2 TLAS
					VkAccelerationStructureGeometryKHR 												实例几何
						type VK_GEOMETRY_TYPE_INSTANCES_KHR
					VkAccelerationStructureBuildGeometryInfoKHR
					VkAccelerationStructureBuildSizesInfoKHR										获取加速结构大小	
					vkGetAccelerationStructureBuildSizesKHR											获取加速结构大小
					vkCreateAccelerationStructureKHR												创建加速结构对象，分配内存资源，但不构建实际的层次结构。
					vkCmdBuildAccelerationStructuresKHR												在命令缓冲区中记录构建命令，实际生成加速结构的层次结构。
		9.5 Shaders
			Ray Generation Shaders
			Intersection Shaders
			Any-Hit Shaders
			Closest Hit Shaders
			Miss Shaders

*/
