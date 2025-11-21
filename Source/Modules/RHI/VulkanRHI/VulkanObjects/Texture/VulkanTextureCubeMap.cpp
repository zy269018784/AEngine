#include "VulkanObjects/Texture/VulkanTextureCubeMap.h"

VulkanTextureCubeMap::VulkanTextureCubeMap(VulkanDevice* Device, RHIPixelFormat InFormat, std::uint32_t InNumMips, std::uint32_t SizeX, std::uint32_t SizeY)
	:  VulkanTexture(Device, RHITextureType::TextureCubeMap, InFormat, InNumMips, SizeX, SizeY, 1, 6)
{
	
}