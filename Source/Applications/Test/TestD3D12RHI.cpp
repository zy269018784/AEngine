#ifdef PROJECT_USE_D3D12
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
using Microsoft::WRL::ComPtr;

#include "D3D12RHI.h"

static const uint32_t FrameCount = 2;
static const uint32_t Width = 800;
static const uint32_t Height = 600;

// 全局变量
static    GLFWwindow* g_Window = nullptr;
static    ComPtr<ID3D12Device> g_Device;
static    ComPtr<IDXGISwapChain3> g_SwapChain;
static    ComPtr<ID3D12CommandQueue> g_CommandQueue;
static    ComPtr<ID3D12GraphicsCommandList> g_CommandList;
static    ComPtr<ID3D12CommandAllocator> g_CommandAllocator;
static    ComPtr<ID3D12Fence> g_Fence;
static    HANDLE g_FenceEvent = nullptr;
static    uint64_t g_FenceValue = 1;


// 三角形相关
static ComPtr<ID3D12RootSignature> g_RootSignature;
static ComPtr<ID3D12PipelineState> g_PipelineState;
static ComPtr<ID3D12Resource> g_VertexBuffer;
static D3D12_VERTEX_BUFFER_VIEW g_VertexBufferView;

static D3D12RHI *RHI = nullptr;
static RHIBuffer *VBO = nullptr;
static RHIGraphicsPipeline* GraphicsPipeline = nullptr;
static RHIShader* VertexShader = nullptr;
static RHIShader* FragmengShader = nullptr;
static RHIWindow* Window = nullptr;
static RHICommandBuffer* CommandBuffer = nullptr;

/*
    着色器资源绑定
*/
RHIShaderResourceBindings* SRB = nullptr;

struct Vertex {
    float position[3];
    float color[4];
};

static bool CreateTriangleResources();

static void CreatePipeline() {

}

// 简化初始化
static bool Init() {
    // 初始化GLFW
    if (!glfwInit()) return false;
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    g_Window = glfwCreateWindow(Width, Height, "D3D12 Triangle", nullptr, nullptr);
    if (!g_Window) return false;

    // 启用调试层
#if defined(_DEBUG)
    ComPtr<ID3D12Debug> debugController;
    if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
        debugController->EnableDebugLayer();
    }
#endif
    HWND hwnd = glfwGetWin32Window(g_Window);
    RHI = new D3D12RHI();
    g_Device =  RHI->Devices[0]->GetHandle();

    Window = RHI->RHICreateWindow(0, hwnd);

    g_CommandQueue = RHI->Devices[0]->Queues[0]->GetHandle();

    // 创建交换链
    ComPtr<IDXGIFactory4> factory;
#if 0
    CreateDXGIFactory1(IID_PPV_ARGS(&factory));
#endif
    factory = ((D3D12Window *)Window)->Factory->GetHandle();
    ComPtr<IDXGISwapChain1> swapChain;
#if 1
    swapChain = ((D3D12Window *)Window)->SwapChain->GetHandle();
#endif
    swapChain.As(&g_SwapChain);
    ((D3D12Window *)Window)-> g_FrameIndex = g_SwapChain->GetCurrentBackBufferIndex();

    std::cout << "CommandPools " << RHI->Devices[0]->CommandPools.size() << std::endl;
    g_CommandAllocator = RHI->Devices[0]->CommandPools[0]->GetHandle();

    g_CommandList = ((D3D12CommandBuffer*)Window->CurrentGraphicsCommandBuffer())->GetHandle();
    g_CommandList->Close();

    // 创建围栏
    if (FAILED(g_Device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&g_Fence)))) {
        return false;
    }
    g_FenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);

    // 创建三角形
    return CreateTriangleResources();
}
std::vector<char> ReadFile(const std::string& filename);

static bool CreateTriangleResources() {
    std::cout << "Creating triangle resources..." << std::endl;
#if 0
    // 1. 创建空的根签名
    D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc = {};
    rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

    ComPtr<ID3DBlob> signature;
    ComPtr<ID3DBlob> error;
    if (FAILED(D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error))) {
        std::cerr << "Failed to serialize root signature" << std::endl;
        return false;
    }
    if (FAILED(g_Device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&g_RootSignature)))) {
        std::cerr << "Failed to create root signature" << std::endl;
        return false;
    }
