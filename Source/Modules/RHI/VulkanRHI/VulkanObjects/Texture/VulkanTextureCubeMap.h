#pragma once
#include <VulkanObjects/Texture/VulkanTexture.h>

class VulkanTextureCubeMap : public VulkanTexture
{
public:
	VulkanTextureCubeMap(VulkanDevice* Device, RHIPixelFormat InFormat, std::uint32_t InNumMips, std::uint32_t SizeX, std::uint32_t SizeY);
};