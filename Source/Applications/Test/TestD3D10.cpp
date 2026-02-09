#include <iostream>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <d3d10.h>
#include <d3dcompiler.h>
#include <dxgi.h>
#include <wrl/client.h>

#pragma comment(lib, "d3d10.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "glfw3.lib")

using namespace Microsoft::WRL;

// 全局变量
static  ComPtr<ID3D10Device>           g_pDevice = nullptr;
static  ComPtr<IDXGISwapChain>         g_pSwapChain = nullptr;
static  ComPtr<ID3D10RenderTargetView> g_pRenderTargetView = nullptr;
static  ComPtr<ID3D10InputLayout>      g_pInputLayout = nullptr;
static  ComPtr<ID3D10Buffer>           g_pVertexBuffer = nullptr;
static  ComPtr<ID3D10VertexShader>     g_pVertexShader = nullptr;
static  ComPtr<ID3D10PixelShader>      g_pPixelShader = nullptr;

// 顶点结构 - 使用 DirectXMath 类型
struct Vertex
{
    float position[3];
    float color[4];
};

// 简单的顶点着色器代码（HLSL 4.0）
const char* g_vertexShaderCode = R"(
struct VS_INPUT
{
    float3 position : POSITION;
    float4 color : COLOR;
};

struct PS_INPUT
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

PS_INPUT main(VS_INPUT input)
{
    PS_INPUT output;
    // 直接传递位置（NDC 空间：-1 到 1）
    output.position = float4(input.position, 1.0f);
    output.color = input.color;
    return output;
}
)";

// 简单的像素着色器代码（HLSL 4.0）
const char* g_pixelShaderCode = R"(
struct PS_INPUT
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

float4 main(PS_INPUT input) : SV_TARGET
{
    return input.color;
}
)";

// 编译着色器
HRESULT D3D10CompileShader(const char* source, const char* entryPoint, 
                     const char* target, ID3D10Blob** blob)
{
    ComPtr<ID3D10Blob> errorBlob;
    
    HRESULT hr = D3DCompile(
        source,
        strlen(source),
        nullptr,
        nullptr,
        nullptr,
        entryPoint,
        target,
        D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG,
        0,
        blob,
        &errorBlob
    );
    
    if (FAILED(hr) && errorBlob)
    {
        std::cerr << "Shader compile error: " 
                  << (char*)errorBlob->GetBufferPointer() << std::endl;
    }
    
    return hr;
}

// 初始化 D3D10
bool InitD3D10(GLFWwindow* window, int width, int height)
{
    HRESULT hr;
    
    std::cout << "Initializing D3D10..." << std::endl;
    
    // 1. 创建设备和交换链
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    swapChainDesc.BufferCount = 1;
    swapChainDesc.BufferDesc.Width = width;
    swapChainDesc.BufferDesc.Height = height;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.OutputWindow = glfwGetWin32Window(window);
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.Windowed = TRUE;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    
    UINT createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D10_CREATE_DEVICE_DEBUG;
    std::cout << "Debug mode enabled" << std::endl;
#endif
    
    hr = D3D10CreateDeviceAndSwapChain(
        nullptr,
        D3D10_DRIVER_TYPE_HARDWARE,
        nullptr,
        createDeviceFlags,
        D3D10_SDK_VERSION,
        &swapChainDesc,
        &g_pSwapChain,
        &g_pDevice
    );
    
    if (FAILED(hr))
    {
        std::cerr << "Failed to create D3D10 device and swap chain! HRESULT: 0x" 
                  << std::hex << hr << std::dec << std::endl;
        return false;
    }
    
    std::cout << "D3D10 device created successfully" << std::endl;
    
    // 2. 创建渲染目标视图
    ComPtr<ID3D10Texture2D> backBuffer;
    hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (void**)&backBuffer);
    if (FAILED(hr))
    {
        std::cerr << "Failed to get back buffer! HRESULT: 0x" 
                  << std::hex << hr << std::dec << std::endl;
        return false;
    }
    
    hr = g_pDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, &g_pRenderTargetView);
    if (FAILED(hr))
    {
        std::cerr << "Failed to create render target view! HRESULT: 0x" 
                  << std::hex << hr << std::dec << std::endl;
        return false;
    }
    
    // 设置渲染目标
    g_pDevice->OMSetRenderTargets(1, g_pRenderTargetView.GetAddressOf(), nullptr);
    
    // 3. 设置视口
    D3D10_VIEWPORT viewport;
    viewport.Width = width;
    viewport.Height = height;
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    g_pDevice->RSSetViewports(1, &viewport);
    
    std::cout << "D3D10 initialized successfully" << std::endl;
    return true;
}

