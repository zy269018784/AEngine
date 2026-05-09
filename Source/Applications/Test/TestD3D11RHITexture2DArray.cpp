#if  PROJECT_USE_D3D12
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

// D3D11 必需的头文件
#include <d3d11.h>
#include <dxgi1_4.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#include "D3D11Objects/Device/D3D11Device.h"
#include "D3D11Objects/Texture/D3D11Texture.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;

// 窗口尺寸
static const UINT WIDTH = 800;
static const UINT HEIGHT = 600;

// 纹理数组参数
static const UINT TEXTURE_COUNT = 3;
static const UINT TEXTURE_WIDTH = 64;
static const UINT TEXTURE_HEIGHT = 64;

// 全局 D3D11 对象
static ID3D11Device* g_device = nullptr;
static ID3D11DeviceContext* g_context = nullptr;
static IDXGISwapChain* g_swapChain = nullptr;
static ID3D11RenderTargetView* g_renderTargetView = nullptr;

// 纹理数组相关对象
static ID3D11Texture2D* g_textureArray = nullptr;
static ID3D11ShaderResourceView* g_textureArrayView = nullptr;
static ID3D11SamplerState* g_samplerState = nullptr;

// 渲染管线对象
static ID3D11VertexShader* g_vertexShader = nullptr;
static ID3D11PixelShader* g_pixelShader = nullptr;
static ID3D11InputLayout* g_inputLayout = nullptr;
static ID3D11Buffer* g_vertexBuffer = nullptr;
static D3D11Device* Device = nullptr;
static D3D11Texture* Texture = nullptr;
// 顶点结构
struct Vertex {
    DirectX::XMFLOAT3 position;  // 位置
    DirectX::XMFLOAT3 texcoord;  // xy: 纹理坐标, z: 纹理数组索引
};

// 检查 HRESULT 的辅助宏
#define CHECK_HR(hr) { if (FAILED(hr)) { std::cerr << "HRESULT failed at line " << __LINE__ << std::endl; return false; } }

// 创建纹理数组数据 - 3个纹理：红、绿、蓝，每个纹理带有渐变效果便于观察
static void CreateTextureArrayData(std::vector<uint8_t>& data) {
    data.resize(TEXTURE_WIDTH * TEXTURE_HEIGHT * 4 * TEXTURE_COUNT);

    for (UINT slice = 0; slice < TEXTURE_COUNT; ++slice) {
        for (UINT y = 0; y < TEXTURE_HEIGHT; ++y) {
            for (UINT x = 0; x < TEXTURE_WIDTH; ++x) {
                UINT index = (slice * TEXTURE_WIDTH * TEXTURE_HEIGHT + y * TEXTURE_WIDTH + x) * 4;

                // 根据纹理索引设置主色调，并添加渐变效果
                float nx = (float)x / (TEXTURE_WIDTH - 1);
                float ny = (float)y / (TEXTURE_HEIGHT - 1);

                switch(slice) {
                    case 0: // 红色纹理 - 红色渐变
                        data[index + 0] = (UINT8)(255);           // R 保持255
                        data[index + 1] = (UINT8)(nx * 255);      // G 渐变
                        data[index + 2] = (UINT8)(ny * 255);      // B 渐变
                        break;
                    case 1: // 绿色纹理 - 绿色渐变
                        data[index + 0] = (UINT8)(nx * 255);      // R 渐变
                        data[index + 1] = (UINT8)(255);           // G 保持255
                        data[index + 2] = (UINT8)(ny * 255);      // B 渐变
                        break;
                    case 2: // 蓝色纹理 - 蓝色渐变
                        data[index + 0] = (UINT8)(nx * 255);      // R 渐变
                        data[index + 1] = (UINT8)(ny * 255);      // G 渐变
                        data[index + 2] = (UINT8)(255);           // B 保持255
                        break;
                }
                data[index + 3] = 255;  // Alpha 始终为255
            }
        }
    }
    std::cout << "Texture array data created with gradients" << std::endl;
}

// 初始化 D3D11
static bool InitD3D11(GLFWwindow* window) {
    std::cout << "Initializing D3D11..." << std::endl;

    IDXGIFactory4* factory = nullptr;
    CHECK_HR(CreateDXGIFactory1(IID_PPV_ARGS(&factory)));

    UINT createDeviceFlags = 0;
#if defined(_DEBUG)
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_FEATURE_LEVEL featureLevels[] = {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0
    };
    D3D_FEATURE_LEVEL selectedFeatureLevel;

    CHECK_HR(D3D11CreateDevice(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        createDeviceFlags,
        featureLevels,
        ARRAYSIZE(featureLevels),
        D3D11_SDK_VERSION,
        &g_device,
        &selectedFeatureLevel,
        &g_context
    ));
    Device = new D3D11Device();
    Device->Handle = g_device;
    std::cout << "D3D11 device created" << std::endl;

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

    CHECK_HR(factory->CreateSwapChain(g_device, &swapChainDesc, &g_swapChain));

    ID3D11Texture2D* backBuffer = nullptr;
    CHECK_HR(g_swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer)));
    CHECK_HR(g_device->CreateRenderTargetView(backBuffer, nullptr, &g_renderTargetView));
    backBuffer->Release();

    factory->Release();

    std::cout << "D3D11 initialized successfully" << std::endl;
    return true;
}

