#pragma once
#include <VulkanObjects/Texture/VulkanTexture.h>

class VulkanTextureCubeMapArray : public VulkanTexture
{
public:
	VulkanTextureCubeMapArray(VulkanDevice* Device, RHIPixelFormat InFormat, std::uint32_t InNumMips, std::uint32_t SizeX, std::uint32_t SizeY, std::uint32_t InArraySize);
};