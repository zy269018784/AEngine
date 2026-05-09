#pragma once


#include "RHI/RHI.h"
#ifdef PROJECT_USE_VULKAN
    #include "VulkanRHI.h"
    #define GLFW_INCLUDE_VULKAN
#endif
#ifdef PROJECT_USE_GLFW
#include <GLFW/glfw3.h>
#endif

#include "Rhi/RHIObjects/RenderTarget/RHISwapChainRenderTarget.h"
#include "Rhi/RHIObjects/CommandBuffer//RHICommandBuffer.h"

#ifdef PROJECT_USE_D3D12
#include "D3D12RHI.h"
#endif

#ifdef OS_IS_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#endif

#ifdef PROJECT_USE_XCB
#define GLFW_EXPOSE_NATIVE_X11
#endif
#ifdef PROJECT_USE_GLFW
    #include <GLFW/glfw3native.h>
#endif
#include "IWindow.h"

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

class RHIApplication
{
public:
    RHIApplication();
    virtual ~RHIApplication();
    virtual void Run();
    virtual void Resize(int w, int h);
private:
    virtual void Init();
    virtual void Draw();
    virtual void Render();
public:
    /*
     *  0:  vulkan
     *  1:  d3d
     *  2:  opengl
     */
    int RHIIndex = 0;
public:
    /*
        GLFW窗口
    */
    IWindow* Window = nullptr;

    RHISurface* Surface = nullptr;
    RHIRenderTarget *RenderTarget = nullptr;

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
