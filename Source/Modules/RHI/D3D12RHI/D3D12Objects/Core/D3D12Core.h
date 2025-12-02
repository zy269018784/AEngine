#pragma once
#include "D3D12_Includes.h"
#include "RHIObjects/Core/RHICore.h"
#include "RHIObjects/Core/RHIVertexInputAttribute.h"
#include "RHIObjects/Shader/RHIShaderResourceBinding.h"
#include "RHIObjects/Shader/RHIShader.h"
#include <d3d12.h>
#include <cstdint>

inline DXGI_FORMAT ToD3D12IndexType(RHIIndexFormat RHIIndexFormat)
{
    DXGI_FORMAT Format = DXGI_FORMAT_R16_UINT;
    switch (RHIIndexFormat)
    {
    case RHIIndexFormat::IndexUInt16:
        Format = DXGI_FORMAT_R16_UINT;
        break;
    case RHIIndexFormat::IndexUInt32:
        Format = DXGI_FORMAT_R32_UINT;
        break;
    default:
        break;
    }
    return Format;
}

inline D3D12_COMPARISON_FUNC ToD3D12CompareOp(RHICompareOp RHICompareOp)
{
    D3D12_COMPARISON_FUNC Func = D3D12_COMPARISON_FUNC_LESS;
    switch (RHICompareOp)
    {
    case RHICompareOp::Never:
        Func = D3D12_COMPARISON_FUNC_NEVER;
        break;
        case RHICompareOp::CompareOpAlways:
        Func = D3D12_COMPARISON_FUNC_ALWAYS;
        break;
    case RHICompareOp::Equal:
        Func = D3D12_COMPARISON_FUNC_EQUAL;
        break;
    case RHICompareOp::NotEqual:
        Func = D3D12_COMPARISON_FUNC_NOT_EQUAL;
        break;
    case RHICompareOp::Less:
        Func = D3D12_COMPARISON_FUNC_LESS;
        break;
    case RHICompareOp::LessOrEqual:
        Func = D3D12_COMPARISON_FUNC_LESS_EQUAL;
        break;
    case RHICompareOp::Greater:
        Func = D3D12_COMPARISON_FUNC_GREATER;
        break;
    case RHICompareOp::GreaterOrEqual:
        Func = D3D12_COMPARISON_FUNC_GREATER_EQUAL;
        break;
    default:
        break;
    }
    return Func;
}

inline D3D12_TEXTURE_ADDRESS_MODE ToD3D12TextureAddressMode(RHIAddressMode Mode)
{
    D3D12_TEXTURE_ADDRESS_MODE d3dMode;
    switch (Mode)
    {
    case RHIAddressMode::REPEAT:
        d3dMode = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
        break;
    case RHIAddressMode::MIRRORED_REPEAT:
        d3dMode = D3D12_TEXTURE_ADDRESS_MODE_MIRROR;
        break;
    case RHIAddressMode::CLAMP_TO_EDGE:
        d3dMode = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
        break;
    case RHIAddressMode::CLAMP_TO_BORDER:
        d3dMode = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
        break;
    default:
        break;
    }
    return d3dMode;
}

inline D3D12_FILTER ToD3D12Filter(RHIFilter Filter)
{
    D3D12_FILTER d3dFilter;
    switch (Filter)
    {
    case RHIFilter::NEAREST:
        d3dFilter = D3D12_FILTER_MIN_MAG_MIP_POINT;
        break;
    case RHIFilter::LINEAR:
        d3dFilter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
        break;
    default:
        break;
    }
    return d3dFilter;
}

inline D3D12_SRV_DIMENSION ToD3D12SRVDimension(RHITextureType InType)
{
    D3D12_SRV_DIMENSION Dimension;
    switch (InType)
    {
    case RHITextureType::Texture1D:
        Dimension = D3D12_SRV_DIMENSION_TEXTURE1D;
        break;
    case RHITextureType::Texture2D:
        Dimension = D3D12_SRV_DIMENSION_TEXTURE2D;
        break;
    case RHITextureType::Texture3D:
        Dimension = D3D12_SRV_DIMENSION_TEXTURE3D;
        break;
    case RHITextureType::Texture1DArray:
        Dimension = D3D12_SRV_DIMENSION_TEXTURE1DARRAY;
        break;
    case RHITextureType::Texture2DArray:
        Dimension = D3D12_SRV_DIMENSION_TEXTURE2DARRAY;
        break;
    case RHITextureType::TextureCubeMap:
        Dimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
        break;
    case RHITextureType::TextureCubeMapArray:
        Dimension = D3D12_SRV_DIMENSION_TEXTURECUBEARRAY;
        break;
    default:
        Dimension = D3D12_SRV_DIMENSION_UNKNOWN;
        break;
    }
    return Dimension;
}

