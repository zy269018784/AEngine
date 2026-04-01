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
#include <d3dx12.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;

// 窗口尺寸
const UINT WIDTH = 800;
const UINT HEIGHT = 600;
const UINT FRAME_COUNT = 2;
const UINT CUBEMAP_SIZE = 64;  // 减小尺寸加快加载

// 全局变量
static ID3D12Device* g_device = nullptr;
static ID3D12CommandQueue* g_commandQueue = nullptr;
static IDXGISwapChain3* g_swapChain = nullptr;
static ID3D12DescriptorHeap* g_rtvHeap = nullptr;
static ID3D12Resource* g_renderTargets[FRAME_COUNT] = {};
static ID3D12CommandAllocator* g_commandAllocator[FRAME_COUNT] = {};
static ID3D12GraphicsCommandList* g_commandList = nullptr;
static ID3D12Fence* g_fence = nullptr;
static UINT64 g_fenceValue[FRAME_COUNT] = {};
static HANDLE g_fenceEvent = nullptr;
static UINT g_rtvDescriptorSize = 0;
static UINT g_frameIndex = 0;
static ID3D12DescriptorHeap* g_srvHeap = nullptr;
static ID3D12Resource* g_cubemap = nullptr;
static ID3D12RootSignature* g_rootSignature = nullptr;
static ID3D12PipelineState* g_pipelineState = nullptr;
static ID3D12Resource* g_vertexBuffer = nullptr;
static D3D12_VERTEX_BUFFER_VIEW g_vertexBufferView = {};

// 简化的顶点结构 - 只包含位置和纹理坐标
struct Vertex {
    DirectX::XMFLOAT3 position;
    DirectX::XMFLOAT2 uv;
};

// 创建一个简单的全屏四边形，确保有东西显示
static Vertex g_vertices[] = {
    { { -0.8f, -0.8f, 0.0f }, { 0.0f, 1.0f } },
    { { -0.8f,  0.8f, 0.0f }, { 0.0f, 0.0f } },
    { {  0.8f,  0.8f, 0.0f }, { 1.0f, 0.0f } },
    { {  0.8f, -0.8f, 0.0f }, { 1.0f, 1.0f } },
};

static UINT g_indices[] = {
    0, 1, 2,
    0, 2, 3
};

static UINT g_numVertices = 4;
static UINT g_numIndices = 6;
static ID3D12Resource* g_indexBuffer = nullptr;
static D3D12_INDEX_BUFFER_VIEW g_indexBufferView = {};

#define CHECK_HR(hr) { if (FAILED(hr)) { std::cerr << "HRESULT failed at line " << __LINE__ << std::endl; return false; } }

static void CreateCubemapData(std::vector<uint8_t>& data, int face) {
    data.resize(CUBEMAP_SIZE * CUBEMAP_SIZE * 4);
    for (UINT y = 0; y < CUBEMAP_SIZE; ++y) {
        for (UINT x = 0; x < CUBEMAP_SIZE; ++x) {
            UINT index = (y * CUBEMAP_SIZE + x) * 4;

            // 每个面使用不同的纯色，带渐变效果使其更明显
            float fx = (float)x / CUBEMAP_SIZE;
            float fy = (float)y / CUBEMAP_SIZE;

            switch (face) {
            case 0: // +X - 红色渐变
                data[index + 0] = (UINT)(255 * fx);
                data[index + 1] = (UINT)(255 * fy);
                data[index + 2] = 0;
                break;
            case 1: // -X - 绿色渐变
                data[index + 0] = 0;
                data[index + 1] = (UINT)(255 * fx);
                data[index + 2] = (UINT)(255 * fy);
                break;
            case 2: // +Y - 蓝色渐变
                data[index + 0] = (UINT)(255 * fx);
                data[index + 1] = 0;
                data[index + 2] = (UINT)(255 * fy);
                break;
            case 3: // -Y - 黄色渐变
                data[index + 0] = (UINT)(255 * fx);
                data[index + 1] = (UINT)(255 * fx);
                data[index + 2] = 0;
                break;
            case 4: // +Z - 品红渐变
                data[index + 0] = (UINT)(255 * fx);
                data[index + 1] = 0;
                data[index + 2] = (UINT)(255 * fx);
                break;
            case 5: // -Z - 青色渐变
                data[index + 0] = 0;
                data[index + 1] = (UINT)(255 * fx);
                data[index + 2] = (UINT)(255 * fx);
                break;
            }
            data[index + 3] = 255;
        }
    }
}

