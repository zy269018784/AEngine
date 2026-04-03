#ifdef PROJECT_USE_D3D12
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
#include "D3D12Objects/Device/D3D12Device.h"
#include "D3D12Objects/Texture/D3D12Texture.h"
#include "D3D12Objects/CommandBuffer/D3D12CommandPool.h"
#include "D3D12Objects/CommandBuffer/D3D12CommandBuffer.h"

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;

// 窗口尺寸
static const UINT WIDTH = 800;
static const UINT HEIGHT = 600;

// 帧缓冲区计数（双缓冲）
static const UINT FRAME_COUNT = 2;

// 纹理数组参数
static const UINT TEXTURE_COUNT = 3;  // 3个纹理
static const UINT TEXTURE_WIDTH = 256;
static const UINT TEXTURE_HEIGHT = 256;

// 全局 D3D12 对象 - 全部改为 static
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

// 纹理数组相关对象
static ID3D12DescriptorHeap* g_srvHeap = nullptr;
static ID3D12Resource* g_textureArray = nullptr;  // 纹理数组资源

// 渲染管线对象
static ID3D12RootSignature* g_rootSignature = nullptr;
static ID3D12PipelineState* g_pipelineState = nullptr;

// 顶点缓冲区对象
static ID3D12Resource* g_vertexBuffer = nullptr;
static D3D12_VERTEX_BUFFER_VIEW g_vertexBufferView = {};

static D3D12Device* Device = nullptr;
static D3D12Texture* Texture = nullptr;
static D3D12CommandPool *CommandPool[FRAME_COUNT] = {};
static D3D12CommandBuffer *CommandBuffer = nullptr;


// 顶点结构 - 添加纹理数组索引
struct Vertex {
    DirectX::XMFLOAT3 position;
    DirectX::XMFLOAT3 texcoord;  // xy: 纹理坐标, z: 纹理数组索引
};

// 检查 HRESULT 的辅助宏
#define CHECK_HR(hr) { if (FAILED(hr)) { std::cerr << "HRESULT failed at line " << __LINE__ << std::endl; return false; } }
#define CHECK_HR_VOID(hr) { if (FAILED(hr)) { std::cerr << "HRESULT failed at line " << __LINE__ << std::endl; return; } }

// 创建纹理数组数据 - 3个纹理：红、绿、蓝
static void CreateTextureArrayData(std::vector<uint8_t>& data) {
    // 纹理数组总大小 = 宽度 * 高度 * 4通道 * 纹理数量
    data.resize(TEXTURE_WIDTH * TEXTURE_HEIGHT * 4 * TEXTURE_COUNT);

    for (UINT slice = 0; slice < TEXTURE_COUNT; ++slice) {
        for (UINT y = 0; y < TEXTURE_HEIGHT; ++y) {
            for (UINT x = 0; x < TEXTURE_WIDTH; ++x) {
                UINT index = (slice * TEXTURE_WIDTH * TEXTURE_HEIGHT + y * TEXTURE_WIDTH + x) * 4;
                
                // 根据纹理索引设置颜色
                switch(slice) {
                    case 0: // 红色纹理
                        data[index + 0] = 255;  // R
                        data[index + 1] = 0;    // G
                        data[index + 2] = 0;    // B
                        break;
                    case 1: // 绿色纹理
                        data[index + 0] = 0;    // R
                        data[index + 1] = 255;  // G
                        data[index + 2] = 0;    // B
                        break;
                    case 2: // 蓝色纹理
                        data[index + 0] = 0;    // R
                        data[index + 1] = 0;    // G
                        data[index + 2] = 255;  // B
                        break;
                }
                data[index + 3] = 255;  // Alpha
            }
        }
    }

    std::cout << "Texture array data created: " << TEXTURE_COUNT << " textures, each " 
              << TEXTURE_WIDTH << "x" << TEXTURE_HEIGHT << std::endl;
}

