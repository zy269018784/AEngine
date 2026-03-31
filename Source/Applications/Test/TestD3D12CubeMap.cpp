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
const UINT CUBEMAP_SIZE = 256;

// 将所有全局变量和函数设为 static
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
static ID3D12Resource* g_indexBuffer = nullptr;
static D3D12_INDEX_BUFFER_VIEW g_indexBufferView = {};
static ID3D12Resource* g_depthStencil = nullptr;
static ID3D12DescriptorHeap* g_dsvHeap = nullptr;

struct Vertex {
    DirectX::XMFLOAT3 position;
    DirectX::XMFLOAT3 normal;
};

static Vertex g_cubeVertices[] = {
    // 前面
    { { -0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f } },
    { { -0.5f,  0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f } },
    { {  0.5f,  0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f } },
    { {  0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f } },
    // 后面
    { { -0.5f, -0.5f,  0.5f }, { 0.0f, 0.0f,  1.0f } },
    { { -0.5f,  0.5f,  0.5f }, { 0.0f, 0.0f,  1.0f } },
    { {  0.5f,  0.5f,  0.5f }, { 0.0f, 0.0f,  1.0f } },
    { {  0.5f, -0.5f,  0.5f }, { 0.0f, 0.0f,  1.0f } },
    // 左面
    { { -0.5f, -0.5f,  0.5f }, { -1.0f, 0.0f, 0.0f } },
    { { -0.5f,  0.5f,  0.5f }, { -1.0f, 0.0f, 0.0f } },
    { { -0.5f,  0.5f, -0.5f }, { -1.0f, 0.0f, 0.0f } },
    { { -0.5f, -0.5f, -0.5f }, { -1.0f, 0.0f, 0.0f } },
    // 右面
    { {  0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f } },
    { {  0.5f,  0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f } },
    { {  0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f, 0.0f } },
    { {  0.5f, -0.5f,  0.5f }, { 1.0f, 0.0f, 0.0f } },
    // 上面
    { { -0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f } },
    { { -0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f, 0.0f } },
    { {  0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f, 0.0f } },
    { {  0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f } },
    // 下面
    { { -0.5f, -0.5f,  0.5f }, { 0.0f, -1.0f, 0.0f } },
    { { -0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f, 0.0f } },
    { {  0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f, 0.0f } },
    { {  0.5f, -0.5f,  0.5f }, { 0.0f, -1.0f, 0.0f } },
};

static UINT g_cubeIndices[] = {
    0, 1, 2, 0, 2, 3,
    4, 6, 5, 4, 7, 6,
    8, 9, 10, 8, 10, 11,
    12, 13, 14, 12, 14, 15,
    16, 17, 18, 16, 18, 19,
    20, 21, 22, 20, 22, 23,
};

#define CHECK_HR(hr) { if (FAILED(hr)) { std::cerr << "HRESULT failed at line " << __LINE__ << std::endl; return false; } }

static void CreateCubemapData(std::vector<uint8_t>& data, int face) {
    data.resize(CUBEMAP_SIZE * CUBEMAP_SIZE * 4);
    for (UINT y = 0; y < CUBEMAP_SIZE; ++y) {
        for (UINT x = 0; x < CUBEMAP_SIZE; ++x) {
            UINT index = (y * CUBEMAP_SIZE + x) * 4;
            bool checker = ((x / 32) + (y / 32)) % 2 == 0;

            switch (face) {
            case 0: // 右面 (+X)
                data[index + 0] = checker ? 255 : 128;
                data[index + 1] = 0;
                data[index + 2] = 0;
                break;
            case 1: // 左面 (-X)
                data[index + 0] = 0;
                data[index + 1] = checker ? 255 : 128;
                data[index + 2] = 0;
                break;
            case 2: // 上面 (+Y)
                data[index + 0] = 0;
                data[index + 1] = 0;
                data[index + 2] = checker ? 255 : 128;
                break;
            case 3: // 下面 (-Y)
                data[index + 0] = checker ? 255 : 128;
                data[index + 1] = checker ? 255 : 128;
                data[index + 2] = 0;
                break;
            case 4: // 前面 (+Z)
                data[index + 0] = checker ? 255 : 128;
                data[index + 1] = 0;
                data[index + 2] = checker ? 255 : 128;
                break;
            case 5: // 后面 (-Z)
                data[index + 0] = 0;
                data[index + 1] = checker ? 255 : 128;
                data[index + 2] = checker ? 255 : 128;
                break;
            }
            data[index + 3] = 255;
        }
    }
}

