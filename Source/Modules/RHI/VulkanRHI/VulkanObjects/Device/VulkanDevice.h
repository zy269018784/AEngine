#pragma once
#include "Vulkan.h"
#include "VulkanObjects/PhysicalDevice/VulkanPhysicalDevice.h"
#include <RHIPixelFormat.h>
#include <vector>

class VulkanCommandPool;
class VulkanCommandBuffer;
class VulkanSemaphore;
class VulkanFence;
class VulkanQueue;
class VulkanDevice
{
public:
	VulkanDevice();
	VulkanDevice(VkDevice h);
	VulkanDevice(VulkanPhysicalDevice *pd, VkDevice h);
	~VulkanDevice();
	VkDevice GetHandle();
	VulkanPhysicalDevice* GetPhysicalDevice();

	/*
		为每个Queue Famliy创建队列
	*/
	void CreateQueue();

	/*
		Create Wrapper
	*/
	void CreateCommandPoolForAllQueueFamliy(const std::vector<VkQueueFamilyProperties> &QueueFamilyProperties);
	VulkanCommandPool* CreateCommandPool(uint32_t QeueFamilyIndex);
	VulkanCommandBuffer* CreateCommandBuffer(VulkanCommandPool * CommandPool);
	VulkanFence* CreateFence(bool Signaled = false);
	VulkanSemaphore* CreateSemaphore(bool Signaled = false);

public:
	void GetPresentQueue(std::uint32_t QueueFamilyIndex, std::uint32_t QueueIndex);
public:
	/*
		Vulkan API Wrapper
	*/
	/*
		Device
	*/
	void DestroyDevice(const VkAllocationCallbacks* Allocator);

	/*
		Device Queue
	*/
	void GetDeviceQueue(std::uint32_t QueueFamilyIndex, std::uint32_t QueueIndex, VkQueue* Queue);
	void GetDeviceQueue2(const VkDeviceQueueInfo2* QueueInfo, VkQueue* Queue);

	/*
		Command Pool
	*/
	VkResult CreateCommandPool(const VkCommandPoolCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator, VkCommandPool* CommandPool);
	void DestroyCommandPool(VkCommandPool CommandPool, const VkAllocationCallbacks* Allocator);
	void TrimCommandPool(VkCommandPool CommandPool, VkCommandPoolTrimFlags Flags);
	VkResult ResetCommandPool(VkCommandPool commandPool, VkCommandPoolResetFlags Flags);

	/*
		Command Buffer
	*/
	VkResult AllocateCommandBuffers(const VkCommandBufferAllocateInfo* AllocateInfo, VkCommandBuffer* CommandBuffers);

	void FreeCommandBuffers(VkCommandPool CommandPool, std::uint32_t CommandBufferCount, const VkCommandBuffer* CommandBuffers);

	/*
		Fence
	*/
	VkResult CreateFence(const VkFenceCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator, VkFence* Fence);
	void DestroyFence(VkFence Fence, const VkAllocationCallbacks* Allocator);
	VkResult WaitForFences(uint32_t FenceCount, const VkFence* pFences, VkBool32 WaitAll, uint64_t Timeout);
	VkResult ResetFences(uint32_t FenceCount, const VkFence* Fences);

	/*
		Semaphore
	*/
	VkResult CreateSemaphore(const VkSemaphoreCreateInfo* CreateInfo,
		const VkAllocationCallbacks* Allocator,
		VkSemaphore* Semaphore);

	void DestroySemaphore(VkSemaphore Semaphore, const VkAllocationCallbacks* Allocator);

	/*
		Event
	*/
	VkResult CreateEvent(const VkEventCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator, VkEvent* Event);
	void DestroyEvent(VkEvent Event, const VkAllocationCallbacks* Allocator);

	/*
		Render Pass
	*/
	VkResult CreateRenderPass(const VkRenderPassCreateInfo* pCreateInfo,
		const VkAllocationCallbacks* pAllocator,
		VkRenderPass* pRenderPass);
	void DestroyRenderPass(VkRenderPass RenderPass, const VkAllocationCallbacks* Allocator);

