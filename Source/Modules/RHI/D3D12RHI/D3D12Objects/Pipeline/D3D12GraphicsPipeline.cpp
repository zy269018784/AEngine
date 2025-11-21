#include "D3D12GraphicsPipeline.h"
#include "D3D12_Includes.h"
#include "D3D12Objects/Core/D3D12Core.h"
#include "D3D12Objects/Shader/D3D12Shader.h"
#include <iostream>

D3D12GraphicsPipeline::D3D12GraphicsPipeline(D3D12Device* InDevice)
    : D3D12Pipeline(InDevice)
{

}

D3D12GraphicsPipeline::~D3D12GraphicsPipeline()
{

}

void D3D12GraphicsPipeline::Create()
{

    // 1. 创建空的根签名
    D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc = {};
    rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

    ID3DBlob *signature;
    ID3DBlob *error;
    if (FAILED(D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error))) {
        std::cerr << "Failed to serialize root signature" << std::endl;
        return;
    }
    if (FAILED(Device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&RootSignature)))) {
        std::cerr << "Failed to create root signature" << std::endl;
        return;
    }

    // 3. 定义输入布局
    D3D12_INPUT_ELEMENT_DESC inputDescs[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
    };

    D3D12_GRAPHICS_PIPELINE_STATE_DESC CreateInfo = {};
    CreateInfo.InputLayout                                         = { inputDescs, _countof(inputDescs) };
    CreateInfo.pRootSignature                                      = RootSignature;

    /*
        Rasterization
    */
    CreateInfo.RasterizerState.FillMode                            = ToD3D12PolygonMode(PolygonMode);
    CreateInfo.RasterizerState.CullMode                            = ToD3D12CullMode(CullMode); // 重要：禁用背面剔除
    CreateInfo.RasterizerState.DepthClipEnable                     = TRUE;
    CreateInfo.RasterizerState.FrontCounterClockwise               = ToD3D12FrontFace(FrontFace);
    CreateInfo.RasterizerState.DepthClipEnable                     = FALSE;

    /*
        Depth Test && Stencil Test
    */
    CreateInfo.DepthStencilState.DepthEnable                       = DepthTestEnable;
    CreateInfo.DepthStencilState.DepthWriteMask                    = D3D12_DEPTH_WRITE_MASK_ZERO;
    if (DepthWriteEnable)
        CreateInfo.DepthStencilState.DepthWriteMask                = D3D12_DEPTH_WRITE_MASK_ALL;  
    CreateInfo.DepthStencilState.DepthFunc                         = ToD3D12CompareOp(DepthCompareOp);
    CreateInfo.DepthStencilState.StencilEnable                     = FALSE;

    /*
        Multisample
    */
    CreateInfo.SampleDesc.Count                                    = ToD3D12SampleCount(SampleCount);
    CreateInfo.SampleDesc.Quality                                  = 0;
    CreateInfo.SampleMask                                          = UINT_MAX;
    

    /*
        Input Assembly
    */
    CreateInfo.PrimitiveTopologyType                               = ToD3D12PrimitiveTopology(Topology);

    /*
        Shader
    */
    for (int i = 0; i < Shaders.size(); i++)
    {
        ID3DBlob* Handle = ((D3D12Shader*)Shaders[i])->GetHandle();
        if (Shaders[i]->Type_ == RHIShaderType::Vertex)
        {
            CreateInfo.VS = { Handle->GetBufferPointer(), Handle->GetBufferSize()};
        }
        else if (Shaders[i]->Type_ == RHIShaderType::Fragment)
        {
            CreateInfo.PS = { Handle->GetBufferPointer(), Handle->GetBufferSize() };
        }
        else if (Shaders[i]->Type_ == RHIShaderType::Geometry)
        {
            CreateInfo.GS = { Handle->GetBufferPointer(), Handle->GetBufferSize() };
        }
    }

    CreateInfo.BlendState.AlphaToCoverageEnable                    = FALSE;
    CreateInfo.BlendState.IndependentBlendEnable                   = FALSE;
    CreateInfo.BlendState.RenderTarget[0].RenderTargetWriteMask    = D3D12_COLOR_WRITE_ENABLE_ALL;


    CreateInfo.NumRenderTargets                                    = 1;
    CreateInfo.RTVFormats[0]                                       = DXGI_FORMAT_R8G8B8A8_UNORM;
}