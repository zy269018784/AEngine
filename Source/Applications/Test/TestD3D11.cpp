#ifdef PROJECT_USE_D3D12
#include <iostream>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <wrl/client.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "glfw3.lib")

using namespace DirectX;
using namespace Microsoft::WRL;

// 全局变量
ComPtr<ID3D11Device>        g_pDevice = nullptr;
ComPtr<ID3D11DeviceContext> g_pContext = nullptr;
ComPtr<IDXGISwapChain>      g_pSwapChain = nullptr;
ComPtr<ID3D11RenderTargetView> g_pRenderTargetView = nullptr;
ComPtr<ID3D11VertexShader>  g_pVertexShader = nullptr;
ComPtr<ID3D11PixelShader>   g_pPixelShader = nullptr;
ComPtr<ID3D11InputLayout>   g_pInputLayout = nullptr;
ComPtr<ID3D11Buffer>        g_pVertexBuffer = nullptr;

// 顶点结构
struct Vertex
{
    XMFLOAT3 position;
    XMFLOAT4 color;
};

// 着色器代码
const char* vertexShaderCode = R"(
struct VS_INPUT
{
    float3 pos : POSITION;
    float4 color : COLOR;
};

struct PS_INPUT
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
};

PS_INPUT main(VS_INPUT input)
{
    PS_INPUT output;
    output.pos = float4(input.pos, 1.0);
    output.color = input.color;
    return output;
}
)";

const char* pixelShaderCode = R"(
struct PS_INPUT
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
};

float4 main(PS_INPUT input) : SV_TARGET
{
    return input.color;
}
)";

// 编译着色器
HRESULT CompileShader(const char* source, const char* entryPoint,
                     const char* target, ID3DBlob** blob)
{
    ComPtr<ID3DBlob> errorBlob;

    HRESULT hr = D3DCompile(
        source,
        strlen(source),
        nullptr,
        nullptr,
        nullptr,
        entryPoint,
        target,
        D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
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

// 初始化 D3D11
bool InitD3D11(GLFWwindow* window, int width, int height)
{
    HRESULT hr;

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

    D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };

    hr = D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        D3D11_CREATE_DEVICE_DEBUG, // 调试标志
        featureLevels,
        1,
        D3D11_SDK_VERSION,
        &swapChainDesc,
        &g_pSwapChain,
        &g_pDevice,
        nullptr,
        &g_pContext
    );

    if (FAILED(hr))
    {
        std::cerr << "Failed to create D3D11 device and swap chain: " << hr << std::endl;
        return false;
    }

    // 2. 创建渲染目标视图
    ComPtr<ID3D11Texture2D> backBuffer;
    hr = g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
    if (FAILED(hr))
    {
        std::cerr << "Failed to get back buffer: " << hr << std::endl;
        return false;
    }

    hr = g_pDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, &g_pRenderTargetView);
    if (FAILED(hr))
    {
        std::cerr << "Failed to create render target view: " << hr << std::endl;
        return false;
    }

    g_pContext->OMSetRenderTargets(1, g_pRenderTargetView.GetAddressOf(), nullptr);

    // 3. 设置视口
    D3D11_VIEWPORT viewport = {};
    viewport.Width = static_cast<float>(width);
    viewport.Height = static_cast<float>(height);
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    g_pContext->RSSetViewports(1, &viewport);

    return true;
}

// 创建着色器
bool CreateShaders()
{
    HRESULT hr;

    // 编译顶点着色器
    ComPtr<ID3DBlob> vsBlob;
    hr = CompileShader(vertexShaderCode, "main", "vs_5_0", &vsBlob);
    if (FAILED(hr)) return false;

    hr = g_pDevice->CreateVertexShader(
        vsBlob->GetBufferPointer(),
        vsBlob->GetBufferSize(),
        nullptr,
        &g_pVertexShader
    );
    if (FAILED(hr)) return false;

    // 编译像素着色器
    ComPtr<ID3DBlob> psBlob;
    hr = CompileShader(pixelShaderCode, "main", "ps_5_0", &psBlob);
    if (FAILED(hr)) return false;

    hr = g_pDevice->CreatePixelShader(
        psBlob->GetBufferPointer(),
        psBlob->GetBufferSize(),
        nullptr,
        &g_pPixelShader
    );
    if (FAILED(hr)) return false;

    // 创建输入布局
    D3D11_INPUT_ELEMENT_DESC layout[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };

    hr = g_pDevice->CreateInputLayout(
        layout,
        2,
        vsBlob->GetBufferPointer(),
        vsBlob->GetBufferSize(),
        &g_pInputLayout
    );
    if (FAILED(hr)) return false;

    return true;
}

