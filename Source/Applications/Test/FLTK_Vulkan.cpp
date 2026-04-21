// FLTK_Vulkan_Triangle.cpp
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/x.H>
#include <FL/fl_draw.H>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_win32.h>
#include <cstdio>
#include <vector>
#include <cstring>

// 顶点着色器 SPIR-V
static const uint32_t vertShaderCode[] = {
    0x07230203,0x00010000,0x0008000a,0x0000002c,0x00000000,0x00020011,0x00000001,0x0006000b,
    0x00000001,0x4c534c47,0x6474732e,0x3035342e,0x00000000,0x0003000e,0x00000000,0x00000001,
    0x000a000f,0x00000000,0x00000004,0x6e69616d,0x00000000,0x0000000b,0x0000000f,0x00000015,
    0x00000019,0x0000001d,0x00030003,0x00000002,0x000001c2,0x00040005,0x00000004,0x6e69616d,
    0x00000000,0x00050005,0x0000000b,0x6172465b,0x6c6f4367,0x0000726f,0x00040005,0x0000000f,
    0x6172465b,0x6c6f4367,0x0000726f,0x00040005,0x00000015,0x6f50205b,0x7469736f,0x00000000,
    0x00040005,0x00000019,0x6f50205b,0x7469736f,0x00000000,0x00040005,0x0000001d,0x6f50205b,
    0x7469736f,0x00000000,0x00040005,0x00000021,0x65646e49,0x00000078,0x00030005,0x00000024,
    0x00767273,0x00040047,0x0000000b,0x0000001e,0x00000000,0x00040047,0x0000000f,0x0000001e,
    0x00000001,0x00040047,0x00000015,0x0000001e,0x00000002,0x00040047,0x00000019,0x0000001e,
    0x00000003,0x00040047,0x0000001d,0x0000001e,0x00000004,0x00020013,0x00000002,0x00030021,
    0x00000003,0x00000002,0x00030016,0x00000006,0x00000020,0x00040017,0x00000007,0x00000006,
    0x00000004,0x00040017,0x00000008,0x00000006,0x00000002,0x0004002b,0x00000006,0x0000000a,
    0x3f800000,0x00040020,0x0000000e,0x00000003,0x00000007,0x00040020,0x00000014,0x00000001,
    0x00000008,0x00040020,0x00000018,0x00000003,0x00000008,0x0004002b,0x00000006,0x0000001c,
    0x3f000000,0x00040020,0x00000020,0x00000007,0x00000008,0x00040015,0x00000022,0x00000020,
    0x00000000,0x0004002b,0x00000022,0x00000023,0x00000000,0x00040020,0x00000027,0x00000007,
    0x00000006,0x00050036,0x00000002,0x00000004,0x00000000,0x00000003,0x000200f8,0x00000005,
    0x0004003d,0x00000008,0x00000016,0x00000015,0x0004003d,0x00000008,0x0000001a,0x00000019,
    0x00050081,0x00000008,0x0000001e,0x00000016,0x0000001a,0x0004003d,0x00000008,0x00000025,
    0x00000021,0x0005008e,0x00000008,0x00000026,0x00000025,0x0000000a,0x00050081,0x00000008,
    0x00000028,0x0000001e,0x00000026,0x0004003d,0x00000008,0x00000029,0x0000001d,0x00050081,
    0x00000008,0x0000002a,0x00000028,0x00000029,0x0003003e,0x00000018,0x0000002a,0x0004003d,
    0x00000007,0x0000002b,0x0000000b,0x0003003e,0x0000000e,0x0000002b,0x000100fd,0x00010038
};

// 片段着色器 SPIR-V
static const uint32_t fragShaderCode[] = {
    0x07230203,0x00010000,0x0008000a,0x00000013,0x00000000,0x00020011,0x00000001,0x0006000b,
    0x00000001,0x4c534c47,0x6474732e,0x3035342e,0x00000000,0x0003000e,0x00000000,0x00000001,
    0x0007000f,0x00000004,0x00000004,0x6e69616d,0x00000000,0x00000009,0x0000000d,0x00030010,
    0x00000004,0x00000007,0x00030003,0x00000002,0x000001c2,0x00040005,0x00000004,0x6e69616d,
    0x00000000,0x00040005,0x00000009,0x6c6f4376,0x0000726f,0x00040005,0x0000000d,0x67617246,
    0x00000000,0x00040047,0x00000009,0x0000001e,0x00000000,0x00040047,0x0000000d,0x0000001e,
    0x00000000,0x00020013,0x00000002,0x00030021,0x00000003,0x00000002,0x00030016,0x00000006,
    0x00000020,0x00040017,0x00000007,0x00000006,0x00000004,0x00040020,0x00000008,0x00000003,
    0x00000007,0x00040020,0x0000000c,0x00000003,0x00000007,0x00050036,0x00000002,0x00000004,
    0x00000000,0x00000003,0x000200f8,0x00000005,0x0004003d,0x00000007,0x0000000a,0x00000009,
    0x0003003e,0x0000000c,0x0000000a,0x000100fd,0x00010038
};

