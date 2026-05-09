#if  PROJECT_USE_D3D12
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

// D3D10 必需的头文件
#include <d3d10_1.h>
#include <d3d10.h>
#include <dxgi.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d10.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;

// 窗口尺寸
static const UINT WIDTH = 800;
static const UINT HEIGHT = 600;

// 纹理参数
static const UINT TEXTURE_WIDTH = 256;
static const UINT TEXTURE_HEIGHT = 256;

// 全局 D3D10 对象 - 全部加上 static
static ID3D10Device* g_device = nullptr;
static IDXGISwapChain* g_swapChain = nullptr;
static ID3D10RenderTargetView* g_renderTargetView = nullptr;
static ID3D10RasterizerState* g_rasterizerState = nullptr;

// 纹理相关对象
static ID3D10Texture2D* g_texture = nullptr;
static ID3D10ShaderResourceView* g_textureView = nullptr;
static ID3D10SamplerState* g_samplerState = nullptr;

// 渲染管线对象
static ID3D10VertexShader* g_vertexShader = nullptr;
static ID3D10PixelShader* g_pixelShader = nullptr;
static ID3D10InputLayout* g_inputLayout = nullptr;
static ID3D10Buffer* g_vertexBuffer = nullptr;

// 顶点结构
struct Vertex {
    DirectX::XMFLOAT3 position;  // 位置
    DirectX::XMFLOAT2 texcoord;  // 纹理坐标 (uv)
};

// 检查 HRESULT 的辅助宏
#define CHECK_HR(hr) { if (FAILED(hr)) { std::cerr << "HRESULT failed at line " << __LINE__ << std::endl; return false; } }

// 创建纹理数据 - 彩色渐变纹理
static void CreateTextureData(std::vector<uint8_t>& data) {
    data.resize(TEXTURE_WIDTH * TEXTURE_HEIGHT * 4);

    for (UINT y = 0; y < TEXTURE_HEIGHT; ++y) {
        for (UINT x = 0; x < TEXTURE_WIDTH; ++x) {
            UINT index = (y * TEXTURE_WIDTH + x) * 4;

            // 创建彩色渐变：
            // 左上角红色，右上角绿色，左下角蓝色，右下角白色
            float nx = (float)x / (TEXTURE_WIDTH - 1);
            float ny = (float)y / (TEXTURE_HEIGHT - 1);

            data[index + 0] = (UINT8)(nx * 255);              // R 从左到右渐变
            data[index + 1] = (UINT8)(ny * 255);              // G 从上到下渐变
            data[index + 2] = (UINT8)((1.0f - nx) * 255);     // B 从右到左渐变
            data[index + 3] = 255;                              // Alpha
        }
    }
    std::cout << "2D texture data created with gradients" << std::endl;
}

