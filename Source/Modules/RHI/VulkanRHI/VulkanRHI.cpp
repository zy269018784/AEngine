#include "VulkanRHI.h"
#include "VulkanRHI/VulkanObjects/Shader/VulkanShader.h"
#include "VulkanRHI/VulkanObjects/Shader/VulkanShaderResourceBindings.h"
#include "VulkanRHI/VulkanObjects/Texture/VulkanTexture.h"
#include "VulkanRHI/VulkanObjects/Resource/VulkanBuffer.h"
#include "VulkanRHI/VulkanObjects/Resource/VulkanSampler.h"
#include "VulkanRHI/VulkanObjects/Pipeline/VulkanGraphicsPipeline.h"
#include "VulkanRHI/VulkanObjects/Surface/VulkanSurface.h"
#include "VulkanRHI/VulkanObjects/RenderTarget/VulkanRenderTarget.h"
#include "VulkanRHI/VulkanObjects/RenderTarget/VulkanSwapChainRenderTarget.h"
#include "VulkanRHI/VulkanObjects/RenderTarget/VulkanTextureRenderTarget.h"
#include "VulkanRHI/VulkanObjects/CommandBuffer/VulkanCommandPool.h"
#include "VulkanRHI/VulkanObjects/Instance/VulkanInstance.h"
#include "VulkanRHI/VulkanObjects/PhysicalDevice/VulkanPhysicalDevice.h"
#include <iostream>

#include "ES32RHI/OpenGLObjects/Surface/OpenGLSurface.h"


VulkanRHI::VulkanRHI(GraphicsAPI APIIndex)
	: RHI(APIIndex)
{
	/*
		创建Instance
	*/
	CreateInstance();
	CreateDevice();
	CreateCommandPool();
}


VulkanRHI::~VulkanRHI()
{
	std::cout << "~VulkanRHI() " << std::endl;
	for (int i = 0; i < Devices.size(); i++)
	{
		delete Devices[i];
	}

	delete Instance;
}

void VulkanRHI::RHIUseGPU(std::uint32_t InGPUIndex)
{
	GPUIndex = InGPUIndex;
}


#if RHI_USE_WIN32_KHR
RHISurface* VulkanRHI::RHICreateSurface(HINSTANCE Hinstance, HWND Hwnd)
{
	VulkanSurface* Surface = new VulkanSurface(Instance, Hinstance, Hwnd);
	Surface->Query(*Instance->GetVulkanPhysicalDevice(GPUIndex));
	Instance->GetVulkanPhysicalDevice(GPUIndex)->Query(Surface);
	return Surface;
}
#endif

#if RHI_USE_WAYLAND_KHR
RHISurface* VulkanRHI::RHICreateSurface(struct wl_display* display, struct wl_surface* wayland_surface)
{
	return nullptr;
}
#endif

#if RHI_USE_XCB_KHR
RHISurface* VulkanRHI::RHICreateSurface(xcb_connection_t* Connection, xcb_window_t Window)
{
	VulkanSurface *Surface = new VulkanSurface(Instance, Connection, Window);
	return Surface;
}
#endif

#if RHI_USE_Xlib_KHR
RHISurface* VulkanRHI::RHICreateSurface(Display* Disp, Window Win)
{
	VulkanSurface *Surface = new VulkanSurface(Instance, Disp, Win);
	return Surface;
}
#endif

RHIRenderTarget *VulkanRHI::RHICreateSwapchainRenderTarget(RHISurface *InSurface)
{
	VulkanSwapChainRenderTarget *RenderTarget = new VulkanSwapChainRenderTarget(Devices[GPUIndex], reinterpret_cast<VulkanSurface *>(InSurface));
	RenderTarget->Create();
	return RenderTarget;
}

RHIRenderTarget *VulkanRHI::RHICreateTextureRenderTarget(std::vector<RHITexture *> InColorAttachments,
													     std::vector<RHITexture *> InDepthAttachments)
{
	VulkanTextureRenderTarget* RenderTarget = new VulkanTextureRenderTarget(Devices[GPUIndex],
		InDepthAttachments[0]->GetX(),
		InDepthAttachments[0]->GetY());
	RenderTarget->Create(InColorAttachments, InDepthAttachments);
	return RenderTarget;
}

