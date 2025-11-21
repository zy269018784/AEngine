#include "VulkanObjects/Device/VulkanDevice.h"
#include <cstring>
/*
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/
/*
	Device
*/
void  VulkanDevice::DestroyDevice(const VkAllocationCallbacks* Allocator)
{
	vkDestroyDevice(Handle, Allocator);
}

/*
	Device Queue
*/
void VulkanDevice::GetDeviceQueue(std::uint32_t QueueFamilyIndex,
	std::uint32_t QueueIndex,
	VkQueue* Queue)
{
	vkGetDeviceQueue(Handle, QueueFamilyIndex, QueueIndex, Queue);
}

void VulkanDevice::GetDeviceQueue2(const VkDeviceQueueInfo2* QueueInfo, VkQueue* Queue)
{
	vkGetDeviceQueue2(Handle, QueueInfo, Queue);
}

/*
	Command Pool
*/
VkResult VulkanDevice::CreateCommandPool(const VkCommandPoolCreateInfo* CreateInfo,
	const VkAllocationCallbacks* Allocator,
	VkCommandPool* CommandPool)
{
	return vkCreateCommandPool(Handle, CreateInfo, nullptr, CommandPool);;
}

void VulkanDevice::DestroyCommandPool(VkCommandPool CommandPool, const VkAllocationCallbacks* Allocator)
{
	vkDestroyCommandPool(Handle, CommandPool, Allocator);
}

void VulkanDevice::TrimCommandPool(VkCommandPool CommandPool, VkCommandPoolTrimFlags Flags)
{
	vkTrimCommandPool(Handle, CommandPool, Flags);
}

VkResult VulkanDevice::ResetCommandPool(VkCommandPool CommandPool, VkCommandPoolResetFlags Flags)
{
	return vkResetCommandPool(Handle, CommandPool, Flags);
}

/*
	Command Buffer
*/
VkResult VulkanDevice::AllocateCommandBuffers(const VkCommandBufferAllocateInfo* AllocateInfo, VkCommandBuffer* CommandBuffers)
{
	return vkAllocateCommandBuffers(Handle, AllocateInfo, CommandBuffers);
}

void VulkanDevice::FreeCommandBuffers(VkCommandPool CommandPool, std::uint32_t CommandBufferCount, const VkCommandBuffer* CommandBuffers)
{
	return vkFreeCommandBuffers(Handle, CommandPool, CommandBufferCount, CommandBuffers);
}


/*
	Fence
*/
VkResult VulkanDevice::CreateFence(const VkFenceCreateInfo* CreateInfo,
	const VkAllocationCallbacks* Allocator,
	VkFence* Fence)
{
	return vkCreateFence(Handle, CreateInfo, Allocator, Fence);
}

void VulkanDevice::DestroyFence(VkFence Fence, const VkAllocationCallbacks* Allocator)
{
	vkDestroyFence(Handle, Fence, Allocator);
}

VkResult VulkanDevice::WaitForFences(uint32_t FenceCount, const VkFence* pFences, VkBool32 WaitAll, uint64_t Timeout)
{
	return vkWaitForFences(Handle, FenceCount, pFences, WaitAll, Timeout);
}

VkResult VulkanDevice::ResetFences(uint32_t FenceCount, const VkFence* Fences)
{
	return vkResetFences(Handle, FenceCount, Fences);
}


/*
	Semaphore
*/
VkResult VulkanDevice::CreateSemaphore(const VkSemaphoreCreateInfo* CreateInfo,
	const VkAllocationCallbacks* Allocator,
	VkSemaphore* Semaphore)
{
	return vkCreateSemaphore(Handle, CreateInfo, Allocator, Semaphore);
}

void VulkanDevice::DestroySemaphore(VkSemaphore Semaphore, const VkAllocationCallbacks* Allocator)
{
	vkDestroySemaphore(Handle, Semaphore, Allocator);
}

/*
	Event
*/
VkResult VulkanDevice::CreateEvent(const VkEventCreateInfo* CreateInfo,
	const VkAllocationCallbacks* Allocator,
	VkEvent* Event)
{
	return vkCreateEvent(Handle, CreateInfo, Allocator, Event);
}

void VulkanDevice::DestroyEvent(VkEvent Event, const VkAllocationCallbacks* Allocator)
{
	vkDestroyEvent(Handle, Event, Allocator);
}

