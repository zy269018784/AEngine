#pragma once
#include <VulkanObjects/Texture/VulkanTexture.h>

class VulkanTexture2D : public VulkanTexture
{
public:
	VulkanTexture2D(VulkanDevice* Device, RHIPixelFormat InFormat, std::uint32_t InNumMips, std::uint32_t InSizeX, std::uint32_t InSizeY);
};