static bool InitD3D12(GLFWwindow* window) {
    std::cout << "Initializing D3D12..." << std::endl;

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
    std::cout << "DXGI Factory created" << std::endl;

    CHECK_HR(D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&g_device)));
    std::cout << "D3D12 Device created" << std::endl;

    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    CHECK_HR(g_device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&g_commandQueue)));
    std::cout << "Command Queue created" << std::endl;

    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
    swapChainDesc.BufferCount = FRAME_COUNT;
    swapChainDesc.Width = WIDTH;
    swapChainDesc.Height = HEIGHT;
    swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapChainDesc.SampleDesc.Count = 1;

    IDXGISwapChain1* tempSwapChain = nullptr;
    CHECK_HR(factory->CreateSwapChainForHwnd(g_commandQueue, glfwGetWin32Window(window),
        &swapChainDesc, nullptr, nullptr, &tempSwapChain));
    g_swapChain = (IDXGISwapChain3*)tempSwapChain;
    g_frameIndex = g_swapChain->GetCurrentBackBufferIndex();
    std::cout << "Swap Chain created" << std::endl;

    D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
    rtvHeapDesc.NumDescriptors = FRAME_COUNT;
    rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    CHECK_HR(g_device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&g_rtvHeap)));
    g_rtvDescriptorSize = g_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

    D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = g_rtvHeap->GetCPUDescriptorHandleForHeapStart();
    for (UINT i = 0; i < FRAME_COUNT; ++i) {
        CHECK_HR(g_swapChain->GetBuffer(i, IID_PPV_ARGS(&g_renderTargets[i])));
        g_device->CreateRenderTargetView(g_renderTargets[i], nullptr, rtvHandle);
        rtvHandle.ptr += g_rtvDescriptorSize;
    }
    std::cout << "RTV Heap created" << std::endl;

    for (UINT i = 0; i < FRAME_COUNT; ++i) {
        CHECK_HR(g_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&g_commandAllocator[i])));
    }
    CHECK_HR(g_device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, g_commandAllocator[0], nullptr, IID_PPV_ARGS(&g_commandList)));
    CHECK_HR(g_commandList->Close());
    std::cout << "Command List created" << std::endl;

    CHECK_HR(g_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&g_fence)));
    g_fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
    if (!g_fenceEvent) return false;

    factory->Release();
    std::cout << "D3D12 initialized successfully" << std::endl;
    return true;
}

static bool CreateBuffers() {
    std::cout << "Creating buffers..." << std::endl;

    UINT vertexBufferSize = sizeof(g_vertices);
    UINT indexBufferSize = sizeof(g_indices);

    // 创建顶点缓冲区
    CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_UPLOAD);
    CD3DX12_RESOURCE_DESC vertexBufferDesc = CD3DX12_RESOURCE_DESC::Buffer(vertexBufferSize);
    HRESULT hr = g_device->CreateCommittedResource(&heapProps, D3D12_HEAP_FLAG_NONE,
        &vertexBufferDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&g_vertexBuffer));
    if (FAILED(hr)) {
        std::cerr << "Failed to create vertex buffer" << std::endl;
        return false;
    }

    UINT8* pVertexDataBegin = nullptr;
    CD3DX12_RANGE readRange(0, 0);
    hr = g_vertexBuffer->Map(0, &readRange, reinterpret_cast<void**>(&pVertexDataBegin));
    if (FAILED(hr)) {
        std::cerr << "Failed to map vertex buffer" << std::endl;
        return false;
    }
    memcpy(pVertexDataBegin, g_vertices, vertexBufferSize);
    g_vertexBuffer->Unmap(0, nullptr);

    g_vertexBufferView.BufferLocation = g_vertexBuffer->GetGPUVirtualAddress();
    g_vertexBufferView.StrideInBytes = sizeof(Vertex);
    g_vertexBufferView.SizeInBytes = vertexBufferSize;

    // 创建索引缓冲区
    CD3DX12_RESOURCE_DESC indexBufferDesc = CD3DX12_RESOURCE_DESC::Buffer(indexBufferSize);
    hr = g_device->CreateCommittedResource(&heapProps, D3D12_HEAP_FLAG_NONE,
        &indexBufferDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&g_indexBuffer));
    if (FAILED(hr)) {
        std::cerr << "Failed to create index buffer" << std::endl;
        return false;
    }

    UINT8* pIndexDataBegin = nullptr;
    hr = g_indexBuffer->Map(0, &readRange, reinterpret_cast<void**>(&pIndexDataBegin));
    if (FAILED(hr)) {
        std::cerr << "Failed to map index buffer" << std::endl;
        return false;
    }
    memcpy(pIndexDataBegin, g_indices, indexBufferSize);
    g_indexBuffer->Unmap(0, nullptr);

    g_indexBufferView.BufferLocation = g_indexBuffer->GetGPUVirtualAddress();
    g_indexBufferView.Format = DXGI_FORMAT_R32_UINT;
    g_indexBufferView.SizeInBytes = indexBufferSize;

    std::cout << "Buffers created successfully" << std::endl;
    return true;
}

