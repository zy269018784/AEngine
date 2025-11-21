#include "VulkanObjects/Texture/VulkanTexture2DArray.h"

VulkanTexture2DArray::VulkanTexture2DArray(VulkanDevice* Device, RHIPixelFormat InFormat, std::uint32_t InNumMips, std::uint32_t InSizeX, std::uint32_t InSizeY, std::uint32_t InArraySize)
	: VulkanTexture(Device, RHITextureType::Texture2DArray, InFormat, InNumMips, InSizeX, InSizeY, 1, InArraySize)
{

}