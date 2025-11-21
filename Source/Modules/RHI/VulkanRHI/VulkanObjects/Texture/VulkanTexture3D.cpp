#include "VulkanObjects/Texture/VulkanTexture3D.h"

VulkanTexture3D::VulkanTexture3D(VulkanDevice* Device, RHIPixelFormat InFormat, std::uint32_t InNumMips, std::uint32_t InSizeX, std::uint32_t InSizeY, std::uint32_t InSizeZ)
	: VulkanTexture(Device, RHITextureType::Texture3D, InFormat, InNumMips, InSizeX, InSizeY, InSizeZ, 1)
{

}