#include "VulkanObjects/Texture/VulkanTextureCubeMapArray.h"

VulkanTextureCubeMapArray::VulkanTextureCubeMapArray(VulkanDevice* Device, RHIPixelFormat InFormat, std::uint32_t InNumMips, std::uint32_t SizeX, std::uint32_t SizeY, std::uint32_t InArraySize)
	: VulkanTexture(Device, RHITextureType::TextureCubeMapArray, InFormat, InNumMips, SizeX, SizeY, 1,  InArraySize * 6)
{

}