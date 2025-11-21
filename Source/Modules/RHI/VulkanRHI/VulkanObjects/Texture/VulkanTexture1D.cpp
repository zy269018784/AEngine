#include "VulkanObjects/Texture/VulkanTexture1D.h"

VulkanTexture1D::VulkanTexture1D(VulkanDevice* Device, RHIPixelFormat InFormat, std::uint32_t InNumMips, std::uint32_t InSizeX)
	: VulkanTexture(Device, RHITextureType::Texture1D, InFormat, InNumMips, InSizeX, 1, 1, 1)
{

}