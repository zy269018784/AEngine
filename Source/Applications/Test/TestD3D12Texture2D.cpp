#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

// D3D12 必需的头文件
#include <d3d12.h>
#include <dxgi1_4.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

// 关键：D3DX12 辅助库 - 定义了 CD3DX12_* 辅助类
#include <d3dx12.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;

// 窗口尺寸
const UINT WIDTH = 800;
const UINT HEIGHT = 600;

// 帧缓冲区计数（双缓冲）
const UINT FRAME_COUNT = 2;

// 全局 D3D12 对象
ID3D12Device* g_device = nullptr;
ID3D12CommandQueue* g_commandQueue = nullptr;
IDXGISwapChain3* g_swapChain = nullptr;
ID3D12DescriptorHeap* g_rtvHeap = nullptr;
ID3D12Resource* g_renderTargets[FRAME_COUNT] = {};
ID3D12CommandAllocator* g_commandAllocator[FRAME_COUNT] = {};
ID3D12GraphicsCommandList* g_commandList = nullptr;
ID3D12Fence* g_fence = nullptr;
UINT64 g_fenceValue[FRAME_COUNT] = {};
HANDLE g_fenceEvent = nullptr;
UINT g_rtvDescriptorSize = 0;
UINT g_frameIndex = 0;

// 纹理相关对象
ID3D12DescriptorHeap* g_srvHeap = nullptr;
ID3D12Resource* g_texture = nullptr;

// 渲染管线对象
ID3D12RootSignature* g_rootSignature = nullptr;
ID3D12PipelineState* g_pipelineState = nullptr;

// 顶点缓冲区对象 - 改为全局变量，避免每帧创建
ID3D12Resource* g_vertexBuffer = nullptr;
D3D12_VERTEX_BUFFER_VIEW g_vertexBufferView = {};

// 顶点结构
struct Vertex {
    DirectX::XMFLOAT3 position;
    DirectX::XMFLOAT2 texcoord;
};

// 简单的 4x4 纹理数据（RGBA，每个通道 8 位）
void CreateTextureData(std::vector<uint8_t>& data) {
    const UINT texWidth = 4;
    const UINT texHeight = 4;
    data.resize(texWidth * texHeight * 4);

    // 创建一个简单的棋盘格图案
    for (UINT y = 0; y < texHeight; ++y) {
        for (UINT x = 0; x < texWidth; ++x) {
            UINT index = (y * texWidth + x) * 4;

            // 棋盘格：如果 (x+y) 是偶数，设置为红色，否则设置为绿色
            if ((x + y) % 2 == 0) {
                data[index + 0] = 255;  // R
                data[index + 1] = 0;    // G
                data[index + 2] = 0;    // B
            } else {
                data[index + 0] = 0;    // R
                data[index + 1] = 255;  // G
                data[index + 2] = 0;    // B
            }
            data[index + 3] = 255;       // A
        }
    }

    // 打印纹理数据以便验证
    std::cout << "Texture data created:" << std::endl;
    for (UINT y = 0; y < texHeight; ++y) {
        for (UINT x = 0; x < texWidth; ++x) {
            UINT index = (y * texWidth + x) * 4;
            std::cout << "(" << (int)data[index] << ","
                      << (int)data[index+1] << ","
                      << (int)data[index+2] << ","
                      << (int)data[index+3] << ") ";
        }
        std::cout << std::endl;
    }
}

// 检查 HRESULT 的辅助宏
#define CHECK_HR(hr) { if (FAILED(hr)) { std::cerr << "HRESULT failed at line " << __LINE__ << std::endl; return false; } }
#define CHECK_HR_VOID(hr) { if (FAILED(hr)) { std::cerr << "HRESULT failed at line " << __LINE__ << std::endl; return; } }

// 初始化 D3D12 设备
bool InitD3D12(GLFWwindow* window) {
    // 启用 D3D12 调试层
#if defined(_DEBUG)
    ID3D12Debug* debugController = nullptr;
    if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
        debugController->EnableDebugLayer();
        debugController->Release();
        std::cout << "D3D12 Debug Layer enabled" << std::endl;
    }
