// Provided by VK_VERSION_1_0
VkResult vkCreateRenderPass(
VkDevice                                    device,
const VkRenderPassCreateInfo*               pCreateInfo,
const VkAllocationCallbacks*                pAllocator,
VkRenderPass*                               pRenderPass);

// Provided by VK_VERSION_1_2
VkResult vkCreateRenderPass2(
VkDevice                                    device,
const VkRenderPassCreateInfo2*              pCreateInfo,
const VkAllocationCallbacks*                pAllocator,
VkRenderPass*                               pRenderPass);

// Provided by VK_KHR_create_renderpass2
// Equivalent to vkCreateRenderPass2
VkResult vkCreateRenderPass2KHR(
VkDevice                                    device,
const VkRenderPassCreateInfo2*              pCreateInfo,
const VkAllocationCallbacks*                pAllocator,
VkRenderPass*                               pRenderPass);




