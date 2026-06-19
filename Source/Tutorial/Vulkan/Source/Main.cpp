// ============================================================
// 完整 Vulkan MRT 示例 - 3个MRT目标 + 纹理加载
// 修正：MRT Pass 和 Final Pass 各自绑定正确的纹理
// ============================================================

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <stdexcept>
#include <array>
#include <algorithm>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize2.h"

#define VK_CHECK(result) if (result != VK_SUCCESS) { \
    throw std::runtime_error("Vulkan error: " + std::to_string(result)); \
}

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;
const int MRT_COUNT = 3;

// ============================================================
// 顶点数据结构 - 使用全屏三角形
// ============================================================
struct Vertex {
    float pos[3];
    float texCoord[2];
};

std::vector<Vertex> vertices = {
    {{-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
    {{ 3.0f, -1.0f, 0.0f}, {2.0f, 0.0f}},
    {{-1.0f,  3.0f, 0.0f}, {0.0f, 2.0f}}
};

// ============================================================
// 辅助函数
// ============================================================
std::vector<char> readFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("failed to open file: " + filename);
    }
    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);
    file.seekg(0);
    file.read(buffer.data(), fileSize);
    return buffer;
}

uint32_t findMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties) {
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);
    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
        if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }
    throw std::runtime_error("failed to find suitable memory type!");
}

void createBuffer(VkDevice device, VkPhysicalDevice physicalDevice,
                  VkDeviceSize size, VkBufferUsageFlags usage,
                  VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory) {
    VkBufferCreateInfo bufferInfo = {};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    VK_CHECK(vkCreateBuffer(device, &bufferInfo, nullptr, &buffer));

    VkMemoryRequirements memReqs;
    vkGetBufferMemoryRequirements(device, buffer, &memReqs);

    VkMemoryAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memReqs.size;
    allocInfo.memoryTypeIndex = findMemoryType(physicalDevice, memReqs.memoryTypeBits, properties);

    VK_CHECK(vkAllocateMemory(device, &allocInfo, nullptr, &bufferMemory));
    VK_CHECK(vkBindBufferMemory(device, buffer, bufferMemory, 0));
}

// ============================================================
// copyBufferToImage - 使用 Fence 确保完成
// ============================================================
void copyBufferToImage(VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue,
                       VkBuffer buffer, VkImage image, uint32_t width, uint32_t height) {
    VkCommandBufferAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = commandPool;
    allocInfo.commandBufferCount = 1;

    VkCommandBuffer commandBuffer;
    VK_CHECK(vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer));

    VkCommandBufferBeginInfo beginInfo = {};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    VK_CHECK(vkBeginCommandBuffer(commandBuffer, &beginInfo));

    VkImageMemoryBarrier barrier = {};
    barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.image = image;
    barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    barrier.subresourceRange.baseMipLevel = 0;
    barrier.subresourceRange.levelCount = 1;
    barrier.subresourceRange.baseArrayLayer = 0;
    barrier.subresourceRange.layerCount = 1;
    barrier.srcAccessMask = 0;
    barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

    vkCmdPipelineBarrier(commandBuffer,
                         VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
                         VK_PIPELINE_STAGE_TRANSFER_BIT,
                         0, 0, nullptr, 0, nullptr, 1, &barrier);

    VkBufferImageCopy region = {};
    region.bufferOffset = 0;
    region.bufferRowLength = 0;
    region.bufferImageHeight = 0;
    region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    region.imageSubresource.mipLevel = 0;
    region.imageSubresource.baseArrayLayer = 0;
    region.imageSubresource.layerCount = 1;
    region.imageOffset = {0, 0, 0};
    region.imageExtent = {width, height, 1};

    vkCmdCopyBufferToImage(commandBuffer, buffer, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

    barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

    vkCmdPipelineBarrier(commandBuffer,
                         VK_PIPELINE_STAGE_TRANSFER_BIT,
                         VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
                         0, 0, nullptr, 0, nullptr, 1, &barrier);

    VK_CHECK(vkEndCommandBuffer(commandBuffer));

    VkFence fence;
    VkFenceCreateInfo fenceInfo = {};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = 0;
    VK_CHECK(vkCreateFence(device, &fenceInfo, nullptr, &fence));

    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;

    VK_CHECK(vkQueueSubmit(graphicsQueue, 1, &submitInfo, fence));
    VK_CHECK(vkWaitForFences(device, 1, &fence, VK_TRUE, 5000000000ULL));

    vkDestroyFence(device, fence, nullptr);
    vkFreeCommandBuffers(device, commandPool, 1, &commandBuffer);
}

// ============================================================
// 主类
// ============================================================
class VulkanMRT {
public:
    void run() {
        try {
            initWindow();
            initVulkan();
            createCommandPool();

            loadTextureInfo();
            createMRTImages();
            createDepthImage();
            uploadTextureToMRT();

            createRenderPasses();
            createFramebuffers();
            createVertexBuffer();

            // 创建描述符
            createDescriptorPool();
            createDescriptorSetLayouts();      // 创建两个不同的布局
            createDescriptorSets();            // 创建描述符集

            createGraphicsPipelines();
            createCommandBuffers();
            createSyncObjects();
            recordCommandBuffers();
            mainLoop();
            cleanup();
        } catch (const std::exception& e) {
            std::cerr << "Exception: " << e.what() << std::endl;
            cleanup();
            throw;
        }
    }

private:
    GLFWwindow* window;

    // Vulkan 核心
    VkInstance instance = VK_NULL_HANDLE;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device = VK_NULL_HANDLE;
    VkQueue graphicsQueue = VK_NULL_HANDLE;
    VkQueue presentQueue = VK_NULL_HANDLE;
    VkSurfaceKHR surface = VK_NULL_HANDLE;
    VkSwapchainKHR swapchain = VK_NULL_HANDLE;
    VkFormat swapchainImageFormat;
    VkExtent2D swapchainExtent;

    // 管线
    VkRenderPass mrtRenderPass = VK_NULL_HANDLE;
    VkRenderPass finalRenderPass = VK_NULL_HANDLE;
    VkPipelineLayout mrtPipelineLayout = VK_NULL_HANDLE;
    VkPipeline mrtPipeline = VK_NULL_HANDLE;
    VkPipelineLayout finalPipelineLayout = VK_NULL_HANDLE;
    VkPipeline finalPipeline = VK_NULL_HANDLE;

    // 命令
    VkCommandPool commandPool = VK_NULL_HANDLE;
    VkCommandBuffer mrtCommandBuffer = VK_NULL_HANDLE;
    VkCommandBuffer finalCommandBuffer = VK_NULL_HANDLE;

    // MRT 纹理
    VkImage mrtImages[MRT_COUNT] = {VK_NULL_HANDLE};
    VkImageView mrtImageViews[MRT_COUNT] = {VK_NULL_HANDLE};
    VkDeviceMemory mrtMemories[MRT_COUNT] = {VK_NULL_HANDLE};