// 初始化 D3D10
static bool InitD3D10(GLFWwindow* window) {
    std::cout << "Initializing D3D10..." << std::endl;

    IDXGIFactory* factory = nullptr;
    CHECK_HR(CreateDXGIFactory(IID_PPV_ARGS(&factory)));

    // 创建 D3D10 设备和交换链
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    swapChainDesc.BufferCount = 1;
    swapChainDesc.BufferDesc.Width = WIDTH;
    swapChainDesc.BufferDesc.Height = HEIGHT;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.OutputWindow = glfwGetWin32Window(window);
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.Windowed = TRUE;

    UINT createDeviceFlags = 0;
#if defined(_DEBUG)
    createDeviceFlags |= D3D10_CREATE_DEVICE_DEBUG;
#endif

    CHECK_HR(D3D10CreateDeviceAndSwapChain(
        nullptr,                          // 适配器
        D3D10_DRIVER_TYPE_HARDWARE,       // 驱动类型
        nullptr,                          // 软件驱动模块
        createDeviceFlags,                 // 创建标志
        D3D10_SDK_VERSION,                  // SDK 版本
        &swapChainDesc,                     // 交换链描述
        &g_swapChain,                        // 返回交换链
        &g_device                             // 返回设备
    ));

    std::cout << "D3D10 device and swap chain created" << std::endl;

    // 创建渲染目标视图
    ID3D10Texture2D* backBuffer = nullptr;
    CHECK_HR(g_swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer)));
    CHECK_HR(g_device->CreateRenderTargetView(backBuffer, nullptr, &g_renderTargetView));
    backBuffer->Release();

    // 设置渲染目标
    g_device->OMSetRenderTargets(1, &g_renderTargetView, nullptr);

    // 设置视口
    D3D10_VIEWPORT viewport = {};
    viewport.Width = WIDTH;
    viewport.Height = HEIGHT;
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    g_device->RSSetViewports(1, &viewport);

    // 创建光栅化状态（禁用背面剔除）
    D3D10_RASTERIZER_DESC rasterizerDesc = {};
    rasterizerDesc.FillMode = D3D10_FILL_SOLID;
    rasterizerDesc.CullMode = D3D10_CULL_NONE;  // 不剔除背面
    rasterizerDesc.FrontCounterClockwise = FALSE;
    rasterizerDesc.DepthClipEnable = TRUE;
    rasterizerDesc.ScissorEnable = FALSE;
    rasterizerDesc.MultisampleEnable = FALSE;
    rasterizerDesc.AntialiasedLineEnable = FALSE;

    CHECK_HR(g_device->CreateRasterizerState(&rasterizerDesc, &g_rasterizerState));
    g_device->RSSetState(g_rasterizerState);

    factory->Release();

    std::cout << "D3D10 initialized successfully" << std::endl;
    return true;
}

// 创建顶点缓冲区 - 一个大的三角形覆盖大部分屏幕
static bool CreateVertexBuffer() {
    std::cout << "Creating vertex buffer..." << std::endl;

    // 创建一个大的三角形，覆盖大部分屏幕
    Vertex vertices[] = {
        { { 0.0f, 0.8f, 0.0f }, { 0.5f, 0.0f } },     // 顶部中间
        { { 0.8f, -0.6f, 0.0f }, { 1.0f, 1.0f } },    // 右下
        { { -0.8f, -0.6f, 0.0f }, { 0.0f, 1.0f } },   // 左下
    };

    std::cout << "Triangle vertices:" << std::endl;
    for (int i = 0; i < 3; i++) {
        std::cout << "  Vertex " << i << ": pos("
                  << vertices[i].position.x << ", "
                  << vertices[i].position.y << ", "
                  << vertices[i].position.z << ") uv("
                  << vertices[i].texcoord.x << ", "
                  << vertices[i].texcoord.y << ")" << std::endl;
    }

    D3D10_BUFFER_DESC bufferDesc = {};
    bufferDesc.Usage = D3D10_USAGE_DEFAULT;
    bufferDesc.ByteWidth = sizeof(vertices);
    bufferDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
    bufferDesc.CPUAccessFlags = 0;
    bufferDesc.MiscFlags = 0;

    D3D10_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = vertices;

    CHECK_HR(g_device->CreateBuffer(&bufferDesc, &initData, &g_vertexBuffer));
    std::cout << "Vertex buffer created" << std::endl;
    return true;
}