static bool CreateCubemapTexture() {
    std::cout << "Creating cubemap texture..." << std::endl;

    D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
    srvHeapDesc.NumDescriptors = 1;
    srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    CHECK_HR(g_device->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&g_srvHeap)));

    D3D12_RESOURCE_DESC textureDesc = {};
    textureDesc.MipLevels = 1;
    textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    textureDesc.Width = CUBEMAP_SIZE;
    textureDesc.Height = CUBEMAP_SIZE;
    textureDesc.DepthOrArraySize = 6;
    textureDesc.SampleDesc.Count = 1;
    textureDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;

    CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_DEFAULT);
    CHECK_HR(g_device->CreateCommittedResource(&heapProps, D3D12_HEAP_FLAG_NONE,
        &textureDesc, D3D12_RESOURCE_STATE_COPY_DEST, nullptr, IID_PPV_ARGS(&g_cubemap)));

    UINT64 uploadBufferSize = 0;
    for (UINT face = 0; face < 6; ++face) {
        uploadBufferSize += GetRequiredIntermediateSize(g_cubemap, face, 1);
    }

    ID3D12Resource* textureUploadHeap = nullptr;
    CD3DX12_HEAP_PROPERTIES uploadHeapProps(D3D12_HEAP_TYPE_UPLOAD);
    CD3DX12_RESOURCE_DESC bufferDesc = CD3DX12_RESOURCE_DESC::Buffer(uploadBufferSize);
    CHECK_HR(g_device->CreateCommittedResource(&uploadHeapProps, D3D12_HEAP_FLAG_NONE,
        &bufferDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&textureUploadHeap)));

    CHECK_HR(g_commandAllocator[g_frameIndex]->Reset());
    CHECK_HR(g_commandList->Reset(g_commandAllocator[g_frameIndex], nullptr));

    UINT64 currentOffset = 0;
    for (UINT face = 0; face < 6; ++face) {
        std::vector<uint8_t> textureData;
        CreateCubemapData(textureData, face);

        D3D12_SUBRESOURCE_DATA subresourceData = {};
        subresourceData.pData = textureData.data();
        subresourceData.RowPitch = CUBEMAP_SIZE * 4;
        subresourceData.SlicePitch = subresourceData.RowPitch * CUBEMAP_SIZE;

        UpdateSubresources(g_commandList, g_cubemap, textureUploadHeap,
            currentOffset, face, 1, &subresourceData);
        currentOffset += GetRequiredIntermediateSize(g_cubemap, face, 1);
    }

    CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
        g_cubemap, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
    g_commandList->ResourceBarrier(1, &barrier);
    CHECK_HR(g_commandList->Close());

    ID3D12CommandList* commandLists[] = { g_commandList };
    g_commandQueue->ExecuteCommandLists(1, commandLists);

    // 等待上传完成
    UINT64 fenceValue = 1;
    CHECK_HR(g_commandQueue->Signal(g_fence, fenceValue));
    g_fence->SetEventOnCompletion(fenceValue, g_fenceEvent);
    WaitForSingleObject(g_fenceEvent, INFINITE);

    textureUploadHeap->Release();

    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    srvDesc.Format = textureDesc.Format;
    srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
    srvDesc.TextureCube.MipLevels = 1;
    g_device->CreateShaderResourceView(g_cubemap, &srvDesc, g_srvHeap->GetCPUDescriptorHandleForHeapStart());

    std::cout << "Cubemap texture created successfully" << std::endl;
    return true;
}

static ID3DBlob* CompileShader(const std::string& source, const std::string& entrypoint, const std::string& target) {
    ID3DBlob* shaderBlob = nullptr;
    ID3DBlob* errorBlob = nullptr;
    UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
    flags |= D3DCOMPILE_DEBUG;
#endif
    HRESULT hr = D3DCompile(source.c_str(), source.size(), nullptr, nullptr, nullptr,
        entrypoint.c_str(), target.c_str(), flags, 0, &shaderBlob, &errorBlob);
    if (FAILED(hr)) {
        if (errorBlob) {
            std::cerr << "Shader compilation error: " << (char*)errorBlob->GetBufferPointer() << std::endl;
            errorBlob->Release();
        }
        return nullptr;
    }
    return shaderBlob;
}