RHIBuffer* VulkanRHI::RHICreateBuffer(RHIBufferType InType, RHIBufferUsageFlag InUsage, std::uint32_t InSize)
{
	VulkanBuffer* Buffer = new VulkanBuffer(Devices[GPUIndex], InType, InUsage, InSize, nullptr);

	return Buffer;
}

RHIBuffer* VulkanRHI::RHICreateBuffer(RHIBufferType InType, RHIBufferUsageFlag InUsage, std::uint32_t InSize, const void* InData)
{
	VulkanBuffer* Buffer = new VulkanBuffer(Devices[GPUIndex], InType, InUsage, InSize, InData);
	return Buffer;
}

RHIGraphicsPipeline* VulkanRHI::RHICreateGraphicsPipeline(RHIRenderPass *RenderPass)
{
	VulkanGraphicsPipeline* Pipeline = new VulkanGraphicsPipeline(Devices[GPUIndex], ((VulkanRenderPass*)RenderPass));
	return Pipeline;
}

RHIShader* VulkanRHI::RHICreateShader(RHIShaderType Type, std::uint32_t* Code, size_t CodeSize)
{
	VulkanShader* Shader = new VulkanShader(Devices[GPUIndex], Type, Code, CodeSize);
	return Shader;
}


RHITexture* VulkanRHI::RHICreateTexture1D(RHIPixelFormat RHIPixelFormat, RHITextureUsageFlag InUsage, std::uint32_t NumMips, std::uint32_t SizeX, void *Data)
{
	VulkanTexture* Texture =  new VulkanTexture(Devices[GPUIndex], RHITextureType::Texture1D, RHIPixelFormat, InUsage, NumMips, SizeX, 1, 1, 1, Data);
	return Texture;
}


RHITexture* VulkanRHI::RHICreateTexture1DArray(RHIPixelFormat RHIPixelFormat, RHITextureUsageFlag InUsage, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t ArraySize, void *Data)
{
	VulkanTexture* Texture = new VulkanTexture(Devices[GPUIndex], RHITextureType::Texture1DArray, RHIPixelFormat, InUsage, NumMips, SizeX, 1, 1, ArraySize, Data);
	return Texture;
}

RHITexture* VulkanRHI::RHICreateTexture2D(RHIPixelFormat RHIPixelFormat, RHITextureUsageFlag InUsage, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, void *Data)
{
	VulkanTexture *Texture = new VulkanTexture(Devices[GPUIndex], RHITextureType::Texture2D, RHIPixelFormat, InUsage, NumMips, SizeX, SizeY, 1, 1, Data);
	return Texture;
}

RHITexture* VulkanRHI::RHICreateTexture2DArray(RHIPixelFormat RHIPixelFormat, RHITextureUsageFlag InUsage, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, std::uint32_t ArraySize, void *Data)
{
	VulkanTexture* Texture = new VulkanTexture(Devices[GPUIndex], RHITextureType::Texture2DArray, RHIPixelFormat, InUsage, NumMips, SizeX, SizeY, 1, ArraySize, Data);
	return Texture;
	
}

RHITexture* VulkanRHI::RHICreateTexture3D(RHIPixelFormat RHIPixelFormat, RHITextureUsageFlag InUsage, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, std::uint32_t SizeZ, void *Data)
{
	VulkanTexture* Texture = new VulkanTexture(Devices[GPUIndex], RHITextureType::Texture3D, RHIPixelFormat, InUsage, NumMips, SizeX, SizeY, SizeZ, 1, Data);
	return Texture;
}

RHITexture* VulkanRHI::RHICreateTextureCube(RHIPixelFormat RHIPixelFormat, RHITextureUsageFlag InUsage, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, void *Data)
{
	VulkanTexture* Texture = new VulkanTexture(Devices[GPUIndex], RHITextureType::TextureCubeMap, RHIPixelFormat, InUsage, NumMips, SizeX, SizeY, 1, 6, Data);
	return Texture;
}

