#include "VulkanObjects/Texture/VulkanTexture1DArray.h"

VulkanTexture1DArray::VulkanTexture1DArray(VulkanDevice* Device, RHIPixelFormat InFormat,std::uint32_t InNumMips, std::uint32_t InSizeX, std::uint32_t InArraySize)
	: VulkanTexture(Device, RHITextureType::Texture1DArray, InFormat, InNumMips, InSizeX, 1, 1, InArraySize)
{

}