    // 纹理数据
    int texWidth = 0, texHeight = 0, texChannels = 0;
    stbi_uc* pixels = nullptr;

    // 深度
    VkImage depthImage = VK_NULL_HANDLE;
    VkImageView depthImageView = VK_NULL_HANDLE;
    VkDeviceMemory depthMemory = VK_NULL_HANDLE;

    // 顶点缓冲
    VkBuffer vertexBuffer = VK_NULL_HANDLE;
    VkDeviceMemory vertexBufferMemory = VK_NULL_HANDLE;

    // Framebuffers
    VkFramebuffer mrtFramebuffer = VK_NULL_HANDLE;
    std::vector<VkFramebuffer> swapchainFramebuffers;

    // 交换链
    std::vector<VkImage> swapchainImages;
    std::vector<VkImageView> swapchainImageViews;

    // 描述符 - MRT Pass 使用 binding 0
    VkDescriptorPool descriptorPool = VK_NULL_HANDLE;
    VkDescriptorSetLayout mrtDescriptorSetLayout = VK_NULL_HANDLE;   // 只含 binding 0
    VkDescriptorSetLayout finalDescriptorSetLayout = VK_NULL_HANDLE; // 含 binding 0,1,2
    VkDescriptorSet mrtDescriptorSet = VK_NULL_HANDLE;              // MRT 的描述符集
    VkDescriptorSet finalDescriptorSet = VK_NULL_HANDLE;            // Final 的描述符集
    VkSampler sampler = VK_NULL_HANDLE;
    VkSampler sampler2 = VK_NULL_HANDLE;
    VkSampler sampler3 = VK_NULL_HANDLE;

    // 同步
    VkSemaphore imageAvailableSemaphore = VK_NULL_HANDLE;
    VkSemaphore renderFinishedSemaphore = VK_NULL_HANDLE;
    VkFence inFlightFence = VK_NULL_HANDLE;

    uint32_t imageIndex = 0;

    // ============================================================
    // 初始化
    // ============================================================
    void initWindow() {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan MRT 3 Targets", nullptr, nullptr);
        if (!window) {
            throw std::runtime_error("failed to create window!");
        }
    }

    void initVulkan() {
        createInstance();
        createSurface();
        pickPhysicalDevice();
        createLogicalDevice();
        createSwapchain();
        createSwapchainImageViews();
    }

    void createInstance() {
        VkApplicationInfo appInfo = {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "MRT Demo";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        VkInstanceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;
        createInfo.enabledLayerCount = 0;

        VK_CHECK(vkCreateInstance(&createInfo, nullptr, &instance));
    }

    void createSurface() {
        VK_CHECK(glfwCreateWindowSurface(instance, window, nullptr, &surface));
    }

    void pickPhysicalDevice() {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
        if (deviceCount == 0) {
            throw std::runtime_error("failed to find GPUs with Vulkan support!");
        }
        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
        for (const auto& device : devices) {
            if (isDeviceSuitable(device)) {
                physicalDevice = device;
                break;
            }
        }
        if (physicalDevice == VK_NULL_HANDLE) {
            throw std::runtime_error("failed to find a suitable GPU!");
        }

        VkPhysicalDeviceProperties props;
        vkGetPhysicalDeviceProperties(physicalDevice, &props);
        std::cout << "GPU: " << props.deviceName << std::endl;
    }

    bool isDeviceSuitable(VkPhysicalDevice device) {
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        bool foundGraphics = false;
        bool foundPresent = false;
        for (uint32_t i = 0; i < queueFamilyCount; i++) {
            if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                foundGraphics = true;
            }
            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
            if (presentSupport) {
                foundPresent = true;
            }
            if (foundGraphics && foundPresent) break;
        }

        if (!foundGraphics || !foundPresent) return false;

        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

        bool swapchainSupported = false;
        for (const auto& ext : availableExtensions) {
            if (strcmp(ext.extensionName, VK_KHR_SWAPCHAIN_EXTENSION_NAME) == 0) {
                swapchainSupported = true;
                break;
            }
        }

        return swapchainSupported;
    }