// 创建顶点缓冲区 - 三个三角形，分别对应三个纹理索引
static bool CreateVertexBuffer() {
    std::cout << "Creating vertex buffer with 3 triangles..." << std::endl;

    // 创建三个三角形，分别对应红、绿、蓝纹理
    // 每个三角形使用不同的纹理数组索引 (0, 1, 2)
    Vertex vertices[] = {
        // 第一个三角形 (红色纹理, 索引0) - 左上角
        { { -0.8f, 0.6f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
        { { -0.4f, 0.6f, 0.0f }, { 1.0f, 0.0f, 0.0f } },
        { { -0.6f, 0.2f, 0.0f }, { 0.5f, 1.0f, 0.0f } },

        // 第二个三角形 (绿色纹理, 索引1) - 中间
        { { -0.3f, 0.1f, 0.0f }, { 0.0f, 0.0f, 1.0f } },
        { { 0.1f, 0.1f, 0.0f }, { 1.0f, 0.0f, 1.0f } },
        { { -0.1f, -0.3f, 0.0f }, { 0.5f, 1.0f, 1.0f } },

        // 第三个三角形 (蓝色纹理, 索引2) - 右下角
        { { 0.3f, -0.2f, 0.0f }, { 0.0f, 0.0f, 2.0f } },
        { { 0.7f, -0.2f, 0.0f }, { 1.0f, 0.0f, 2.0f } },
        { { 0.5f, -0.6f, 0.0f }, { 0.5f, 1.0f, 2.0f } }
    };

    std::cout << "Triangle vertices created with indices 0, 1, 2" << std::endl;

    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.ByteWidth = sizeof(vertices);
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = vertices;

    CHECK_HR(g_device->CreateBuffer(&bufferDesc, &initData, &g_vertexBuffer));
    std::cout << "Vertex buffer created" << std::endl;
    return true;
}

// 创建纹理数组
static bool CreateTextureArray() {
    std::cout << "Creating texture array..." << std::endl;

    std::vector<uint8_t> textureData;
    CreateTextureArrayData(textureData);

    D3D11_TEXTURE2D_DESC textureDesc = {};
    textureDesc.Width = TEXTURE_WIDTH;
    textureDesc.Height = TEXTURE_HEIGHT;
    textureDesc.MipLevels = 1;
    textureDesc.ArraySize = TEXTURE_COUNT;
    textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    textureDesc.SampleDesc.Count = 1;
    textureDesc.SampleDesc.Quality = 0;
    textureDesc.Usage = D3D11_USAGE_DEFAULT;
    textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

    std::vector<D3D11_SUBRESOURCE_DATA> initData(TEXTURE_COUNT);
    for (UINT i = 0; i < TEXTURE_COUNT; ++i) {
        initData[i].pSysMem = textureData.data() + (i * TEXTURE_WIDTH * TEXTURE_HEIGHT * 4);
        initData[i].SysMemPitch = TEXTURE_WIDTH * 4;
        initData[i].SysMemSlicePitch = initData[i].SysMemPitch * TEXTURE_HEIGHT;
    }
#if 0
    CHECK_HR(g_device->CreateTexture2D(&textureDesc, initData.data(), &g_textureArray));
#else
    Texture = new D3D11Texture(Device, RHITextureType::Texture2DArray, RHIPixelFormat::PF_R8G8B8A8_UNORM, 1, TEXTURE_WIDTH, TEXTURE_HEIGHT, 1, 3, textureData.data());
    g_textureArray = (ID3D11Texture2D*)Texture->Handle;
#endif
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Format = textureDesc.Format;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
    srvDesc.Texture2DArray.MipLevels = 1;
    srvDesc.Texture2DArray.ArraySize = TEXTURE_COUNT;
    srvDesc.Texture2DArray.FirstArraySlice = 0;

    CHECK_HR(g_device->CreateShaderResourceView(g_textureArray, &srvDesc, &g_textureArrayView));

    D3D11_SAMPLER_DESC samplerDesc = {};
    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    samplerDesc.MinLOD = 0;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

    CHECK_HR(g_device->CreateSamplerState(&samplerDesc, &g_samplerState));

    std::cout << "Texture array created with " << TEXTURE_COUNT << " slices" << std::endl;
    return true;
}

// 编译着色器
static ID3DBlob* CompileShader(const std::string& source, const std::string& entrypoint, const std::string& target) {
    ID3DBlob* shaderBlob = nullptr;
    ID3DBlob* errorBlob = nullptr;

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

// 创建着色器
static bool CreateShaders() {
    std::cout << "Creating shaders..." << std::endl;

    const char* vsSource = R"(
        struct VSInput {
            float4 position : POSITION;
            float3 texcoord : TEXCOORD;
        };
        struct VSOutput {
            float4 position : SV_POSITION;
            float2 uv : TEXCOORD0;
            uint arrayIndex : TEXCOORD1;
        };
        VSOutput main(VSInput input) {
            VSOutput output;
            output.position = input.position;
            output.uv = input.texcoord.xy;
            output.arrayIndex = (uint)input.texcoord.z;
            return output;
        }
    )";

    const char* psSource = R"(
        Texture2DArray g_textureArray : register(t0);
        SamplerState g_sampler : register(s0);
        struct PSInput {
            float4 position : SV_POSITION;
            float2 uv : TEXCOORD0;
            uint arrayIndex : TEXCOORD1;
        };
        float4 main(PSInput input) : SV_TARGET {
            // 从纹理数组采样，使用输入的数组索引
            float3 texcoord = float3(input.uv, input.arrayIndex);
            return g_textureArray.Sample(g_sampler, texcoord);
        }
    )";

    ID3DBlob* vsBlob = CompileShader(vsSource, "main", "vs_5_0");
    ID3DBlob* psBlob = CompileShader(psSource, "main", "ps_5_0");
    if (!vsBlob || !psBlob) return false;

    CHECK_HR(g_device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, &g_vertexShader));
    CHECK_HR(g_device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, &g_pixelShader));

    D3D11_INPUT_ELEMENT_DESC inputLayoutDesc[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
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

// 渲染循环
static void Render() {
    if (!g_context || !g_vertexBuffer) {
        std::cerr << "Missing render resources" << std::endl;
        return;
    }

    // 设置渲染目标
    g_context->OMSetRenderTargets(1, &g_renderTargetView, nullptr);

    // 清屏为深灰色
    float clearColor[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    g_context->ClearRenderTargetView(g_renderTargetView, clearColor);

    // 设置视口
    D3D11_VIEWPORT viewport = { 0, 0, WIDTH, HEIGHT, 0, 1 };
    g_context->RSSetViewports(1, &viewport);

    // 设置着色器
    g_context->VSSetShader(g_vertexShader, nullptr, 0);
    g_context->PSSetShader(g_pixelShader, nullptr, 0);

    // 设置输入布局
    g_context->IASetInputLayout(g_inputLayout);

    // 设置顶点缓冲区
    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    g_context->IASetVertexBuffers(0, 1, &g_vertexBuffer, &stride, &offset);
    g_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // 设置纹理资源
    g_context->PSSetShaderResources(0, 1, &g_textureArrayView);
    g_context->PSSetSamplers(0, 1, &g_samplerState);

    // 绘制三个三角形（共9个顶点）
    g_context->Draw(9, 0);

    // 呈现
    g_swapChain->Present(1, 0);

    static int frameCount = 0;
    frameCount++;
    if (frameCount % 60 == 0) {
        std::cout << "Rendered frame " << frameCount << std::endl;
    }
}

// 清理资源
static void Cleanup() {
    std::cout << "Cleaning up..." << std::endl;

    if (g_vertexBuffer) { g_vertexBuffer->Release(); g_vertexBuffer = nullptr; }
    if (g_inputLayout) { g_inputLayout->Release(); g_inputLayout = nullptr; }
    if (g_vertexShader) { g_vertexShader->Release(); g_vertexShader = nullptr; }
    if (g_pixelShader) { g_pixelShader->Release(); g_pixelShader = nullptr; }
    if (g_textureArrayView) { g_textureArrayView->Release(); g_textureArrayView = nullptr; }
    if (g_textureArray) { g_textureArray->Release(); g_textureArray = nullptr; }
    if (g_samplerState) { g_samplerState->Release(); g_samplerState = nullptr; }
    if (g_renderTargetView) { g_renderTargetView->Release(); g_renderTargetView = nullptr; }
    if (g_swapChain) { g_swapChain->Release(); g_swapChain = nullptr; }
    if (g_context) { g_context->Release(); g_context = nullptr; }
    if (g_device) {
#if defined(_DEBUG)
        ID3D11Debug* debugDevice = nullptr;
        if (SUCCEEDED(g_device->QueryInterface(IID_PPV_ARGS(&debugDevice)))) {
            debugDevice->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
            debugDevice->Release();
        }
#endif
        g_device->Release();
        g_device = nullptr;
    }

    std::cout << "Cleanup complete" << std::endl;
}

// 主函数
int TestD3D11RHITexture2DArray(int argc, char **argv)
{
    std::cout << "Starting D3D11 Texture2D Array Test..." << std::endl;
    std::cout << "Window size: " << WIDTH << "x" << HEIGHT << std::endl;

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "D3D11 Texture Array - RGB Triangles", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    std::cout << "Window created successfully" << std::endl;

    if (!InitD3D11(window)) {
        std::cerr << "Failed to initialize D3D11" << std::endl;
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

    if (!CreateTextureArray()) {
        std::cerr << "Failed to create texture array" << std::endl;
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