#endif

    IDXGIFactory4* factory = nullptr;
    CHECK_HR(CreateDXGIFactory1(IID_PPV_ARGS(&factory)));

    // 创建 D3D12 设备
    CHECK_HR(D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&g_device)));

    // 2. 创建命令队列
    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    CHECK_HR(g_device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&g_commandQueue)));

    // 3. 创建交换链
    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
    swapChainDesc.BufferCount = FRAME_COUNT;
    swapChainDesc.Width = WIDTH;
    swapChainDesc.Height = HEIGHT;
    swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapChainDesc.SampleDesc.Count = 1;

    IDXGISwapChain1* tempSwapChain = nullptr;
    CHECK_HR(factory->CreateSwapChainForHwnd(
        g_commandQueue,
        glfwGetWin32Window(window),
        &swapChainDesc,
        nullptr,
        nullptr,
        &tempSwapChain
    ));

    g_swapChain = (IDXGISwapChain3*)tempSwapChain;
    g_frameIndex = g_swapChain->GetCurrentBackBufferIndex();

    // 4. 创建 RTV 描述符堆
    D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
    rtvHeapDesc.NumDescriptors = FRAME_COUNT;
    rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    CHECK_HR(g_device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&g_rtvHeap)));
    g_rtvDescriptorSize = g_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

    // 5. 创建 RTV（每个后备缓冲区的视图）
    D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = g_rtvHeap->GetCPUDescriptorHandleForHeapStart();
    for (UINT i = 0; i < FRAME_COUNT; ++i) {
        CHECK_HR(g_swapChain->GetBuffer(i, IID_PPV_ARGS(&g_renderTargets[i])));
        g_device->CreateRenderTargetView(g_renderTargets[i], nullptr, rtvHandle);
        rtvHandle.ptr += g_rtvDescriptorSize;
    }

    // 6. 创建命令分配器和命令列表
    for (UINT i = 0; i < FRAME_COUNT; ++i) {
        CHECK_HR(g_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&g_commandAllocator[i])));
    }
    CHECK_HR(g_device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, g_commandAllocator[0], nullptr, IID_PPV_ARGS(&g_commandList)));
    CHECK_HR(g_commandList->Close());

    // 7. 创建同步对象
    CHECK_HR(g_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&g_fence)));
    g_fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
    if (!g_fenceEvent) {
        std::cerr << "Failed to create fence event" << std::endl;
        return false;
    }

    factory->Release();
    return true;
}

// 创建顶点缓冲区 - 新增函数
static bool CreateVertexBuffer() {
    // 全屏三角形的三个顶点
    Vertex triangleVertices[] = {
        { { -1.0f, -1.0f, 0.0f }, { 0.0f, 1.0f } },
        { { 3.0f, -1.0f, 0.0f }, { 2.0f, 1.0f } },
        { { -1.0f, 3.0f, 0.0f }, { 0.0f, -1.0f } }
    };

    UINT vertexBufferSize = sizeof(triangleVertices);

    // 创建上传堆
    CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_UPLOAD);
    CD3DX12_RESOURCE_DESC bufferDesc = CD3DX12_RESOURCE_DESC::Buffer(vertexBufferSize);

    HRESULT hr = g_device->CreateCommittedResource(
        &heapProps,
        D3D12_HEAP_FLAG_NONE,
        &bufferDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&g_vertexBuffer)
    );

    if (FAILED(hr) || !g_vertexBuffer) {
        std::cerr << "Failed to create vertex buffer" << std::endl;
        return false;
    }

    // 复制顶点数据
    UINT8* pVertexDataBegin = nullptr;
    CD3DX12_RANGE readRange(0, 0);
    hr = g_vertexBuffer->Map(0, &readRange, reinterpret_cast<void**>(&pVertexDataBegin));
    if (FAILED(hr)) {
        std::cerr << "Failed to map vertex buffer" << std::endl;
        g_vertexBuffer->Release();
        g_vertexBuffer = nullptr;
        return false;
    }

    memcpy(pVertexDataBegin, triangleVertices, vertexBufferSize);
    g_vertexBuffer->Unmap(0, nullptr);

    // 初始化顶点缓冲区视图
    g_vertexBufferView.BufferLocation = g_vertexBuffer->GetGPUVirtualAddress();
    g_vertexBufferView.StrideInBytes = sizeof(Vertex);
    g_vertexBufferView.SizeInBytes = vertexBufferSize;

    std::cout << "Vertex buffer created successfully" << std::endl;
    return true;
}

