#include "vulkan_window.h"
#include <QVulkanInstance>
#include <QVulkanFunctions>
#include <QDebug>
#include <vector>

#define VK_CHECK_RESULT(f) { \
VkResult res = (f); \
if (res != VK_SUCCESS) { \
qFatal("Vulkan error: %d", res); \
} \
}

VulkanWindow::VulkanWindow(QWindow *parent)
: QWindow(parent)
, m_instance(nullptr)
, m_surface(VK_NULL_HANDLE)
, m_device(VK_NULL_HANDLE)
, m_swapchain(VK_NULL_HANDLE)
, m_renderPass(VK_NULL_HANDLE)
, m_pipelineLayout(VK_NULL_HANDLE)
, m_graphicsPipeline(VK_NULL_HANDLE)
, m_commandPool(VK_NULL_HANDLE)
{
setSurfaceType(QWindow::VulkanSurface);
}

VulkanWindow::~VulkanWindow()
{
if (m_device) {
vkDeviceWaitIdle(m_device);

        for (size_t i = 0; i < m_inFlightFences.size(); i++) {
            vkDestroySemaphore(m_device, m_renderFinishedSemaphores[i], nullptr);
            vkDestroySemaphore(m_device, m_imageAvailableSemaphores[i], nullptr);
            vkDestroyFence(m_device, m_inFlightFences[i], nullptr);
        }

        vkDestroyCommandPool(m_device, m_commandPool, nullptr);

        for (auto framebuffer : m_swapchainFramebuffers) {
            vkDestroyFramebuffer(m_device, framebuffer, nullptr);
        }

        if (m_graphicsPipeline) {
            vkDestroyPipeline(m_device, m_graphicsPipeline, nullptr);
        }

        if (m_pipelineLayout) {
            vkDestroyPipelineLayout(m_device, m_pipelineLayout, nullptr);
        }

        if (m_renderPass) {
            vkDestroyRenderPass(m_device, m_renderPass, nullptr);
        }

        for (auto imageView : m_swapchainImageViews) {
            vkDestroyImageView(m_device, imageView, nullptr);
        }

        if (m_swapchain) {
            vkDestroySwapchainKHR(m_device, m_swapchain, nullptr);
        }

        if (m_surface) {
            vkDestroySurfaceKHR(m_instance->vkInstance(), m_surface, nullptr);
        }

        vkDestroyDevice(m_device, nullptr);
    }

    delete m_instance;
}

void VulkanWindow::initialize()
{
m_instance = new QVulkanInstance();

    // Enable validation layers in debug builds
#ifdef QT_DEBUG
m_instance->setLayers(QByteArrayList() << "VK_LAYER_KHRONOS_validation");
#endif

    if (!m_instance->create()) {
        qFatal("Failed to create Vulkan instance: %d", m_instance->errorCode());
    }

    // Create Vulkan surface for this window
    m_surface = m_instance->surfaceForWindow(this);
    if (m_surface == VK_NULL_HANDLE) {
        qFatal("Failed to create Vulkan surface");
    }

    initVulkan();
}