/*
	Render Pass
*/
VkResult VulkanDevice::CreateRenderPass(const VkRenderPassCreateInfo* pCreateInfo,
	const VkAllocationCallbacks* pAllocator,
	VkRenderPass* pRenderPass)
{
	return vkCreateRenderPass(Handle, pCreateInfo, pAllocator, pRenderPass);
}

void VulkanDevice::DestroyRenderPass(VkRenderPass RenderPass, const VkAllocationCallbacks* Allocator)
{
	vkDestroyRenderPass(Handle, RenderPass, Allocator);
}

/*
	Physical Storage Buffer Access
*/
VkDeviceAddress VulkanDevice::GetBufferDeviceAddress(const VkBufferDeviceAddressInfo* Info)
{
	return vkGetBufferDeviceAddress(Handle, Info);
}

std::uint64_t VulkanDevice::GetBufferOpaqueCaptureAddress(const VkBufferDeviceAddressInfo* Info)
{
	return vkGetBufferOpaqueCaptureAddress(Handle, Info);
}

/*
	Framebuffer
*/
VkResult VulkanDevice::CreateFramebuffer(const VkFramebufferCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator, VkFramebuffer* Framebuffer)
{
	return vkCreateFramebuffer(Handle, CreateInfo, nullptr, Framebuffer);
}

void VulkanDevice::DestroyFramebuffer(VkFramebuffer Framebuffer, const VkAllocationCallbacks* Allocator)
{
	vkDestroyFramebuffer(Handle, Framebuffer, Allocator);
}

/*
	Shader
*/
VkResult VulkanDevice::CreateShaderModule(const VkShaderModuleCreateInfo* CreateInfo,
	const VkAllocationCallbacks* Allocator,
	VkShaderModule* ShaderModule)
{
	return vkCreateShaderModule(Handle, CreateInfo, nullptr, ShaderModule);
}

void VulkanDevice::DestroyShaderModule(VkShaderModule ShaderModule,
	const VkAllocationCallbacks* Allocator)
{
	vkDestroyShaderModule(Handle, ShaderModule, Allocator);
}

/*
	Pipeline
*/
VkResult VulkanDevice::CreateGraphicsPipelines(VkPipelineCache PipelineCache,
	std::uint32_t CreateInfoCount,
	const VkGraphicsPipelineCreateInfo* CreateInfos,
	const VkAllocationCallbacks* Allocator,
	VkPipeline* Pipelines)
{
	return vkCreateGraphicsPipelines(Handle, PipelineCache, CreateInfoCount, CreateInfos, nullptr, Pipelines);
}

VkResult VulkanDevice::CreateComputePipelines(VkPipelineCache PipelineCache,
	std::uint32_t CreateInfoCount,
	const VkComputePipelineCreateInfo* CreateInfos,
	const VkAllocationCallbacks* Allocator,
	VkPipeline* Pipelines)
{
	return vkCreateComputePipelines(Handle, PipelineCache, 1, CreateInfos, nullptr, Pipelines);
}

void VulkanDevice::DestroyPipeline(VkPipeline Pipeline, const VkAllocationCallbacks* Allocator)
{
	vkDestroyPipeline(Handle, Pipeline, Allocator);
}

/*
	Pipeline Cache
*/
VkResult VulkanDevice::CreatePipelineCache(const VkPipelineCacheCreateInfo* CreateInfo,
	const VkAllocationCallbacks* Allocator,
	VkPipelineCache* PipelineCache)
{
	return vkCreatePipelineCache(Handle, CreateInfo, nullptr, PipelineCache);
}

void VulkanDevice::DestroyPipelineCache(VkPipelineCache PipelineCache,
	const VkAllocationCallbacks* Allocator)
{
	vkDestroyPipelineCache(Handle, PipelineCache, Allocator);
}

/*
	Pipeline Layout
*/
VkResult VulkanDevice::CreatePipelineLayout(const VkPipelineLayoutCreateInfo* CreateInfo,
	const VkAllocationCallbacks* Allocator,
	VkPipelineLayout* PipelineLayout)
{
	return vkCreatePipelineLayout(Handle, CreateInfo, nullptr, PipelineLayout);
}

void VulkanDevice::DestroyPipelineLayout(VkPipelineLayout PipelineLayout, const VkAllocationCallbacks* Allocator)
{
	vkDestroyPipelineLayout(Handle, PipelineLayout, Allocator);
}

/*
	Memory
*/
VkResult VulkanDevice::AllocateMemory(const VkMemoryAllocateInfo* AllocateInfo,
	const VkAllocationCallbacks* Allocator,
	VkDeviceMemory* Memory)
{
	return vkAllocateMemory(Handle, AllocateInfo, nullptr, Memory);
}

