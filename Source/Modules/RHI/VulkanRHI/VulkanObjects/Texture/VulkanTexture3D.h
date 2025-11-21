#pragma once
#include <VulkanObjects/Texture/VulkanTexture.h>

class VulkanTexture3D : public VulkanTexture
{
public:
	VulkanTexture3D(VulkanDevice* Device, RHIPixelFormat InFormat, std::uint32_t InNumMips, std::uint32_t InSizeX, std::uint32_t InSizeY, std::uint32_t InSizeZ);
};