	/*
		Physical Storage Buffer Access
	*/
	VkDeviceAddress GetBufferDeviceAddress(const VkBufferDeviceAddressInfo* Info);

	std::uint64_t GetBufferOpaqueCaptureAddress(const VkBufferDeviceAddressInfo* Info);

	/*
		Framebuffer
	*/
	VkResult CreateFramebuffer(const VkFramebufferCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator, VkFramebuffer* Framebuffer);
	void DestroyFramebuffer(VkFramebuffer Framebuffer, const VkAllocationCallbacks* Allocator);

	/*
		Shader
	*/
	VkResult CreateShaderModule(const VkShaderModuleCreateInfo* CreateInfo,
		const VkAllocationCallbacks* Allocator,
		VkShaderModule* ShaderModule);

	void DestroyShaderModule(VkShaderModule ShaderModule,
		const VkAllocationCallbacks* Allocator);

	/*
		Pipeline
	*/
	VkResult CreateGraphicsPipelines(VkPipelineCache PipelineCache,
		std::uint32_t CreateInfoCount,
		const VkGraphicsPipelineCreateInfo* CreateInfos,
		const VkAllocationCallbacks* Allocator,
		VkPipeline* Pipelines);
	VkResult CreateComputePipelines(VkPipelineCache PipelineCache,
		std::uint32_t CreateInfoCount,
		const VkComputePipelineCreateInfo* CreateInfos,
		const VkAllocationCallbacks* Allocator,
		VkPipeline* Pipelines);
	void DestroyPipeline(VkPipeline Pipeline, const VkAllocationCallbacks* Allocator);

	/*
		Pipeline Cache
	*/
	VkResult CreatePipelineCache(const VkPipelineCacheCreateInfo* CreateInfo,
		const VkAllocationCallbacks* Allocator,
		VkPipelineCache* PipelineCache);
	void DestroyPipelineCache(VkPipelineCache PipelineCache, const VkAllocationCallbacks* Allocator);

	/*
		Pipeline Layout
	*/
	VkResult CreatePipelineLayout(const VkPipelineLayoutCreateInfo* CreateInfo,
		const VkAllocationCallbacks* Allocator,
		VkPipelineLayout* PipelineLayout);
	void DestroyPipelineLayout(VkPipelineLayout PipelineLayout, const VkAllocationCallbacks* Allocator);

	/* Memory */ 
	VkResult AllocateMemory(const VkMemoryAllocateInfo* AllocateInfo,
		const VkAllocationCallbacks* Allocator,
		VkDeviceMemory* Memory);

	void FreeMemory(VkDeviceMemory Memory,
		const VkAllocationCallbacks* Allocator);

	VkResult MapMemory(VkDeviceMemory Memory,
		VkDeviceSize Offset,
		VkDeviceSize Size,
		VkMemoryMapFlags Flags,
		void** Data);

	void UnmapMemory(VkDeviceMemory Memory);

	/*
		Buffer
	*/
	VkResult CreateBuffer(const VkBufferCreateInfo* CreateInfo,
		const VkAllocationCallbacks* Allocator,
		VkBuffer* Buffer);

	void CopyBuffer(VkDeviceMemory Memory, 
		VkDeviceSize MemorySize, 
		void* BufferData);

	void DestroyBuffer(VkBuffer Buffer,
		const VkAllocationCallbacks* Allocator);

	VkResult BindBufferMemory(VkBuffer Buffer,
		VkDeviceMemory Memory,
		VkDeviceSize MemoryOffset);

	void GetBufferMemoryRequirements(VkBuffer Buffer,
		VkMemoryRequirements* MemoryRequirements);

	void GetImageMemoryRequirements(VkImage Image,
		VkMemoryRequirements* MemoryRequirements);

	/*
		Buffer View
	*/
	VkBufferView CreateBufferView(VkBuffer Buffer, VkFormat format, VkDeviceSize offset, VkDeviceSize range);

	void DestroyBufferView(
		VkBufferView BufferView,
		const VkAllocationCallbacks* Allocator);