// 创建着色器
bool D3D10CreateShaders()
{
    HRESULT hr;
    
    std::cout << "Creating shaders..." << std::endl;
    
    // 编译顶点着色器
    ComPtr<ID3D10Blob> vsBlob;
    hr = D3D10CompileShader(g_vertexShaderCode, "main", "vs_4_0", &vsBlob);
    if (FAILED(hr))
    {
        std::cerr << "Failed to compile vertex shader" << std::endl;
        return false;
    }
    
    hr = g_pDevice->CreateVertexShader(
        vsBlob->GetBufferPointer(),
        vsBlob->GetBufferSize(),
        &g_pVertexShader
    );
    if (FAILED(hr))
    {
        std::cerr << "Failed to create vertex shader! HRESULT: 0x" 
                  << std::hex << hr << std::dec << std::endl;
        return false;
    }
    
    // 编译像素着色器
    ComPtr<ID3D10Blob> psBlob;
    hr = D3D10CompileShader(g_pixelShaderCode, "main", "ps_4_0", &psBlob);
    if (FAILED(hr))
    {
        std::cerr << "Failed to compile pixel shader" << std::endl;
        return false;
    }
    
    hr = g_pDevice->CreatePixelShader(
        psBlob->GetBufferPointer(),
        psBlob->GetBufferSize(),
        &g_pPixelShader
    );
    if (FAILED(hr))
    {
        std::cerr << "Failed to create pixel shader! HRESULT: 0x" 
                  << std::hex << hr << std::dec << std::endl;
        return false;
    }
    
    // 创建输入布局
    D3D10_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 }
    };
    UINT numElements = sizeof(layout) / sizeof(layout[0]);
    
    hr = g_pDevice->CreateInputLayout(
        layout,
        numElements,
        vsBlob->GetBufferPointer(),
        vsBlob->GetBufferSize(),
        &g_pInputLayout
    );
    
    if (FAILED(hr))
    {
        std::cerr << "Failed to create input layout! HRESULT: 0x" 
                  << std::hex << hr << std::dec << std::endl;
        return false;
    }
    
    std::cout << "Shaders created successfully" << std::endl;
    return true;
}

// 创建顶点缓冲区
bool D3D10CreateVertexBuffer()
{
    std::cout << "Creating vertex buffer..." << std::endl;
    
    // 定义三角形的三个顶点（直接在NDC空间：-1到1）
    Vertex vertices[] =
    {
        // 位置 (x, y, z)           // 颜色 (r, g, b, a)
        { { 0.0f,  0.5f, 0.0f },    { 1.0f, 0.0f, 0.0f, 1.0f } },   // 红色 - 顶部
        { { 0.5f, -0.5f, 0.0f },    { 0.0f, 1.0f, 0.0f, 1.0f } },   // 绿色 - 右下
        { { -0.5f, -0.5f, 0.0f },   { 0.0f, 0.0f, 1.0f, 1.0f } }    // 蓝色 - 左下
    };
    
    // 创建顶点缓冲区描述
    D3D10_BUFFER_DESC bufferDesc;
    bufferDesc.Usage = D3D10_USAGE_DEFAULT;
    bufferDesc.ByteWidth = sizeof(vertices);
    bufferDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
    bufferDesc.CPUAccessFlags = 0;
    bufferDesc.MiscFlags = 0;
    
    // 设置初始化数据
    D3D10_SUBRESOURCE_DATA initData;
    initData.pSysMem = vertices;
    initData.SysMemPitch = 0;
    initData.SysMemSlicePitch = 0;
    
    // 创建顶点缓冲区
    HRESULT hr = g_pDevice->CreateBuffer(&bufferDesc, &initData, &g_pVertexBuffer);
    if (FAILED(hr))
    {
        std::cerr << "Failed to create vertex buffer! HRESULT: 0x" 
                  << std::hex << hr << std::dec << std::endl;
        return false;
    }
    
    std::cout << "Vertex buffer created successfully" << std::endl;
    return true;
}