RHITexture* VulkanRHI::RHICreateTextureCubeArray(RHIPixelFormat RHIPixelFormat, RHITextureUsageFlag InUsage, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, std::uint32_t ArraySize, void *Data)
{
	ArraySize *= 6;
	VulkanTexture* Texture = new VulkanTexture(Devices[GPUIndex], RHITextureType::TextureCubeMapArray, RHIPixelFormat, InUsage, NumMips, SizeX, SizeY, 1,  ArraySize, Data);
	return Texture;
}

void VulkanRHI::RHIUpdateTexture(RHITexture* Texture, const void* InData, std::uint32_t InSize)
{
	VulkanTexture *VKTexture = ((VulkanTexture*)Texture);
	//VKTexture->Update(InData, InSize);
}

RHISampler* VulkanRHI::RHICreateSampler(RHIFilter MinFilter,
	RHIFilter MagFilter,
	RHIAddressMode AddressModeU,
	RHIAddressMode AddressModeV,
	RHIAddressMode AddressModeW)
{
	return new VulkanSampler(Devices[GPUIndex], MinFilter, MagFilter, AddressModeU, AddressModeV, AddressModeW);
}

RHIShaderResourceBindings* VulkanRHI::RHICreateShaderResourceBindings()
{
	return new VulkanShaderResourceBindings(Devices[GPUIndex]);
}

VkCommandBuffer VulkanRHI::beginSingleTimeCommands() {
	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandPool = GraphicsCommandPool->GetHandle();
	allocInfo.commandBufferCount = 1;

	VkCommandBuffer commandBuffer;
	std::cout << "AllocateCommandBuffers start " << Devices[GPUIndex]->GetHandle() << std::endl;
	auto ret = Devices[GPUIndex]->AllocateCommandBuffers(&allocInfo, &commandBuffer);
	std::cout << "AllocateCommandBuffers end " << ret << std::endl;

	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	std::cout << "vkBeginCommandBuffer start" << std::endl;
	ret = vkBeginCommandBuffer(commandBuffer, &beginInfo);
	std::cout << "vkBeginCommandBuffer end " << ret << std::endl;
	return commandBuffer;
}

void VulkanRHI::endSingleTimeCommands(VkCommandBuffer commandBuffer) {
	vkEndCommandBuffer(commandBuffer);

	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer;

	//vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
	//vkQueueWaitIdle(graphicsQueue);

	Devices[GPUIndex]->FreeCommandBuffers(GraphicsCommandPool->GetHandle(), 1, &commandBuffer);
}

void VulkanRHI::transitionImageLayout(VkImage image, VkFormat format, VkImageLayout OldLayout, VkImageLayout NewLayout)
{
	VkCommandBuffer commandBuffer = beginSingleTimeCommands();

	VkImageMemoryBarrier barrier{};
	barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	barrier.oldLayout = OldLayout;
	barrier.newLayout = NewLayout;
	barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	barrier.image = image;
	barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	barrier.subresourceRange.baseMipLevel = 0;
	barrier.subresourceRange.levelCount = 1;
	barrier.subresourceRange.baseArrayLayer = 0;
	barrier.subresourceRange.layerCount = 1;

	VkPipelineStageFlags sourceStage;
	VkPipelineStageFlags destinationStage;

	if (OldLayout == VK_IMAGE_LAYOUT_UNDEFINED && NewLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
		barrier.srcAccessMask = 0;
		barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

		sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
		destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
	}
	else if (OldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && NewLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
		barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

		sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
	}
	else {
		//throw std::invalid_argument("unsupported layout transition!");
	}
	std::cout << "vkCmdPipelineBarrier start" << std::endl;
	vkCmdPipelineBarrier(
		commandBuffer,
		sourceStage, destinationStage,
		0,
		0, nullptr,
		0, nullptr,
		1, &barrier
	);
	std::cout << "vkCmdPipelineBarrier end" << std::endl;

	endSingleTimeCommands(commandBuffer);
}