inline D3D12_RESOURCE_DIMENSION TextureTypeToResourceDimension(RHITextureType ResourceType)
{
    D3D12_RESOURCE_DIMENSION Dimension;
    switch (ResourceType)
    {
    case RHITextureType::Texture1D:
    case RHITextureType::Texture1DArray:
        Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE1D;
        break;
    case RHITextureType::Texture2D:
    case RHITextureType::Texture2DArray:
    case RHITextureType::TextureCubeMap:
    case RHITextureType::TextureCubeMapArray:
        Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
        break;
    case RHITextureType::Texture3D:
        Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE3D;
        break;
    default:
        Dimension = D3D12_RESOURCE_DIMENSION_UNKNOWN;
        break;
    }
    return Dimension;
}

inline UINT ToD3D12SampleCount(std::uint32_t InSampleCount)
{
    UINT SampleCount = 1;
    switch (InSampleCount)
    {
    case 1:
        SampleCount = 1;
        break;
    case 2:
        SampleCount = 2;
        break;
    case 4:
        SampleCount = 4;
        break;
    case 8:
        SampleCount = 8;
        break;
    case 16:
        SampleCount = 16;
        break;
    case 32:
        SampleCount = 32;
        break;
    case 64:
        SampleCount = 64;
        break;
    default:
        break;
    }
    return SampleCount;
}

inline D3D12_FILL_MODE ToD3D12PolygonMode(RHIPolygonMode RHIPolygonMode)
{
    D3D12_FILL_MODE Mode;
    switch (RHIPolygonMode)
    {
    case RHIPolygonMode::Fill:
        Mode = D3D12_FILL_MODE_SOLID;
        break;
    case RHIPolygonMode::Line:
        Mode = D3D12_FILL_MODE_WIREFRAME;
        break;
    case RHIPolygonMode::Point:
        // D3D12 没有直接的点填充模式，使用线框模式近似
        Mode = D3D12_FILL_MODE_WIREFRAME;
        break;
    default:
        break;
    }
    return Mode;
}

inline D3D12_CULL_MODE ToD3D12CullMode(RHICullMode RHICullMode)
{
    D3D12_CULL_MODE Mode = D3D12_CULL_MODE_NONE;
    switch (RHICullMode)
    {
    case RHICullMode::Front:
        Mode = D3D12_CULL_MODE_FRONT;
        break;
    case RHICullMode::Back:
        Mode = D3D12_CULL_MODE_BACK;
        break;
    case RHICullMode::Front_Back:
        // D3D12 不支持同时剔除前后，使用背面剔除
        Mode = D3D12_CULL_MODE_BACK;
        break;
    default:
        Mode = D3D12_CULL_MODE_NONE;
        break;
    }
    return Mode;
}

inline BOOL ToD3D12FrontFace(RHIFrontFace RHIFrontFace)
{
    BOOL FrontCounterClockwise;
    switch (RHIFrontFace)
    {
    case RHIFrontFace::CW:
        FrontCounterClockwise = FALSE;
        break;
    case RHIFrontFace::CCW:
        FrontCounterClockwise = TRUE;
        break;
    default:
        FrontCounterClockwise = TRUE;
        break;
    }
    return FrontCounterClockwise;
}

inline D3D12_COMPARISON_FUNC ToD3D12DepthComparisonFunc(RHICompareOp RHICompareOp)
{
    D3D12_COMPARISON_FUNC Func = D3D12_COMPARISON_FUNC_LESS;
    switch (RHICompareOp)
    {
    case RHICompareOp::Never:
        Func = D3D12_COMPARISON_FUNC_NEVER;
        break;
        case RHICompareOp::CompareOpAlways:
        Func = D3D12_COMPARISON_FUNC_ALWAYS;
        break;
    case RHICompareOp::Equal:
        Func = D3D12_COMPARISON_FUNC_EQUAL;
        break;
    case RHICompareOp::NotEqual:
        Func = D3D12_COMPARISON_FUNC_NOT_EQUAL;
        break;
    case RHICompareOp::Less:
        Func = D3D12_COMPARISON_FUNC_LESS;
        break;
    case RHICompareOp::LessOrEqual:
        Func = D3D12_COMPARISON_FUNC_LESS_EQUAL;
        break;
    case RHICompareOp::Greater:
        Func = D3D12_COMPARISON_FUNC_GREATER;
        break;
    case RHICompareOp::GreaterOrEqual:
        Func = D3D12_COMPARISON_FUNC_GREATER_EQUAL;
        break;
    default:
        break;
    }
    return Func;
}