// 创建纹理和 SRV 描述符堆
bool CreateTextureAndSRV() {
    // 1. 创建 SRV 描述符堆（用于着色器访问纹理）
    D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
    srvHeapDesc.NumDescriptors = 1;
    srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    CHECK_HR(g_device->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&g_srvHeap)));

    // 2. 生成纹理数据
    std::vector<uint8_t> textureData;
    CreateTextureData(textureData);
    const UINT texWidth = 4;
    const UINT texHeight = 4;

    // 3. 创建纹理资源
    D3D12_RESOURCE_DESC textureDesc = {};
    textureDesc.MipLevels = 1;
    textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    textureDesc.Width = texWidth;
    textureDesc.Height = texHeight;
    textureDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
    textureDesc.DepthOrArraySize = 1;
    textureDesc.SampleDesc.Count = 1;
    textureDesc.SampleDesc.Quality = 0;
    textureDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;

    CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_DEFAULT);
    CHECK_HR(g_device->CreateCommittedResource(
        &heapProps,
        D3D12_HEAP_FLAG_NONE,
        &textureDesc,
        D3D12_RESOURCE_STATE_COPY_DEST,
        nullptr,
        IID_PPV_ARGS(&g_texture)
    ));

    // 4. 创建上传堆并将数据上传到纹理
    UINT64 uploadBufferSize = GetRequiredIntermediateSize(g_texture, 0, 1);
    ID3D12Resource* textureUploadHeap = nullptr;
    CD3DX12_HEAP_PROPERTIES uploadHeapProps(D3D12_HEAP_TYPE_UPLOAD);
    CD3DX12_RESOURCE_DESC bufferDesc = CD3DX12_RESOURCE_DESC::Buffer(uploadBufferSize);
    CHECK_HR(g_device->CreateCommittedResource(
        &uploadHeapProps,
        D3D12_HEAP_FLAG_NONE,
        &bufferDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&textureUploadHeap)
    ));

    // 记录上传命令
    CHECK_HR(g_commandAllocator[g_frameIndex]->Reset());
    CHECK_HR(g_commandList->Reset(g_commandAllocator[g_frameIndex], nullptr));

    D3D12_SUBRESOURCE_DATA textureSubData = {};
    textureSubData.pData = textureData.data();
    textureSubData.RowPitch = texWidth * 4;
    textureSubData.SlicePitch = textureSubData.RowPitch * texHeight;

    UpdateSubresources(g_commandList, g_texture, textureUploadHeap, 0, 0, 1, &textureSubData);

    CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
        g_texture,
        D3D12_RESOURCE_STATE_COPY_DEST,
        D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE
    );
    g_commandList->ResourceBarrier(1, &barrier);

    CHECK_HR(g_commandList->Close());

    // 执行命令列表
    ID3D12CommandList* commandLists[] = { g_commandList };
    g_commandQueue->ExecuteCommandLists(1, commandLists);

    // 等待上传完成
    CHECK_HR(g_commandQueue->Signal(g_fence, 1));
    g_fence->SetEventOnCompletion(1, g_fenceEvent);
    WaitForSingleObject(g_fenceEvent, INFINITE);

    textureUploadHeap->Release();

    // 5. 创建 SRV（着色器资源视图）
    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    srvDesc.Format = textureDesc.Format;
    srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = 1;
    g_device->CreateShaderResourceView(g_texture, &srvDesc, g_srvHeap->GetCPUDescriptorHandleForHeapStart());

    // 添加调试输出
    std::cout << "Texture created successfully" << std::endl;
    std::cout << "Texture format: " << textureDesc.Format << std::endl;
    std::cout << "Texture size: " << texWidth << "x" << texHeight << std::endl;

    return true;
}