static bool CreatePipeline() {
    std::cout << "Creating pipeline..." << std::endl;

    // 创建根签名
    CD3DX12_DESCRIPTOR_RANGE range;
    range.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);

    CD3DX12_ROOT_PARAMETER rootParams[1];
    rootParams[0].InitAsDescriptorTable(1, &range, D3D12_SHADER_VISIBILITY_PIXEL);

    CD3DX12_STATIC_SAMPLER_DESC samplerDesc;
    samplerDesc.Init(0, D3D12_FILTER_MIN_MAG_MIP_LINEAR);

    CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc;
    rootSigDesc.Init(1, rootParams, 1, &samplerDesc,
        D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

    ID3DBlob* signature = nullptr;
    ID3DBlob* error = nullptr;
    HRESULT hr = D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error);
    if (FAILED(hr)) {
        std::cerr << "Failed to serialize root signature" << std::endl;
        return false;
    }

    hr = g_device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&g_rootSignature));
    signature->Release();
    if (FAILED(hr)) {
        std::cerr << "Failed to create root signature" << std::endl;
        return false;
    }

    D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
    };

    // 简单的像素着色器，直接显示纹理颜色
    const char* vsSource = R"(
        struct VSInput {
            float4 position : POSITION;
            float2 uv : TEXCOORD;
        };
        struct VSOutput {
            float4 position : SV_POSITION;
            float2 uv : TEXCOORD;
            float3 direction : TEXCOORD1;
        };
        VSOutput main(VSInput input) {
            VSOutput output;
            output.position = input.position;
            output.uv = input.uv;
            // 使用UV坐标来生成采样方向，让每个三角形显示不同的立方体面
            output.direction = normalize(float3(input.uv * 2.0 - 1.0, 1.0));
            return output;
        }
    )";

    const char* psSource = R"(
        TextureCube g_cubemap : register(t0);
        SamplerState g_sampler : register(s0);
        struct PSInput {
            float4 position : SV_POSITION;
            float2 uv : TEXCOORD;
            float3 direction : TEXCOORD1;
        };
        float4 main(PSInput input) : SV_TARGET {
            // 根据UV坐标选择不同的立方体贴图方向
            float3 dir;
            if (input.uv.x < 0.33) {
                // 左侧区域 - 显示红色面
                dir = normalize(float3(-1, input.uv.y * 2 - 1, 0));
            } else if (input.uv.x < 0.66) {
                // 中间区域 - 显示绿色面
                dir = normalize(float3(1, input.uv.y * 2 - 1, 0));
            } else {
                // 右侧区域 - 显示蓝色面
                dir = normalize(float3(0, input.uv.y * 2 - 1, 1));
            }
            return g_cubemap.Sample(g_sampler, dir);
        }
    )";

    ID3DBlob* vsBlob = CompileShader(vsSource, "main", "vs_5_0");
    ID3DBlob* psBlob = CompileShader(psSource, "main", "ps_5_0");
    if (!vsBlob || !psBlob) return false;

    D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
    psoDesc.InputLayout = { inputLayout, 2 };
    psoDesc.pRootSignature = g_rootSignature;
    psoDesc.VS = { vsBlob->GetBufferPointer(), vsBlob->GetBufferSize() };
    psoDesc.PS = { psBlob->GetBufferPointer(), psBlob->GetBufferSize() };
    psoDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
    psoDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
    psoDesc.RasterizerState.FrontCounterClockwise = FALSE;
    psoDesc.RasterizerState.DepthClipEnable = TRUE;
    psoDesc.BlendState.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
    psoDesc.DepthStencilState.DepthEnable = FALSE;  // 暂时禁用深度测试简化问题
    psoDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;
    psoDesc.SampleMask = UINT_MAX;
    psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    psoDesc.NumRenderTargets = 1;
    psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
    psoDesc.SampleDesc.Count = 1;

    hr = g_device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&g_pipelineState));
    vsBlob->Release();
    psBlob->Release();

    if (FAILED(hr)) {
        std::cerr << "Failed to create pipeline state" << std::endl;
        return false;
    }

    std::cout << "Pipeline created successfully" << std::endl;
    return true;
}

static void WaitForPreviousFrame() {
    const UINT64 fenceValue = g_fenceValue[g_frameIndex];
    g_commandQueue->Signal(g_fence, fenceValue);
    if (g_fence->GetCompletedValue() < fenceValue) {
        g_fence->SetEventOnCompletion(fenceValue, g_fenceEvent);
        WaitForSingleObject(g_fenceEvent, INFINITE);
    }
    g_fenceValue[g_frameIndex] = fenceValue + 1;
}