inline D3D12_STENCIL_OP ToD3D12StencilOp(RHIStencilOp RHIStencilOp)
{
    D3D12_STENCIL_OP Op;
    switch (RHIStencilOp)
    {
    case RHIStencilOp::Keep:
        Op = D3D12_STENCIL_OP_KEEP;
        break;
    case RHIStencilOp::Zero:
        Op = D3D12_STENCIL_OP_ZERO;
        break;
    case RHIStencilOp::Replace:
        Op = D3D12_STENCIL_OP_REPLACE;
        break;
    case RHIStencilOp::Incr:
        Op = D3D12_STENCIL_OP_INCR_SAT;
        break;
    case RHIStencilOp::IncrWrap:
        Op = D3D12_STENCIL_OP_INCR;
        break;
    case RHIStencilOp::Decr:
        Op = D3D12_STENCIL_OP_DECR_SAT;
        break;
    case RHIStencilOp::DecrWrap:
        Op = D3D12_STENCIL_OP_DECR;
        break;
    case RHIStencilOp::Invert:
        Op = D3D12_STENCIL_OP_INVERT;
        break;
    default:
        break;
    }
    return Op;
}

inline D3D12_BLEND_OP ToD3D12BlendOp(RHIBlendOp RHIBlendOp)
{
    D3D12_BLEND_OP Op;
    switch (RHIBlendOp)
    {
    case RHIBlendOp::Add:
        Op = D3D12_BLEND_OP_ADD;
        break;
    case RHIBlendOp::Sub:
        Op = D3D12_BLEND_OP_SUBTRACT;
        break;
    case RHIBlendOp::Min:
        Op = D3D12_BLEND_OP_MIN;
        break;
    case RHIBlendOp::Max:
        Op = D3D12_BLEND_OP_MAX;
        break;
    case RHIBlendOp::Reverse_Sub:
        Op = D3D12_BLEND_OP_REV_SUBTRACT;
        break;
    default:
        break;
    }
    return Op;
}

inline D3D12_BLEND ToD3D12Blend(RHIBlendFactor RHIBlendFactor)
{
    D3D12_BLEND Blend;
    switch (RHIBlendFactor)
    {
    case RHIBlendFactor::Zero:
        Blend = D3D12_BLEND_ZERO;
        break;
    case RHIBlendFactor::One:
        Blend = D3D12_BLEND_ONE;
        break;
    case RHIBlendFactor::SrcColor:
        Blend = D3D12_BLEND_SRC_COLOR;
        break;
    case RHIBlendFactor::OneMinusSrcColor:
        Blend = D3D12_BLEND_INV_SRC_COLOR;
        break;
    case RHIBlendFactor::DstColor:
        Blend = D3D12_BLEND_DEST_COLOR;
        break;
    case RHIBlendFactor::OneMinusDstColor:
        Blend = D3D12_BLEND_INV_DEST_COLOR;
        break;
    case RHIBlendFactor::SrcAlpha:
        Blend = D3D12_BLEND_SRC_ALPHA;
        break;
    case RHIBlendFactor::OneMinusSrcAlpha:
        Blend = D3D12_BLEND_INV_SRC_ALPHA;
        break;
    case RHIBlendFactor::DstAlpha:
        Blend = D3D12_BLEND_DEST_ALPHA;
        break;
    case RHIBlendFactor::OneMinusDstAlpha:
        Blend = D3D12_BLEND_INV_DEST_ALPHA;
        break;
    case RHIBlendFactor::ConstantColor:
        Blend = D3D12_BLEND_BLEND_FACTOR;
        break;
    case RHIBlendFactor::OneMinusConstantColor:
        Blend = D3D12_BLEND_INV_BLEND_FACTOR;
        break;
    case RHIBlendFactor::ConstantAlpha:
        Blend = D3D12_BLEND_BLEND_FACTOR;
        break;
    case RHIBlendFactor::OneMinusConstantAlpha:
        Blend = D3D12_BLEND_INV_BLEND_FACTOR;
        break;
    case RHIBlendFactor::SrcAlphaSaturate:
        Blend = D3D12_BLEND_SRC_ALPHA_SAT;
        break;
    case RHIBlendFactor::Src1Color:
        Blend = D3D12_BLEND_SRC1_COLOR;
        break;
    case RHIBlendFactor::OneMinusSrc1Color:
        Blend = D3D12_BLEND_INV_SRC1_COLOR;
        break;
    case RHIBlendFactor::Src1Alpha:
        Blend = D3D12_BLEND_SRC1_ALPHA;
        break;
    case RHIBlendFactor::OneMinusSrc1Alpha:
        Blend = D3D12_BLEND_INV_SRC1_ALPHA;
        break;
    default:
        Blend = D3D12_BLEND_ZERO;
        break;
    }
    return Blend;
}