// 编译着色器
ID3DBlob* CompileShader(const std::string& source, const std::string& entrypoint, const std::string& target) {
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

// 创建根签名和 PSO
bool CreatePipeline() {
    // 1. 创建根签名
    CD3DX12_DESCRIPTOR_RANGE range;
    range.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);

    CD3DX12_ROOT_PARAMETER rootParam;
    rootParam.InitAsDescriptorTable(1, &range, D3D12_SHADER_VISIBILITY_PIXEL);

    // 创建静态采样器 - 确保寄存器匹配
    CD3DX12_STATIC_SAMPLER_DESC samplerDesc;
    samplerDesc.Init(
        0,                                  // shader register
        D3D12_FILTER_MIN_MAG_MIP_LINEAR,    // filter
        D3D12_TEXTURE_ADDRESS_MODE_CLAMP,   // addressU
        D3D12_TEXTURE_ADDRESS_MODE_CLAMP,   // addressV
        D3D12_TEXTURE_ADDRESS_MODE_CLAMP    // addressW
    );

    CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc;
    rootSigDesc.Init(1, &rootParam, 1, &samplerDesc,
                     D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

    ID3DBlob* signature = nullptr;
    ID3DBlob* error = nullptr;
    HRESULT hr = D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1,
                                              &signature, &error);
    if (FAILED(hr)) {
        if (error) {
            std::cerr << "Root signature serialization error: "
                      << (char*)error->GetBufferPointer() << std::endl;
            error->Release();
        }
        return false;
    }

    hr = g_device->CreateRootSignature(0, signature->GetBufferPointer(),
                                        signature->GetBufferSize(),
                                        IID_PPV_ARGS(&g_rootSignature));
    signature->Release();
    if (error) error->Release();

    if (FAILED(hr)) {
        std::cerr << "Failed to create root signature" << std::endl;
        return false;
    }

    // 2. 定义顶点布局
    D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
    };

    // 3. 编译着色器
    // 顶点着色器
    const char* vsSource = R"(
        struct VSInput {
            float4 position : POSITION;
            float2 texcoord : TEXCOORD;
        };
        struct VSOutput {
            float4 position : SV_POSITION;
            float2 texcoord : TEXCOORD;
        };
        VSOutput main(VSInput input) {
            VSOutput output;
            output.position = input.position;
            output.texcoord = input.texcoord;
            return output;
        }
    )";

    // 像素着色器 - 使用纹理采样
    const char* psSource = R"(
        Texture2D g_texture : register(t0);
        SamplerState g_sampler : register(s0);
        struct PSInput {
            float4 position : SV_POSITION;
            float2 texcoord : TEXCOORD;
        };
        float4 main(PSInput input) : SV_TARGET {
            return g_texture.Sample(g_sampler, input.texcoord);
        }
    )";

    ID3DBlob* vsBlob = CompileShader(vsSource, "main", "vs_5_0");
    ID3DBlob* psBlob = CompileShader(psSource, "main", "ps_5_0");
    if (!vsBlob || !psBlob) return false;

    // 4. 创建 PSO
    D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
    psoDesc.InputLayout = { inputLayout, 2 };
    psoDesc.pRootSignature = g_rootSignature;
    psoDesc.VS = { reinterpret_cast<BYTE*>(vsBlob->GetBufferPointer()), vsBlob->GetBufferSize() };
    psoDesc.PS = { reinterpret_cast<BYTE*>(psBlob->GetBufferPointer()), psBlob->GetBufferSize() };
    psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
    psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
    psoDesc.DepthStencilState.DepthEnable = FALSE;
    psoDesc.DepthStencilState.StencilEnable = FALSE;
    psoDesc.SampleMask = UINT_MAX;
    psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    psoDesc.NumRenderTargets = 1;
    psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
    psoDesc.SampleDesc.Count = 1;

    CHECK_HR(g_device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&g_pipelineState)));

    if (vsBlob) vsBlob->Release();
    if (psBlob) psBlob->Release();

    std::cout << "Pipeline created successfully" << std::endl;
    return true;
}

