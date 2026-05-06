#include "ES32RHI.h"
#include "VulkanRHI.h"


#ifdef PROJECT_USE_D3D12
#include "D3D12RHI.h"
// 简化的修复版本
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <d3d12.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>
#include <iostream>
#include <wrl.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <d3d12.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#include <d3dx12.h>

#include "D3D12Objects/CommandBuffer/D3D12CommandPool.h"
#include "D3D12Objects/Factory/D3D12Factory.h"
#include "D3D12Objects/Pipeline/D3D12GraphicsPipeline.h"
#include "D3D12Objects/SwapChain/D3D12SwapChain.h"
#include "D3D12Objects/Window/D3D12Window.h"
#include "D3D12Objects/Factory/D3D12Factory.h"


#if 11
// 必须链接这些库
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#endif
#include <iostream>
#include <vector>
#include <string>
#include <wrl.h>
#include "D3D12Objects/Resource/D3D12Buffer.h"
#include "D3D12Objects/Shader/D3D12Shader.h"
#include "D3D12Objects/Window/D3D12Window.h"
#include "D3D12Objects/CommandBuffer/D3D12CommandBuffer.h"
#include "RHIObjects/Shader/RHIShaderResourceBindings.h"
using Microsoft::WRL::ComPtr;

#include "D3D12RHI.h"
int RHIIndex = 1;
static const uint32_t FrameCount = 2;
static const uint32_t Width = 800;
static const uint32_t Height = 600;

// 全局变量
static    GLFWwindow* g_Window = nullptr;
/*
   顶点输入
*/
static std::vector<RHICommandBuffer::VertexInput> VertexInputs;


static RHI *pRHI = nullptr;
static RHIBuffer *VBO = nullptr;
static RHIGraphicsPipeline* GraphicsPipeline = nullptr;
static RHIShader* VertexShader = nullptr;
static RHIShader* FragmengShader = nullptr;
static RHICommandBuffer* CommandBuffer = nullptr;

/*
    着色器资源绑定
*/
RHIShaderResourceBindings* SRB = nullptr;


#if 1
/*
    VBO1三角形: 红色和黄色
    VBO1三角形: 蓝色和绿色
*/
static float VertexAttributes[] = {
    // VBO1
    0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
   -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,

   -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,  0.0f,
   -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f,  0.0f,
    0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f,  0.0f,
};

#endif




struct Vertex {
    float position[3];
    float color[4];
};
static void CreateVBO();
static void CreateVertexDescriptioin();
static bool CreateTriangleResources();
static void CreateSRB();
static void CreateGraphicsPipeline();

// 简化初始化
static bool Init() {
    // 初始化GLFW
    if (!glfwInit()) return false;

    // 启用调试层
#if defined(_DEBUG)
    ComPtr<ID3D12Debug> debugController;
    if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
        debugController->EnableDebugLayer();
    }
#endif


    //pRHI = new D3D12RHI();

    if (0 == RHIIndex)
    {
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        g_Window = glfwCreateWindow(Width, Height, "D3D12 Triangle", nullptr, nullptr);
        if (!g_Window) return false;
        pRHI = new VulkanRHI();
    }
    else if (1 == RHIIndex)
    {
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        g_Window = glfwCreateWindow(Width, Height, "D3D12 Triangle", nullptr, nullptr);
        if (!g_Window) return false;
        pRHI = new D3D12RHI();
    }
    else if (2 == RHIIndex)
    {
        /*
            opengl需要
        */
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        g_Window = glfwCreateWindow(Width, Height, "D3D12 Triangle", nullptr, nullptr);
        if (!g_Window) return false;
        glfwMakeContextCurrent(g_Window);
        pRHI = new ES32RHI();
    }
    HWND hwnd = glfwGetWin32Window(g_Window);
    HINSTANCE instacne = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);
  //  Window = pRHI->RHICreateWindow(instacne, hwnd);