static void Render() {
    g_commandAllocator[g_frameIndex]->Reset();
    g_commandList->Reset(g_commandAllocator[g_frameIndex], g_pipelineState);

    // 转换渲染目标状态
    CD3DX12_RESOURCE_BARRIER rtBarrier = CD3DX12_RESOURCE_BARRIER::Transition(
        g_renderTargets[g_frameIndex], D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
    g_commandList->ResourceBarrier(1, &rtBarrier);

    CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(g_rtvHeap->GetCPUDescriptorHandleForHeapStart(), g_frameIndex, g_rtvDescriptorSize);
    g_commandList->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);

    // 清屏为灰色，便于调试
    const float clearColor[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    g_commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);

    // 设置视口和裁剪矩形
    D3D12_VIEWPORT viewport = { 0, 0, (float)WIDTH, (float)HEIGHT, 0, 1 };
    D3D12_RECT scissorRect = { 0, 0, (LONG)WIDTH, (LONG)HEIGHT };
    g_commandList->RSSetViewports(1, &viewport);
    g_commandList->RSSetScissorRects(1, &scissorRect);

    // 设置根签名和描述符堆
    g_commandList->SetGraphicsRootSignature(g_rootSignature);
    ID3D12DescriptorHeap* heaps[] = { g_srvHeap };
    g_commandList->SetDescriptorHeaps(1, heaps);
    g_commandList->SetGraphicsRootDescriptorTable(0, g_srvHeap->GetGPUDescriptorHandleForHeapStart());

    // 设置顶点和索引缓冲区
    g_commandList->IASetVertexBuffers(0, 1, &g_vertexBufferView);
    g_commandList->IASetIndexBuffer(&g_indexBufferView);
    g_commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // 绘制
    g_commandList->DrawIndexedInstanced(g_numIndices, 1, 0, 0, 0);

    // 转换回呈现状态
    CD3DX12_RESOURCE_BARRIER presentBarrier = CD3DX12_RESOURCE_BARRIER::Transition(
        g_renderTargets[g_frameIndex], D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
    g_commandList->ResourceBarrier(1, &presentBarrier);

    g_commandList->Close();

    // 执行命令列表
    ID3D12CommandList* commandLists[] = { g_commandList };
    g_commandQueue->ExecuteCommandLists(1, commandLists);

    // 呈现
    g_swapChain->Present(1, 0);

    WaitForPreviousFrame();
    g_frameIndex = g_swapChain->GetCurrentBackBufferIndex();
}

static void Cleanup() {
    std::cout << "Cleaning up..." << std::endl;
    WaitForPreviousFrame();
    if (g_indexBuffer) g_indexBuffer->Release();
    if (g_vertexBuffer) g_vertexBuffer->Release();
    for (UINT i = 0; i < FRAME_COUNT; ++i) {
        if (g_renderTargets[i]) g_renderTargets[i]->Release();
        if (g_commandAllocator[i]) g_commandAllocator[i]->Release();
    }
    if (g_cubemap) g_cubemap->Release();
    if (g_srvHeap) g_srvHeap->Release();
    if (g_rootSignature) g_rootSignature->Release();
    if (g_pipelineState) g_pipelineState->Release();
    if (g_commandList) g_commandList->Release();
    if (g_commandQueue) g_commandQueue->Release();
    if (g_rtvHeap) g_rtvHeap->Release();
    if (g_swapChain) g_swapChain->Release();
    if (g_fence) g_fence->Release();
    if (g_fenceEvent) CloseHandle(g_fenceEvent);
    if (g_device) g_device->Release();
    std::cout << "Cleanup completed" << std::endl;
}

int TestD3D12Cubemap(int argc, char** argv) {
    std::cout << "=== D3D12 Cubemap Test Starting ===" << std::endl;

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "D3D12 Cubemap Test", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    std::cout << "Window created" << std::endl;

    if (!InitD3D12(window)) {
        std::cerr << "Failed to initialize D3D12" << std::endl;
        goto cleanup;
    }

    if (!CreateBuffers()) {
        std::cerr << "Failed to create buffers" << std::endl;
        goto cleanup;
    }

    if (!CreateCubemapTexture()) {
        std::cerr << "Failed to create cubemap texture" << std::endl;
        goto cleanup;
    }

    if (!CreatePipeline()) {
        std::cerr << "Failed to create pipeline" << std::endl;
        goto cleanup;
    }

    std::cout << "=== Initialization Complete ===" << std::endl;
    std::cout << "Running - Close window to exit" << std::endl;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        Render();
    }

cleanup:
    Cleanup();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}