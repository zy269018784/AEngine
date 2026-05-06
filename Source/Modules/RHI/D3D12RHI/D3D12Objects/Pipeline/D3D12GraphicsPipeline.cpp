#include "D3D12GraphicsPipeline.h"
#include "D3D12_Includes.h"
#include "D3D12Objects/Core/D3D12Core.h"
#include "D3D12Objects/Shader/D3D12Shader.h"
#include <iostream>

D3D12GraphicsPipeline::   D3D12GraphicsPipeline(D3D12Device* InDevice)
    : D3D12Pipeline(InDevice)
{

}

D3D12GraphicsPipeline::~D3D12GraphicsPipeline()
{

}

void D3D12GraphicsPipeline::Create()
{
    ID3DBlob* error;

    // 1. 创建空的根签名
    D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc = {};
    rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

    if (FAILED(D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &Signature, &error))) {
        std::cerr << "Failed to serialize root signature" << std::endl;
        return;
    }
    if (FAILED(Device->CreateRootSignature(0, Signature->GetBufferPointer(), Signature->GetBufferSize(), IID_PPV_ARGS(&RootSignature)))) {
        std::cerr << "Failed to create root signature" << std::endl;
        return;
    }
    D3D12_GRAPHICS_PIPELINE_STATE_DESC CreateInfo = {};

    CreateInfo.pRootSignature = RootSignature;

    /*
        1. Rasterization
    */
    CreateInfo.RasterizerState.FillMode                            = ToD3D12PolygonMode(PolygonMode);
    CreateInfo.RasterizerState.CullMode                            = ToD3D12CullMode(CullMode);
    CreateInfo.RasterizerState.FrontCounterClockwise               = ToD3D12FrontFace(FrontFace);
    CreateInfo.RasterizerState.DepthClipEnable                     = FALSE;

    /*
        2. Depth Test
    */
    // 2.1 DepthTestEnable
    CreateInfo.DepthStencilState.DepthEnable                       = DepthTestEnable;
    // 2.2 DepthWriteEnable
    CreateInfo.DepthStencilState.DepthWriteMask                    = D3D12_DEPTH_WRITE_MASK_ZERO;
    if (DepthWriteEnable)
        CreateInfo.DepthStencilState.DepthWriteMask                = D3D12_DEPTH_WRITE_MASK_ALL;
    // 2.3 DepthCompareOp
    CreateInfo.DepthStencilState.DepthFunc                         = ToD3D12CompareOp(DepthCompareOp);

    /*
        3. Stencil Test
    */
    CreateInfo.DepthStencilState.StencilEnable                     = FALSE;

    /*
        4. Multisample
    */
    // 4.1 SampleCount
    CreateInfo.SampleDesc.Count                                    = ToD3D12SampleCount(SampleCount);
    CreateInfo.SampleDesc.Quality                                  = 0;
    CreateInfo.SampleMask                                          = UINT_MAX;

    /*
        5. Input Assembly
    */
    // 5.1 Topology
    CreateInfo.PrimitiveTopologyType                               = ToD3D12PrimitiveTopology(Topology);

    /*
        6. Shader
    */
    for (int i = 0; i < Shaders.size(); i++)
    {
        ID3DBlob* Handle = ((D3D12Shader*)Shaders[i])->GetHandle();
        if (Shaders[i]->GetType() == RHIShaderType::Vertex)
        {
            CreateInfo.VS = { Handle->GetBufferPointer(), Handle->GetBufferSize()};
        }
        else if (Shaders[i]->GetType() == RHIShaderType::Fragment)
        {
            CreateInfo.PS = { Handle->GetBufferPointer(), Handle->GetBufferSize() };
        }
        else if (Shaders[i]->GetType() == RHIShaderType::Geometry)
        {
            CreateInfo.GS = { Handle->GetBufferPointer(), Handle->GetBufferSize() };
        }
    }

    /*
        7. Vertex Input Bindings & Attributes
    */
    std::vector<D3D12_INPUT_ELEMENT_DESC> VertexInputBindingDescriptions;
    for (int i = 0; i < VertexInputLayout.Attributes.size(); i++)
    {
        D3D12_INPUT_ELEMENT_DESC VertexInputBindingDescription;
        VertexInputBindingDescription.SemanticIndex =  0;
        VertexInputBindingDescription.InputSlot = VertexInputLayout.Attributes[i].GetBinding();
        VertexInputBindingDescription.SemanticName = VertexInputLayout.Attributes[i].GetName();
        VertexInputBindingDescription.Format = ToD3D12Format(VertexInputLayout.Attributes[i].GetFormat());
        VertexInputBindingDescription.AlignedByteOffset = VertexInputLayout.Attributes[i].GetOffset();
        VertexInputBindingDescription.InputSlotClass = ToD3D12InputClassification(VertexInputLayout.Bindings[i].GetInstanceStepRate());
        VertexInputBindingDescription.InstanceDataStepRate = 0;
        VertexInputBindingDescriptions.push_back(VertexInputBindingDescription);
    }
    CreateInfo.InputLayout = { VertexInputBindingDescriptions.data(), (UINT)VertexInputBindingDescriptions.size() };

    /*
        8. Blend
    */
    CreateInfo.BlendState.AlphaToCoverageEnable = FALSE;
    CreateInfo.BlendState.IndependentBlendEnable = FALSE;
    CreateInfo.BlendState.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;


    CreateInfo.NumRenderTargets = 1;
    CreateInfo.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;

    if (FAILED(Device->CreateGraphicsPipelineState(&CreateInfo, IID_PPV_ARGS(&Handle)))) {
        std::cerr << "Failed to create PSO" << std::endl;
        return;
    }
}