#if 0
    ((D3D12Window *)Window)-> g_FrameIndex =  ((D3D12Window *)Window)->SwapChain->GetCurrentBackBufferIndex();

    std::cout << "CommandPools " << pRHI->Devices[0]->CommandPools.size() << std::endl;

    ((D3D12CommandBuffer*)Window->CurrentGraphicsCommandBuffer())->GetHandle()->Close();
#endif
    CreateVBO();
    CreateVertexDescriptioin();
    CreateGraphicsPipeline();

   // CommandBuffer = Window->CurrentGraphicsCommandBuffer();
    CommandBuffer->RHISetGraphicsPipeline(GraphicsPipeline);
    return true;
    // 创建三角形
    return CreateTriangleResources();
}
std::vector<char> ReadFile(const std::string& filename);

static bool CreateTriangleResources() {
    std::cout << "Creating triangle resources..." << std::endl;

    // 2. 编译着色器
    const char* vsCode = R"(
        struct VS_IN {
            float3 pos : POSITION;
            float4 col : COLOR;
        };
        struct PS_IN {
            float4 pos : SV_POSITION;
            float4 col : COLOR;
        };
        PS_IN main(VS_IN input) {
            PS_IN output;
            output.pos = float4(input.pos, 1.0);
            output.col = input.col;
            return output;
        }
    )";

    const char* psCode = R"(
        struct PS_IN {
            float4 pos : SV_POSITION;
            float4 col : COLOR;
        };
        float4 main(PS_IN input) : SV_Target {
            return input.col;
        }
    )";

    UINT compileFlags = 0;
#ifdef _DEBUG
    compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
    std::cout << "CreateTriangleResources 1" << std::endl;
    if (1 != RHIIndex)
    {
        auto vertShaderCode = ReadFile("DrawTriangle_vert.spv");
        auto fragShaderCode = ReadFile("DrawTriangle_frag.spv");
        std::cout << "RHICreateShader 1" << std::endl;
        VertexShader= pRHI->RHICreateShader(RHIShaderType::Vertex, (std::uint32_t*)vertShaderCode.data(), vertShaderCode.size());
        FragmengShader = pRHI->RHICreateShader(RHIShaderType::Fragment, (std::uint32_t*)fragShaderCode.data(), fragShaderCode.size());
        std::cout << "RHICreateShader 2" << std::endl;
    } else
    {
        VertexShader = pRHI->RHICreateShader(RHIShaderType::Vertex, (std::uint32_t*)vsCode, strlen(vsCode));
        FragmengShader = pRHI->RHICreateShader(RHIShaderType::Fragment, (std::uint32_t*)psCode, strlen(psCode));
    }
    std::cout << "CreateTriangleResources " << std::endl;
#if 1

    CreateSRB();
#endif
    std::cout << "CreateTriangleResources 2" << std::endl;
#if 1
    RHIVertexInputLayout VertexInputLayout;
    /*
        int binding, int location, RHIVertexInputAttribute::Format format, std::uint32_t offset, int matrixSlice = -1
    */
    VertexInputLayout.SetAttributes({
                                            { "POSITION", 0, 0, RHIVertexInputAttribute::Format::Float3,  0 * sizeof(float), 0 },
                                            { "COLOR", 0, 1, RHIVertexInputAttribute::Format::Float4,  3 * sizeof(float), 0 },
                                            // { 0, 2, RHIVertexInputAttribute::Format::Float2,  6 * sizeof(float), 0 }
                                    });
    /*
        std::uint32_t stride, RHIVertexInputBinding::Classification cls = PerVertex, std::uint32_t stepRate = 1
    */
    VertexInputLayout.SetBindings({
                                          { 7 * sizeof(float), RHIVertexInputBinding::Classification::PerVertex, 0 },
                                  });

    /*
        用于创建Descriptor Set Layout和Pipeline Layout
    */
    GraphicsPipeline = pRHI->RHICreateGraphicsPipeline((RHIRenderPass *)0);
    GraphicsPipeline->SetShaderResourceBindings(SRB);
    GraphicsPipeline->SetPolygonMode(RHIPolygonMode::Fill);
    GraphicsPipeline->SetCullMode(RHICullMode::CullModeNone);
    GraphicsPipeline->SetFrontFace(RHIFrontFace::CW);
    GraphicsPipeline->SetTopology(RHITopology::Triangles);
    GraphicsPipeline->SetVertexInputLayout(VertexInputLayout);
    GraphicsPipeline->SetShaderStages({ VertexShader , FragmengShader });
    GraphicsPipeline->Create();

   // CommandBuffer = Window->CurrentGraphicsCommandBuffer();
    CommandBuffer->RHISetGraphicsPipeline(GraphicsPipeline);