// 初始化 D3D12 设备
static bool InitD3D12(GLFWwindow* window) {
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
    Device = new D3D12Device();
    Device->Handle = g_device;


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

    // 5. 创建 RTV
    D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = g_rtvHeap->GetCPUDescriptorHandleForHeapStart();
    for (UINT i = 0; i < FRAME_COUNT; ++i) {
        CHECK_HR(g_swapChain->GetBuffer(i, IID_PPV_ARGS(&g_renderTargets[i])));
        g_device->CreateRenderTargetView(g_renderTargets[i], nullptr, rtvHandle);
        rtvHandle.ptr += g_rtvDescriptorSize;
    }

    // 6. 创建命令分配器和命令列表
    for (UINT i = 0; i < FRAME_COUNT; ++i) {
       // CHECK_HR(g_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&g_commandAllocator[i])));

        CommandPool[i] = new D3D12CommandPool(Device);
        g_commandAllocator[i] = CommandPool[i]->GetHandle();
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
    std::cout << "D3D12 initialized successfully" << std::endl;
    return true;
}

// 创建顶点缓冲区 - 三个三角形，每个使用不同的纹理索引
static bool CreateVertexBuffer() {
    // 创建三个三角形，分别对应红、绿、蓝纹理
    // 每个三角形使用不同的纹理数组索引（0,1,2）
    Vertex vertices[] = {
        // 红色三角形 (索引0) - 左上角
        { { -0.8f, 0.3f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
        { { -0.3f, 0.3f, 0.0f }, { 1.0f, 0.0f, 0.0f } },
        { { -0.55f, 0.8f, 0.0f }, { 0.5f, 1.0f, 0.0f } },
        
        // 绿色三角形 (索引1) - 中间
        { { -0.2f, -0.2f, 0.0f }, { 0.0f, 0.0f, 1.0f } },
        { { 0.3f, -0.2f, 0.0f }, { 1.0f, 0.0f, 1.0f } },
        { { 0.05f, 0.3f, 0.0f }, { 0.5f, 1.0f, 1.0f } },
        
        // 蓝色三角形 (索引2) - 右下角
        { { 0.4f, -0.7f, 0.0f }, { 0.0f, 0.0f, 2.0f } },
        { { 0.9f, -0.7f, 0.0f }, { 1.0f, 0.0f, 2.0f } },
        { { 0.65f, -0.2f, 0.0f }, { 0.5f, 1.0f, 2.0f } }
    };

    UINT vertexBufferSize = sizeof(vertices);

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

    memcpy(pVertexDataBegin, vertices, vertexBufferSize);
    g_vertexBuffer->Unmap(0, nullptr);

    // 初始化顶点缓冲区视图
    g_vertexBufferView.BufferLocation = g_vertexBuffer->GetGPUVirtualAddress();
    g_vertexBufferView.StrideInBytes = sizeof(Vertex);
    g_vertexBufferView.SizeInBytes = vertexBufferSize;

    std::cout << "Vertex buffer created successfully with 3 triangles" << std::endl;
    return true;
}

// 创建纹理数组和 SRV
static bool CreateTextureArrayAndSRV() {
    // 1. 创建 SRV 描述符堆
    D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
    srvHeapDesc.NumDescriptors = 1;
    srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    CHECK_HR(g_device->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&g_srvHeap)));

    // 2. 生成纹理数组数据
    std::vector<uint8_t> textureData;
    CreateTextureArrayData(textureData);

    // 3. 创建纹理数组资源 - 使用 Texture2DArray
    D3D12_RESOURCE_DESC textureDesc = {};
    textureDesc.MipLevels = 1;
    textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    textureDesc.Width = TEXTURE_WIDTH;
    textureDesc.Height = TEXTURE_HEIGHT;
    textureDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
    textureDesc.DepthOrArraySize = TEXTURE_COUNT;  // 纹理数组大小
    textureDesc.SampleDesc.Count = 1;
    textureDesc.SampleDesc.Quality = 0;
    textureDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;  // 仍然是2D纹理，但有多个切片

    CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_DEFAULT);
#if 0
    CHECK_HR(g_device->CreateCommittedResource(
        &heapProps,
        D3D12_HEAP_FLAG_NONE,
        &textureDesc,
        D3D12_RESOURCE_STATE_COPY_DEST,
        nullptr,
        IID_PPV_ARGS(&g_textureArray)
    ));
#else
    Texture = new D3D12Texture(Device, RHITextureType::Texture2DArray, RHIPixelFormat::PF_R8G8B8A8_UNORM, 1, TEXTURE_WIDTH, TEXTURE_HEIGHT, 1, TEXTURE_COUNT, textureData.data());
    g_textureArray = (ID3D12Resource*)Texture->Handle;
#endif
#if 0
    // 4. 创建上传堆
    UINT64 uploadBufferSize = GetRequiredIntermediateSize(g_textureArray, 0, TEXTURE_COUNT);
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
#else
    ID3D12Resource* textureUploadHeap = nullptr;
    textureUploadHeap = Texture->pUploadBuffer;
#endif

#if 0
    // 记录上传命令
    CHECK_HR(g_commandAllocator[g_frameIndex]->Reset());
    CHECK_HR(g_commandList->Reset(g_commandAllocator[g_frameIndex], nullptr));

    // 准备子资源数据
    std::vector<D3D12_SUBRESOURCE_DATA> textureSubData(TEXTURE_COUNT);
    for (UINT i = 0; i < TEXTURE_COUNT; ++i) {
        textureSubData[i].pData = textureData.data() + (i * TEXTURE_WIDTH * TEXTURE_HEIGHT * 4);
        textureSubData[i].RowPitch = TEXTURE_WIDTH * 4;
        textureSubData[i].SlicePitch = textureSubData[i].RowPitch * TEXTURE_HEIGHT;
    }

    UpdateSubresources(g_commandList, g_textureArray, textureUploadHeap, 0, 0, TEXTURE_COUNT, textureSubData.data());

    CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
        g_textureArray,
        D3D12_RESOURCE_STATE_COPY_DEST,
        D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE
    );
    g_commandList->ResourceBarrier(1, &barrier);

    CHECK_HR(g_commandList->Close());

    // 执行命令列表
    ID3D12CommandList* commandLists[] = { g_commandList };
    g_commandQueue->ExecuteCommandLists(1, commandLists);