class FltkVulkanWindow : public Fl_Window {
private:
    // Vulkan 核心对象
    VkInstance instance = VK_NULL_HANDLE;
    VkSurfaceKHR surface = VK_NULL_HANDLE;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device = VK_NULL_HANDLE;
    VkQueue graphicsQueue = VK_NULL_HANDLE;
    VkQueue presentQueue = VK_NULL_HANDLE;
    VkSwapchainKHR swapchain = VK_NULL_HANDLE;
    VkRenderPass renderPass = VK_NULL_HANDLE;
    VkPipelineLayout pipelineLayout = VK_NULL_HANDLE;
    VkPipeline graphicsPipeline = VK_NULL_HANDLE;
    VkCommandPool commandPool = VK_NULL_HANDLE;
    std::vector<VkCommandBuffer> commandBuffers;
    VkSemaphore imageAvailableSemaphore = VK_NULL_HANDLE;
    VkSemaphore renderFinishedSemaphore = VK_NULL_HANDLE;
    VkFence inFlightFence = VK_NULL_HANDLE;

    // 顶点缓冲
    VkBuffer vertexBuffer = VK_NULL_HANDLE;
    VkDeviceMemory vertexBufferMemory = VK_NULL_HANDLE;

    std::vector<VkImage> swapchainImages;
    std::vector<VkImageView> swapchainImageViews;
    std::vector<VkFramebuffer> framebuffers;

    bool vulkanReady = false;
    uint32_t currentImageIndex = 0;
    VkExtent2D swapchainExtent;
    uint32_t graphicsQueueFamily = 0;
    uint32_t presentQueueFamily = 0;
    int lastWidth = 0;
    int lastHeight = 0;

    // 顶点数据
    struct Vertex {
        float pos[2];
        float color[3];
    };

