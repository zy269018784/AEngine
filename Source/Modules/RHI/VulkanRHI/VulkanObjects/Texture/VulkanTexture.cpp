#include <VulkanObjects/Texture/VulkanTexture.h>
#include <VulkanPixelFormat.h>
#include <iostream>

VkCommandBuffer VulkanTexture::BeginSingleTimeCommands()
{
	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandPool = CommandPool->GetHandle();
	allocInfo.commandBufferCount = 1;

	VkCommandBuffer commandBuffer;
	Device->AllocateCommandBuffers(&allocInfo, &commandBuffer);

	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	vkBeginCommandBuffer(commandBuffer, &beginInfo);

	return commandBuffer;
}

void VulkanTexture::EndSingleTimeCommands(VkCommandBuffer commandBuffer)
{
	vkEndCommandBuffer(commandBuffer);

	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer;

	vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
	vkQueueWaitIdle(graphicsQueue);

	CommandPool->FreeCommandBuffers(1, &commandBuffer);
}

void VulkanTexture::CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height) {
	VkCommandBuffer CommandBuffer = BeginSingleTimeCommands();

	VkBufferImageCopy region{};
	region.bufferOffset = 0;
	region.bufferRowLength = 0;
	region.bufferImageHeight = 0;
	region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	region.imageSubresource.mipLevel = 0;
	region.imageSubresource.baseArrayLayer = 0;
	region.imageSubresource.layerCount = 1;
	region.imageOffset = { 0, 0, 0 };
	region.imageExtent = {
		width,
		height,
		1
	};

	vkCmdCopyBufferToImage(CommandBuffer, buffer, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

	EndSingleTimeCommands(CommandBuffer);
}
#if 0
void VulkanTexture::createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory)
{
	VkBufferCreateInfo bufferInfo{};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = size;
	bufferInfo.usage = usage;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	if (vkCreateBuffer(Device->GetHandle(), &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
		throw std::runtime_error("failed to create buffer!");
	}

	VkMemoryRequirements memRequirements;
	vkGetBufferMemoryRequirements(Device->GetHandle(), buffer, &memRequirements);

	VkMemoryAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = 0;// findMemoryType(memRequirements.memoryTypeBits, properties);

	if (vkAllocateMemory(Device->GetHandle(), &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate buffer memory!");
	}

	vkBindBufferMemory(Device->GetHandle(), buffer, bufferMemory, 0);
}
#endif
VulkanTexture::VulkanTexture(VulkanDevice* InDevice, RHITextureType InType, RHIPixelFormat InFormat, std::uint32_t InNumMips, std::uint32_t InX, std::uint32_t InY, std::uint32_t InZ, std::uint32_t InArraySize)
	: RHITexture(InType, InFormat, InX, InY, InZ, InNumMips, InArraySize), Device(InDevice)
{
	VkImageAspectFlagBits Aspect = VK_IMAGE_ASPECT_COLOR_BIT;
	if (InFormat == RHIPixelFormat::PF_DepthStencil) 
	{
		Aspect = VK_IMAGE_ASPECT_DEPTH_BIT;
	}
	//VkImageViewType ImageViewType = ToVulkanImageViewType(InType);

	Image = new VulkanImage(InDevice, InType, InFormat, InX, InY, InZ, InArraySize, InNumMips, 1);
	ImageView = new VulkanImageView(InDevice, Image, InType,  Aspect, InFormat, InNumMips, InArraySize);
}

VulkanTexture::~VulkanTexture()
{
	delete ImageView;
	delete Image;
}

//void VulkanTexture::Update(const void* InData, std::uint32_t InSize)
//{
//	Image->Update(InData, InSize);
//
//	VkFormat Format = ToVkFormat(GetFormat());
//	std::cout << "InFormat " << (int)GetFormat() << " " << "fmt " << Format << " X " << GetX() << " Y " << GetY() << std::endl;
//	//std::cout << "CommandPool " << CommandPool << " " << Image->CommandPool << std::endl;
//	Image->TransitionImageLayout(Format, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
//	Image->CopyBufferToImage(Image->StagingBuffer, static_cast<uint32_t>(GetX()), static_cast<uint32_t>(GetY()));
//	Image->TransitionImageLayout(Format, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
//}

void VulkanTexture::Update(int MipmapLevel, int XOffset, int YOffset, int ZOffset, int Width, int Height, int Depth, const void* InData)
{
	std::uint32_t Size;
	std::uint32_t PixelSize = 4;
	switch (GetType())
	{
	case RHITextureType::Texture1D:
		Size = PixelSize * Width;
		break;
	case RHITextureType::Texture1DArray:
		Size = PixelSize * Width * Height;
		break;
	case RHITextureType::Texture2D:
		Size = PixelSize * Width * Height;
		break;
	case RHITextureType::Texture2DArray:
		Size = PixelSize * Width * Height * Depth;
		break;
	case RHITextureType::Texture3D:
		Size = PixelSize * Width * Height * Depth;
		break;
	case RHITextureType::TextureCubeMap:
		Size = PixelSize * Width * Height;
		std::cout << "TextureCubeMap size " << Size << std::endl;
		break;
	case RHITextureType::TextureCubeMapArray:
		Size = PixelSize * Width * Height * Depth;
		std::cout << "TextureCubeMapArray size " << Size << std::endl;
		break;
	}
	/*
		To do: 
			staging buffer 放这里
	*/
	Image->Update(InData, Size);
	VkFormat Format = ToVkFormat(GetFormat());
	Image->TransitionImageLayout(Format, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
	Image->CopyBufferToImage(Image->StagingBuffer, MipmapLevel, XOffset, YOffset, ZOffset, Width, Height, Depth);
	Image->TransitionImageLayout(Format, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
}