void VulkanDevice::FreeMemory(VkDeviceMemory Memory,
	const VkAllocationCallbacks* Allocator)
{
	vkFreeMemory(Handle, Memory, Allocator);
}

VkResult VulkanDevice::MapMemory(VkDeviceMemory Memory,
	VkDeviceSize Offset,
	VkDeviceSize Size,
	VkMemoryMapFlags Flags,
	void** Data)
{
	return vkMapMemory(Handle, Memory, Offset, Size, Flags, Data);
}

void VulkanDevice::UnmapMemory(VkDeviceMemory Memory)
{
	vkUnmapMemory(Handle, Memory);
}

/*
	Buffer
*/
VkResult VulkanDevice::CreateBuffer(const VkBufferCreateInfo* CreateInfo,
	const VkAllocationCallbacks* Allocator,
	VkBuffer* Buffer)
{
	return vkCreateBuffer(Handle, CreateInfo, Allocator, Buffer);
}

void VulkanDevice::CopyBuffer(VkDeviceMemory Memory, VkDeviceSize MemorySize, void* BufferData)
{
	void* data;
	vkMapMemory(Handle, Memory, 0, MemorySize, 0, &data);
	memcpy(data, BufferData, static_cast<size_t>(MemorySize));
	vkUnmapMemory(Handle, Memory);
}

void VulkanDevice::DestroyBuffer(VkBuffer Buffer,
	const VkAllocationCallbacks* Allocator)
{
	vkDestroyBuffer(Handle, Buffer, Allocator);
}

VkResult VulkanDevice::BindBufferMemory(VkBuffer Buffer,
	VkDeviceMemory Memory,
	VkDeviceSize MemoryOffset)
{
	return vkBindBufferMemory(Handle, Buffer, Memory, MemoryOffset);
}

void VulkanDevice::GetBufferMemoryRequirements(VkBuffer Buffer,
	VkMemoryRequirements* MemoryRequirements)
{
	vkGetBufferMemoryRequirements(Handle, Buffer, MemoryRequirements);
}

void VulkanDevice::GetImageMemoryRequirements(VkImage Image,
	VkMemoryRequirements* MemoryRequirements)
{
	vkGetImageMemoryRequirements(Handle, Image, MemoryRequirements);
}

/*
	Buffer View
*/
VkBufferView VulkanDevice::CreateBufferView(VkBuffer Buffer, VkFormat Format, VkDeviceSize Offset, VkDeviceSize Range)
{
	VkBufferView BufferView;
	VkBufferViewCreateInfo CreateInfo;
	memset(&CreateInfo, 0, sizeof(VkBufferViewCreateInfo));
	CreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO;
	CreateInfo.format = Format;
	CreateInfo.offset = Offset;
	CreateInfo.range = Range;
	vkCreateBufferView(Handle, &CreateInfo, nullptr, &BufferView);
	return BufferView;
}

void VulkanDevice::DestroyBufferView(
	VkBufferView BufferView,
	const VkAllocationCallbacks* Allocator)
{
	vkDestroyBufferView(Handle, BufferView, Allocator);
}

/*
	Image 
*/
VkResult VulkanDevice::CreateImage(const VkImageCreateInfo* pCreateInfo,
	const VkAllocationCallbacks* pAllocator,
	VkImage* pImage)
{
	return vkCreateImage(Handle, pCreateInfo, pAllocator, pImage);
}

VkResult VulkanDevice::BindImageMemory(VkImage Image,
	VkDeviceMemory Memory,
	VkDeviceSize MemoryOffset)
{
	return vkBindImageMemory(Handle, Image, Memory, MemoryOffset);
}

void VulkanDevice::DestroyImage(VkImage Image, const VkAllocationCallbacks* Allocator)
{
	vkDestroyImage(Handle, Image, Allocator);
}

/*
	Image View
*/
VkResult VulkanDevice::CreateImageView(const VkImageViewCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator, VkImageView* ImageView)
{
	return vkCreateImageView(Handle, CreateInfo, nullptr, ImageView);
}

void VulkanDevice::DestroyImageView(VkImageView ImageView, const VkAllocationCallbacks* Allocator)
{
	vkDestroyImageView(Handle, ImageView, Allocator);
}