#else

#endif

    return true;
}

static void CreateVBO()
{
    VBO = pRHI->RHICreateBuffer(RHIBufferType::VertexBuffer, RHIBufferUsageFlag::VertexBuffer, sizeof(VertexAttributes), VertexAttributes);
    std::cout << "CreateVBO OK" << std::endl;
}

static void CreateVertexDescriptioin()
{
    VertexInputs.push_back(std::make_pair(VBO, 0 * sizeof(float)));
}

static void CreateSRB()
{
    SRB = pRHI->RHICreateShaderResourceBindings();
    SRB->Create();
}

static void CreateGraphicsPipeline()
{
    // 2. 编译着色器
    const char* vsCode = R"(
        struct VS_IN {
            float3 pos : POSITION;
            float4 col : COLOR;
        };
        struct PS_IN {
            float4 pos : SV_POSITION;
            float4 col : COLOR;
        };
        PS_IN main(VS_IN input) {
            PS_IN output;
            output.pos = float4(input.pos, 1.0);
            output.col = input.col;
            return output;
        }
    )";

    const char* psCode = R"(
        struct PS_IN {
            float4 pos : SV_POSITION;
            float4 col : COLOR;
        };
        float4 main(PS_IN input) : SV_Target {
            return input.col;
        }
    )";
    if (1 != RHIIndex)
    {
        auto vertShaderCode = ReadFile("DrawTriangle_vert.spv");
        auto fragShaderCode = ReadFile("DrawTriangle_frag.spv");
        // 创建Shader
        VertexShader= pRHI->RHICreateShader(RHIShaderType::Vertex,   (std::uint32_t*)vertShaderCode.data(), vertShaderCode.size());
        FragmengShader = pRHI->RHICreateShader(RHIShaderType::Fragment, (std::uint32_t*)fragShaderCode.data(), fragShaderCode.size());
    }
    else
    {
        VertexShader = pRHI->RHICreateShader(RHIShaderType::Vertex, (std::uint32_t*)vsCode, strlen(vsCode));
        FragmengShader = pRHI->RHICreateShader(RHIShaderType::Fragment, (std::uint32_t*)psCode, strlen(psCode));
    }

    RHIVertexInputLayout VertexInputLayout;
    /*
        int binding, int location, RHIVertexInputAttribute::Format format, std::uint32_t offset, int matrixSlice = -1
    */
    VertexInputLayout.SetAttributes({
                                            { "POSITION", 0, 0, RHIVertexInputAttribute::Format::Float3,  0 * sizeof(float), 0 },
                                            { "COLOR", 0, 1, RHIVertexInputAttribute::Format::Float4,  3 * sizeof(float), 0 },
                                            // { 0, 2, RHIVertexInputAttribute::Format::Float2,  6 * sizeof(float), 0 }
                                    });
    /*
        std::uint32_t stride, RHIVertexInputBinding::Classification cls = PerVertex, std::uint32_t stepRate = 1
    */
    VertexInputLayout.SetBindings({
                                          { 7 * sizeof(float), RHIVertexInputBinding::Classification::PerVertex, 0 },
                                  });

    /*
        用于创建Descriptor Set Layout和Pipeline Layout
    */
    //GraphicsPipeline = pRHI->RHICreateGraphicsPipeline(Window);
    GraphicsPipeline->SetShaderResourceBindings(SRB);
    GraphicsPipeline->SetPolygonMode(RHIPolygonMode::Fill);
    GraphicsPipeline->SetCullMode(RHICullMode::CullModeNone);
    GraphicsPipeline->SetFrontFace(RHIFrontFace::CCW);
    GraphicsPipeline->SetTopology(RHITopology::Triangles);
    GraphicsPipeline->SetVertexInputLayout(VertexInputLayout);
    GraphicsPipeline->SetShaderStages({ VertexShader , FragmengShader });
    GraphicsPipeline->Create();
}