// 创建2D纹理
static bool Create2DTexture() {
    std::cout << "Creating 2D texture..." << std::endl;

    std::vector<uint8_t> textureData;
    CreateTextureData(textureData);

    D3D10_TEXTURE2D_DESC textureDesc = {};
    textureDesc.Width = TEXTURE_WIDTH;
    textureDesc.Height = TEXTURE_HEIGHT;
    textureDesc.MipLevels = 1;
    textureDesc.ArraySize = 1;
    textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    textureDesc.SampleDesc.Count = 1;
    textureDesc.SampleDesc.Quality = 0;
    textureDesc.Usage = D3D10_USAGE_DEFAULT;
    textureDesc.BindFlags = D3D10_BIND_SHADER_RESOURCE;
    textureDesc.CPUAccessFlags = 0;
    textureDesc.MiscFlags = 0;

    D3D10_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = textureData.data();
    initData.SysMemPitch = TEXTURE_WIDTH * 4;

    CHECK_HR(g_device->CreateTexture2D(&textureDesc, &initData, &g_texture));

    // 创建着色器资源视图
    D3D10_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Format = textureDesc.Format;
    srvDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = 1;

    CHECK_HR(g_device->CreateShaderResourceView(g_texture, &srvDesc, &g_textureView));

    // 创建采样器状态
    D3D10_SAMPLER_DESC samplerDesc = {};
    samplerDesc.Filter = D3D10_FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU = D3D10_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV = D3D10_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW = D3D10_TEXTURE_ADDRESS_WRAP;
    samplerDesc.ComparisonFunc = D3D10_COMPARISON_NEVER;
    samplerDesc.MinLOD = 0;
    samplerDesc.MaxLOD = D3D10_FLOAT32_MAX;

    CHECK_HR(g_device->CreateSamplerState(&samplerDesc, &g_samplerState));

    std::cout << "2D texture created with size " << TEXTURE_WIDTH << "x" << TEXTURE_HEIGHT << std::endl;
    return true;
}

// 编译着色器 - D3D10 使用 ID3D10Blob
static ID3D10Blob* CompileShader(const std::string& source, const std::string& entrypoint, const std::string& target) {
    ID3D10Blob* shaderBlob = nullptr;
    ID3D10Blob* errorBlob = nullptr;

    UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(_DEBUG)
    flags |= D3DCOMPILE_DEBUG;
#endif

    HRESULT hr = D3DCompile(
        source.c_str(),
        source.size(),
        nullptr,
        nullptr,
        nullptr,
        entrypoint.c_str(),
        target.c_str(),
        flags,
        0,
        &shaderBlob,
        &errorBlob
    );

    if (FAILED(hr)) {
        if (errorBlob) {
            std::cerr << "Shader compilation error: " << (char*)errorBlob->GetBufferPointer() << std::endl;
            errorBlob->Release();
        }
        return nullptr;
    }
    return shaderBlob;
}

// 创建着色器 - D3D10 版本
static bool CreateShaders() {
    std::cout << "Creating shaders..." << std::endl;

    // D3D10 着色器语法 (Shader Model 4.0)
    const char* vsSource = R"(
        struct VSInput {
            float4 position : POSITION;
            float2 texcoord : TEXCOORD;
        };
        struct VSOutput {
            float4 position : SV_POSITION;
            float2 texcoord : TEXCOORD0;
        };
        VSOutput main(VSInput input) {
            VSOutput output;
            output.position = input.position;
            output.texcoord = input.texcoord;
            return output;
        }
    )";

    const char* psSource = R"(
        Texture2D g_texture : register(t0);
        SamplerState g_sampler : register(s0);
        struct PSInput {
            float4 position : SV_POSITION;
            float2 texcoord : TEXCOORD0;
        };
        float4 main(PSInput input) : SV_TARGET {
            // 从2D纹理采样
            return g_texture.Sample(g_sampler, input.texcoord);
        }
    )";

    ID3D10Blob* vsBlob = CompileShader(vsSource, "main", "vs_4_0");
    ID3D10Blob* psBlob = CompileShader(psSource, "main", "ps_4_0");
    if (!vsBlob || !psBlob) return false;

    CHECK_HR(g_device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &g_vertexShader));
    CHECK_HR(g_device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), &g_pixelShader));

    // 创建输入布局 - D3D10 使用 D3D10_INPUT_ELEMENT_DESC
    D3D10_INPUT_ELEMENT_DESC inputLayoutDesc[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 },
    };

    CHECK_HR(g_device->CreateInputLayout(
        inputLayoutDesc,
        ARRAYSIZE(inputLayoutDesc),
        vsBlob->GetBufferPointer(),
        vsBlob->GetBufferSize(),
        &g_inputLayout
    ));

    vsBlob->Release();
    psBlob->Release();

    std::cout << "Shaders created successfully" << std::endl;
    return true;
}