    std::vector<Vertex> vertices = {
        {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
        {{ 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
        {{ 0.0f,  0.5f}, {0.0f, 0.0f, 1.0f}}
    };

public:
    FltkVulkanWindow(int w, int h, const char* title) : Fl_Window(w, h, title) {
        end();
        lastWidth = w;
        lastHeight = h;
    }

    ~FltkVulkanWindow() {
        cleanup();
    }

    void cleanup() {
        if (vulkanReady && device != VK_NULL_HANDLE) {
            vkDeviceWaitIdle(device);

            if (vertexBuffer) vkDestroyBuffer(device, vertexBuffer, nullptr);
            if (vertexBufferMemory) vkFreeMemory(device, vertexBufferMemory, nullptr);
            if (inFlightFence) vkDestroyFence(device, inFlightFence, nullptr);
            if (renderFinishedSemaphore) vkDestroySemaphore(device, renderFinishedSemaphore, nullptr);
            if (imageAvailableSemaphore) vkDestroySemaphore(device, imageAvailableSemaphore, nullptr);

            for (auto fb : framebuffers) if (fb) vkDestroyFramebuffer(device, fb, nullptr);
            for (auto iv : swapchainImageViews) if (iv) vkDestroyImageView(device, iv, nullptr);
            if (graphicsPipeline) vkDestroyPipeline(device, graphicsPipeline, nullptr);
            if (pipelineLayout) vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
            if (renderPass) vkDestroyRenderPass(device, renderPass, nullptr);
            if (commandPool) vkDestroyCommandPool(device, commandPool, nullptr);
            if (swapchain) vkDestroySwapchainKHR(device, swapchain, nullptr);
            vkDestroyDevice(device, nullptr);
            if (surface) vkDestroySurfaceKHR(instance, surface, nullptr);
            if (instance) vkDestroyInstance(instance, nullptr);
        }
        vulkanReady = false;
    }

    HWND getWindowHandle() {
        if (!shown()) show();
        return fl_xid(this);
    }

    VkShaderModule createShaderModule(const uint32_t* code, size_t size) {
        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = size;
        createInfo.pCode = code;

        VkShaderModule shaderModule;
        if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
            printf("Failed to create shader module!\n");
            return VK_NULL_HANDLE;
        }
        return shaderModule;
    }

    void initVulkan() {
        if (vulkanReady) return;

        printf("Initializing Vulkan...\n");

        // 1. 创建实例
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "FLTK Vulkan Triangle";
        appInfo.apiVersion = VK_API_VERSION_1_0;

        const char* extensions[] = {"VK_KHR_surface", "VK_KHR_win32_surface"};
        VkInstanceCreateInfo instInfo{};
        instInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instInfo.pApplicationInfo = &appInfo;
        instInfo.enabledExtensionCount = 2;
        instInfo.ppEnabledExtensionNames = extensions;

        if (vkCreateInstance(&instInfo, nullptr, &instance) != VK_SUCCESS) {
            printf("Failed to create instance!\n");
            return;
        }

        // 2. 创建表面
        HWND hwnd = getWindowHandle();
        VkWin32SurfaceCreateInfoKHR surfInfo{};
        surfInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
        surfInfo.hinstance = GetModuleHandle(nullptr);
        surfInfo.hwnd = hwnd;

        if (vkCreateWin32SurfaceKHR(instance, &surfInfo, nullptr, &surface) != VK_SUCCESS) {
            printf("Failed to create surface!\n");
            return;
        }

        // 3. 选择物理设备
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
        if (deviceCount == 0) return;

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
        physicalDevice = devices[0];

        VkPhysicalDeviceProperties props;
        vkGetPhysicalDeviceProperties(physicalDevice, &props);
        printf("GPU: %s\n", props.deviceName);

        // 4. 查找队列族
        uint32_t familyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &familyCount, nullptr);
        std::vector<VkQueueFamilyProperties> families(familyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &familyCount, families.data());

        graphicsQueueFamily = UINT32_MAX;
        presentQueueFamily = UINT32_MAX;
        for (uint32_t i = 0; i < familyCount; i++) {
            if (families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                graphicsQueueFamily = i;
            }
            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surface, &presentSupport);
            if (presentSupport) {
                presentQueueFamily = i;
            }
            if (graphicsQueueFamily != UINT32_MAX && presentQueueFamily != UINT32_MAX) break;
        }

        // 5. 创建设备
        std::vector<VkDeviceQueueCreateInfo> queueInfos;
        float priority = 1.0f;

        if (graphicsQueueFamily == presentQueueFamily) {
            VkDeviceQueueCreateInfo qInfo{};
            qInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            qInfo.queueFamilyIndex = graphicsQueueFamily;
            qInfo.queueCount = 1;
            qInfo.pQueuePriorities = &priority;
            queueInfos.push_back(qInfo);
        } else {
            VkDeviceQueueCreateInfo gInfo{}, pInfo{};
            gInfo.sType = pInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            gInfo.queueFamilyIndex = graphicsQueueFamily;
            gInfo.queueCount = 1;
            gInfo.pQueuePriorities = &priority;
            pInfo.queueFamilyIndex = presentQueueFamily;
            pInfo.queueCount = 1;
            pInfo.pQueuePriorities = &priority;
            queueInfos.push_back(gInfo);
            queueInfos.push_back(pInfo);
        }

        const char* devExtensions[] = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
        VkDeviceCreateInfo devInfo{};
        devInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        devInfo.queueCreateInfoCount = (uint32_t)queueInfos.size();
        devInfo.pQueueCreateInfos = queueInfos.data();
        devInfo.enabledExtensionCount = 1;
        devInfo.ppEnabledExtensionNames = devExtensions;

        if (vkCreateDevice(physicalDevice, &devInfo, nullptr, &device) != VK_SUCCESS) {
            printf("Failed to create device!\n");
            return;
        }

        vkGetDeviceQueue(device, graphicsQueueFamily, 0, &graphicsQueue);
        vkGetDeviceQueue(device, presentQueueFamily, 0, &presentQueue);

        // 6. 创建交换链
        createSwapchain();

        // 7. 创建渲染通道
        VkAttachmentDescription colorAtt{};
        colorAtt.format = VK_FORMAT_B8G8R8A8_UNORM;
        colorAtt.samples = VK_SAMPLE_COUNT_1_BIT;
        colorAtt.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        colorAtt.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        colorAtt.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        colorAtt.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        colorAtt.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        colorAtt.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        VkAttachmentReference colorRef{};
        colorRef.attachment = 0;
        colorRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        VkSubpassDescription subpass{};
        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpass.colorAttachmentCount = 1;
        subpass.pColorAttachments = &colorRef;

        VkRenderPassCreateInfo rpInfo{};
        rpInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        rpInfo.attachmentCount = 1;
        rpInfo.pAttachments = &colorAtt;
        rpInfo.subpassCount = 1;
        rpInfo.pSubpasses = &subpass;

        if (vkCreateRenderPass(device, &rpInfo, nullptr, &renderPass) != VK_SUCCESS) {
            printf("Failed to create render pass!\n");
            return;
        }

        // 8. 创建顶点缓冲
        VkBufferCreateInfo bufInfo{};
        bufInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufInfo.size = sizeof(vertices[0]) * vertices.size();
        bufInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
        bufInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        if (vkCreateBuffer(device, &bufInfo, nullptr, &vertexBuffer) != VK_SUCCESS) {
            printf("Failed to create vertex buffer!\n");
            return;
        }

        VkMemoryRequirements memReqs;
        vkGetBufferMemoryRequirements(device, vertexBuffer, &memReqs);

        VkPhysicalDeviceMemoryProperties memProps;
        vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProps);

