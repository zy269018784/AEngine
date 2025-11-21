#include <VulkanObjects/Texture/VulkanTexture2D.h>
#include <iostream>
VulkanTexture2D::VulkanTexture2D(VulkanDevice* Device, RHIPixelFormat InFormat, std::uint32_t InNumMips, std::uint32_t InSizeX, std::uint32_t InSizeY)
	:  VulkanTexture(Device, RHITextureType::Texture2D, InFormat, InNumMips, InSizeX, InSizeY, 1, 1)
{

}