void VulkanWindow::initVulkan()
{
// Pick physical device
uint32_t deviceCount = 0;
vkEnumeratePhysicalDevices(m_instance->vkInstance(), &deviceCount, nullptr);

    if (deviceCount == 0) {
        qFatal("No Vulkan devices found");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(m_instance->vkInstance(), &deviceCount, devices.data());

    // Use first suitable device
    m_physicalDevice = devices[0];

    // Create logical device
    float queuePriority = 1.0f;
    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = 0; // Simplified - should find graphics queue family
    queueCreateInfo.queueCount = 1;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    const char* deviceExtensions[] = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

    VkDeviceCreateInfo deviceCreateInfo{};
    deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.queueCreateInfoCount = 1;
    deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
    deviceCreateInfo.enabledExtensionCount = 1;
    deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions;

    VK_CHECK_RESULT(vkCreateDevice(m_physicalDevice, &deviceCreateInfo, nullptr, &m_device));

    // Get device queues
    vkGetDeviceQueue(m_device, 0, 0, &m_graphicsQueue);
    vkGetDeviceQueue(m_device, 0, 0, &m_presentQueue); // Simplified

    m_devFuncs = m_instance->deviceFunctions(m_device);

    // Create sync objects
    m_imageAvailableSemaphores.resize(2);
    m_renderFinishedSemaphores.resize(2);
    m_inFlightFences.resize(2);

    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (size_t i = 0; i < 2; i++) {
        VK_CHECK_RESULT(vkCreateSemaphore(m_device, &semaphoreInfo, nullptr, &m_imageAvailableSemaphores[i]));
        VK_CHECK_RESULT(vkCreateSemaphore(m_device, &semaphoreInfo, nullptr, &m_renderFinishedSemaphores[i]));
        VK_CHECK_RESULT(vkCreateFence(m_device, &fenceInfo, nullptr, &m_inFlightFences[i]));
    }

    // Create command pool
    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.queueFamilyIndex = 0;
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

    VK_CHECK_RESULT(vkCreateCommandPool(m_device, &poolInfo, nullptr, &m_commandPool));

    initSwapchain();
    initRenderPass();
    initFramebuffers();
    initPipeline();

    // Create command buffers
    m_commandBuffers.resize(m_swapchainFramebuffers.size());

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = m_commandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = (uint32_t)m_commandBuffers.size();

    VK_CHECK_RESULT(vkAllocateCommandBuffers(m_device, &allocInfo, m_commandBuffers.data()));

    recordCommandBuffer();
}

void VulkanWindow::initSwapchain()
{
// Simplified swapchain creation - in real code, query surface capabilities
VkSwapchainCreateInfoKHR createInfo{};
createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
createInfo.surface = m_surface;
createInfo.minImageCount = 2; // Double buffering
createInfo.imageFormat = VK_FORMAT_B8G8R8A8_UNORM;
createInfo.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
createInfo.imageExtent = { (uint32_t)width(), (uint32_t)height() };
createInfo.imageArrayLayers = 1;
createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
createInfo.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
createInfo.presentMode = VK_PRESENT_MODE_FIFO_KHR;
createInfo.clipped = VK_TRUE;

    VK_CHECK_RESULT(vkCreateSwapchainKHR(m_device, &createInfo, nullptr, &m_swapchain));

    // Get swapchain images
    uint32_t imageCount;
    vkGetSwapchainImagesKHR(m_device, m_swapchain, &imageCount, nullptr);
    m_swapchainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(m_device, m_swapchain, &imageCount, m_swapchainImages.data());

    // Create image views
    m_swapchainImageViews.resize(m_swapchainImages.size());
    for (size_t i = 0; i < m_swapchainImages.size(); i++) {
        VkImageViewCreateInfo viewInfo{};
        viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        viewInfo.image = m_swapchainImages[i];
        viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        viewInfo.format = VK_FORMAT_B8G8R8A8_UNORM;
        viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        viewInfo.subresourceRange.baseMipLevel = 0;
        viewInfo.subresourceRange.levelCount = 1;
        viewInfo.subresourceRange.baseArrayLayer = 0;
        viewInfo.subresourceRange.layerCount = 1;

        VK_CHECK_RESULT(vkCreateImageView(m_device, &viewInfo, nullptr, &m_swapchainImageViews[i]));
    }
}

void VulkanWindow::initRenderPass()
{
VkAttachmentDescription colorAttachment{};
colorAttachment.format = VK_FORMAT_B8G8R8A8_UNORM;
colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentReference colorAttachmentRef{};
    colorAttachmentRef.attachment = 0;
    colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpass{};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &colorAttachmentRef;

    VkRenderPassCreateInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.attachmentCount = 1;
    renderPassInfo.pAttachments = &colorAttachment;
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpass;

    VK_CHECK_RESULT(vkCreateRenderPass(m_device, &renderPassInfo, nullptr, &m_renderPass));
}

void VulkanWindow::initFramebuffers()
{
m_swapchainFramebuffers.resize(m_swapchainImageViews.size());

    for (size_t i = 0; i < m_swapchainImageViews.size(); i++) {
        VkImageView attachments[] = { m_swapchainImageViews[i] };

        VkFramebufferCreateInfo framebufferInfo{};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = m_renderPass;
        framebufferInfo.attachmentCount = 1;
        framebufferInfo.pAttachments = attachments;
        framebufferInfo.width = width();
        framebufferInfo.height = height();
        framebufferInfo.layers = 1;

        VK_CHECK_RESULT(vkCreateFramebuffer(m_device, &framebufferInfo, nullptr, &m_swapchainFramebuffers[i]));
    }
}

void VulkanWindow::initPipeline()
{
// Very simple pipeline - just clear the screen
VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
vertShaderStageInfo.module = VK_NULL_HANDLE; // Would load shaders in real implementation
vertShaderStageInfo.pName = "main";

    VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
    fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragShaderStageInfo.module = VK_NULL_HANDLE;
    fragShaderStageInfo.pName = "main";

    VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

    VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

    VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
    inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    inputAssembly.primitiveRestartEnable = VK_FALSE;

    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = (float)width();
    viewport.height = (float)height();
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    VkRect2D scissor{};
    scissor.offset = {0, 0};
    scissor.extent = {(uint32_t)width(), (uint32_t)height()};

    VkPipelineViewportStateCreateInfo viewportState{};
    viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportState.viewportCount = 1;
    viewportState.pViewports = &viewport;
    viewportState.scissorCount = 1;
    viewportState.pScissors = &scissor;

    VkPipelineRasterizationStateCreateInfo rasterizer{};
    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.depthClampEnable = VK_FALSE;
    rasterizer.rasterizerDiscardEnable = VK_FALSE;
    rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizer.lineWidth = 1.0f;
    rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
    rasterizer.depthBiasEnable = VK_FALSE;

    VkPipelineMultisampleStateCreateInfo multisampling{};
    multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.sampleShadingEnable = VK_FALSE;
    multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

    VkPipelineColorBlendAttachmentState colorBlendAttachment{};
    colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    colorBlendAttachment.blendEnable = VK_FALSE;

    VkPipelineColorBlendStateCreateInfo colorBlending{};
    colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending.logicOpEnable = VK_FALSE;
    colorBlending.attachmentCount = 1;
    colorBlending.pAttachments = &colorBlendAttachment;

    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;

    VK_CHECK_RESULT(vkCreatePipelineLayout(m_device, &pipelineLayoutInfo, nullptr, &m_pipelineLayout));

    VkGraphicsPipelineCreateInfo pipelineInfo{};
    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.stageCount = 2;
    pipelineInfo.pStages = shaderStages;
    pipelineInfo.pVertexInputState = &vertexInputInfo;
    pipelineInfo.pInputAssemblyState = &inputAssembly;
    pipelineInfo.pViewportState = &viewportState;
    pipelineInfo.pRasterizationState = &rasterizer;
    pipelineInfo.pMultisampleState = &multisampling;
    pipelineInfo.pColorBlendState = &colorBlending;
    pipelineInfo.layout = m_pipelineLayout;
    pipelineInfo.renderPass = m_renderPass;
    pipelineInfo.subpass = 0;

    VK_CHECK_RESULT(vkCreateGraphicsPipelines(m_device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &m_graphicsPipeline));
}

void VulkanWindow::recordCommandBuffer()
{
for (size_t i = 0; i < m_commandBuffers.size(); i++) {
VkCommandBufferBeginInfo beginInfo{};
beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        VK_CHECK_RESULT(vkBeginCommandBuffer(m_commandBuffers[i], &beginInfo));

        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = m_renderPass;
        renderPassInfo.framebuffer = m_swapchainFramebuffers[i];
        renderPassInfo.renderArea.offset = {0, 0};
        renderPassInfo.renderArea.extent = {(uint32_t)width(), (uint32_t)height()};

        VkClearValue clearColor = {{{0.2f, 0.3f, 0.8f, 1.0f}}};
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;

        vkCmdBeginRenderPass(m_commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
        vkCmdBindPipeline(m_commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, m_graphicsPipeline);
        vkCmdDraw(m_commandBuffers[i], 3, 1, 0, 0); // Draw triangle
        vkCmdEndRenderPass(m_commandBuffers[i]);

        VK_CHECK_RESULT(vkEndCommandBuffer(m_commandBuffers[i]));
    }
}

void VulkanWindow::render()
{
vkWaitForFences(m_device, 1, &m_inFlightFences[m_currentFrame], VK_TRUE, UINT64_MAX);

    uint32_t imageIndex;
    VkResult result = vkAcquireNextImageKHR(m_device, m_swapchain, UINT64_MAX, 
                                           m_imageAvailableSemaphores[m_currentFrame], 
                                           VK_NULL_HANDLE, &imageIndex);

    if (result == VK_ERROR_OUT_OF_DATE_KHR) {
        // Handle swapchain recreation
        return;
    } else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
        qFatal("Failed to acquire swapchain image");
    }

    vkResetFences(m_device, 1, &m_inFlightFences[m_currentFrame]);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = {m_imageAvailableSemaphores[m_currentFrame]};
    VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &m_commandBuffers[imageIndex];

    VkSemaphore signalSemaphores[] = {m_renderFinishedSemaphores[m_currentFrame]};
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    VK_CHECK_RESULT(vkQueueSubmit(m_graphicsQueue, 1, &submitInfo, m_inFlightFences[m_currentFrame]));

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = &m_swapchain;
    presentInfo.pImageIndices = &imageIndex;

    result = vkQueuePresentKHR(m_presentQueue, &presentInfo);

    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || m_frameBufferResized) {
        m_frameBufferResized = false;
        // Recreate swapchain
    } else if (result != VK_SUCCESS) {
        qFatal("Failed to present swapchain image");
    }

    m_currentFrame = (m_currentFrame + 1) % 2;
}

void VulkanWindow::exposeEvent(QExposeEvent *event)
{
if (isExposed()) {
render();
}
}

void VulkanWindow::resizeEvent(QResizeEvent *event)
{
m_frameBufferResized = true;
QWindow::resizeEvent(event);
}

bool VulkanWindow::event(QEvent *event)
{
switch (event->type()) {
case QEvent::UpdateRequest:
render();
break;
default:
break;
}
return QWindow::event(event);
}

// VulkanWidget implementation
VulkanWidget::VulkanWidget(QWidget *parent)
: QWidget(parent)
{
m_vulkanWindow = new VulkanWindow();
m_container = QWidget::createWindowContainer(m_vulkanWindow, this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_container);
    layout->setContentsMargins(0, 0, 0, 0);
    
    m_vulkanWindow->initialize();
}

VulkanWidget::~VulkanWidget()
{
// Cleanup handled by VulkanWindow destructor
}