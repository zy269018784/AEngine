#include <VulkanPixelFormat.h>
#include "RHIObjects/Texture/RHITexture.h"

VkFormat ToVkFormat(RHIPixelFormat PF)
{
	VkFormat Format = VK_FORMAT_UNDEFINED;
	switch (PF)
	{
	case RHIPixelFormat::PF_Unknown:
		Format = VK_FORMAT_UNDEFINED;
		break;

		// 深度模板
	case RHIPixelFormat::PF_DepthStencil:
		Format = VK_FORMAT_D24_UNORM_S8_UINT; // 或 VK_FORMAT_D32_SFLOAT_S8_UINT
		break;

		// 1通道 - 8位
	case RHIPixelFormat::PF_R8_SINT:
		Format = VK_FORMAT_R8_SINT;
		break;
	case RHIPixelFormat::PF_R8_UINT:
		Format = VK_FORMAT_R8_UINT;
		break;
	case RHIPixelFormat::PF_R8_SNORM:
		Format = VK_FORMAT_R8_SNORM;
		break;
	case RHIPixelFormat::PF_R8_UNORM:
		Format = VK_FORMAT_R8_UNORM;
		break;
	case RHIPixelFormat::PF_R8_SRGB:
		Format = VK_FORMAT_R8_SRGB;
		break;

		// 2通道 - 8位
	case RHIPixelFormat::PF_R8G8_SINT:
		Format = VK_FORMAT_R8G8_SINT;
		break;
	case RHIPixelFormat::PF_R8G8_UINT:
		Format = VK_FORMAT_R8G8_UINT;
		break;
	case RHIPixelFormat::PF_R8G8_SNORM:
		Format = VK_FORMAT_R8G8_SNORM;
		break;
	case RHIPixelFormat::PF_R8G8_UNORM:
		Format = VK_FORMAT_R8G8_UNORM;
		break;
	case RHIPixelFormat::PF_R8G8_SRGB:
		Format = VK_FORMAT_R8G8_SRGB;
		break;

		// 3通道 - 8位
	case RHIPixelFormat::PF_R8G8B8_SINT:
		Format = VK_FORMAT_R8G8B8_SINT;
		break;
	case RHIPixelFormat::PF_R8G8B8_UINT:
		Format = VK_FORMAT_R8G8B8_UINT;
		break;
	case RHIPixelFormat::PF_R8G8B8_SNORM:
		Format = VK_FORMAT_R8G8B8_SNORM;
		break;
	case RHIPixelFormat::PF_R8G8B8_UNORM:
		Format = VK_FORMAT_R8G8B8_UNORM;
		break;
	case RHIPixelFormat::PF_R8G8B8_SRGB:
		Format = VK_FORMAT_R8G8B8_SRGB;
		break;

		// 4通道 - 8位
	case RHIPixelFormat::PF_R8G8B8A8_SINT:
		Format = VK_FORMAT_R8G8B8A8_SINT;
		break;
	case RHIPixelFormat::PF_R8G8B8A8_UINT:
		Format = VK_FORMAT_R8G8B8A8_UINT;
		break;
	case RHIPixelFormat::PF_R8G8B8A8_SNORM:
		Format = VK_FORMAT_R8G8B8A8_SNORM;
		break;
	case RHIPixelFormat::PF_R8G8B8A8_UNORM:
		Format = VK_FORMAT_R8G8B8A8_UNORM;
		break;
	case RHIPixelFormat::PF_R8G8B8A8_SRGB:
		Format = VK_FORMAT_R8G8B8A8_SRGB;
		break;

		// 1通道 - 16位
	case RHIPixelFormat::PF_R16_SINT:
		Format = VK_FORMAT_R16_SINT;
		break;
	case RHIPixelFormat::PF_R16_UINT:
		Format = VK_FORMAT_R16_UINT;
		break;
	case RHIPixelFormat::PF_R16_SNORM:
		Format = VK_FORMAT_R16_SNORM;
		break;
	case RHIPixelFormat::PF_R16_UNORM:
		Format = VK_FORMAT_R16_UNORM;
		break;
	case RHIPixelFormat::PF_R16_FLOAT:
		Format = VK_FORMAT_R16_SFLOAT;
		break;

		// 2通道 - 16位
	case RHIPixelFormat::PF_R16G16_SINT:
		Format = VK_FORMAT_R16G16_SINT;
		break;
	case RHIPixelFormat::PF_R16G16_UINT:
		Format = VK_FORMAT_R16G16_UINT;
		break;
	case RHIPixelFormat::PF_R16G16_SNORM:
		Format = VK_FORMAT_R16G16_SNORM;
		break;
	case RHIPixelFormat::PF_R16G16_UNORM:
		Format = VK_FORMAT_R16G16_UNORM;
		break;
	case RHIPixelFormat::PF_R16G16_FLOAT:
		Format = VK_FORMAT_R16G16_SFLOAT;
		break;

		// 3通道 - 16位
	case RHIPixelFormat::PF_R16G16B16_SINT:
		Format = VK_FORMAT_R16G16B16_SINT;
		break;
	case RHIPixelFormat::PF_R16G16B16_UINT:
		Format = VK_FORMAT_R16G16B16_UINT;
		break;
	case RHIPixelFormat::PF_R16G16B16_SNORM:
		Format = VK_FORMAT_R16G16B16_SNORM;
		break;
	case RHIPixelFormat::PF_R16G16B16_UNORM:
		Format = VK_FORMAT_R16G16B16_UNORM;
		break;
	case RHIPixelFormat::PF_R16G16B16_FLOAT:
		Format = VK_FORMAT_R16G16B16_SFLOAT;
		break;

		// 4通道 - 16位
	case RHIPixelFormat::PF_R16G16B16A16_SINT:
		Format = VK_FORMAT_R16G16B16A16_SINT;
		break;
	case RHIPixelFormat::PF_R16G16B16A16_UINT:
		Format = VK_FORMAT_R16G16B16A16_UINT;
		break;
	case RHIPixelFormat::PF_R16G16B16A16_SNORM:
		Format = VK_FORMAT_R16G16B16A16_SNORM;
		break;
	case RHIPixelFormat::PF_R16G16B16A16_UNORM:
		Format = VK_FORMAT_R16G16B16A16_UNORM;
		break;
	case RHIPixelFormat::PF_R16G16B16A16_FLOAT:
		Format = VK_FORMAT_R16G16B16A16_SFLOAT;
		break;

		// 1通道 - 32位
	case RHIPixelFormat::PF_R32_SINT:
		Format = VK_FORMAT_R32_SINT;
		break;
	case RHIPixelFormat::PF_R32_UINT:
		Format = VK_FORMAT_R32_UINT;
		break;
	case RHIPixelFormat::PF_R32_FLOAT:
		Format = VK_FORMAT_R32_SFLOAT;
		break;

		// 2通道 - 32位
	case RHIPixelFormat::PF_R32G32_SINT:
		Format = VK_FORMAT_R32G32_SINT;
		break;
	case RHIPixelFormat::PF_R32G32_UINT:
		Format = VK_FORMAT_R32G32_UINT;
		break;
	case RHIPixelFormat::PF_R32G32_FLOAT:
		Format = VK_FORMAT_R32G32_SFLOAT;
		break;

		// 3通道 - 32位
	case RHIPixelFormat::PF_R32G32B32_SINT:
		Format = VK_FORMAT_R32G32B32_SINT;
		break;
	case RHIPixelFormat::PF_R32G32B32_UINT:
		Format = VK_FORMAT_R32G32B32_UINT;
		break;
	case RHIPixelFormat::PF_R32G32B32_FLOAT:
		Format = VK_FORMAT_R32G32B32_SFLOAT;
		break;

		// 4通道 - 32位
	case RHIPixelFormat::PF_R32G32B32A32_SINT:
		Format = VK_FORMAT_R32G32B32A32_SINT;
		break;
	case RHIPixelFormat::PF_R32G32B32A32_UINT:
		Format = VK_FORMAT_R32G32B32A32_UINT;
		break;
	case RHIPixelFormat::PF_R32G32B32A32_FLOAT:
		Format = VK_FORMAT_R32G32B32A32_SFLOAT;
		break;

	default:
		Format = VK_FORMAT_UNDEFINED;
		break;
	}
	return Format;
}