// 等待 GPU 完成当前帧
void WaitForPreviousFrame() {
    if (!g_commandQueue || !g_fence) return;

    const UINT64 fenceValue = g_fenceValue[g_frameIndex];

    // 提交信号
    HRESULT hr = g_commandQueue->Signal(g_fence, fenceValue);
    if (FAILED(hr)) return;

    // 等待完成
    if (g_fence->GetCompletedValue() < fenceValue) {
        hr = g_fence->SetEventOnCompletion(fenceValue, g_fenceEvent);
        if (SUCCEEDED(hr)) {
            WaitForSingleObject(g_fenceEvent, INFINITE);
        }
    }

    g_fenceValue[g_frameIndex] = fenceValue + 1;
}

// 渲染循环
void TestD3D12Texture2DRender() {
    if (!g_commandAllocator[g_frameIndex] || !g_commandList || !g_pipelineState || !g_vertexBuffer) {
        std::cerr << "Missing required resources for rendering" << std::endl;
        return;
    }

    // 获取当前帧的分配器
    HRESULT hr = g_commandAllocator[g_frameIndex]->Reset();
    if (FAILED(hr)) {
        std::cerr << "Failed to reset command allocator" << std::endl;
        return;
    }

    hr = g_commandList->Reset(g_commandAllocator[g_frameIndex], g_pipelineState);
    if (FAILED(hr)) {
        std::cerr << "Failed to reset command list" << std::endl;
        return;
    }

    // 确保纹理处于正确的状态
    CD3DX12_RESOURCE_BARRIER textureBarrier = CD3DX12_RESOURCE_BARRIER::Transition(
        g_texture,
        D3D12_RESOURCE_STATE_COPY_DEST,
        D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE
    );
    g_commandList->ResourceBarrier(1, &textureBarrier);

    // 将渲染目标从呈现状态转换为渲染目标状态
    CD3DX12_RESOURCE_BARRIER rtBarrier = CD3DX12_RESOURCE_BARRIER::Transition(
        g_renderTargets[g_frameIndex],
        D3D12_RESOURCE_STATE_PRESENT,
        D3D12_RESOURCE_STATE_RENDER_TARGET
    );
    g_commandList->ResourceBarrier(1, &rtBarrier);

    // 设置渲染目标
    CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(
        g_rtvHeap->GetCPUDescriptorHandleForHeapStart(),
        g_frameIndex,
        g_rtvDescriptorSize
    );
    g_commandList->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);

    // 清屏为深蓝色背景
    const float clearColor[] = { 0.1f, 0.2f, 0.4f, 1.0f };
    g_commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);

    // 设置视口和裁剪矩形
    D3D12_VIEWPORT viewport = { 0, 0, static_cast<float>(WIDTH), static_cast<float>(HEIGHT), 0, 1 };
    D3D12_RECT scissorRect = { 0, 0, static_cast<LONG>(WIDTH), static_cast<LONG>(HEIGHT) };
    g_commandList->RSSetViewports(1, &viewport);
    g_commandList->RSSetScissorRects(1, &scissorRect);

    // 设置根签名和描述符堆
    g_commandList->SetGraphicsRootSignature(g_rootSignature);
    ID3D12DescriptorHeap* heaps[] = { g_srvHeap };
    g_commandList->SetDescriptorHeaps(1, heaps);

    CD3DX12_GPU_DESCRIPTOR_HANDLE srvHandle(g_srvHeap->GetGPUDescriptorHandleForHeapStart());
    g_commandList->SetGraphicsRootDescriptorTable(0, srvHandle);

    // 设置顶点缓冲区
    g_commandList->IASetVertexBuffers(0, 1, &g_vertexBufferView);
    g_commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    g_commandList->DrawInstanced(3, 1, 0, 0);

    static int frameCount = 0;
    frameCount++;
    if (frameCount % 60 == 0) {
        std::cout << "Rendered frame " << frameCount << std::endl;
    }

    // 准备呈现
    CD3DX12_RESOURCE_BARRIER presentBarrier = CD3DX12_RESOURCE_BARRIER::Transition(
        g_renderTargets[g_frameIndex],
        D3D12_RESOURCE_STATE_RENDER_TARGET,
        D3D12_RESOURCE_STATE_PRESENT
    );
    g_commandList->ResourceBarrier(1, &presentBarrier);

    hr = g_commandList->Close();
    if (FAILED(hr)) {
        std::cerr << "Failed to close command list" << std::endl;
        return;
    }

    // 执行命令列表
    ID3D12CommandList* commandLists[] = { g_commandList };
    g_commandQueue->ExecuteCommandLists(1, commandLists);

    // 呈现
    g_swapChain->Present(1, 0);

    // 等待 GPU
    WaitForPreviousFrame();

    // 更新帧索引
    g_frameIndex = g_swapChain->GetCurrentBackBufferIndex();
}