inline D3D12_PRIMITIVE_TOPOLOGY_TYPE ToD3D12PrimitiveTopology(RHITopology RHITopology)
{
    D3D12_PRIMITIVE_TOPOLOGY_TYPE Topology = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    switch (RHITopology)
    {
    case RHITopology::Points:
        Topology = D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT;
        break;
    case RHITopology::Lines:
    case RHITopology::LineStrip:
        Topology = D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE;
        break;
    case RHITopology::Triangles:
    case RHITopology::TriangleStrip:
    case RHITopology::TriangleFan:
        Topology = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
        break;
    case RHITopology::Patches:
        Topology = D3D12_PRIMITIVE_TOPOLOGY_TYPE_PATCH;
        break;
    default:
        break;
    }
    return Topology;
}

inline D3D_PRIMITIVE_TOPOLOGY ToD3DPrimitiveTopology(RHITopology RHITopology)
{
    D3D_PRIMITIVE_TOPOLOGY Topology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    switch (RHITopology)
    {
    case RHITopology::Points:
        Topology = D3D_PRIMITIVE_TOPOLOGY_POINTLIST;
        break;
    case RHITopology::Lines:
        Topology = D3D_PRIMITIVE_TOPOLOGY_LINELIST;
        break;
    case RHITopology::LineStrip:
        Topology = D3D_PRIMITIVE_TOPOLOGY_LINESTRIP;
        break;
    case RHITopology::Triangles:
        Topology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
        break;
    case RHITopology::TriangleStrip:
        Topology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
        break;
    case RHITopology::TriangleFan:
        // D3D12 不支持三角形扇，需要转换为三角形列表
        Topology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
        break;
    case RHITopology::Patches:
        Topology = D3D_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST;
        break;
    default:
        break;
    }
    return Topology;
}

inline D3D12_SHADER_VISIBILITY ToD3D12ShaderVisibility(RHIShaderType Type)
{
    D3D12_SHADER_VISIBILITY Visibility = D3D12_SHADER_VISIBILITY_VERTEX;
    switch (Type)
    {
    case RHIShaderType::Vertex:
        Visibility = D3D12_SHADER_VISIBILITY_VERTEX;
        break;
    case RHIShaderType::TessellationControl:
        Visibility = D3D12_SHADER_VISIBILITY_HULL;
        break;
    case RHIShaderType::TessellationEvaluation:
        Visibility = D3D12_SHADER_VISIBILITY_DOMAIN;
        break;
    case RHIShaderType::Fragment:
        Visibility = D3D12_SHADER_VISIBILITY_PIXEL;
        break;
    case RHIShaderType::Compute:
        Visibility = D3D12_SHADER_VISIBILITY_ALL; // Compute 通常使用 ALL
        break;
    case RHIShaderType::Geometry:
        Visibility = D3D12_SHADER_VISIBILITY_GEOMETRY;
        break;
    case RHIShaderType::Mesh:
        // Mesh shader 在 D3D12 中较新，可能需要特定处理
        Visibility = D3D12_SHADER_VISIBILITY_ALL;
        break;
    case RHIShaderType::Task:
        // Task shader 在 D3D12 中较新，可能需要特定处理
        Visibility = D3D12_SHADER_VISIBILITY_ALL;
        break;
    default:
        break;
    }
    return Visibility;
}