// 创建顶点缓冲区
bool CreateVertexBuffer()
{
    // 定义三角形的三个顶点
    Vertex vertices[] = {
        // 位置                   // 颜色
        { XMFLOAT3(0.0f, 0.5f, 0.0f),  XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },   // 顶点1: 红色
        { XMFLOAT3(0.5f, -0.5f, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },   // 顶点2: 绿色
        { XMFLOAT3(-0.5f, -0.5f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) }   // 顶点3: 蓝色
    };

    // 创建顶点缓冲区描述
    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.ByteWidth = sizeof(vertices);
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bufferDesc.CPUAccessFlags = 0;
    bufferDesc.MiscFlags = 0;
    bufferDesc.StructureByteStride = 0;

    // 创建初始化数据
    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = vertices;
    initData.SysMemPitch = 0;
    initData.SysMemSlicePitch = 0;

    // 创建顶点缓冲区
    HRESULT hr = g_pDevice->CreateBuffer(&bufferDesc, &initData, &g_pVertexBuffer);
    if (FAILED(hr))
    {
        std::cerr << "Failed to create vertex buffer: " << hr << std::endl;
        return false;
    }

    return true;
}

// 渲染函数
void D3D11Render()
{
    // 1. 清除渲染目标
    float clearColor[4] = { 0.2f, 0.3f, 0.4f, 1.0f }; // 深蓝色背景
    g_pContext->ClearRenderTargetView(g_pRenderTargetView.Get(), clearColor);

    // 2. 设置顶点缓冲区
    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    g_pContext->IASetVertexBuffers(0, 1, g_pVertexBuffer.GetAddressOf(), &stride, &offset);

    // 3. 设置图元拓扑
    g_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // 4. 设置输入布局
    g_pContext->IASetInputLayout(g_pInputLayout.Get());

    // 5. 设置着色器
    g_pContext->VSSetShader(g_pVertexShader.Get(), nullptr, 0);
    g_pContext->PSSetShader(g_pPixelShader.Get(), nullptr, 0);

    // 6. 绘制三角形
    g_pContext->Draw(3, 0);

    // 7. 呈现到屏幕
    g_pSwapChain->Present(1, 0); // 垂直同步
}

// 清理资源
void D3D11Cleanup()
{
    // ComPtr 会自动释放资源，但可以显式重置
    g_pVertexBuffer.Reset();
    g_pInputLayout.Reset();
    g_pPixelShader.Reset();
    g_pVertexShader.Reset();
    g_pRenderTargetView.Reset();
    g_pSwapChain.Reset();
    g_pContext.Reset();
    g_pDevice.Reset();
}

// 主函数
int TestD3D11(int argc, char **argv)
{
    // 1. 初始化 GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // 2. 创建 GLFW 窗口
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // 不使用 OpenGL
    GLFWwindow* window = glfwCreateWindow(800, 600, "D3D11 + GLFW Triangle", nullptr, nullptr);

    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // 3. 初始化 D3D11
    if (!InitD3D11(window, 800, 600))
    {
        std::cerr << "Failed to initialize D3D11" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    // 4. 创建着色器
    if (!CreateShaders())
    {
        std::cerr << "Failed to create shaders" << std::endl;
        D3D11Cleanup();
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    // 5. 创建顶点缓冲区
    if (!CreateVertexBuffer())
    {
        std::cerr << "Failed to create vertex buffer" << std::endl;
        D3D11Cleanup();
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    std::cout << "D3D11 + GLFW Triangle Example" << std::endl;
    std::cout << "Press ESC to exit" << std::endl;

    // 6. 主渲染循环
    while (!glfwWindowShouldClose(window))
    {
        // 处理事件
        glfwPollEvents();

        // 检查 ESC 键
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }

        // 渲染
        D3D11Render();
    }

    // 7. 清理
    D3D11Cleanup();
    glfwDestroyWindow(window);
    glfwTerminate();

    std::cout << "Application terminated successfully" << std::endl;
    return 0;
}
#endif