#elif 0
    for (int ArrayIndex = 0; ArrayIndex < TEXTURE_COUNT; ArrayIndex++)
    {
        int Offset = TEXTURE_WIDTH * TEXTURE_HEIGHT * 4 * ArrayIndex;
        uint8_t* Pixels = textureData.data() + (ArrayIndex * TEXTURE_WIDTH * TEXTURE_HEIGHT * 4);
        Texture->Update(0, 0, 0, ArrayIndex, TEXTURE_WIDTH, TEXTURE_HEIGHT, 1, Pixels);
    }
#endif
    // 等待上传完成
    CHECK_HR(g_commandQueue->Signal(g_fence, 1));
    g_fence->SetEventOnCompletion(1, g_fenceEvent);
    WaitForSingleObject(g_fenceEvent, INFINITE);

    textureUploadHeap->Release();

    // 5. 创建 SRV for Texture2DArray
    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    srvDesc.Format = textureDesc.Format;
    srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2DARRAY;  // 重要：使用 Texture2DArray
    srvDesc.Texture2DArray.MipLevels = 1;
    srvDesc.Texture2DArray.ArraySize = TEXTURE_COUNT;
    srvDesc.Texture2DArray.FirstArraySlice = 0;
    srvDesc.Texture2DArray.PlaneSlice = 0;
    
    g_device->CreateShaderResourceView(g_textureArray, &srvDesc, g_srvHeap->GetCPUDescriptorHandleForHeapStart());

    std::cout << "Texture array created successfully with " << TEXTURE_COUNT << " slices" << std::endl;
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

