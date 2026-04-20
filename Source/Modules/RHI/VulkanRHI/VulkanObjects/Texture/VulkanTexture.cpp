#include "VulkanObjects/Texture/VulkanTexture.h"
#include "VulkanObjects/Core/VulkanCore.h"

#include <iostream>

VulkanTexture::VulkanTexture(VulkanDevice* InDevice, RHITextureType InType, RHIPixelFormat InFormat, std::uint32_t InNumMips, std::uint32_t InX, std::uint32_t InY, std::uint32_t InZ, std::uint32_t InArraySize, void *InData)
	: RHITexture(InType, InFormat, InX, InY, InZ, InNumMips, InArraySize, InData), Device(InDevice)
{
	VkImageAspectFlags Aspect = 0;
	switch (InFormat) {
		case RHIPixelFormat::PF_DepthStencil:
			Aspect |= VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;
			break;
		case RHIPixelFormat::PF_DepthStencil_D24_S8:
			Aspect |= VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;
			break;
		case RHIPixelFormat::PF_DepthStencil_D32_S8:
			Aspect |= VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;
			break;
		case RHIPixelFormat::PF_DepthOnly_D32:
			Aspect |= VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;
			break;
		case RHIPixelFormat::PF_DepthOnly_D16:
			Aspect |= VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;
			break;
		default:
			Aspect |= VK_IMAGE_ASPECT_COLOR_BIT;
	}

	Image = new VulkanImage(InDevice, InType, InFormat, InX, InY, InZ, InArraySize, InNumMips, 1);
	ImageView = new VulkanImageView(InDevice, Image, InType,  Aspect, InFormat, InNumMips, InArraySize);

	UpdateImageData();
}

VulkanTexture::~VulkanTexture()
{
	delete ImageView;
	delete Image;
}

void VulkanTexture::Update(int MipmapLevel, int XOffset, int YOffset, int ZOffset, int Width, int Height, int Depth, const void* InData)
{
	std::uint32_t Size;
	std::uint32_t PixelSize = 4;
	switch (GetType())
	{
	case RHITextureType::Texture1D:
		Size = 1 * Width;
		break;
	case RHITextureType::Texture1DArray:
		Size = PixelSize * Width * Height;
		break;
	case RHITextureType::Texture2D:
		Size = PixelSize * Width * Height;
		break;
	case RHITextureType::Texture2DArray:
		Size = PixelSize * Width * Height * Depth;
		break;
	case RHITextureType::Texture3D:
		Size = PixelSize * Width * Height * Depth;
		break;
	case RHITextureType::TextureCubeMap:
		Size = PixelSize * Width * Height;
		break;
	case RHITextureType::TextureCubeMapArray:
		Size = PixelSize * Width * Height * Depth;
		break;
	}

	/*
		To do: 
			staging buffer 放这里
	*/
	Image->Update(InData, Size);
	VkFormat Format = ToVkFormat(GetFormat());
	Image->TransitionImageLayout(Format, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
	Image->CopyBufferToImage(Image->StagingBuffer, MipmapLevel, XOffset, YOffset, ZOffset, Width, Height, Depth);
	Image->TransitionImageLayout(Format, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
}