#endif
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
#if 0
    auto vertShaderCode = ReadFile("DrawTriangle_vert.spv");
    auto fragShaderCode = ReadFile("DrawTriangle_frag.spv");
    VertexShader= RHI->RHICreateShader(RHIShaderType::Vertex, (std::uint32_t*)vertShaderCode.data(), vertShaderCode.size());
    FragmengShader = RHI->RHICreateShader(RHIShaderType::Fragment, (std::uint32_t*)fragShaderCode.data(), fragShaderCode.size());
#else
    VertexShader = RHI->RHICreateShader(RHIShaderType::Vertex, (std::uint32_t*)vsCode, strlen(vsCode));
    FragmengShader = RHI->RHICreateShader(RHIShaderType::Fragment, (std::uint32_t*)psCode, strlen(psCode));
#endif
    std::cout << "CreateTriangleResources 1" << std::endl;
#if 1
    SRB = RHI->RHICreateShaderResourceBindings();
    SRB->SetBindings({

                     });
    SRB->Create();
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
    GraphicsPipeline = RHI->RHICreateGraphicsPipeline(nullptr);
    GraphicsPipeline->SetShaderResourceBindings(SRB);
    GraphicsPipeline->SetPolygonMode(RHIPolygonMode::Fill);
    GraphicsPipeline->SetCullMode(RHICullMode::Back);
    GraphicsPipeline->SetFrontFace(RHIFrontFace::CW);
    GraphicsPipeline->SetTopology(RHITopology::Triangles);
    GraphicsPipeline->SetVertexInputLayout(VertexInputLayout);
    GraphicsPipeline->SetShaderStages({ VertexShader , FragmengShader });
    GraphicsPipeline->Create();

    g_PipelineState = ((D3D12GraphicsPipeline*)GraphicsPipeline)->GetHandle();

    g_RootSignature =  ((D3D12GraphicsPipeline*)GraphicsPipeline)->RootSignature;

#else

#endif
    // 5. 创建顶点缓冲区
    Vertex vertices[] = {
        { {  0.0f,  0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } }, // 上 - 红
        { {  0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } }, // 右下 - 绿
        { { -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } }  // 左下 - 蓝
    };

    const UINT bufferSize = sizeof(vertices);

    VBO = RHI->RHICreateBuffer(RHIBuffer::VertexBuffer, RHIBuffer::Dynamic, bufferSize, vertices);
    g_VertexBuffer = ((D3D12Buffer *)VBO)->GetHandle();

    // 创建顶点缓冲区视图
    g_VertexBufferView.BufferLocation = g_VertexBuffer->GetGPUVirtualAddress();
    g_VertexBufferView.StrideInBytes = sizeof(Vertex);
    g_VertexBufferView.SizeInBytes = bufferSize;

    std::cout << "Triangle resources created successfully!" << std::endl;
    return true;
}

static void WaitForGPU() {
    const UINT64 fence = g_FenceValue;
    g_CommandQueue->Signal(g_Fence.Get(), fence);
    g_FenceValue++;

    if (g_Fence->GetCompletedValue() < fence) {
        g_Fence->SetEventOnCompletion(fence, g_FenceEvent);
        WaitForSingleObject(g_FenceEvent, INFINITE);
    }
     ((D3D12Window *)Window)->g_FrameIndex = g_SwapChain->GetCurrentBackBufferIndex();
}

static void Render() {

    CommandBuffer = Window->CurrentGraphicsCommandBuffer();

    Window->RHIBeginFrame();

    CommandBuffer->RHISetGraphicsPipeline(GraphicsPipeline);

    float x = 0;
    float y = 0;
    float w = 800;
    float h = 600;
    //Window->GetExtent(x, y, w, h);

    Window->RHIBeginRenderPass();

    // 设置管线状态
    g_CommandList->SetGraphicsRootSignature(g_RootSignature.Get());

    RHIViewport Viewport(0, 0, w, h);
    CommandBuffer->RHISetViewport(Viewport);

    RHIScissor Scissor(0, 0, w, h);
    CommandBuffer->RHISetScissor(Scissor);

    // 设置顶点缓冲区和绘制
    CommandBuffer->RHISetPrimitiveTopology(RHITopology::Triangles);

    g_CommandList->IASetVertexBuffers(0, 1, &g_VertexBufferView);

    CommandBuffer->RHIDrawPrimitive(3, 1, 0, 0);

    // 呈现
    Window->RHIEndFrame();

    WaitForGPU();
}

static void Cleanup() {
    WaitForGPU();
    
    if (g_FenceEvent) CloseHandle(g_FenceEvent);
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