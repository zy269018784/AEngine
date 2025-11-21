#pragma once
#include <VulkanObjects/Texture/VulkanTexture.h>

class VulkanTexture2DArray : public VulkanTexture
{
public:
	VulkanTexture2DArray(VulkanDevice* Device, RHIPixelFormat InFormat, std::uint32_t InSizeX, std::uint32_t InSizeY, std::uint32_t InArraySize, std::uint32_t InNumMips);
};