        uint32_t memType = 0;
        for (uint32_t i = 0; i < memProps.memoryTypeCount; i++) {
            if ((memReqs.memoryTypeBits & (1 << i)) &&
                (memProps.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)) {
                memType = i;
                break;
            }
        }

        VkMemoryAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memReqs.size;
        allocInfo.memoryTypeIndex = memType;

        if (vkAllocateMemory(device, &allocInfo, nullptr, &vertexBufferMemory) != VK_SUCCESS) {
            printf("Failed to allocate vertex buffer memory!\n");
            return;
        }

        vkBindBufferMemory(device, vertexBuffer, vertexBufferMemory, 0);

        void* data;
        vkMapMemory(device, vertexBufferMemory, 0, bufInfo.size, 0, &data);
        memcpy(data, vertices.data(), (size_t)bufInfo.size);
        vkUnmapMemory(device, vertexBufferMemory);

        // 9. 创建管线布局
        VkPipelineLayoutCreateInfo layoutInfo{};
        layoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;

        if (vkCreatePipelineLayout(device, &layoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
            printf("Failed to create pipeline layout!\n");
            return;
        }

        // 10. 创建图形管线
        VkShaderModule vertModule = createShaderModule(vertShaderCode, sizeof(vertShaderCode));
        VkShaderModule fragModule = createShaderModule(fragShaderCode, sizeof(fragShaderCode));

        VkPipelineShaderStageCreateInfo vertStage{};
        vertStage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        vertStage.stage = VK_SHADER_STAGE_VERTEX_BIT;
        vertStage.module = vertModule;
        vertStage.pName = "main";

        VkPipelineShaderStageCreateInfo fragStage{};
        fragStage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        fragStage.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        fragStage.module = fragModule;
        fragStage.pName = "main";

        VkPipelineShaderStageCreateInfo stages[] = {vertStage, fragStage};

        VkVertexInputBindingDescription bindingDesc{};
        bindingDesc.binding = 0;
        bindingDesc.stride = sizeof(Vertex);
        bindingDesc.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        VkVertexInputAttributeDescription attrDesc[2];
        attrDesc[0].binding = 0;
        attrDesc[0].location = 0;
        attrDesc[0].format = VK_FORMAT_R32G32_SFLOAT;
        attrDesc[0].offset = offsetof(Vertex, pos);

        attrDesc[1].binding = 0;
        attrDesc[1].location = 1;
        attrDesc[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attrDesc[1].offset = offsetof(Vertex, color);

        VkPipelineVertexInputStateCreateInfo vertexInput{};
        vertexInput.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        vertexInput.vertexBindingDescriptionCount = 1;
        vertexInput.pVertexBindingDescriptions = &bindingDesc;
        vertexInput.vertexAttributeDescriptionCount = 2;
        vertexInput.pVertexAttributeDescriptions = attrDesc;

        VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
        inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

        VkViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = (float)swapchainExtent.width;
        viewport.height = (float)swapchainExtent.height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        VkRect2D scissor{};
        scissor.offset = {0, 0};
        scissor.extent = swapchainExtent;

        VkPipelineViewportStateCreateInfo viewportState{};
        viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewportState.viewportCount = 1;
        viewportState.pViewports = &viewport;
        viewportState.scissorCount = 1;
        viewportState.pScissors = &scissor;

        VkPipelineRasterizationStateCreateInfo rasterizer{};
        rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
        rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
        rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
        rasterizer.lineWidth = 1.0f;

        VkPipelineMultisampleStateCreateInfo multisampling{};
        multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

        VkPipelineColorBlendAttachmentState blendAtt{};
        blendAtt.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
                                   VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

        VkPipelineColorBlendStateCreateInfo colorBlending{};
        colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        colorBlending.attachmentCount = 1;
        colorBlending.pAttachments = &blendAtt;

        VkGraphicsPipelineCreateInfo pipelineInfo{};
        pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        pipelineInfo.stageCount = 2;
        pipelineInfo.pStages = stages;
        pipelineInfo.pVertexInputState = &vertexInput;
        pipelineInfo.pInputAssemblyState = &inputAssembly;
        pipelineInfo.pViewportState = &viewportState;
        pipelineInfo.pRasterizationState = &rasterizer;
        pipelineInfo.pMultisampleState = &multisampling;
        pipelineInfo.pColorBlendState = &colorBlending;
        pipelineInfo.layout = pipelineLayout;
        pipelineInfo.renderPass = renderPass;
        pipelineInfo.subpass = 0;

        if (vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS) {
            printf("Failed to create graphics pipeline!\n");
        }

        vkDestroyShaderModule(device, vertModule, nullptr);
        vkDestroyShaderModule(device, fragModule, nullptr);

        // 11. 创建帧缓冲和命令缓冲
        createFramebuffersAndCommandBuffers();

        // 12. 创建同步对象
        VkSemaphoreCreateInfo semInfo{};
        semInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        VkFenceCreateInfo fenceInfo{};
        fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

        if (vkCreateSemaphore(device, &semInfo, nullptr, &imageAvailableSemaphore) != VK_SUCCESS ||
            vkCreateSemaphore(device, &semInfo, nullptr, &renderFinishedSemaphore) != VK_SUCCESS ||
            vkCreateFence(device, &fenceInfo, nullptr, &inFlightFence) != VK_SUCCESS) {
            printf("Failed to create sync objects!\n");
            return;
        }

        vulkanReady = true;
        printf("Vulkan initialized successfully!\n");
    }

    void createSwapchain() {
        VkSurfaceCapabilitiesKHR caps;
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &caps);

        swapchainExtent = caps.currentExtent;
        if (swapchainExtent.width == 0xFFFFFFFF) {
            swapchainExtent = {(uint32_t)w(), (uint32_t)h()};
        }

        uint32_t imageCount = caps.minImageCount + 1;
        if (caps.maxImageCount > 0 && imageCount > caps.maxImageCount) {
            imageCount = caps.maxImageCount;
        }

        VkSwapchainCreateInfoKHR swapInfo{};
        swapInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        swapInfo.surface = surface;
        swapInfo.minImageCount = imageCount;
        swapInfo.imageFormat = VK_FORMAT_B8G8R8A8_UNORM;
        swapInfo.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
        swapInfo.imageExtent = swapchainExtent;
        swapInfo.imageArrayLayers = 1;
        swapInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
        swapInfo.preTransform = caps.currentTransform;
        swapInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        swapInfo.presentMode = VK_PRESENT_MODE_FIFO_KHR;
        swapInfo.clipped = VK_TRUE;
        swapInfo.oldSwapchain = swapchain;

        if (vkCreateSwapchainKHR(device, &swapInfo, nullptr, &swapchain) != VK_SUCCESS) {
            printf("Failed to create swapchain!\n");
            return;
        }

        if (swapInfo.oldSwapchain != VK_NULL_HANDLE) {
            vkDestroySwapchainKHR(device, swapInfo.oldSwapchain, nullptr);
        }

        vkGetSwapchainImagesKHR(device, swapchain, &imageCount, nullptr);
        swapchainImages.resize(imageCount);
        vkGetSwapchainImagesKHR(device, swapchain, &imageCount, swapchainImages.data());

        // 创建图像视图
        swapchainImageViews.resize(imageCount);
        for (size_t i = 0; i < imageCount; i++) {
            VkImageViewCreateInfo viewInfo{};
            viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            viewInfo.image = swapchainImages[i];
            viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
            viewInfo.format = VK_FORMAT_B8G8R8A8_UNORM;
            viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            viewInfo.subresourceRange.baseMipLevel = 0;
            viewInfo.subresourceRange.levelCount = 1;
            viewInfo.subresourceRange.baseArrayLayer = 0;
            viewInfo.subresourceRange.layerCount = 1;
            vkCreateImageView(device, &viewInfo, nullptr, &swapchainImageViews[i]);
        }
    }