static bool InitD3D12(GLFWwindow* window) {
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
    CHECK_HR(D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&g_device)));

    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    CHECK_HR(g_device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&g_commandQueue)));

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

    for (UINT i = 0; i < FRAME_COUNT; ++i) {
        CHECK_HR(g_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&g_commandAllocator[i])));
    }
    CHECK_HR(g_device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, g_commandAllocator[0], nullptr, IID_PPV_ARGS(&g_commandList)));
    CHECK_HR(g_commandList->Close());

    CHECK_HR(g_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&g_fence)));
    g_fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
    if (!g_fenceEvent) return false;

    factory->Release();
    std::cout << "D3D12 initialized" << std::endl;
    return true;
}

static bool CreateBuffers() {
    UINT vertexBufferSize = sizeof(g_cubeVertices);
    UINT indexBufferSize = sizeof(g_cubeIndices);

    CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_UPLOAD);
    CD3DX12_RESOURCE_DESC vertexBufferDesc = CD3DX12_RESOURCE_DESC::Buffer(vertexBufferSize);
    HRESULT hr = g_device->CreateCommittedResource(&heapProps, D3D12_HEAP_FLAG_NONE,
        &vertexBufferDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&g_vertexBuffer));
    if (FAILED(hr)) return false;

    UINT8* pVertexDataBegin = nullptr;
    CD3DX12_RANGE readRange(0, 0);
    hr = g_vertexBuffer->Map(0, &readRange, reinterpret_cast<void**>(&pVertexDataBegin));
    if (FAILED(hr)) return false;
    memcpy(pVertexDataBegin, g_cubeVertices, vertexBufferSize);
    g_vertexBuffer->Unmap(0, nullptr);

    CD3DX12_RESOURCE_DESC indexBufferDesc = CD3DX12_RESOURCE_DESC::Buffer(indexBufferSize);
    hr = g_device->CreateCommittedResource(&heapProps, D3D12_HEAP_FLAG_NONE,
        &indexBufferDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&g_indexBuffer));
    if (FAILED(hr)) return false;

    UINT8* pIndexDataBegin = nullptr;
    hr = g_indexBuffer->Map(0, &readRange, reinterpret_cast<void**>(&pIndexDataBegin));
    if (FAILED(hr)) return false;
    memcpy(pIndexDataBegin, g_cubeIndices, indexBufferSize);
    g_indexBuffer->Unmap(0, nullptr);

    g_vertexBufferView.BufferLocation = g_vertexBuffer->GetGPUVirtualAddress();
    g_vertexBufferView.StrideInBytes = sizeof(Vertex);
    g_vertexBufferView.SizeInBytes = vertexBufferSize;

    g_indexBufferView.BufferLocation = g_indexBuffer->GetGPUVirtualAddress();
    g_indexBufferView.Format = DXGI_FORMAT_R32_UINT;
    g_indexBufferView.SizeInBytes = indexBufferSize;

    return true;
}

static bool CreateCubemapTexture() {
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
    CHECK_HR(g_commandQueue->Signal(g_fence, 1));
    g_fence->SetEventOnCompletion(1, g_fenceEvent);
    WaitForSingleObject(g_fenceEvent, INFINITE);
    textureUploadHeap->Release();

    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    srvDesc.Format = textureDesc.Format;
    srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
    srvDesc.TextureCube.MipLevels = 1;
    g_device->CreateShaderResourceView(g_cubemap, &srvDesc, g_srvHeap->GetCPUDescriptorHandleForHeapStart());

    return true;
}