// 清理资源
void TestD3D12Texture2DCleanup() {
    std::cout << "Cleaning up resources..." << std::endl;

    WaitForPreviousFrame();

    // 释放顶点缓冲区
    if (g_vertexBuffer) {
        g_vertexBuffer->Release();
        g_vertexBuffer = nullptr;
    }

    // 释放所有 COM 对象
    for (UINT i = 0; i < FRAME_COUNT; ++i) {
        if (g_renderTargets[i]) {
            g_renderTargets[i]->Release();
            g_renderTargets[i] = nullptr;
        }
        if (g_commandAllocator[i]) {
            g_commandAllocator[i]->Release();
            g_commandAllocator[i] = nullptr;
        }
    }

    if (g_texture) {
        g_texture->Release();
        g_texture = nullptr;
    }
    if (g_srvHeap) {
        g_srvHeap->Release();
        g_srvHeap = nullptr;
    }
    if (g_rootSignature) {
        g_rootSignature->Release();
        g_rootSignature = nullptr;
    }
    if (g_pipelineState) {
        g_pipelineState->Release();
        g_pipelineState = nullptr;
    }
    if (g_commandList) {
        g_commandList->Release();
        g_commandList = nullptr;
    }
    if (g_commandQueue) {
        g_commandQueue->Release();
        g_commandQueue = nullptr;
    }
    if (g_rtvHeap) {
        g_rtvHeap->Release();
        g_rtvHeap = nullptr;
    }
    if (g_swapChain) {
        g_swapChain->Release();
        g_swapChain = nullptr;
    }
    if (g_fence) {
        g_fence->Release();
        g_fence = nullptr;
    }
    if (g_fenceEvent) {
        CloseHandle(g_fenceEvent);
        g_fenceEvent = nullptr;
    }
    if (g_device) {
        g_device->Release();
        g_device = nullptr;
    }

    std::cout << "Cleanup complete" << std::endl;
}

int TestD3D12Texture2D(int argc, char **argv) {
    std::cout << "Starting D3D12 Texture2D Test..." << std::endl;

    // 初始化 GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // 禁用 OpenGL
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "D3D12 + GLFW 2D Texture", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    std::cout << "GLFW window created successfully" << std::endl;

    // 初始化 D3D12
    if (!InitD3D12(window)) {
        std::cerr << "Failed to initialize D3D12" << std::endl;
        TestD3D12Texture2DCleanup();
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    std::cout << "D3D12 initialized successfully" << std::endl;

    // 创建纹理和 SRV
    if (!CreateTextureAndSRV()) {
        std::cerr << "Failed to create texture" << std::endl;
        TestD3D12Texture2DCleanup();
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    // 创建顶点缓冲区
    if (!CreateVertexBuffer()) {
        std::cerr << "Failed to create vertex buffer" << std::endl;
        TestD3D12Texture2DCleanup();
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    // 创建管线
    if (!CreatePipeline()) {
        std::cerr << "Failed to create pipeline" << std::endl;
        TestD3D12Texture2DCleanup();
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    std::cout << "Entering main loop..." << std::endl;

    // 主循环
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        TestD3D12Texture2DRender();
    }

    std::cout << "Exiting main loop..." << std::endl;

    // 清理资源
    TestD3D12Texture2DCleanup();
    glfwDestroyWindow(window);
    glfwTerminate();

    std::cout << "Test completed successfully" << std::endl;
    return 0;
}