// 渲染循环 - D3D10 版本
static void Render() {
    if (!g_device || !g_vertexBuffer) {
        std::cerr << "Missing render resources" << std::endl;
        return;
    }

    // 清屏为深灰色
    float clearColor[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    g_device->ClearRenderTargetView(g_renderTargetView, clearColor);

    // 设置输入布局
    g_device->IASetInputLayout(g_inputLayout);

    // 设置顶点缓冲区
    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    g_device->IASetVertexBuffers(0, 1, &g_vertexBuffer, &stride, &offset);
    g_device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // 设置着色器 - D3D10 不需要额外的参数
    g_device->VSSetShader(g_vertexShader);
    g_device->PSSetShader(g_pixelShader);

    // 设置纹理资源
    g_device->PSSetShaderResources(0, 1, &g_textureView);
    g_device->PSSetSamplers(0, 1, &g_samplerState);

    // 绘制三角形
    g_device->Draw(3, 0);

    // 呈现
    g_swapChain->Present(1, 0);

    static int frameCount = 0;
    frameCount++;
    if (frameCount % 60 == 0) {
        std::cout << "Rendered frame " << frameCount << std::endl;
    }
}

// 清理资源 - D3D10 版本
static void Cleanup() {
    std::cout << "Cleaning up..." << std::endl;

    if (g_vertexBuffer) { g_vertexBuffer->Release(); g_vertexBuffer = nullptr; }
    if (g_inputLayout) { g_inputLayout->Release(); g_inputLayout = nullptr; }
    if (g_vertexShader) { g_vertexShader->Release(); g_vertexShader = nullptr; }
    if (g_pixelShader) { g_pixelShader->Release(); g_pixelShader = nullptr; }
    if (g_textureView) { g_textureView->Release(); g_textureView = nullptr; }
    if (g_texture) { g_texture->Release(); g_texture = nullptr; }
    if (g_samplerState) { g_samplerState->Release(); g_samplerState = nullptr; }
    if (g_rasterizerState) { g_rasterizerState->Release(); g_rasterizerState = nullptr; }
    if (g_renderTargetView) { g_renderTargetView->Release(); g_renderTargetView = nullptr; }
    if (g_swapChain) { g_swapChain->Release(); g_swapChain = nullptr; }
    if (g_device) {
        // D3D10 没有内置的调试报告，直接释放
        g_device->Release();
        g_device = nullptr;
    }

    std::cout << "Cleanup complete" << std::endl;
}

// 主函数
int TestD3D10Texture2D(int argc, char **argv) {
    std::cout << "Starting D3D10 2D Texture Test..." << std::endl;
    std::cout << "Window size: " << WIDTH << "x" << HEIGHT << std::endl;

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "D3D10 2D Texture", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    std::cout << "Window created successfully" << std::endl;

    if (!InitD3D10(window)) {
        std::cerr << "Failed to initialize D3D10" << std::endl;
        Cleanup();
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    if (!CreateVertexBuffer()) {
        std::cerr << "Failed to create vertex buffer" << std::endl;
        Cleanup();
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    if (!Create2DTexture()) {
        std::cerr << "Failed to create 2D texture" << std::endl;
        Cleanup();
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    if (!CreateShaders()) {
        std::cerr << "Failed to create shaders" << std::endl;
        Cleanup();
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    std::cout << "All resources created successfully" << std::endl;
    std::cout << "Entering main loop..." << std::endl;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        Render();
    }

    std::cout << "Exiting main loop..." << std::endl;

    Cleanup();
    glfwDestroyWindow(window);
    glfwTerminate();

    std::cout << "Test completed successfully" << std::endl;
    return 0;
}
#endif