/*
	Descriptor Set Layout
*/
VkResult VulkanDevice::CreateDescriptorSetLayout(VkDescriptorSetLayoutCreateInfo* CreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorSetLayout* DescriptorSetLayout)
{
	return vkCreateDescriptorSetLayout(Handle, CreateInfo, pAllocator, DescriptorSetLayout);
}

void VulkanDevice::DestroyDescriptorSetLayout(VkDescriptorSetLayout DescriptorSetLayout,
	const VkAllocationCallbacks* Allocator)
{
	vkDestroyDescriptorSetLayout(Handle, DescriptorSetLayout, Allocator);
}

VkResult VulkanDevice::AllocateDescriptorSets(const VkDescriptorSetAllocateInfo* AllocateInfo, VkDescriptorSet* DescriptorSets)
{
	return vkAllocateDescriptorSets(Handle, AllocateInfo, DescriptorSets);
}

VkResult VulkanDevice::FreeDescriptorSets(VkDescriptorPool DescriptorPool, uint32_t DescriptorSetCount, const VkDescriptorSet* DescriptorSets)
{
	return vkFreeDescriptorSets(Handle, DescriptorPool, DescriptorSetCount, DescriptorSets);
}

/*
	Descriptor Pool
*/
VkResult VulkanDevice::CreateDescriptorPool(const VkDescriptorPoolCreateInfo* CreateInfo,
	const VkAllocationCallbacks* Allocator,
	VkDescriptorPool* DescriptorPool)
{
	return vkCreateDescriptorPool(Handle, CreateInfo, nullptr, DescriptorPool);
}

void VulkanDevice::DestroyDescriptorPool(VkDescriptorPool DescriptorPool,
	const VkAllocationCallbacks* Allocator)
{
	vkDestroyDescriptorPool(Handle, DescriptorPool, Allocator);
}

/*
	Update Descriptor Sets
*/
void VulkanDevice::UpdateDescriptorSets(uint32_t                    DescriptorWriteCount,
	const VkWriteDescriptorSet* DescriptorWrites,
	uint32_t                    DescriptorCopyCount,
	const VkCopyDescriptorSet* DescriptorCopies)
{
	vkUpdateDescriptorSets(Handle, DescriptorWriteCount, DescriptorWrites, DescriptorCopyCount, DescriptorCopies);
}

/*
	Sampler
*/
VkResult VulkanDevice::CreateSampler(const VkSamplerCreateInfo* pCreateInfo,
	const VkAllocationCallbacks* pAllocator,
	VkSampler* pSampler)
{
	return vkCreateSampler(Handle, pCreateInfo, pAllocator, pSampler);
}

void  VulkanDevice::DestroySampler(VkSampler Sampler, const VkAllocationCallbacks* Allocator)
{
	vkDestroySampler(Handle, Sampler, Allocator);
}

/*
	Query Pool
*/
VkResult VulkanDevice::CreateQueryPool(const VkQueryPoolCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator, VkQueryPool* QueryPool)
{
	return vkCreateQueryPool(Handle, CreateInfo, nullptr, QueryPool);
}

/*
	Swap Chain
*/
VkResult VulkanDevice::CreateSwapchainKHR(const VkSwapchainCreateInfoKHR* pCreateInfo,
	const VkAllocationCallbacks* pAllocator,
	VkSwapchainKHR* pSwapchain)
{
	return vkCreateSwapchainKHR(Handle, pCreateInfo, pAllocator, pSwapchain);
}

void VulkanDevice::DestroySwapchainKHR(VkSwapchainKHR Swapchain, const VkAllocationCallbacks* Allocator)
{
	vkDestroySwapchainKHR(Handle, Swapchain, Allocator);
}

VkResult VulkanDevice::GetSwapchainImagesKHR(VkSwapchainKHR                              swapchain,
	uint32_t* pSwapchainImageCount,
	VkImage* pSwapchainImages)
{
	return vkGetSwapchainImagesKHR(Handle, swapchain, pSwapchainImageCount, pSwapchainImages);
}

VkResult VulkanDevice::AcquireNextImageKHR(VkSwapchainKHR   swapchain,
	uint64_t                                    timeout,
	VkSemaphore                                 semaphore,
	VkFence                                     fence,
	uint32_t* pImageIndex)
{
	return vkAcquireNextImageKHR(Handle, swapchain, timeout, semaphore, fence, pImageIndex);
}

/*
	Wait Idle Operations
*/
VkResult VulkanDevice::DeviceWaitIdle()
{
	return vkDeviceWaitIdle(Handle);
}




