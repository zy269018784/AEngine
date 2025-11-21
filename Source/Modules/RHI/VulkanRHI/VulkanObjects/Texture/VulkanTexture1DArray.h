#pragma once
#include <VulkanObjects/Texture/VulkanTexture.h>

class VulkanTexture1DArray : public VulkanTexture
{
public:
	VulkanTexture1DArray(VulkanDevice* Device, RHIPixelFormat InFormat, std::uint32_t InNumMips, std::uint32_t InSizeX, std::uint32_t InArraySize);
};