inline D3D12_LOGIC_OP ToD3D12LogicOp(RHILogicOp RHILogicOp)
{
    D3D12_LOGIC_OP Op = D3D12_LOGIC_OP_NOOP;
    switch (RHILogicOp)
    {
    case RHILogicOp::CLEAR:
        Op = D3D12_LOGIC_OP_CLEAR;
        break;
    case RHILogicOp::SET:
        Op = D3D12_LOGIC_OP_SET;
        break;
    case RHILogicOp::COPY:
        Op = D3D12_LOGIC_OP_COPY;
        break;
    case RHILogicOp::COPY_INVERTED:
        Op = D3D12_LOGIC_OP_COPY_INVERTED;
        break;
    case RHILogicOp::NOOP:
        Op = D3D12_LOGIC_OP_NOOP;
        break;
    case RHILogicOp::INVERT:
        Op = D3D12_LOGIC_OP_INVERT;
        break;
    case RHILogicOp::AND:
        Op = D3D12_LOGIC_OP_AND;
        break;
    case RHILogicOp::NAND:
        Op = D3D12_LOGIC_OP_NAND;
        break;
    case RHILogicOp::OR:
        Op = D3D12_LOGIC_OP_OR;
        break;
    case RHILogicOp::NOR:
        Op = D3D12_LOGIC_OP_NOR;
        break;
    case RHILogicOp::XOR:
        Op = D3D12_LOGIC_OP_XOR;
        break;
    case RHILogicOp::EQUIV:
        Op = D3D12_LOGIC_OP_EQUIV;
        break;
    case RHILogicOp::AND_REVERSE:
        Op = D3D12_LOGIC_OP_AND_REVERSE;
        break;
    case RHILogicOp::AND_INVERTED:
        Op = D3D12_LOGIC_OP_AND_INVERTED;
        break;
    case RHILogicOp::OR_REVERSE:
        Op = D3D12_LOGIC_OP_OR_REVERSE;
        break;
    case RHILogicOp::OR_INVERTED:
        Op = D3D12_LOGIC_OP_OR_INVERTED;
        break;
    default:
        break;
    }
    return Op;
}

inline D3D12_INPUT_CLASSIFICATION ToD3D12InputClassification(std::uint32_t StepRate)
{
    D3D12_INPUT_CLASSIFICATION Classification = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
    switch (StepRate)
    {
    case 0:
        Classification = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
        break;
    case 1:
        Classification = D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA;
        break;
    default:
        break;
    }
    return Classification;
}

inline DXGI_FORMAT ToD3D12Format(RHIVertexInputAttribute::Format Format)
{
    DXGI_FORMAT fmt;
    switch (Format)
    {
    case RHIVertexInputAttribute::Float4:
        fmt = DXGI_FORMAT_R32G32B32A32_FLOAT;
        break;
    case RHIVertexInputAttribute::Float3:
        fmt = DXGI_FORMAT_R32G32B32_FLOAT;
        break;
    case RHIVertexInputAttribute::Float2:
        fmt = DXGI_FORMAT_R32G32_FLOAT;
        break;
    case RHIVertexInputAttribute::Float:
        fmt = DXGI_FORMAT_R32_FLOAT;
        break;
    case RHIVertexInputAttribute::UNormByte4:
        fmt = DXGI_FORMAT_R8G8B8A8_UNORM;
        break;
    case RHIVertexInputAttribute::UNormByte2:
        fmt = DXGI_FORMAT_R8G8_UNORM;
        break;
    case RHIVertexInputAttribute::UNormByte:
        fmt = DXGI_FORMAT_R8_UNORM;
        break;
    case RHIVertexInputAttribute::UInt4:
        fmt = DXGI_FORMAT_R32G32B32A32_UINT;
        break;
    case RHIVertexInputAttribute::UInt3:
        fmt = DXGI_FORMAT_R32G32B32_UINT;
        break;
    case RHIVertexInputAttribute::UInt2:
        fmt = DXGI_FORMAT_R32G32_UINT;
        break;
    case RHIVertexInputAttribute::UInt:
        fmt = DXGI_FORMAT_R32_UINT;
        break;
    case RHIVertexInputAttribute::SInt4:
        fmt = DXGI_FORMAT_R32G32B32A32_SINT;
        break;
    case RHIVertexInputAttribute::SInt3:
        fmt = DXGI_FORMAT_R32G32B32_SINT;
        break;
    case RHIVertexInputAttribute::SInt2:
        fmt = DXGI_FORMAT_R32G32_SINT;
        break;
    case RHIVertexInputAttribute::SInt:
        fmt = DXGI_FORMAT_R32_SINT;
        break;
    case RHIVertexInputAttribute::Half4:
        fmt = DXGI_FORMAT_R16G16B16A16_FLOAT;
        break;
    case RHIVertexInputAttribute::Half3:
        //fmt = DXGI_FORMAT_R16G16B16_FLOAT;
        break;
    case RHIVertexInputAttribute::Half2:
        fmt = DXGI_FORMAT_R16G16_FLOAT;
        break;
    case RHIVertexInputAttribute::Half:
        fmt = DXGI_FORMAT_R16_FLOAT;
        break;
    default:
        fmt = DXGI_FORMAT_UNKNOWN;
        break;
    }
    return fmt;
}