    void createLogicalDevice() {
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

        int graphicsFamily = -1;
        int presentFamily = -1;
        for (uint32_t i = 0; i < queueFamilyCount; i++) {
            if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                graphicsFamily = i;
            }
            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surface, &presentSupport);
            if (presentSupport) {
                presentFamily = i;
            }
            if (graphicsFamily != -1 && presentFamily != -1) break;
        }

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::vector<int> uniqueFamilies = {graphicsFamily, presentFamily};
        std::sort(uniqueFamilies.begin(), uniqueFamilies.end());
        uniqueFamilies.erase(std::unique(uniqueFamilies.begin(), uniqueFamilies.end()), uniqueFamilies.end());

        float queuePriority = 1.0f;
        for (int family : uniqueFamilies) {
            VkDeviceQueueCreateInfo queueCreateInfo = {};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = family;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        const char* deviceExtensions[] = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
        VkDeviceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.queueCreateInfoCount = queueCreateInfos.size();
        createInfo.pQueueCreateInfos = queueCreateInfos.data();
        createInfo.enabledExtensionCount = 1;
        createInfo.ppEnabledExtensionNames = deviceExtensions;

        VK_CHECK(vkCreateDevice(physicalDevice, &createInfo, nullptr, &device));

        vkGetDeviceQueue(device, graphicsFamily, 0, &graphicsQueue);
        vkGetDeviceQueue(device, presentFamily, 0, &presentQueue);
    }

    void createSwapchain() {
        VkSurfaceCapabilitiesKHR capabilities;
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &capabilities);

        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, nullptr);
        std::vector<VkSurfaceFormatKHR> formats(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, formats.data());
        swapchainImageFormat = formats[0].format;

        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, nullptr);
        std::vector<VkPresentModeKHR> presentModes(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, presentModes.data());

        swapchainExtent = capabilities.currentExtent;
        if (swapchainExtent.width < 100) {
            swapchainExtent = {WIDTH, HEIGHT};
        }

        VkSwapchainCreateInfoKHR createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        createInfo.surface = surface;
        createInfo.minImageCount = 2;
        createInfo.imageFormat = swapchainImageFormat;
        createInfo.imageColorSpace = formats[0].colorSpace;
        createInfo.imageExtent = swapchainExtent;
        createInfo.imageArrayLayers = 1;
        createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
        createInfo.preTransform = capabilities.currentTransform;
        createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        createInfo.presentMode = VK_PRESENT_MODE_FIFO_KHR;
        createInfo.clipped = VK_TRUE;
        createInfo.oldSwapchain = VK_NULL_HANDLE;

        VK_CHECK(vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapchain));

        uint32_t imageCount;
        vkGetSwapchainImagesKHR(device, swapchain, &imageCount, nullptr);
        swapchainImages.resize(imageCount);
        vkGetSwapchainImagesKHR(device, swapchain, &imageCount, swapchainImages.data());
    }

    void createSwapchainImageViews() {
        swapchainImageViews.resize(swapchainImages.size());
        for (size_t i = 0; i < swapchainImages.size(); i++) {
            VkImageViewCreateInfo createInfo = {};
            createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            createInfo.image = swapchainImages[i];
            createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
            createInfo.format = swapchainImageFormat;
            createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            createInfo.subresourceRange.baseMipLevel = 0;
            createInfo.subresourceRange.levelCount = 1;
            createInfo.subresourceRange.baseArrayLayer = 0;
            createInfo.subresourceRange.layerCount = 1;
            VK_CHECK(vkCreateImageView(device, &createInfo, nullptr, &swapchainImageViews[i]));
        }
    }

    void createCommandPool() {
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

        int graphicsFamily = -1;
        for (uint32_t i = 0; i < queueFamilyCount; i++) {
            if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                graphicsFamily = i;
                break;
            }
        }

        VkCommandPoolCreateInfo poolInfo = {};
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
        poolInfo.queueFamilyIndex = graphicsFamily;
        VK_CHECK(vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool));
    }

    void loadTextureInfo() {
        pixels = stbi_load("textures/asuka.jpg", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
        if (!pixels) {
            std::cerr << "Failed to load texture, using default" << std::endl;
            texWidth = 512;
            texHeight = 512;
            pixels = new stbi_uc[512 * 512 * 4];
            for (int i = 0; i < 512 * 512 * 4; i += 4) {
                pixels[i] = 255;
                pixels[i+1] = 128;
                pixels[i+2] = 64;
                pixels[i+3] = 255;
            }
            return;
        }

        std::cout << "Loaded texture: " << texWidth << "x" << texHeight << std::endl;

        const int MAX_SIZE = 512;
        if (texWidth > MAX_SIZE || texHeight > MAX_SIZE) {
            float scale = std::min((float)MAX_SIZE / texWidth, (float)MAX_SIZE / texHeight);
            int newWidth = (int)(texWidth * scale);
            int newHeight = (int)(texHeight * scale);
            newWidth = std::max(1, newWidth);
            newHeight = std::max(1, newHeight);

            std::cout << "Resizing to " << newWidth << "x" << newHeight << std::endl;

            stbi_uc* resized = new stbi_uc[newWidth * newHeight * 4];
            stbir_resize(pixels, texWidth, texHeight, 0,
                        resized, newWidth, newHeight, 0,
                        STBIR_RGBA, STBIR_TYPE_UINT8_SRGB,
                        STBIR_EDGE_CLAMP, STBIR_FILTER_DEFAULT);

            stbi_image_free(pixels);
            pixels = resized;
            texWidth = newWidth;
            texHeight = newHeight;
        }
    }

    void uploadTextureToMRT() {
        if (!pixels) return;

        VkDeviceSize imageSize = texWidth * texHeight * 4;
        std::cout << "Uploading texture: " << imageSize / 1024 << " KB" << std::endl;

        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;
        createBuffer(device, physicalDevice, imageSize,
                     VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                     VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                     stagingBuffer, stagingBufferMemory);

        void* data;
        VK_CHECK(vkMapMemory(device, stagingBufferMemory, 0, imageSize, 0, &data));
        memcpy(data, pixels, (size_t)imageSize);
        vkUnmapMemory(device, stagingBufferMemory);

        stbi_image_free(pixels);
        pixels = nullptr;

        for (int i = 0; i < MRT_COUNT; i++) {
            copyBufferToImage(device, commandPool, graphicsQueue, stagingBuffer,
                             mrtImages[i], texWidth, texHeight);
        }
        std::cout << "All textures uploaded!" << std::endl;

        vkDestroyBuffer(device, stagingBuffer, nullptr);
        vkFreeMemory(device, stagingBufferMemory, nullptr);
    }

    void createMRTImages() {
        if (texWidth == 0 || texHeight == 0) {
            texWidth = 512;
            texHeight = 512;
        }

        for (int i = 0; i < MRT_COUNT; i++) {
            VkImageCreateInfo imageInfo = {};
            imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
            imageInfo.imageType = VK_IMAGE_TYPE_2D;
            imageInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
            imageInfo.extent = {static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight), 1};
            imageInfo.mipLevels = 1;
            imageInfo.arrayLayers = 1;
            imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
            imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
            imageInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
            imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
            imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

            VK_CHECK(vkCreateImage(device, &imageInfo, nullptr, &mrtImages[i]));

            VkMemoryRequirements memReqs;
            vkGetImageMemoryRequirements(device, mrtImages[i], &memReqs);

            VkMemoryAllocateInfo allocInfo = {};
            allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
            allocInfo.allocationSize = memReqs.size;
            allocInfo.memoryTypeIndex = findMemoryType(physicalDevice, memReqs.memoryTypeBits,
                                                       VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

            VK_CHECK(vkAllocateMemory(device, &allocInfo, nullptr, &mrtMemories[i]));
            VK_CHECK(vkBindImageMemory(device, mrtImages[i], mrtMemories[i], 0));

            VkImageViewCreateInfo viewInfo = {};
            viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            viewInfo.image = mrtImages[i];
            viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
            viewInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
            viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            viewInfo.subresourceRange.baseMipLevel = 0;
            viewInfo.subresourceRange.levelCount = 1;
            viewInfo.subresourceRange.baseArrayLayer = 0;
            viewInfo.subresourceRange.layerCount = 1;

            VK_CHECK(vkCreateImageView(device, &viewInfo, nullptr, &mrtImageViews[i]));

            std::cout << "Created MRT[" << i << "] ImageView: " << mrtImageViews[i] << std::endl;
        }
    }

    void createDepthImage() {
        VkImageCreateInfo imageInfo = {};
        imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        imageInfo.imageType = VK_IMAGE_TYPE_2D;
        imageInfo.format = VK_FORMAT_D32_SFLOAT;
        imageInfo.extent = {static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight), 1};
        imageInfo.mipLevels = 1;
        imageInfo.arrayLayers = 1;
        imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
        imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
        imageInfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
        imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

        VK_CHECK(vkCreateImage(device, &imageInfo, nullptr, &depthImage));

        VkMemoryRequirements memReqs;
        vkGetImageMemoryRequirements(device, depthImage, &memReqs);

        VkMemoryAllocateInfo allocInfo = {};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memReqs.size;
        allocInfo.memoryTypeIndex = findMemoryType(physicalDevice, memReqs.memoryTypeBits,
                                                   VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

        VK_CHECK(vkAllocateMemory(device, &allocInfo, nullptr, &depthMemory));
        VK_CHECK(vkBindImageMemory(device, depthImage, depthMemory, 0));

        VkImageViewCreateInfo viewInfo = {};
        viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        viewInfo.image = depthImage;
        viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        viewInfo.format = VK_FORMAT_D32_SFLOAT;
        viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
        viewInfo.subresourceRange.baseMipLevel = 0;
        viewInfo.subresourceRange.levelCount = 1;
        viewInfo.subresourceRange.baseArrayLayer = 0;
        viewInfo.subresourceRange.layerCount = 1;

        VK_CHECK(vkCreateImageView(device, &viewInfo, nullptr, &depthImageView));
    }

    void createVertexBuffer() {
        VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;
        createBuffer(device, physicalDevice, bufferSize,
                     VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                     VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                     stagingBuffer, stagingBufferMemory);

        void* data;
        vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, vertices.data(), (size_t)bufferSize);
        vkUnmapMemory(device, stagingBufferMemory);

        createBuffer(device, physicalDevice, bufferSize,
                     VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                     VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                     vertexBuffer, vertexBufferMemory);

        VkCommandBufferAllocateInfo allocInfo = {};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = commandPool;
        allocInfo.commandBufferCount = 1;

        VkCommandBuffer commandBuffer;
        vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer);

        VkCommandBufferBeginInfo beginInfo = {};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

        vkBeginCommandBuffer(commandBuffer, &beginInfo);

        VkBufferCopy copyRegion = {};
        copyRegion.size = bufferSize;
        vkCmdCopyBuffer(commandBuffer, stagingBuffer, vertexBuffer, 1, &copyRegion);

        vkEndCommandBuffer(commandBuffer);

        VkSubmitInfo submitInfo = {};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffer;

        vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
        vkQueueWaitIdle(graphicsQueue);

        vkFreeCommandBuffers(device, commandPool, 1, &commandBuffer);
        vkDestroyBuffer(device, stagingBuffer, nullptr);
        vkFreeMemory(device, stagingBufferMemory, nullptr);
    }

    void createRenderPasses() {
        // ===== MRT RenderPass =====
        std::vector<VkAttachmentDescription> colorAttachments(MRT_COUNT);
        for (int i = 0; i < MRT_COUNT; i++) {
            colorAttachments[i].format = VK_FORMAT_R8G8B8A8_UNORM;
            colorAttachments[i].samples = VK_SAMPLE_COUNT_1_BIT;
            colorAttachments[i].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
            colorAttachments[i].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
            colorAttachments[i].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
            colorAttachments[i].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
            colorAttachments[i].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
            colorAttachments[i].finalLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        }

        VkAttachmentDescription depthAttachment = {};
        depthAttachment.format = VK_FORMAT_D32_SFLOAT;
        depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
        depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

        std::vector<VkAttachmentReference> colorRefs(MRT_COUNT);
        for (int i = 0; i < MRT_COUNT; i++) {
            colorRefs[i].attachment = i;
            colorRefs[i].layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
        }

        VkAttachmentReference depthRef = {};
        depthRef.attachment = MRT_COUNT;
        depthRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

        VkSubpassDescription subpass = {};
        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpass.colorAttachmentCount = MRT_COUNT;
        subpass.pColorAttachments = colorRefs.data();
        subpass.pDepthStencilAttachment = &depthRef;

        std::vector<VkAttachmentDescription> attachments = colorAttachments;
        attachments.push_back(depthAttachment);

        VkRenderPassCreateInfo renderPassInfo = {};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        renderPassInfo.attachmentCount = attachments.size();
        renderPassInfo.pAttachments = attachments.data();
        renderPassInfo.subpassCount = 1;
        renderPassInfo.pSubpasses = &subpass;

        VK_CHECK(vkCreateRenderPass(device, &renderPassInfo, nullptr, &mrtRenderPass));

        // ===== Final RenderPass =====
        VkAttachmentDescription finalColorAttachment = {};
        finalColorAttachment.format = swapchainImageFormat;
        finalColorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
        finalColorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        finalColorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        finalColorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        finalColorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        finalColorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        finalColorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        VkAttachmentReference finalColorRef = {};
        finalColorRef.attachment = 0;
        finalColorRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        VkSubpassDescription finalSubpass = {};
        finalSubpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        finalSubpass.colorAttachmentCount = 1;
        finalSubpass.pColorAttachments = &finalColorRef;

        VkRenderPassCreateInfo finalRenderPassInfo = {};
        finalRenderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        finalRenderPassInfo.attachmentCount = 1;
        finalRenderPassInfo.pAttachments = &finalColorAttachment;
        finalRenderPassInfo.subpassCount = 1;
        finalRenderPassInfo.pSubpasses = &finalSubpass;

        VK_CHECK(vkCreateRenderPass(device, &finalRenderPassInfo, nullptr, &finalRenderPass));
    }

    void createFramebuffers() {
        std::vector<VkImageView> attachments;
        for (int i = 0; i < MRT_COUNT; i++) {
            attachments.push_back(mrtImageViews[i]);
        }
        attachments.push_back(depthImageView);

        VkFramebufferCreateInfo framebufferInfo = {};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = mrtRenderPass;
        framebufferInfo.attachmentCount = attachments.size();
        framebufferInfo.pAttachments = attachments.data();
        framebufferInfo.width = texWidth;
        framebufferInfo.height = texHeight;
        framebufferInfo.layers = 1;

        VK_CHECK(vkCreateFramebuffer(device, &framebufferInfo, nullptr, &mrtFramebuffer));

        swapchainFramebuffers.resize(swapchainImageViews.size());
        for (size_t i = 0; i < swapchainImageViews.size(); i++) {
            VkFramebufferCreateInfo info = {};
            info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            info.renderPass = finalRenderPass;
            info.attachmentCount = 1;
            info.pAttachments = &swapchainImageViews[i];
            info.width = swapchainExtent.width;
            info.height = swapchainExtent.height;
            info.layers = 1;

            VK_CHECK(vkCreateFramebuffer(device, &info, nullptr, &swapchainFramebuffers[i]));
        }
    }

    // ============================================================
    // 创建描述符池
    // ============================================================
    void createDescriptorPool() {
        VkDescriptorPoolSize poolSize = {};
        poolSize.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        poolSize.descriptorCount = 4;  // MRT需要1个，Final需要3个，共4个

        VkDescriptorPoolCreateInfo poolInfo = {};
        poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        poolInfo.poolSizeCount = 1;
        poolInfo.pPoolSizes = &poolSize;
        poolInfo.maxSets = 2;  // MRT和Final各一个描述符集

        VK_CHECK(vkCreateDescriptorPool(device, &poolInfo, nullptr, &descriptorPool));
    }

    // ============================================================
    // 创建描述符集布局 - 两个不同的布局
    // ============================================================
    void createDescriptorSetLayouts() {
        // ----- MRT 描述符集布局 (只包含 binding 0) -----
        VkDescriptorSetLayoutBinding mrtBinding = {};
        mrtBinding.binding = 0;
        mrtBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        mrtBinding.descriptorCount = 1;
        mrtBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

        VkDescriptorSetLayoutCreateInfo mrtLayoutInfo = {};
        mrtLayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        mrtLayoutInfo.bindingCount = 1;
        mrtLayoutInfo.pBindings = &mrtBinding;

        VK_CHECK(vkCreateDescriptorSetLayout(device, &mrtLayoutInfo, nullptr, &mrtDescriptorSetLayout));

        // ----- Final 描述符集布局 (包含 binding 0, 1, 2) -----
        std::vector<VkDescriptorSetLayoutBinding> finalBindings(3);
        for (int i = 0; i < 3; i++) {
            finalBindings[i].binding = i;
            finalBindings[i].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
            finalBindings[i].descriptorCount = 1;
            finalBindings[i].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
        }

        VkDescriptorSetLayoutCreateInfo finalLayoutInfo = {};
        finalLayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        finalLayoutInfo.bindingCount = 3;
        finalLayoutInfo.pBindings = finalBindings.data();

        VK_CHECK(vkCreateDescriptorSetLayout(device, &finalLayoutInfo, nullptr, &finalDescriptorSetLayout));

        std::cout << "Created MRT DescriptorSetLayout (1 binding)" << std::endl;
        std::cout << "Created Final DescriptorSetLayout (3 bindings)" << std::endl;
    }

    // ============================================================
    // 创建描述符集
    // ============================================================
    void createDescriptorSets() {
        // 创建采样器
        VkSamplerCreateInfo samplerInfo = {};
        samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
        samplerInfo.magFilter = VK_FILTER_LINEAR;
        samplerInfo.minFilter = VK_FILTER_LINEAR;
        samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
        samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
        samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;

        VK_CHECK(vkCreateSampler(device, &samplerInfo, nullptr, &sampler));
        VK_CHECK(vkCreateSampler(device, &samplerInfo, nullptr, &sampler2));
        VK_CHECK(vkCreateSampler(device, &samplerInfo, nullptr, &sampler3));

        // ============================================================
        // 1. MRT 描述符集 (只绑定 texture 到 binding 0)
        // ============================================================
        VkDescriptorSetAllocateInfo mrtAllocInfo = {};
        mrtAllocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        mrtAllocInfo.descriptorPool = descriptorPool;
        mrtAllocInfo.descriptorSetCount = 1;
        mrtAllocInfo.pSetLayouts = &mrtDescriptorSetLayout;

        VK_CHECK(vkAllocateDescriptorSets(device, &mrtAllocInfo, &mrtDescriptorSet));

        // MRT 使用 mrtImages[0] (纹理数据)
        VkDescriptorImageInfo mrtImageInfo = {};
        mrtImageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        mrtImageInfo.imageView = mrtImageViews[0];  // 使用纹理数据 (不是纯色)
        mrtImageInfo.sampler = sampler;

        VkWriteDescriptorSet mrtWrite = {};
        mrtWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        mrtWrite.dstSet = mrtDescriptorSet;
        mrtWrite.dstBinding = 0;
        mrtWrite.dstArrayElement = 0;
        mrtWrite.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        mrtWrite.descriptorCount = 1;
        mrtWrite.pImageInfo = &mrtImageInfo;

        vkUpdateDescriptorSets(device, 1, &mrtWrite, 0, nullptr);

        // ============================================================
        // 2. Final 描述符集 (绑定 3 个 MRT 纹理)
        // ============================================================
        VkDescriptorSetAllocateInfo finalAllocInfo = {};
        finalAllocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        finalAllocInfo.descriptorPool = descriptorPool;
        finalAllocInfo.descriptorSetCount = 1;
        finalAllocInfo.pSetLayouts = &finalDescriptorSetLayout;

        VK_CHECK(vkAllocateDescriptorSets(device, &finalAllocInfo, &finalDescriptorSet));

        // 创建三个独立的 VkDescriptorImageInfo
        VkDescriptorImageInfo finalImageInfo0 = {};
        finalImageInfo0.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        finalImageInfo0.imageView = mrtImageViews[0];  // MRT[0] - 红色
        finalImageInfo0.sampler = sampler;

        VkDescriptorImageInfo finalImageInfo1 = {};
        finalImageInfo1.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        finalImageInfo1.imageView = mrtImageViews[1];  // MRT[1] - 绿色
        finalImageInfo1.sampler = sampler2;

        VkDescriptorImageInfo finalImageInfo2 = {};
        finalImageInfo2.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        finalImageInfo2.imageView = mrtImageViews[2];  // MRT[2] - 蓝色
        finalImageInfo2.sampler = sampler3;

        // 创建三个写操作
        VkWriteDescriptorSet finalWrite0 = {};
        finalWrite0.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        finalWrite0.dstSet = finalDescriptorSet;
        finalWrite0.dstBinding = 0;
        finalWrite0.dstArrayElement = 0;
        finalWrite0.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        finalWrite0.descriptorCount = 1;
        finalWrite0.pImageInfo = &finalImageInfo0;

        VkWriteDescriptorSet finalWrite1 = {};
        finalWrite1.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        finalWrite1.dstSet = finalDescriptorSet;
        finalWrite1.dstBinding = 1;
        finalWrite1.dstArrayElement = 0;
        finalWrite1.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        finalWrite1.descriptorCount = 1;
        finalWrite1.pImageInfo = &finalImageInfo1;

        VkWriteDescriptorSet finalWrite2 = {};
        finalWrite2.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        finalWrite2.dstSet = finalDescriptorSet;
        finalWrite2.dstBinding = 2;
        finalWrite2.dstArrayElement = 0;
        finalWrite2.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        finalWrite2.descriptorCount = 1;
        finalWrite2.pImageInfo = &finalImageInfo2;

        std::vector<VkWriteDescriptorSet> finalWrites = {finalWrite0, finalWrite1, finalWrite2};

        vkUpdateDescriptorSets(device, finalWrites.size(), finalWrites.data(), 0, nullptr);

        std::cout << "=== Descriptor Sets Created ===" << std::endl;
        std::cout << "MRT DescriptorSet: binding 0 -> MRT[0] (texture data)" << std::endl;
        std::cout << "Final DescriptorSet:" << std::endl;
        std::cout << "  binding 0 -> MRT[0]" << std::endl;
        std::cout << "  binding 1 -> MRT[1]" << std::endl;
        std::cout << "  binding 2 -> MRT[2]" << std::endl;
    }

    VkShaderModule createShaderModule(const std::vector<char>& code) {
        VkShaderModuleCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = code.size();
        createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());
        VkShaderModule shaderModule;
        VK_CHECK(vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule));
        return shaderModule;
    }

    // ============================================================
    // 创建图形管线
    // ============================================================
    void createGraphicsPipelines() {
        // ============================================================
        // MRT Pipeline
        // ============================================================
        auto mrtVertCode = readFile("RT_Texture2D_vert.spv");
        auto mrtFragCode = readFile("RT_Texture2D_frag.spv");

        VkShaderModule mrtVertModule = createShaderModule(mrtVertCode);
        VkShaderModule mrtFragModule = createShaderModule(mrtFragCode);

        VkPipelineShaderStageCreateInfo mrtVertStage = {};
        mrtVertStage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        mrtVertStage.stage = VK_SHADER_STAGE_VERTEX_BIT;
        mrtVertStage.module = mrtVertModule;
        mrtVertStage.pName = "main";

        VkPipelineShaderStageCreateInfo mrtFragStage = {};
        mrtFragStage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        mrtFragStage.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        mrtFragStage.module = mrtFragModule;
        mrtFragStage.pName = "main";

        VkPipelineShaderStageCreateInfo mrtStages[] = {mrtVertStage, mrtFragStage};

        VkVertexInputBindingDescription bindingDescription = {};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        std::vector<VkVertexInputAttributeDescription> attributeDescriptions(2);
        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, pos);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, texCoord);

        VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
        vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        vertexInputInfo.vertexBindingDescriptionCount = 1;
        vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
        vertexInputInfo.vertexAttributeDescriptionCount = attributeDescriptions.size();
        vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

        VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
        inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        inputAssembly.primitiveRestartEnable = VK_FALSE;

        VkPipelineViewportStateCreateInfo viewportState = {};
        viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewportState.viewportCount = 1;
        viewportState.scissorCount = 1;

        VkPipelineRasterizationStateCreateInfo rasterizer = {};
        rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        rasterizer.depthClampEnable = VK_FALSE;
        rasterizer.rasterizerDiscardEnable = VK_FALSE;
        rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
        rasterizer.lineWidth = 1.0f;
        rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
        rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;

        VkPipelineMultisampleStateCreateInfo multisampling = {};
        multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        multisampling.sampleShadingEnable = VK_FALSE;
        multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

        VkPipelineDepthStencilStateCreateInfo depthStencil = {};
        depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
        depthStencil.depthTestEnable = VK_TRUE;
        depthStencil.depthWriteEnable = VK_TRUE;
        depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
        depthStencil.depthBoundsTestEnable = VK_FALSE;
        depthStencil.stencilTestEnable = VK_FALSE;

        std::vector<VkPipelineColorBlendAttachmentState> colorBlendAttachments(MRT_COUNT);
        for (int i = 0; i < MRT_COUNT; i++) {
            colorBlendAttachments[i].colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
                                                      VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
            colorBlendAttachments[i].blendEnable = VK_FALSE;
        }

        VkPipelineColorBlendStateCreateInfo colorBlending = {};
        colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        colorBlending.logicOpEnable = VK_FALSE;
        colorBlending.attachmentCount = MRT_COUNT;
        colorBlending.pAttachments = colorBlendAttachments.data();

        std::vector<VkDynamicState> dynamicStates = {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};
        VkPipelineDynamicStateCreateInfo dynamicState = {};
        dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
        dynamicState.dynamicStateCount = dynamicStates.size();
        dynamicState.pDynamicStates = dynamicStates.data();

        // ✅ MRT Pipeline Layout 使用 mrtDescriptorSetLayout (只含 binding 0)
        VkPipelineLayoutCreateInfo mrtPipelineLayoutInfo = {};
        mrtPipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        mrtPipelineLayoutInfo.setLayoutCount = 1;
        mrtPipelineLayoutInfo.pSetLayouts = &mrtDescriptorSetLayout;

        VK_CHECK(vkCreatePipelineLayout(device, &mrtPipelineLayoutInfo, nullptr, &mrtPipelineLayout));

        VkGraphicsPipelineCreateInfo mrtPipelineInfo = {};
        mrtPipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        mrtPipelineInfo.stageCount = 2;
        mrtPipelineInfo.pStages = mrtStages;
        mrtPipelineInfo.pVertexInputState = &vertexInputInfo;
        mrtPipelineInfo.pInputAssemblyState = &inputAssembly;
        mrtPipelineInfo.pViewportState = &viewportState;
        mrtPipelineInfo.pRasterizationState = &rasterizer;
        mrtPipelineInfo.pMultisampleState = &multisampling;
        mrtPipelineInfo.pDepthStencilState = &depthStencil;
        mrtPipelineInfo.pColorBlendState = &colorBlending;
        mrtPipelineInfo.pDynamicState = &dynamicState;
        mrtPipelineInfo.layout = mrtPipelineLayout;
        mrtPipelineInfo.renderPass = mrtRenderPass;
        mrtPipelineInfo.subpass = 0;

        VK_CHECK(vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &mrtPipelineInfo, nullptr, &mrtPipeline));

        vkDestroyShaderModule(device, mrtVertModule, nullptr);
        vkDestroyShaderModule(device, mrtFragModule, nullptr);

        // ============================================================
        // Final Pipeline
        // ============================================================
        auto finalVertCode = readFile("TextureRenderTarget_vert.spv");
        auto finalFragCode = readFile("TextureRenderTarget_frag.spv");

        VkShaderModule finalVertModule = createShaderModule(finalVertCode);
        VkShaderModule finalFragModule = createShaderModule(finalFragCode);

        VkPipelineShaderStageCreateInfo finalVertStage = {};
        finalVertStage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        finalVertStage.stage = VK_SHADER_STAGE_VERTEX_BIT;
        finalVertStage.module = finalVertModule;
        finalVertStage.pName = "main";

        VkPipelineShaderStageCreateInfo finalFragStage = {};
        finalFragStage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        finalFragStage.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        finalFragStage.module = finalFragModule;
        finalFragStage.pName = "main";

        VkPipelineShaderStageCreateInfo finalStages[] = {finalVertStage, finalFragStage};

        VkPipelineVertexInputStateCreateInfo finalVertexInputInfo = {};
        finalVertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        finalVertexInputInfo.vertexBindingDescriptionCount = 0;
        finalVertexInputInfo.vertexAttributeDescriptionCount = 0;

        VkPipelineColorBlendAttachmentState finalColorBlend = {};
        finalColorBlend.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
                                         VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
        finalColorBlend.blendEnable = VK_FALSE;

        VkPipelineColorBlendStateCreateInfo finalColorBlending = {};
        finalColorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        finalColorBlending.logicOpEnable = VK_FALSE;
        finalColorBlending.attachmentCount = 1;
        finalColorBlending.pAttachments = &finalColorBlend;

        // ✅ Final Pipeline Layout 使用 finalDescriptorSetLayout (含 binding 0,1,2)
        VkPipelineLayoutCreateInfo finalPipelineLayoutInfo = {};
        finalPipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        finalPipelineLayoutInfo.setLayoutCount = 1;
        finalPipelineLayoutInfo.pSetLayouts = &finalDescriptorSetLayout;

        VK_CHECK(vkCreatePipelineLayout(device, &finalPipelineLayoutInfo, nullptr, &finalPipelineLayout));

        VkGraphicsPipelineCreateInfo finalPipelineInfo = {};
        finalPipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        finalPipelineInfo.stageCount = 2;
        finalPipelineInfo.pStages = finalStages;
        finalPipelineInfo.pVertexInputState = &finalVertexInputInfo;
        finalPipelineInfo.pInputAssemblyState = &inputAssembly;
        finalPipelineInfo.pViewportState = &viewportState;
        finalPipelineInfo.pRasterizationState = &rasterizer;
        finalPipelineInfo.pMultisampleState = &multisampling;
        finalPipelineInfo.pDepthStencilState = &depthStencil;
        finalPipelineInfo.pColorBlendState = &finalColorBlending;
        finalPipelineInfo.pDynamicState = &dynamicState;
        finalPipelineInfo.layout = finalPipelineLayout;
        finalPipelineInfo.renderPass = finalRenderPass;
        finalPipelineInfo.subpass = 0;

        VK_CHECK(vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &finalPipelineInfo, nullptr, &finalPipeline));

        vkDestroyShaderModule(device, finalVertModule, nullptr);
        vkDestroyShaderModule(device, finalFragModule, nullptr);
    }

    void createCommandBuffers() {
        VkCommandBufferAllocateInfo allocInfo = {};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = commandPool;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandBufferCount = 1;

        VK_CHECK(vkAllocateCommandBuffers(device, &allocInfo, &mrtCommandBuffer));
        VK_CHECK(vkAllocateCommandBuffers(device, &allocInfo, &finalCommandBuffer));
    }

    void createSyncObjects() {
        VkSemaphoreCreateInfo semaphoreInfo = {};
        semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        VkFenceCreateInfo fenceInfo = {};
        fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

        VK_CHECK(vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphore));
        VK_CHECK(vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinishedSemaphore));
        VK_CHECK(vkCreateFence(device, &fenceInfo, nullptr, &inFlightFence));
    }

    // ============================================================
    // 录制命令缓冲区
    // ============================================================
    void recordCommandBuffers() {
        // ===== 1. MRT Command Buffer =====
        VkCommandBufferBeginInfo beginInfo = {};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

        VK_CHECK(vkBeginCommandBuffer(mrtCommandBuffer, &beginInfo));

        VkRenderPassBeginInfo renderPassInfo = {};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = mrtRenderPass;
        renderPassInfo.framebuffer = mrtFramebuffer;
        renderPassInfo.renderArea.offset = {0, 0};
        renderPassInfo.renderArea.extent = {static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight)};

        std::vector<VkClearValue> clearValues(MRT_COUNT + 1);
        for (int i = 0; i < MRT_COUNT; i++) {
            clearValues[i].color = {{0.0f, 0.0f, 0.0f, 1.0f}};
        }
        clearValues[MRT_COUNT].depthStencil = {1.0f, 0};
        renderPassInfo.clearValueCount = clearValues.size();
        renderPassInfo.pClearValues = clearValues.data();

        vkCmdBeginRenderPass(mrtCommandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
        vkCmdBindPipeline(mrtCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, mrtPipeline);

        // ✅ MRT Pass 绑定 mrtDescriptorSet (只含 binding 0)
        vkCmdBindDescriptorSets(mrtCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
                                mrtPipelineLayout, 0, 1, &mrtDescriptorSet, 0, nullptr);

        VkViewport viewport = {};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = (float)texWidth;
        viewport.height = (float)texHeight;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;
        vkCmdSetViewport(mrtCommandBuffer, 0, 1, &viewport);

        VkRect2D scissor = {};
        scissor.offset = {0, 0};
        scissor.extent = {static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight)};
        vkCmdSetScissor(mrtCommandBuffer, 0, 1, &scissor);

        VkBuffer vertexBuffers[] = {vertexBuffer};
        VkDeviceSize offsets[] = {0};
        vkCmdBindVertexBuffers(mrtCommandBuffer, 0, 1, vertexBuffers, offsets);

        vkCmdDraw(mrtCommandBuffer, 3, 1, 0, 0);
        vkCmdEndRenderPass(mrtCommandBuffer);

        VK_CHECK(vkEndCommandBuffer(mrtCommandBuffer));

        // ===== 2. Final Command Buffer =====
        VK_CHECK(vkBeginCommandBuffer(finalCommandBuffer, &beginInfo));

        renderPassInfo.renderPass = finalRenderPass;
        renderPassInfo.framebuffer = swapchainFramebuffers[0];
        renderPassInfo.renderArea.extent = swapchainExtent;
        renderPassInfo.clearValueCount = 1;
        VkClearValue clearColor = {{{0.1f, 0.1f, 0.1f, 1.0f}}};
        renderPassInfo.pClearValues = &clearColor;

        vkCmdBeginRenderPass(finalCommandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
        vkCmdBindPipeline(finalCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, finalPipeline);

        // ✅ Final Pass 绑定 finalDescriptorSet (含 binding 0,1,2)
        vkCmdBindDescriptorSets(finalCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
                                finalPipelineLayout, 0, 1, &finalDescriptorSet, 0, nullptr);

        viewport.width = (float)swapchainExtent.width;
        viewport.height = (float)swapchainExtent.height;
        vkCmdSetViewport(finalCommandBuffer, 0, 1, &viewport);

        scissor.extent = swapchainExtent;
        vkCmdSetScissor(finalCommandBuffer, 0, 1, &scissor);

        vkCmdDraw(finalCommandBuffer, 3, 1, 0, 0);
        vkCmdEndRenderPass(finalCommandBuffer);
        VK_CHECK(vkEndCommandBuffer(finalCommandBuffer));
    }

    void drawFrame() {
        vkWaitForFences(device, 1, &inFlightFence, VK_TRUE, UINT64_MAX);
        vkResetFences(device, 1, &inFlightFence);

        VkResult result = vkAcquireNextImageKHR(device, swapchain, UINT64_MAX, imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);
        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR) {
            return;
        }
        VK_CHECK(result);

        VkCommandBufferBeginInfo beginInfo = {};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        vkResetCommandBuffer(finalCommandBuffer, 0);
        VK_CHECK(vkBeginCommandBuffer(finalCommandBuffer, &beginInfo));

        VkRenderPassBeginInfo renderPassInfo = {};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = finalRenderPass;
        renderPassInfo.framebuffer = swapchainFramebuffers[imageIndex];
        renderPassInfo.renderArea.offset = {0, 0};
        renderPassInfo.renderArea.extent = swapchainExtent;
        renderPassInfo.clearValueCount = 1;
        VkClearValue clearColor = {{{0.1f, 0.1f, 0.1f, 1.0f}}};
        renderPassInfo.pClearValues = &clearColor;

        vkCmdBeginRenderPass(finalCommandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
        vkCmdBindPipeline(finalCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, finalPipeline);
        vkCmdBindDescriptorSets(finalCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
                                finalPipelineLayout, 0, 1, &finalDescriptorSet, 0, nullptr);

        VkViewport viewport = {};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = (float)swapchainExtent.width;
        viewport.height = (float)swapchainExtent.height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;
        vkCmdSetViewport(finalCommandBuffer, 0, 1, &viewport);

        VkRect2D scissor = {};
        scissor.offset = {0, 0};
        scissor.extent = swapchainExtent;
        vkCmdSetScissor(finalCommandBuffer, 0, 1, &scissor);

        vkCmdDraw(finalCommandBuffer, 3, 1, 0, 0);
        vkCmdEndRenderPass(finalCommandBuffer);
        VK_CHECK(vkEndCommandBuffer(finalCommandBuffer));

        // 提交 MRT Pass
        VkSubmitInfo mrtSubmitInfo = {};
        mrtSubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        mrtSubmitInfo.commandBufferCount = 1;
        mrtSubmitInfo.pCommandBuffers = &mrtCommandBuffer;
        VK_CHECK(vkQueueSubmit(graphicsQueue, 1, &mrtSubmitInfo, VK_NULL_HANDLE));

        // 等待 MRT 完成
        VkFence mrtFence;
        VkFenceCreateInfo fenceInfo = {};
        fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        VK_CHECK(vkCreateFence(device, &fenceInfo, nullptr, &mrtFence));

        VkSubmitInfo fenceSubmitInfo = {};
        fenceSubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        fenceSubmitInfo.commandBufferCount = 0;
        VK_CHECK(vkQueueSubmit(graphicsQueue, 1, &fenceSubmitInfo, mrtFence));
        VK_CHECK(vkWaitForFences(device, 1, &mrtFence, VK_TRUE, UINT64_MAX));
        vkDestroyFence(device, mrtFence, nullptr);

        // 提交 Final Pass
        VkSubmitInfo finalSubmitInfo = {};
        finalSubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        finalSubmitInfo.waitSemaphoreCount = 1;
        finalSubmitInfo.pWaitSemaphores = &imageAvailableSemaphore;
        VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
        finalSubmitInfo.pWaitDstStageMask = waitStages;
        finalSubmitInfo.commandBufferCount = 1;
        finalSubmitInfo.pCommandBuffers = &finalCommandBuffer;
        finalSubmitInfo.signalSemaphoreCount = 1;
        finalSubmitInfo.pSignalSemaphores = &renderFinishedSemaphore;

        VK_CHECK(vkQueueSubmit(graphicsQueue, 1, &finalSubmitInfo, inFlightFence));

        VkPresentInfoKHR presentInfo = {};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = &renderFinishedSemaphore;
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = &swapchain;
        presentInfo.pImageIndices = &imageIndex;

        result = vkQueuePresentKHR(presentQueue, &presentInfo);
        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR) {
            return;
        }
        VK_CHECK(result);
    }

    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
            drawFrame();
        }
        vkDeviceWaitIdle(device);
    }

    void cleanup() {
        if (device != VK_NULL_HANDLE) {
            vkDeviceWaitIdle(device);
        }

        if (renderFinishedSemaphore != VK_NULL_HANDLE) vkDestroySemaphore(device, renderFinishedSemaphore, nullptr);
        if (imageAvailableSemaphore != VK_NULL_HANDLE) vkDestroySemaphore(device, imageAvailableSemaphore, nullptr);
        if (inFlightFence != VK_NULL_HANDLE) vkDestroyFence(device, inFlightFence, nullptr);

        if (commandPool != VK_NULL_HANDLE) vkDestroyCommandPool(device, commandPool, nullptr);

        if (mrtPipeline != VK_NULL_HANDLE) vkDestroyPipeline(device, mrtPipeline, nullptr);
        if (finalPipeline != VK_NULL_HANDLE) vkDestroyPipeline(device, finalPipeline, nullptr);
        if (mrtPipelineLayout != VK_NULL_HANDLE) vkDestroyPipelineLayout(device, mrtPipelineLayout, nullptr);
        if (finalPipelineLayout != VK_NULL_HANDLE) vkDestroyPipelineLayout(device, finalPipelineLayout, nullptr);

        if (mrtRenderPass != VK_NULL_HANDLE) vkDestroyRenderPass(device, mrtRenderPass, nullptr);
        if (finalRenderPass != VK_NULL_HANDLE) vkDestroyRenderPass(device, finalRenderPass, nullptr);

        if (sampler != VK_NULL_HANDLE) vkDestroySampler(device, sampler, nullptr);
        if (mrtDescriptorSetLayout != VK_NULL_HANDLE) vkDestroyDescriptorSetLayout(device, mrtDescriptorSetLayout, nullptr);
        if (finalDescriptorSetLayout != VK_NULL_HANDLE) vkDestroyDescriptorSetLayout(device, finalDescriptorSetLayout, nullptr);
        if (descriptorPool != VK_NULL_HANDLE) vkDestroyDescriptorPool(device, descriptorPool, nullptr);

        if (vertexBuffer != VK_NULL_HANDLE) vkDestroyBuffer(device, vertexBuffer, nullptr);
        if (vertexBufferMemory != VK_NULL_HANDLE) vkFreeMemory(device, vertexBufferMemory, nullptr);

        if (mrtFramebuffer != VK_NULL_HANDLE) vkDestroyFramebuffer(device, mrtFramebuffer, nullptr);
        for (auto fb : swapchainFramebuffers) {
            if (fb != VK_NULL_HANDLE) vkDestroyFramebuffer(device, fb, nullptr);
        }

        for (auto iv : swapchainImageViews) {
            if (iv != VK_NULL_HANDLE) vkDestroyImageView(device, iv, nullptr);
        }
        if (swapchain != VK_NULL_HANDLE) vkDestroySwapchainKHR(device, swapchain, nullptr);

        for (int i = 0; i < MRT_COUNT; i++) {
            if (mrtImageViews[i] != VK_NULL_HANDLE) vkDestroyImageView(device, mrtImageViews[i], nullptr);
            if (mrtImages[i] != VK_NULL_HANDLE) vkDestroyImage(device, mrtImages[i], nullptr);
            if (mrtMemories[i] != VK_NULL_HANDLE) vkFreeMemory(device, mrtMemories[i], nullptr);
        }

        if (depthImageView != VK_NULL_HANDLE) vkDestroyImageView(device, depthImageView, nullptr);
        if (depthImage != VK_NULL_HANDLE) vkDestroyImage(device, depthImage, nullptr);
        if (depthMemory != VK_NULL_HANDLE) vkFreeMemory(device, depthMemory, nullptr);

        if (device != VK_NULL_HANDLE) vkDestroyDevice(device, nullptr);
        if (surface != VK_NULL_HANDLE) vkDestroySurfaceKHR(instance, surface, nullptr);
        if (instance != VK_NULL_HANDLE) vkDestroyInstance(instance, nullptr);

        if (window) {
            glfwDestroyWindow(window);
            glfwTerminate();
        }
    }
};

int main() {
    try {
        VulkanMRT app;
        app.run();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}