static bool CreateDepthStencil() {
    D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc = {};
    dsvHeapDesc.NumDescriptors = 1;
    dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
    CHECK_HR(g_device->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&g_dsvHeap)));

    D3D12_RESOURCE_DESC depthStencilDesc = {};
    depthStencilDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    depthStencilDesc.Width = WIDTH;
    depthStencilDesc.Height = HEIGHT;
    depthStencilDesc.DepthOrArraySize = 1;
    depthStencilDesc.MipLevels = 1;
    depthStencilDesc.Format = DXGI_FORMAT_D32_FLOAT;
    depthStencilDesc.SampleDesc.Count = 1;
    depthStencilDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

    CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_DEFAULT);
    D3D12_CLEAR_VALUE depthClearValue = {};
    depthClearValue.Format = DXGI_FORMAT_D32_FLOAT;
    depthClearValue.DepthStencil.Depth = 1.0f;

    CHECK_HR(g_device->CreateCommittedResource(&heapProps, D3D12_HEAP_FLAG_NONE,
        &depthStencilDesc, D3D12_RESOURCE_STATE_DEPTH_WRITE, &depthClearValue, IID_PPV_ARGS(&g_depthStencil)));
    g_device->CreateDepthStencilView(g_depthStencil, nullptr, g_dsvHeap->GetCPUDescriptorHandleForHeapStart());

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
        if (errorBlob) std::cerr << (char*)errorBlob->GetBufferPointer() << std::endl;
        return nullptr;
    }
    return shaderBlob;
}

