#pragma once

#include "ES32RHI.h"
#include "RHI.h"
#ifdef PROJECT_USE_VULKAN
    #include "VulkanRHI.h"
    #define GLFW_INCLUDE_VULKAN
#endif
#include <GLFW/glfw3.h>


#ifdef OS_IS_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#endif

#ifdef PROJECT_USE_X11
#define GLFW_EXPOSE_NATIVE_X11
#endif

#include <GLFW/glfw3native.h>

#include "Window/IWindow.h"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <limits>
#include <optional>
#include <set>


#define USE_RHI_VULKAN 0
class RHIApplication
{
public:
    RHIApplication(IWindow* Window);
    RHIApplication(GLFWwindow* Window) {};
    virtual ~RHIApplication();
    virtual void Run();
    virtual void Resize(int w, int h);
private:
    virtual void Init();
    virtual void Draw();
    virtual void Render();
protected:
    /*
        GLFW窗口
    */
    IWindow* Window = nullptr;
    RHIWindow* RHIWindow_ = nullptr;
    /*
        RHI
    */
    RHI* pRHI = nullptr;
    /*
        VBO
    */
    RHIBuffer* RHIVBO = nullptr;
    /*
        EBO
    */
    RHIBuffer* RHIEBO = nullptr;
    /*
        Pipeline
    */
    RHIGraphicsPipeline* GraphicsPipeline = nullptr;
    /*
       顶点输入
    */
    std::vector<RHICommandBuffer::VertexInput> VertexInputs;
    /*
        着色器资源绑定
    */
    RHIShaderResourceBindings* SRB = nullptr;

    RHIShader* VertexShader = nullptr;
    RHIShader* FragmengShader = nullptr;
    RHIShader* GeometryShader = nullptr;
    RHIShader* ComputeShader = nullptr;
};
