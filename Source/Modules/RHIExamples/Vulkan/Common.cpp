#include "Common.h"
#include <iostream>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <fstream>
#include <sstream>
#include <iostream>

std::vector<char> ReadFile(const std::string& filename)
{
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("failed to open file!");
    }

    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();

    return buffer;
}

std::string ReadFile2(const std::string& filename)
{
    std::string vertexCode;
    std::ifstream vShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(filename);
        std::stringstream vShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    }
    //std::cout << "vertexCode: " << vertexCode << std::endl;


    return vertexCode;
}

GLFWwindow* InitWindow(int width, int height)
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	return glfwCreateWindow(width, height, "Vulkan", nullptr, nullptr);
}

void CleanupWindow(GLFWwindow* Window)
{
	glfwDestroyWindow(Window);

	glfwTerminate();
}

int TestVulkan()
{
    std::cout << "TestVulkan" << std::endl;


    std::vector<const char*> InstanceExtensions =
    {
        "VK_KHR_surface",
        //"VK_KHR_win32_surface",
        "VK_KHR_xcb_surface"
    };

    std::vector<const char*> InstanceLayers =
    {
         "VK_LAYER_KHRONOS_validation"
    };


    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    glfwSetErrorCallback([](int error, const char* desc) {
        std::cerr << "GLFW Error " << error << ": " << desc << std::endl;
        });

    auto Window = glfwCreateWindow(800, 600, "Vulkan", nullptr, nullptr);
    if (!Window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // 3. 获取 GLFW 所需的 Vulkan 扩展
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    // 4. 打印扩展列表（调试用）
    std::cout << "Required extensions:" << std::endl;
    for (uint32_t i = 0; i < glfwExtensionCount; i++) {
        std::cout << "  " << glfwExtensions[i] << std::endl;
    }

    VkApplicationInfo AppInfo{};
    AppInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    AppInfo.pApplicationName = "Hello Triangle";
    AppInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    AppInfo.pEngineName = "No Engine";
    AppInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    AppInfo.apiVersion = VK_API_VERSION_1_0;
    std::cout << "VulkanInstance " << std::endl;
    VkInstanceCreateInfo CreateInfo{};
    CreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    CreateInfo.pApplicationInfo = &AppInfo;
    CreateInfo.enabledExtensionCount        = glfwExtensionCount;
    CreateInfo.ppEnabledExtensionNames      = glfwExtensions;
    CreateInfo.enabledLayerCount            = InstanceLayers.size();
    CreateInfo.ppEnabledLayerNames          = InstanceLayers.data();
    CreateInfo.pNext = nullptr;

    VkInstance Instance;
    VkResult ret = vkCreateInstance(&CreateInfo, nullptr, &Instance);
    if (ret != VK_SUCCESS)
    {
        std::cout << "vkCreateInstance " << ret << std::endl;
    }


    VkSurfaceKHR Handle;
    VkResult Result = glfwCreateWindowSurface(Instance, Window, nullptr, &Handle);
    if (VK_SUCCESS != Result)
    {
        std::cout << "glfwCreateWindowSurface failed " << Result << std::endl;
        throw std::runtime_error("failed to create window surface!");
    }

    glfwDestroyWindow(Window);

    glfwTerminate();

    return 0;
}