static bool CreatePipeline() {
    CD3DX12_DESCRIPTOR_RANGE range;
    range.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);

    CD3DX12_ROOT_PARAMETER rootParams[2];
    rootParams[0].InitAsDescriptorTable(1, &range, D3D12_SHADER_VISIBILITY_PIXEL);
    rootParams[1].InitAsConstantBufferView(0, 0, D3D12_SHADER_VISIBILITY_VERTEX);

    CD3DX12_STATIC_SAMPLER_DESC samplerDesc;
    samplerDesc.Init(0, D3D12_FILTER_MIN_MAG_MIP_LINEAR);

    CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc;
    rootSigDesc.Init(2, rootParams, 1, &samplerDesc,
        D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

    ID3DBlob* signature = nullptr;
    ID3DBlob* error = nullptr;
    HRESULT hr = D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error);
    if (FAILED(hr)) return false;

    hr = g_device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&g_rootSignature));
    signature->Release();
    if (FAILED(hr)) return false;

    D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
    };

    const char* vsSource = R"(
        cbuffer ConstantBuffer : register(b0) {
            float4x4 WorldViewProj;
        };
        struct VSInput { float4 position : POSITION; float3 normal : NORMAL; };
        struct VSOutput { float4 position : SV_POSITION; float3 normal : NORMAL; };
        VSOutput main(VSInput input) {
            VSOutput output;
            output.position = mul(input.position, WorldViewProj);
            output.normal = normalize(input.normal);
            return output;
        }
    )";

    const char* psSource = R"(
        TextureCube g_cubemap : register(t0);
        SamplerState g_sampler : register(s0);
        struct PSInput { float4 position : SV_POSITION; float3 normal : NORMAL; };
        float4 main(PSInput input) : SV_TARGET {
            return g_cubemap.Sample(g_sampler, normalize(input.normal));
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
    psoDesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;
    psoDesc.RasterizerState.FrontCounterClockwise = TRUE;
    psoDesc.RasterizerState.DepthClipEnable = TRUE;
    psoDesc.BlendState.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
    psoDesc.DepthStencilState.DepthEnable = TRUE;
    psoDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
    psoDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
    psoDesc.SampleMask = UINT_MAX;
    psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    psoDesc.NumRenderTargets = 1;
    psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
    psoDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
    psoDesc.SampleDesc.Count = 1;

    hr = g_device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&g_pipelineState));
    vsBlob->Release();
    psBlob->Release();

    return SUCCEEDED(hr);
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

    CD3DX12_RESOURCE_BARRIER rtBarrier = CD3DX12_RESOURCE_BARRIER::Transition(
        g_renderTargets[g_frameIndex], D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
    g_commandList->ResourceBarrier(1, &rtBarrier);

    CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(g_rtvHeap->GetCPUDescriptorHandleForHeapStart(), g_frameIndex, g_rtvDescriptorSize);
    CD3DX12_CPU_DESCRIPTOR_HANDLE dsvHandle(g_dsvHeap->GetCPUDescriptorHandleForHeapStart());
    g_commandList->OMSetRenderTargets(1, &rtvHandle, FALSE, &dsvHandle);

    const float clearColor[] = { 0.1f, 0.1f, 0.2f, 1.0f };
    g_commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
    g_commandList->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

    D3D12_VIEWPORT viewport = { 0, 0, (float)WIDTH, (float)HEIGHT, 0, 1 };
    D3D12_RECT scissorRect = { 0, 0, (LONG)WIDTH, (LONG)HEIGHT };
    g_commandList->RSSetViewports(1, &viewport);
    g_commandList->RSSetScissorRects(1, &scissorRect);

    g_commandList->SetGraphicsRootSignature(g_rootSignature);
    ID3D12DescriptorHeap* heaps[] = { g_srvHeap };
    g_commandList->SetDescriptorHeaps(1, heaps);
    g_commandList->SetGraphicsRootDescriptorTable(0, g_srvHeap->GetGPUDescriptorHandleForHeapStart());

    static float angle = 0;
    angle += 0.01f;
    XMMATRIX world = XMMatrixRotationY(angle) * XMMatrixRotationX(angle * 0.5f);
    XMMATRIX view = XMMatrixLookAtLH(XMVectorSet(0, 0, -2.5f, 0), XMVectorSet(0, 0, 0, 0), XMVectorSet(0, 1, 0, 0));
    XMMATRIX proj = XMMatrixPerspectiveFovLH(XMConvertToRadians(60.0f), (float)WIDTH / HEIGHT, 0.1f, 100.0f);
    XMMATRIX worldViewProj = XMMatrixTranspose(world * view * proj);

    struct ConstantBuffer { XMMATRIX worldViewProj; } cb = { worldViewProj };
    ID3D12Resource* constantBuffer = nullptr;
    CD3DX12_HEAP_PROPERTIES uploadHeapProps(D3D12_HEAP_TYPE_UPLOAD);
    CD3DX12_RESOURCE_DESC bufferDesc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(ConstantBuffer));
    g_device->CreateCommittedResource(&uploadHeapProps, D3D12_HEAP_FLAG_NONE, &bufferDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&constantBuffer));
    if (constantBuffer) {
        void* mappedData = nullptr;
        constantBuffer->Map(0, nullptr, &mappedData);
        memcpy(mappedData, &cb, sizeof(cb));
        constantBuffer->Unmap(0, nullptr);
        g_commandList->SetGraphicsRootConstantBufferView(1, constantBuffer->GetGPUVirtualAddress());
    }

    g_commandList->IASetVertexBuffers(0, 1, &g_vertexBufferView);
    g_commandList->IASetIndexBuffer(&g_indexBufferView);
    g_commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    g_commandList->DrawIndexedInstanced(36, 1, 0, 0, 0);

    if (constantBuffer) constantBuffer->Release();

    CD3DX12_RESOURCE_BARRIER presentBarrier = CD3DX12_RESOURCE_BARRIER::Transition(
        g_renderTargets[g_frameIndex], D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
    g_commandList->ResourceBarrier(1, &presentBarrier);
    g_commandList->Close();

    ID3D12CommandList* commandLists[] = { g_commandList };
    g_commandQueue->ExecuteCommandLists(1, commandLists);
    g_swapChain->Present(1, 0);
    WaitForPreviousFrame();
    g_frameIndex = g_swapChain->GetCurrentBackBufferIndex();
}

static void Cleanup() {
    WaitForPreviousFrame();
    if (g_indexBuffer) g_indexBuffer->Release();
    if (g_vertexBuffer) g_vertexBuffer->Release();
    if (g_depthStencil) g_depthStencil->Release();
    if (g_dsvHeap) g_dsvHeap->Release();
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
}

int TestD3D12Cubemap(int argc, char** argv) {
    std::cout << "Starting D3D12 Cubemap Test..." << std::endl;

    if (!glfwInit()) return -1;
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "D3D12 Cubemap", nullptr, nullptr);
    if (!window) { glfwTerminate(); return -1; }

    if (!InitD3D12(window)) goto cleanup;
    if (!CreateBuffers()) goto cleanup;
    if (!CreateCubemapTexture()) goto cleanup;
    if (!CreateDepthStencil()) goto cleanup;
    if (!CreatePipeline()) goto cleanup;

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