    void createFramebuffersAndCommandBuffers() {
        // 创建帧缓冲
        framebuffers.resize(swapchainImageViews.size());
        for (size_t i = 0; i < swapchainImageViews.size(); i++) {
            VkImageView attachments[] = {swapchainImageViews[i]};

            VkFramebufferCreateInfo fbInfo{};
            fbInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            fbInfo.renderPass = renderPass;
            fbInfo.attachmentCount = 1;
            fbInfo.pAttachments = attachments;
            fbInfo.width = swapchainExtent.width;
            fbInfo.height = swapchainExtent.height;
            fbInfo.layers = 1;
            vkCreateFramebuffer(device, &fbInfo, nullptr, &framebuffers[i]);
        }

        // 创建命令池（如果还没有）
        if (commandPool == VK_NULL_HANDLE) {
            VkCommandPoolCreateInfo poolInfo{};
            poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
            poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
            poolInfo.queueFamilyIndex = graphicsQueueFamily;
            vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool);
        }

        // 创建命令缓冲
        commandBuffers.resize(framebuffers.size());
        VkCommandBufferAllocateInfo cmdAlloc{};
        cmdAlloc.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        cmdAlloc.commandPool = commandPool;
        cmdAlloc.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        cmdAlloc.commandBufferCount = (uint32_t)commandBuffers.size();
        vkAllocateCommandBuffers(device, &cmdAlloc, commandBuffers.data());