	/*
		Image
	*/
	void MapFormatSupport(RHIPixelFormat UEFormat, VkFormat InFormat, const VkComponentMapping& ComponentMapping);
	void SetupFormats();

	VkResult CreateImage(const VkImageCreateInfo* pCreateInfo,
		const VkAllocationCallbacks* pAllocator,
		VkImage* pImage);
	 
	VkResult BindImageMemory(VkImage Image,
		VkDeviceMemory Memory,
		VkDeviceSize MemoryOffset);

	void DestroyImage(VkImage Image, const VkAllocationCallbacks* Allocator);

	/*
		Image View
	*/
	VkResult CreateImageView(const VkImageViewCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator, VkImageView* View);
	void DestroyImageView(VkImageView ImageView, const VkAllocationCallbacks* Allocator);

	/*
		Descriptor Set Layout
	*/
	VkResult CreateDescriptorSetLayout(VkDescriptorSetLayoutCreateInfo* CreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorSetLayout* DescriptorSetLayout);
	void DestroyDescriptorSetLayout(VkDescriptorSetLayout DescriptorSetLayout, const VkAllocationCallbacks* Allocator);

	VkResult AllocateDescriptorSets(const VkDescriptorSetAllocateInfo* pAllocateInfo, VkDescriptorSet* pDescriptorSets);

	VkResult FreeDescriptorSets(VkDescriptorPool DescriptorPool, uint32_t DescriptorSetCount, const VkDescriptorSet* DescriptorSets);
	/*
		Descriptor Pool
	*/
	VkResult CreateDescriptorPool(const VkDescriptorPoolCreateInfo* CreateInfo,
		const VkAllocationCallbacks* Allocator,
		VkDescriptorPool* DescriptorPool);
	void DestroyDescriptorPool(VkDescriptorPool DescriptorPool, const VkAllocationCallbacks* Allocator);

	/*
		Update Descriptor Sets
	*/
	void UpdateDescriptorSets(uint32_t                    DescriptorWriteCount,
		const VkWriteDescriptorSet* DescriptorWrites,
		uint32_t                    DescriptorCopyCount,
		const VkCopyDescriptorSet* DescriptorCopies);

	/*
		Sampler
	*/
	VkResult CreateSampler(const VkSamplerCreateInfo* pCreateInfo,
		const VkAllocationCallbacks* pAllocator,
		VkSampler* pSampler);

	void DestroySampler(VkSampler Sampler, const VkAllocationCallbacks* Allocator);

	/*
		Query Pool
	*/
	VkResult CreateQueryPool(const VkQueryPoolCreateInfo* CreateInfo, const VkAllocationCallbacks* Allocator, VkQueryPool* QueryPool);

	/*
		Swap Chain
	*/
	VkResult CreateSwapchainKHR(const VkSwapchainCreateInfoKHR* pCreateInfo,
		const VkAllocationCallbacks* pAllocator,
		VkSwapchainKHR* pSwapchain);

	void DestroySwapchainKHR(VkSwapchainKHR Swapchain, const VkAllocationCallbacks* Allocator);

	VkResult GetSwapchainImagesKHR(VkSwapchainKHR                              swapchain,
		uint32_t* pSwapchainImageCount,
		VkImage* pSwapchainImages);

	VkResult AcquireNextImageKHR(VkSwapchainKHR   swapchain,
		uint64_t                                    timeout,
		VkSemaphore                                 semaphore,
		VkFence                                     fence,
		uint32_t* pImageIndex);

	/*
		Wait Idle Operations
	*/
	VkResult DeviceWaitIdle();
public:	
	/*
		Present Queue
	*/
	VkQueue		PresentQueue;
	/*
		为每个Queue Family创建1个Command Pool
	*/
	std::vector<VulkanCommandPool*> CommandPools;
	/*
		每个Queue Family创建1个或多个队列
	*/
	std::vector<VulkanQueue*> Queues;
private:
	VkDevice Handle;
	/*
		1个VulkanDevice对应1个VulkanPhysicalDevice
	*/
	VulkanPhysicalDevice* PhysicalDevice;	
};