// 创建根签名和 PSO
static bool CreatePipeline() {
    // 1. 创建根签名 - 需要纹理数组和采样器
    CD3DX12_DESCRIPTOR_RANGE range;
    range.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);

    CD3DX12_ROOT_PARAMETER rootParam;
    rootParam.InitAsDescriptorTable(1, &range, D3D12_SHADER_VISIBILITY_PIXEL);

    // 创建静态采样器
    CD3DX12_STATIC_SAMPLER_DESC samplerDesc;
    samplerDesc.Init(
        0,                                  // shader register
        D3D12_FILTER_MIN_MAG_MIP_LINEAR,    // filter
        D3D12_TEXTURE_ADDRESS_MODE_WRAP,    // addressU
        D3D12_TEXTURE_ADDRESS_MODE_WRAP,    // addressV
        D3D12_TEXTURE_ADDRESS_MODE_WRAP     // addressW
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

    // 2. 定义顶点布局 - 现在使用 float3 纹理坐标（包含数组索引）
    D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
    };

    // 3. 编译着色器
    const char* vsSource = R"(
        struct VSInput {
            float4 position : POSITION;
            float3 texcoord : TEXCOORD;  // xy: UV, z: array index
        };
        struct VSOutput {
            float4 position : SV_POSITION;
            float2 uv : TEXCOORD0;
            uint arrayIndex : TEXCOORD1;  // 纹理数组索引
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
        Texture2DArray g_textureArray : register(t0);  // 纹理数组
        SamplerState g_sampler : register(s0);
        struct PSInput {
            float4 position : SV_POSITION;
            float2 uv : TEXCOORD0;
            uint arrayIndex : TEXCOORD1;
        };
        float4 main(PSInput input) : SV_TARGET {
            // 从纹理数组采样，使用输入的数组索引
            return g_textureArray.Sample(g_sampler, float3(input.uv, input.arrayIndex));
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
    
    // 设置光栅化状态
    psoDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
    psoDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
    psoDesc.RasterizerState.FrontCounterClockwise = FALSE;
    psoDesc.RasterizerState.DepthBias = 0;
    psoDesc.RasterizerState.DepthBiasClamp = 0.0f;
    psoDesc.RasterizerState.SlopeScaledDepthBias = 0.0f;
    psoDesc.RasterizerState.DepthClipEnable = TRUE;
    psoDesc.RasterizerState.MultisampleEnable = FALSE;
    psoDesc.RasterizerState.AntialiasedLineEnable = FALSE;
    
    // 设置混合状态
    psoDesc.BlendState.RenderTarget[0].BlendEnable = FALSE;
    psoDesc.BlendState.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
    
    psoDesc.DepthStencilState.DepthEnable = FALSE;
    psoDesc.DepthStencilState.StencilEnable = FALSE;
    psoDesc.SampleMask = UINT_MAX;
    psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    psoDesc.NumRenderTargets = 1;
    psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
    psoDesc.SampleDesc.Count = 1;

    hr = g_device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&g_pipelineState));
    if (FAILED(hr)) {
        std::cerr << "Failed to create pipeline state" << std::endl;
        vsBlob->Release();
        psBlob->Release();
        return false;
    }

    vsBlob->Release();
    psBlob->Release();

    std::cout << "Pipeline created successfully for texture array" << std::endl;
    return true;
}

// 等待 GPU 完成当前帧
static void WaitForPreviousFrame() {
    if (!g_commandQueue || !g_fence) return;

    const UINT64 fenceValue = g_fenceValue[g_frameIndex];

    HRESULT hr = g_commandQueue->Signal(g_fence, fenceValue);
    if (FAILED(hr)) return;

    if (g_fence->GetCompletedValue() < fenceValue) {
        hr = g_fence->SetEventOnCompletion(fenceValue, g_fenceEvent);
        if (SUCCEEDED(hr)) {
            WaitForSingleObject(g_fenceEvent, INFINITE);
        }
    }

    g_fenceValue[g_frameIndex] = fenceValue + 1;
}

