#include "VulkanRHI/VulkanObjects/Texture/VulkanTexture.h"
#include "VulkanRHI/VulkanObjects/Core/VulkanCore.h"
#include "VulkanRHI/VulkanObjects/Device/VulkanDevice.h"
#include "VulkanRHI/VulkanObjects/Resource/VulkanImage.h"
#include "VulkanRHI/VulkanObjects/Resource/VulkanImageView.h"
#include "VulkanRHI/VulkanObjects/CommandBuffer/VulkanCommandPool.h"
#include <iostream>

VulkanTexture::VulkanTexture(VulkanDevice* InDevice,
	RHITextureType InType,
	RHIPixelFormat InFormat,
	RHITextureUsageFlag InUsage,
	RHIImageLayout InLayout,
	std::uint32_t InNumMips, std::uint32_t InX, std::uint32_t InY, std::uint32_t InZ, std::uint32_t InArraySize, void *InData)
	: RHITexture(InType, InFormat, InUsage, InLayout, InX, InY, InZ, InNumMips, InArraySize, InData), Device(InDevice)
{
	Image = new VulkanImage(InDevice, InType, InFormat, InUsage, InLayout, InX, InY, InZ, InArraySize, InNumMips, 1, nullptr);
	ImageView = new VulkanImageView(InDevice, Image, InType, InFormat, InUsage, InNumMips, InArraySize);

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
	Image->TransitionImageLayout(Format, ToVkImageLayout(GetLayout()), VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
	Image->CopyBufferToImage(Image->StagingBuffer, MipmapLevel, XOffset, YOffset, ZOffset, Width, Height, Depth);
	Image->TransitionImageLayout(Format, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
}

void VulkanTexture::TransitionImageLayout(int dir)
{
	VkImageLayout OldLayout;
	VkImageLayout NewLayout;
	if (0 == dir)
	{
		OldLayout = VK_IMAGE_LAYOUT_PREINITIALIZED;
		NewLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
	}
	else {
		OldLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		NewLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
	}
	Image->TransitionImageLayout(ToVkFormat(GetFormat()), OldLayout, NewLayout);
}

void VulkanTexture::TransitionTo(RHIImageLayout InLayout)
{

}

VkImageView VulkanTexture::GetImageView() const {
	return ImageView->GetHandle();
}