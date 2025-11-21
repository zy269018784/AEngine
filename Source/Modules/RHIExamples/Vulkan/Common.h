#pragma once
#include <string>
#include <vector>
#include <fstream>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

std::vector<char> ReadFile(const std::string& filename);
std::string ReadFile2(const std::string& filename);
GLFWwindow* InitWindow(int width, int height);
void CleanupWindow(GLFWwindow* Window);
int TestVulkan();