// 渲染函数
void D3D10Render()
{
    // 1. 清除渲染目标为深蓝色
    float clearColor[4] = { 0.1f, 0.2f, 0.4f, 1.0f };
    g_pDevice->ClearRenderTargetView(g_pRenderTargetView.Get(), clearColor);
    
    // 2. 设置顶点缓冲区
    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    g_pDevice->IASetVertexBuffers(0, 1, g_pVertexBuffer.GetAddressOf(), &stride, &offset);
    
    // 3. 设置图元拓扑为三角形列表
    g_pDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    
    // 4. 设置输入布局
    g_pDevice->IASetInputLayout(g_pInputLayout.Get());
    
    // 5. 设置着色器
    g_pDevice->VSSetShader(g_pVertexShader.Get());
    g_pDevice->PSSetShader(g_pPixelShader.Get());
    
    // 6. 绘制三角形
    g_pDevice->Draw(3, 0);  // 绘制3个顶点（一个三角形）
    
    // 7. 呈现到屏幕
    g_pSwapChain->Present(1, 0); // 垂直同步
}

// 窗口大小改变回调
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    if (width == 0 || height == 0) return;
    
    std::cout << "Window resized to " << width << "x" << height << std::endl;
    
    // 释放旧的渲染目标视图
    g_pRenderTargetView.Reset();
    
    // 调整交换链缓冲区大小
    g_pSwapChain->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);
    
    // 重新创建渲染目标视图
    ComPtr<ID3D10Texture2D> backBuffer;
    g_pSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (void**)&backBuffer);
    g_pDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, &g_pRenderTargetView);
    
    // 重新设置渲染目标
    g_pDevice->OMSetRenderTargets(1, g_pRenderTargetView.GetAddressOf(), nullptr);
    
    // 更新视口
    D3D10_VIEWPORT viewport;
    viewport.Width = width;
    viewport.Height = height;
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    g_pDevice->RSSetViewports(1, &viewport);
}

// 清理资源
void D3D10Cleanup()
{
    std::cout << "Cleaning up resources..." << std::endl;
    
    g_pVertexBuffer.Reset();
    g_pInputLayout.Reset();
    g_pPixelShader.Reset();
    g_pVertexShader.Reset();
    g_pRenderTargetView.Reset();
    g_pSwapChain.Reset();
    g_pDevice.Reset();
    
    std::cout << "Resources cleaned up" << std::endl;
}

// 主函数
int TestD3D10(int argc, char **argv)
{
    std::cout << "==========================================" << std::endl;
    std::cout << "D3D10 + GLFW Triangle Example (No D3DX)" << std::endl;
    std::cout << "==========================================" << std::endl;
    
    // 1. 初始化 GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return -1;
    }
    std::cout << "GLFW initialized successfully" << std::endl;
    
    // 2. 创建 GLFW 窗口
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);  // 不使用 OpenGL
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);     // 允许调整大小
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "D3D10 Simple Triangle", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return -1;
    }
    std::cout << "GLFW window created successfully (800x600)" << std::endl;
    
    // 设置窗口大小回调
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    // 3. 初始化 D3D10
    if (!InitD3D10(window, 800, 600))
    {
        std::cerr << "Failed to initialize D3D10!" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }
    
    // 4. 创建着色器
    if (!D3D10CreateShaders())
    {
        std::cerr << "Failed to create shaders!" << std::endl;
        D3D10Cleanup();
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }
    
    // 5. 创建顶点缓冲区
    if (!D3D10CreateVertexBuffer())
    {
        std::cerr << "Failed to create vertex buffer!" << std::endl;
        D3D10Cleanup();
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }
    
    std::cout << std::endl;
    std::cout << "Application ready!" << std::endl;
    std::cout << "Controls:" << std::endl;
    std::cout << "  - ESC: Exit application" << std::endl;
    std::cout << std::endl;
    std::cout << "Triangle vertices (NDC coordinates):" << std::endl;
    std::cout << "  1. (0.0,  0.5)  - Red" << std::endl;
    std::cout << "  2. (0.5, -0.5)  - Green" << std::endl;
    std::cout << "  3. (-0.5, -0.5) - Blue" << std::endl;
    std::cout << std::endl;
    
    // 主循环
    while (!glfwWindowShouldClose(window))
    {
        // 处理事件
        glfwPollEvents();
        
        // 检查 ESC 键退出
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
        
        // 渲染
        D3D10Render();
    }
    
    // 清理
    D3D10Cleanup();
    glfwDestroyWindow(window);
    glfwTerminate();
    
    std::cout << std::endl;
    std::cout << "Application terminated successfully" << std::endl;
    std::cout << "==========================================" << std::endl;
    
    return 0;
}