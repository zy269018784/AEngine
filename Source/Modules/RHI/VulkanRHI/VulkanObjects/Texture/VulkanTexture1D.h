#pragma once
#include <VulkanObjects/Texture/VulkanTexture.h>
#include "VulkanObjects/Resource/VulkanImage.h"
#include <VulkanObjects/Resource/VulkanImageView.h>
class VulkanTexture1D : public VulkanTexture
{
public:
	VulkanTexture1D(VulkanDevice* Device, RHIPixelFormat InFormat, std::uint32_t InNumMips, std::uint32_t InSizeX);

};