static void WaitForGPU() {
#if 0
    const UINT64 fence = ((D3D12Window *)Window)->FenceValue;
    ((D3D12RHI *    )pRHI)->Devices[0]->Queues[0]->GetHandle()->Signal(((D3D12Window *)Window)->Fence, fence);
    ((D3D12Window *)Window)->FenceValue++;

    if (((D3D12Window *)Window)->Fence->GetCompletedValue() < fence) {
        ((D3D12Window *)Window)->Fence->SetEventOnCompletion(fence,  ((D3D12Window *)Window)->FenceEvent);
        WaitForSingleObject( ((D3D12Window *)Window)->FenceEvent, INFINITE);
    }
     ((D3D12Window *)Window)->g_FrameIndex =  ((D3D12Window *)Window)->SwapChain->GetCurrentBackBufferIndex();
#endif
}

static void D3D12Draw()
{
    float x = 0;
    float y = 0;
    float w = 800;
    float h = 600;
   // Window->GetExtent(x, y, w, h);

   // CommandBuffer = Window->CurrentGraphicsCommandBuffer();
   // CommandBuffer->RHISetGraphicsPipeline(GraphicsPipeline);

    RHIViewport Viewport(0, 0, w, h);
    CommandBuffer->RHISetViewport(Viewport);

    RHIScissor Scissor(0, 0, w, h);
    CommandBuffer->RHISetScissor(Scissor);

    /* vulkan 必须*/
  //  CommandBuffer->RHISetGraphicsPipeline(GraphicsPipeline);
#if 1
    // 设置顶点缓冲区和绘制
    CommandBuffer->RHISetPrimitiveTopology(RHITopology::Triangles);

    CommandBuffer->RHISetDepthTestEnable(true);
    CommandBuffer->RHISetDepthCompareOp(RHICompareOp::Less);
    CommandBuffer->RHISetDepthWriteEnable(true);
    /*
        开启深度测试, 这个也要开启
    */
    CommandBuffer->RHISetDepthBoundsTestEnable(true);
    /*

    */
    CommandBuffer->RHISetStencilTestEnable(false);
#endif
    CommandBuffer->RHISetVertexInput(0, VertexInputs.size(), VertexInputs.data(), nullptr, 0, RHIIndexFormat::IndexUInt32);

    CommandBuffer->RHIDrawPrimitive(3, 1, 0, 0);

}

static void Render()
{
    while (!glfwWindowShouldClose(g_Window))
    {
        glfwPollEvents();
        if (glfwGetKey(g_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            break;
        }
       // Window->RHIBeginFrame();
       // Window->RHIBeginRenderPass();
        D3D12Draw();
       // Window->RHIEndRenderPass();
       // Window->RHIEndFrame();

        glfwSwapBuffers(g_Window);
        glfwPollEvents();
    }
}

static void Cleanup() {

    if (g_Window) glfwDestroyWindow(g_Window);
    glfwTerminate();
}

int TestD3D12RHI(int argc, char **argv)
{
    if (!Init()) {
        Cleanup();
        return -1;
    }

    std::cout << "Running D3D12 Triangle Example. Press ESC to exit." << std::endl;

    while (!glfwWindowShouldClose(g_Window)) {
        glfwPollEvents();
        if (glfwGetKey(g_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            break;
        }
        Render();
    }

    Cleanup();
    return 0;
}
#endif