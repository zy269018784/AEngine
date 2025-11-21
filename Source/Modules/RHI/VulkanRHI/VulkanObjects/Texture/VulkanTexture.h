#pragma once
#include "Vulkan.h"
#include "RHIObjects/Texture/RHITexture2D.h"
#include "RHIObjects/Core/RHICore.h"
#include "VulkanObjects/Device/VulkanDevice.h"
#include "VulkanObjects/Resource/VulkanImage.h"
#include "VulkanObjects/Resource/VulkanImageView.h"
#include "VulkanObjects/CommandBuffer/VulkanCommandPool.h"

class VulkanTexture : public RHITexture
{
public:
	VulkanTexture(VulkanDevice *Device, RHITextureType InType, RHIPixelFormat InFormat, std::uint32_t InNumMips, std::uint32_t InX, std::uint32_t InY, std::uint32_t InZ, std::uint32_t InArraySize);
	~VulkanTexture();
	//void Update(const void* InData, std::uint32_t InSize);
	void Update(int MipmapLevel, int XOffset, int YOffset, int ZOffset, int Width, int Height, int Depth, const void* InData) override;
private:
	VkCommandBuffer BeginSingleTimeCommands();
	void EndSingleTimeCommands(VkCommandBuffer commandBuffer);
	void CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
public:
	VulkanImage		*Image;
	VulkanImageView	*ImageView;
	VulkanDevice* Device;
	VulkanCommandPool *CommandPool;
	VkQueue graphicsQueue;
};

/*
创建纹理的步骤:
	1. 加载纹理贴图
	2. 创建Satging Buffer.
	   map Staging Buffer内存到CPU
	   拷贝纹理贴图到 Staging Buffer
	3. 创建Image和Image View
	4. Copy Staging Buffer到Image
		vkCmdCopyBufferToImage
	
*/