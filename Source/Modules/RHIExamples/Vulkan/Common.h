#pragma once
#include <string>
#include <vector>
#include <fstream>
#if   PROJECT_USE_VULKAN
    #define GLFW_INCLUDE_VULKAN
#endif
#if  PROJECT_USE_GLFW
#include <GLFW/glfw3.h>
GLFWwindow* InitWindow(int width, int height);
void CleanupWindow(GLFWwindow* Window);
#endif
std::vector<char> ReadFile(const std::string& filename);
std::string ReadFile2(const std::string& filename);

int TestVulkan();