        // 记录命令缓冲
        for (size_t i = 0; i < commandBuffers.size(); i++) {
            VkCommandBufferBeginInfo beginInfo{};
            beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            vkBeginCommandBuffer(commandBuffers[i], &beginInfo);

            VkClearValue clearColor = {0.1f, 0.1f, 0.2f, 1.0f};
            VkRenderPassBeginInfo rpBegin{};
            rpBegin.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            rpBegin.renderPass = renderPass;
            rpBegin.framebuffer = framebuffers[i];
            rpBegin.renderArea.offset = {0, 0};
            rpBegin.renderArea.extent = swapchainExtent;
            rpBegin.clearValueCount = 1;
            rpBegin.pClearValues = &clearColor;

            vkCmdBeginRenderPass(commandBuffers[i], &rpBegin, VK_SUBPASS_CONTENTS_INLINE);
            vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);

            VkDeviceSize offsets[] = {0};
            vkCmdBindVertexBuffers(commandBuffers[i], 0, 1, &vertexBuffer, offsets);
            vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);

            vkCmdEndRenderPass(commandBuffers[i]);
            vkEndCommandBuffer(commandBuffers[i]);
        }
    }

    void drawFrame() {
        if (!vulkanReady) return;

        // 检查窗口大小是否改变
        if (w() != lastWidth || h() != lastHeight) {
            lastWidth = w();
            lastHeight = h();
            recreateSwapchain();
            return;
        }

        vkWaitForFences(device, 1, &inFlightFence, VK_TRUE, UINT64_MAX);
        vkResetFences(device, 1, &inFlightFence);

        uint32_t imageIndex;
        VkResult result = vkAcquireNextImageKHR(device, swapchain, UINT64_MAX,
                                                  imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);

        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR) {
            recreateSwapchain();
            return;
        } else if (result != VK_SUCCESS) {
            return;
        }

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        VkSemaphore waitSemaphores[] = {imageAvailableSemaphore};
        VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffers[imageIndex];

        VkSemaphore signalSemaphores[] = {renderFinishedSemaphore};
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        vkQueueSubmit(graphicsQueue, 1, &submitInfo, inFlightFence);

        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;

        VkSwapchainKHR swapchains[] = {swapchain};
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapchains;
        presentInfo.pImageIndices = &imageIndex;

        vkQueuePresentKHR(presentQueue, &presentInfo);
    }

    void recreateSwapchain() {
        if (!vulkanReady) return;

        printf("Recreating swapchain...\n");
        vkDeviceWaitIdle(device);

        // 清理旧的资源
        for (auto fb : framebuffers) if (fb) vkDestroyFramebuffer(device, fb, nullptr);
        for (auto iv : swapchainImageViews) if (iv) vkDestroyImageView(device, iv, nullptr);
        vkFreeCommandBuffers(device, commandPool, (uint32_t)commandBuffers.size(), commandBuffers.data());
        commandBuffers.clear();
        framebuffers.clear();
        swapchainImageViews.clear();
        swapchainImages.clear();

        // 重建交换链
        VkSurfaceCapabilitiesKHR caps;
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &caps);

        swapchainExtent = caps.currentExtent;
        if (swapchainExtent.width == 0xFFFFFFFF) {
            swapchainExtent = {(uint32_t)w(), (uint32_t)h()};
        }

        uint32_t imageCount = caps.minImageCount + 1;
        if (caps.maxImageCount > 0 && imageCount > caps.maxImageCount) {
            imageCount = caps.maxImageCount;
        }

        VkSwapchainCreateInfoKHR swapInfo{};
        swapInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        swapInfo.surface = surface;
        swapInfo.minImageCount = imageCount;
        swapInfo.imageFormat = VK_FORMAT_B8G8R8A8_UNORM;
        swapInfo.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
        swapInfo.imageExtent = swapchainExtent;
        swapInfo.imageArrayLayers = 1;
        swapInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
        swapInfo.preTransform = caps.currentTransform;
        swapInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        swapInfo.presentMode = VK_PRESENT_MODE_FIFO_KHR;
        swapInfo.clipped = VK_TRUE;
        swapInfo.oldSwapchain = swapchain;

        VkSwapchainKHR oldSwapchain = swapchain;
        if (vkCreateSwapchainKHR(device, &swapInfo, nullptr, &swapchain) != VK_SUCCESS) {
            printf("Failed to recreate swapchain!\n");
            swapchain = oldSwapchain;
            return;
        }

        if (oldSwapchain != VK_NULL_HANDLE) {
            vkDestroySwapchainKHR(device, oldSwapchain, nullptr);
        }

        vkGetSwapchainImagesKHR(device, swapchain, &imageCount, nullptr);
        swapchainImages.resize(imageCount);
        vkGetSwapchainImagesKHR(device, swapchain, &imageCount, swapchainImages.data());

        // 重建图像视图
        swapchainImageViews.resize(imageCount);
        for (size_t i = 0; i < imageCount; i++) {
            VkImageViewCreateInfo viewInfo{};
            viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            viewInfo.image = swapchainImages[i];
            viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
            viewInfo.format = VK_FORMAT_B8G8R8A8_UNORM;
            viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            viewInfo.subresourceRange.baseMipLevel = 0;
            viewInfo.subresourceRange.levelCount = 1;
            viewInfo.subresourceRange.baseArrayLayer = 0;
            viewInfo.subresourceRange.layerCount = 1;
            vkCreateImageView(device, &viewInfo, nullptr, &swapchainImageViews[i]);
        }

        // 重建帧缓冲和命令缓冲
        createFramebuffersAndCommandBuffers();

        printf("Swapchain recreated!\n");
    }

    virtual void draw() override {
        if (!vulkanReady) {
            initVulkan();
            if (!vulkanReady) {
                fl_color(FL_RED);
                fl_rectf(0, 0, w(), h());
                fl_color(FL_WHITE);
                fl_font(FL_HELVETICA, 16);
                fl_draw("Vulkan initialization failed", 50, 50);
                return;
            }
        }

        drawFrame();
        redraw();
    }

    virtual int handle(int event) override {
        if (event == FL_KEYBOARD && Fl::event_key() == FL_Escape) {
            return 0;
        }
        return Fl_Window::handle(event);
    }
};

int Fltk_Vulkan(int argc, char** argv) {
    FltkVulkanWindow window(800, 600, "FLTK + Vulkan - Colorful Triangle");
    window.show(argc, argv);
    return Fl::run();
}