// 渲染循环
static void TestD3D12RHITexture2DArrayRender() {
    if (!g_commandAllocator[g_frameIndex] || !g_commandList || !g_pipelineState || !g_vertexBuffer) {
        std::cerr << "Missing required resources for rendering" << std::endl;
        return;
    }

    // 重置命令分配器和命令列表
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

    // 清屏为灰色背景
    const float clearColor[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    g_commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);

    // 设置视口和裁剪矩形
    D3D12_VIEWPORT viewport = { 0, 0, static_cast<float>(WIDTH), static_cast<float>(HEIGHT), 0, 1 };
    D3D12_RECT scissorRect = { 0, 0, static_cast<LONG>(WIDTH), static_cast<LONG>(HEIGHT) };
    g_commandList->RSSetViewports(1, &viewport);
    g_commandList->RSSetScissorRects(1, &scissorRect);

    // 设置根签名
    g_commandList->SetGraphicsRootSignature(g_rootSignature);

    // 设置描述符堆和根描述符表
    ID3D12DescriptorHeap* heaps[] = { g_srvHeap };
    g_commandList->SetDescriptorHeaps(1, heaps);
    
    CD3DX12_GPU_DESCRIPTOR_HANDLE srvHandle(g_srvHeap->GetGPUDescriptorHandleForHeapStart());
    g_commandList->SetGraphicsRootDescriptorTable(0, srvHandle);

    // 设置顶点缓冲区
    g_commandList->IASetVertexBuffers(0, 1, &g_vertexBufferView);
    g_commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    
    // 绘制3个三角形（每个3个顶点）
    g_commandList->DrawInstanced(9, 1, 0, 0);

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
static void TestD3D12RHITexture2DArrayCleanup() {
    std::cout << "Cleaning up resources..." << std::endl;
    
    WaitForPreviousFrame();

    if (g_vertexBuffer) {
        g_vertexBuffer->Release();
        g_vertexBuffer = nullptr;
    }

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

    if (g_textureArray) {
        g_textureArray->Release();
        g_textureArray = nullptr;
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

// 主函数
int TestD3D12RHITexture2DArray(int argc, char **argv) {
    std::cout << "Starting D3D12 Texture2D Array Test..." << std::endl;
    
    // 初始化 GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "D3D12 + GLFW 2D Texture Array", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    std::cout << "GLFW window created successfully" << std::endl;

    // 初始化 D3D12
    if (!InitD3D12(window)) {
        std::cerr << "Failed to initialize D3D12" << std::endl;
        TestD3D12RHITexture2DArrayCleanup();
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    // 创建顶点缓冲区
    if (!CreateVertexBuffer()) {
        std::cerr << "Failed to create vertex buffer" << std::endl;
        TestD3D12RHITexture2DArrayCleanup();
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    // 创建纹理数组和 SRV
    if (!CreateTextureArrayAndSRV()) {
        std::cerr << "Failed to create texture array" << std::endl;
        TestD3D12RHITexture2DArrayCleanup();
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    // 创建管线
    if (!CreatePipeline()) {
        std::cerr << "Failed to create pipeline" << std::endl;
        TestD3D12RHITexture2DArrayCleanup();
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    std::cout << "Entering main loop..." << std::endl;

    // 主循环
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        TestD3D12RHITexture2DArrayRender();
    }

    std::cout << "Exiting main loop..." << std::endl;

    // 清理资源
    TestD3D12RHITexture2DArrayCleanup();
    glfwDestroyWindow(window);
    glfwTerminate();

    std::cout << "Test completed successfully" << std::endl;
    return 0;
}
#endif