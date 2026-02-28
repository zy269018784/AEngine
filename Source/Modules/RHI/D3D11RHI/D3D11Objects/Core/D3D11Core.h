#pragma once
#include "D3D11_Includes.h"
#include "RHIObjects/Core/RHICore.h"
#include "RHIObjects/Core/RHIVertexInputAttribute.h"
#include "RHIObjects/Shader/RHIShaderResourceBinding.h"
#include "RHIObjects/Shader/RHIShader.h"
#include <d3d11.h>
#include <d3d11_1.h>  // 如果需要D3D11.1特性
#include <cstdint>

inline DXGI_FORMAT ToD3D11IndexType(RHIIndexFormat RHIIndexFormat)
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

inline D3D11_COMPARISON_FUNC ToD3D11CompareOp(RHICompareOp RHICompareOp)
{
    D3D11_COMPARISON_FUNC Func = D3D11_COMPARISON_LESS;
    switch (RHICompareOp)
    {
    case RHICompareOp::Never:
        Func = D3D11_COMPARISON_NEVER;
        break;
    case RHICompareOp::CompareOpAlways:
        Func = D3D11_COMPARISON_ALWAYS;
        break;
    case RHICompareOp::Equal:
        Func = D3D11_COMPARISON_EQUAL;
        break;
    case RHICompareOp::NotEqual:
        Func = D3D11_COMPARISON_NOT_EQUAL;
        break;
    case RHICompareOp::Less:
        Func = D3D11_COMPARISON_LESS;
        break;
    case RHICompareOp::LessOrEqual:
        Func = D3D11_COMPARISON_LESS_EQUAL;
        break;
    case RHICompareOp::Greater:
        Func = D3D11_COMPARISON_GREATER;
        break;
    case RHICompareOp::GreaterOrEqual:
        Func = D3D11_COMPARISON_GREATER_EQUAL;
        break;
    default:
        break;
    }
    return Func;
}

inline D3D11_TEXTURE_ADDRESS_MODE ToD3D11TextureAddressMode(RHIAddressMode Mode)
{
    D3D11_TEXTURE_ADDRESS_MODE d3dMode = D3D11_TEXTURE_ADDRESS_WRAP;
    switch (Mode)
    {
    case RHIAddressMode::REPEAT:
        d3dMode = D3D11_TEXTURE_ADDRESS_WRAP;
        break;
    case RHIAddressMode::MIRRORED_REPEAT:
        d3dMode = D3D11_TEXTURE_ADDRESS_MIRROR;
        break;
    case RHIAddressMode::CLAMP_TO_EDGE:
        d3dMode = D3D11_TEXTURE_ADDRESS_CLAMP;
        break;
    case RHIAddressMode::CLAMP_TO_BORDER:
        d3dMode = D3D11_TEXTURE_ADDRESS_BORDER;
        break;
    //case RHIAddressMode::MIRROR_CLAMP_TO_EDGE:
    //    d3dMode = D3D11_TEXTURE_ADDRESS_MIRROR_ONCE;
    //    break;
    default:
        break;
    }
    return d3dMode;
}

inline D3D11_FILTER ToD3D11Filter(RHIFilter Filter)
{
    D3D11_FILTER d3dFilter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    switch (Filter)
    {
    case RHIFilter::NEAREST:
        d3dFilter = D3D11_FILTER_MIN_MAG_MIP_POINT;
        break;
    case RHIFilter::LINEAR:
        d3dFilter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        break;
    //case RHIFilter::CUBIC:
    //    // D3D11没有直接的cubic filter，使用各向异性过滤近似
    //    d3dFilter = D3D11_FILTER_ANISOTROPIC;
    //    break;
    default:
        break;
    }
    return d3dFilter;
}

inline D3D11_SRV_DIMENSION ToD3D11SRVDimension(RHITextureType InType)
{
    D3D11_SRV_DIMENSION Dimension = D3D11_SRV_DIMENSION_UNKNOWN;
    switch (InType)
    {
    case RHITextureType::Texture1D:
        Dimension = D3D11_SRV_DIMENSION_TEXTURE1D;
        break;
    case RHITextureType::Texture2D:
        Dimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        break;
    case RHITextureType::Texture3D:
        Dimension = D3D11_SRV_DIMENSION_TEXTURE3D;
        break;
    case RHITextureType::Texture1DArray:
        Dimension = D3D11_SRV_DIMENSION_TEXTURE1DARRAY;
        break;
    case RHITextureType::Texture2DArray:
        Dimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
        break;
    case RHITextureType::TextureCubeMap:
        Dimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
        break;
    case RHITextureType::TextureCubeMapArray:
        Dimension = D3D11_SRV_DIMENSION_TEXTURECUBEARRAY;
        break;
    default:
        Dimension = D3D11_SRV_DIMENSION_UNKNOWN;
        break;
    }
    return Dimension;
}

inline D3D11_RESOURCE_DIMENSION TextureTypeToResourceDimension(RHITextureType ResourceType)
{
    D3D11_RESOURCE_DIMENSION Dimension = D3D11_RESOURCE_DIMENSION_UNKNOWN;
    switch (ResourceType)
    {
    case RHITextureType::Texture1D:
    case RHITextureType::Texture1DArray:
        Dimension = D3D11_RESOURCE_DIMENSION_TEXTURE1D;
        break;
    case RHITextureType::Texture2D:
    case RHITextureType::Texture2DArray:
    case RHITextureType::TextureCubeMap:
    case RHITextureType::TextureCubeMapArray:
        Dimension = D3D11_RESOURCE_DIMENSION_TEXTURE2D;
        break;
    case RHITextureType::Texture3D:
        Dimension = D3D11_RESOURCE_DIMENSION_TEXTURE3D;
        break;
    default:
        Dimension = D3D11_RESOURCE_DIMENSION_UNKNOWN;
        break;
    }
    return Dimension;
}

inline UINT ToD3D11SampleCount(std::uint32_t InSampleCount)
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

inline D3D11_FILL_MODE ToD3D11PolygonMode(RHIPolygonMode RHIPolygonMode)
{
    D3D11_FILL_MODE Mode = D3D11_FILL_SOLID;
    switch (RHIPolygonMode)
    {
    case RHIPolygonMode::Fill:
        Mode = D3D11_FILL_SOLID;
        break;
    case RHIPolygonMode::Line:
        Mode = D3D11_FILL_WIREFRAME;
        break;
    case RHIPolygonMode::Point:
        // D3D11没有直接的点填充模式，使用线框模式近似
        Mode = D3D11_FILL_WIREFRAME;
        break;
    default:
        break;
    }
    return Mode;
}

inline D3D11_CULL_MODE ToD3D11CullMode(RHICullMode RHICullMode)
{
    D3D11_CULL_MODE Mode = D3D11_CULL_NONE;
    switch (RHICullMode)
    {
    case RHICullMode::Front:
        Mode = D3D11_CULL_FRONT;
        break;
    case RHICullMode::Back:
        Mode = D3D11_CULL_BACK;
        break;
    case RHICullMode::Front_Back:
        // D3D11 不支持同时剔除前后，不剔除
        Mode = D3D11_CULL_NONE;
        break;
    default:
        Mode = D3D11_CULL_NONE;
        break;
    }
    return Mode;
}

inline BOOL ToD3D11FrontFace(RHIFrontFace RHIFrontFace)
{
    BOOL FrontCounterClockwise = TRUE;
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

inline D3D11_COMPARISON_FUNC ToD3D11DepthComparisonFunc(RHICompareOp RHICompareOp)
{
    D3D11_COMPARISON_FUNC Func = D3D11_COMPARISON_LESS;
    switch (RHICompareOp)
    {
    case RHICompareOp::Never:
        Func = D3D11_COMPARISON_NEVER;
        break;
    case RHICompareOp::CompareOpAlways:
        Func = D3D11_COMPARISON_ALWAYS;
        break;
    case RHICompareOp::Equal:
        Func = D3D11_COMPARISON_EQUAL;
        break;
    case RHICompareOp::NotEqual:
        Func = D3D11_COMPARISON_NOT_EQUAL;
        break;
    case RHICompareOp::Less:
        Func = D3D11_COMPARISON_LESS;
        break;
    case RHICompareOp::LessOrEqual:
        Func = D3D11_COMPARISON_LESS_EQUAL;
        break;
    case RHICompareOp::Greater:
        Func = D3D11_COMPARISON_GREATER;
        break;
    case RHICompareOp::GreaterOrEqual:
        Func = D3D11_COMPARISON_GREATER_EQUAL;
        break;
    default:
        break;
    }
    return Func;
}

inline D3D11_STENCIL_OP ToD3D11StencilOp(RHIStencilOp RHIStencilOp)
{
    D3D11_STENCIL_OP Op = D3D11_STENCIL_OP_KEEP;
    switch (RHIStencilOp)
    {
    case RHIStencilOp::Keep:
        Op = D3D11_STENCIL_OP_KEEP;
        break;
    case RHIStencilOp::Zero:
        Op = D3D11_STENCIL_OP_ZERO;
        break;
    case RHIStencilOp::Replace:
        Op = D3D11_STENCIL_OP_REPLACE;
        break;
    case RHIStencilOp::Incr:
        Op = D3D11_STENCIL_OP_INCR_SAT;
        break;
    case RHIStencilOp::IncrWrap:
        Op = D3D11_STENCIL_OP_INCR;
        break;
    case RHIStencilOp::Decr:
        Op = D3D11_STENCIL_OP_DECR_SAT;
        break;
    case RHIStencilOp::DecrWrap:
        Op = D3D11_STENCIL_OP_DECR;
        break;
    case RHIStencilOp::Invert:
        Op = D3D11_STENCIL_OP_INVERT;
        break;
    default:
        break;
    }
    return Op;
}

inline D3D11_BLEND_OP ToD3D11BlendOp(RHIBlendOp RHIBlendOp)
{
    D3D11_BLEND_OP Op = D3D11_BLEND_OP_ADD;
    switch (RHIBlendOp)
    {
    case RHIBlendOp::Add:
        Op = D3D11_BLEND_OP_ADD;
        break;
    case RHIBlendOp::Sub:
        Op = D3D11_BLEND_OP_SUBTRACT;
        break;
    case RHIBlendOp::Min:
        Op = D3D11_BLEND_OP_MIN;
        break;
    case RHIBlendOp::Max:
        Op = D3D11_BLEND_OP_MAX;
        break;
    case RHIBlendOp::Reverse_Sub:
        Op = D3D11_BLEND_OP_REV_SUBTRACT;
        break;
    default:
        break;
    }
    return Op;
}

inline D3D11_BLEND ToD3D11Blend(RHIBlendFactor RHIBlendFactor)
{
    D3D11_BLEND Blend = D3D11_BLEND_ZERO;
    switch (RHIBlendFactor)
    {
    case RHIBlendFactor::Zero:
        Blend = D3D11_BLEND_ZERO;
        break;
    case RHIBlendFactor::One:
        Blend = D3D11_BLEND_ONE;
        break;
    case RHIBlendFactor::SrcColor:
        Blend = D3D11_BLEND_SRC_COLOR;
        break;
    case RHIBlendFactor::OneMinusSrcColor:
        Blend = D3D11_BLEND_INV_SRC_COLOR;
        break;
    case RHIBlendFactor::DstColor:
        Blend = D3D11_BLEND_DEST_COLOR;
        break;
    case RHIBlendFactor::OneMinusDstColor:
        Blend = D3D11_BLEND_INV_DEST_COLOR;
        break;
    case RHIBlendFactor::SrcAlpha:
        Blend = D3D11_BLEND_SRC_ALPHA;
        break;
    case RHIBlendFactor::OneMinusSrcAlpha:
        Blend = D3D11_BLEND_INV_SRC_ALPHA;
        break;
    case RHIBlendFactor::DstAlpha:
        Blend = D3D11_BLEND_DEST_ALPHA;
        break;
    case RHIBlendFactor::OneMinusDstAlpha:
        Blend = D3D11_BLEND_INV_DEST_ALPHA;
        break;
    case RHIBlendFactor::ConstantColor:
    case RHIBlendFactor::ConstantAlpha:
        Blend = D3D11_BLEND_BLEND_FACTOR;
        break;
    case RHIBlendFactor::OneMinusConstantColor:
    case RHIBlendFactor::OneMinusConstantAlpha:
        Blend = D3D11_BLEND_INV_BLEND_FACTOR;
        break;
    case RHIBlendFactor::SrcAlphaSaturate:
        Blend = D3D11_BLEND_SRC_ALPHA_SAT;
        break;
    case RHIBlendFactor::Src1Color:
        Blend = D3D11_BLEND_SRC1_COLOR;
        break;
    case RHIBlendFactor::OneMinusSrc1Color:
        Blend = D3D11_BLEND_INV_SRC1_COLOR;
        break;
    case RHIBlendFactor::Src1Alpha:
        Blend = D3D11_BLEND_SRC1_ALPHA;
        break;
    case RHIBlendFactor::OneMinusSrc1Alpha:
        Blend = D3D11_BLEND_INV_SRC1_ALPHA;
        break;
    default:
        Blend = D3D11_BLEND_ZERO;
        break;
    }
    return Blend;
}

inline D3D11_PRIMITIVE_TOPOLOGY ToD3D11Topology(RHITopology RHITopology)
{
    D3D11_PRIMITIVE_TOPOLOGY Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    switch (RHITopology)
    {
    case RHITopology::Points:
        Topology = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
        break;
    case RHITopology::Lines:
        Topology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
        break;
    case RHITopology::LineStrip:
        Topology = D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
        break;
    case RHITopology::Triangles:
        Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
        break;
    case RHITopology::TriangleStrip:
        Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
        break;
    case RHITopology::TriangleFan:
        // D3D11 不支持三角形扇，需要转换为三角形列表
        Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
        break;
    case RHITopology::LinesWithAdjacency:
        Topology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST_ADJ;
        break;
    case RHITopology::LineStripWithAdjacency:
        Topology = D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ;
        break;
    case RHITopology::TrianglesWithAdjacency:
        Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ;
        break;
    case RHITopology::TriangleStripWithAdjacency:
        Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ;
        break;
    case RHITopology::Patches:
        // 对于面片拓扑，D3D11需要指定控制点数量
        // 返回基础值，实际使用时需要根据控制点数量选择
        Topology = D3D11_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST;
        break;
    default:
        break;
    }
    return Topology;
}

inline D3D11_LOGIC_OP ToD3D11LogicOp(RHILogicOp RHILogicOp)
{
    D3D11_LOGIC_OP Op = D3D11_LOGIC_OP_NOOP;
    switch (RHILogicOp)
    {
    case RHILogicOp::CLEAR:
        Op = D3D11_LOGIC_OP_CLEAR;
        break;
    case RHILogicOp::SET:
        Op = D3D11_LOGIC_OP_SET;
        break;
    case RHILogicOp::COPY:
        Op = D3D11_LOGIC_OP_COPY;
        break;
    case RHILogicOp::COPY_INVERTED:
        Op = D3D11_LOGIC_OP_COPY_INVERTED;
        break;
    case RHILogicOp::NOOP:
        Op = D3D11_LOGIC_OP_NOOP;
        break;
    case RHILogicOp::INVERT:
        Op = D3D11_LOGIC_OP_INVERT;
        break;
    case RHILogicOp::AND:
        Op = D3D11_LOGIC_OP_AND;
        break;
    case RHILogicOp::NAND:
        Op = D3D11_LOGIC_OP_NAND;
        break;
    case RHILogicOp::OR:
        Op = D3D11_LOGIC_OP_OR;
        break;
    case RHILogicOp::NOR:
        Op = D3D11_LOGIC_OP_NOR;
        break;
    case RHILogicOp::XOR:
        Op = D3D11_LOGIC_OP_XOR;
        break;
    case RHILogicOp::EQUIV:
        Op = D3D11_LOGIC_OP_EQUIV;
        break;
    case RHILogicOp::AND_REVERSE:
        Op = D3D11_LOGIC_OP_AND_REVERSE;
        break;
    case RHILogicOp::AND_INVERTED:
        Op = D3D11_LOGIC_OP_AND_INVERTED;
        break;
    case RHILogicOp::OR_REVERSE:
        Op = D3D11_LOGIC_OP_OR_REVERSE;
        break;
    case RHILogicOp::OR_INVERTED:
        Op = D3D11_LOGIC_OP_OR_INVERTED;
        break;
    default:
        break;
    }
    return Op;
}

inline D3D11_INPUT_CLASSIFICATION ToD3D11InputClassification(std::uint32_t StepRate)
{
    D3D11_INPUT_CLASSIFICATION Classification = D3D11_INPUT_PER_VERTEX_DATA;
    switch (StepRate)
    {
    case 0:
        Classification = D3D11_INPUT_PER_VERTEX_DATA;
        break;
    case 1:
        Classification = D3D11_INPUT_PER_INSTANCE_DATA;
        break;
    default:
        Classification = D3D11_INPUT_PER_VERTEX_DATA;
        break;
    }
    return Classification;
}

inline DXGI_FORMAT ToD3D11Format(RHIVertexInputAttribute::Format Format)
{
    DXGI_FORMAT fmt = DXGI_FORMAT_UNKNOWN;
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
#if 0
    case RHIVertexInputAttribute::SNormByte4:
        fmt = DXGI_FORMAT_R8G8B8A8_SNORM;
        break;
    case RHIVertexInputAttribute::SNormByte2:
        fmt = DXGI_FORMAT_R8G8_SNORM;
        break;
    case RHIVertexInputAttribute::SNormByte:
        fmt = DXGI_FORMAT_R8_SNORM;
        break;
#endif
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
        // D3D11 没有 R16G16B16_FLOAT 格式，需要打包或使用其他格式
        fmt = DXGI_FORMAT_R16G16B16A16_FLOAT;
        break;
    case RHIVertexInputAttribute::Half2:
        fmt = DXGI_FORMAT_R16G16_FLOAT;
        break;
    case RHIVertexInputAttribute::Half:
        fmt = DXGI_FORMAT_R16_FLOAT;
        break;
#if 0
    case RHIVertexInputAttribute::UIntShort4:
        fmt = DXGI_FORMAT_R16G16B16A16_UINT;
        break;
    case RHIVertexInputAttribute::UIntShort2:
        fmt = DXGI_FORMAT_R16G16_UINT;
        break;
    case RHIVertexInputAttribute::UIntShort:
        fmt = DXGI_FORMAT_R16_UINT;
        break;
    case RHIVertexInputAttribute::SIntShort4:
        fmt = DXGI_FORMAT_R16G16B16A16_SINT;
        break;
    case RHIVertexInputAttribute::SIntShort2:
        fmt = DXGI_FORMAT_R16G16_SINT;
        break;
    case RHIVertexInputAttribute::SIntShort:
        fmt = DXGI_FORMAT_R16_SINT;
        break;
    case RHIVertexInputAttribute::UNormShort4:
        fmt = DXGI_FORMAT_R16G16B16A16_UNORM;
        break;
    case RHIVertexInputAttribute::UNormShort2:
        fmt = DXGI_FORMAT_R16G16_UNORM;
        break;
    case RHIVertexInputAttribute::UNormShort:
        fmt = DXGI_FORMAT_R16_UNORM;
        break;
    case RHIVertexInputAttribute::SNormShort4:
        fmt = DXGI_FORMAT_R16G16B16A16_SNORM;
        break;
    case RHIVertexInputAttribute::SNormShort2:
        fmt = DXGI_FORMAT_R16G16_SNORM;
        break;
    case RHIVertexInputAttribute::SNormShort:
        fmt = DXGI_FORMAT_R16_SNORM;
        break;
#endif
    default:
        fmt = DXGI_FORMAT_UNKNOWN;
        break;
    }
    return fmt;
}

inline DXGI_FORMAT ToD3D11Format(RHIPixelFormat PF)
{
    switch (PF)
    {
    case RHIPixelFormat::PF_Unknown:
        return DXGI_FORMAT_UNKNOWN;

        // 深度模板
    case RHIPixelFormat::PF_DepthStencil:
        // D3D11 常用的深度模板格式
        // 注意：D3D11 创建深度模板视图时需要匹配的格式
        return DXGI_FORMAT_D24_UNORM_S8_UINT;

        // 1通道 - 8位
    case RHIPixelFormat::PF_R8_SINT:
        return DXGI_FORMAT_R8_SINT;
    case RHIPixelFormat::PF_R8_UINT:
        return DXGI_FORMAT_R8_UINT;
    case RHIPixelFormat::PF_R8_SNORM:
        return DXGI_FORMAT_R8_SNORM;
    case RHIPixelFormat::PF_R8_UNORM:
        return DXGI_FORMAT_R8_UNORM;
    case RHIPixelFormat::PF_R8_SRGB:
        // D3D11 没有单独的 R8_SRGB，但可以在创建着色器资源视图时指定 SRGB
        // 或者使用 DXGI_FORMAT_R8_UNORM 配合 D3D11_SHADER_RESOURCE_VIEW_DESC 的 Format 字段
        return DXGI_FORMAT_R8_UNORM;

        // 2通道 - 8位
    case RHIPixelFormat::PF_R8G8_SINT:
        return DXGI_FORMAT_R8G8_SINT;
    case RHIPixelFormat::PF_R8G8_UINT:
        return DXGI_FORMAT_R8G8_UINT;
    case RHIPixelFormat::PF_R8G8_SNORM:
        return DXGI_FORMAT_R8G8_SNORM;
    case RHIPixelFormat::PF_R8G8_UNORM:
        return DXGI_FORMAT_R8G8_UNORM;
    case RHIPixelFormat::PF_R8G8_SRGB:
        return DXGI_FORMAT_R8G8_UNORM; // 同上

        // 3通道 - 8位
    case RHIPixelFormat::PF_R8G8B8_SINT:
        // D3D11 不支持直接的 R8G8B8 格式，必须使用 R8G8B8A8
        // 在着色器中访问时，alpha 通道的值是未定义的
        return DXGI_FORMAT_R8G8B8A8_SINT;
    case RHIPixelFormat::PF_R8G8B8_UINT:
        return DXGI_FORMAT_R8G8B8A8_UINT;
    case RHIPixelFormat::PF_R8G8B8_SNORM:
        return DXGI_FORMAT_R8G8B8A8_SNORM;
    case RHIPixelFormat::PF_R8G8B8_UNORM:
        return DXGI_FORMAT_R8G8B8A8_UNORM;
    case RHIPixelFormat::PF_R8G8B8_SRGB:
        return DXGI_FORMAT_R8G8B8A8_UNORM;

        // 4通道 - 8位
    case RHIPixelFormat::PF_R8G8B8A8_SINT:
        return DXGI_FORMAT_R8G8B8A8_SINT;
    case RHIPixelFormat::PF_R8G8B8A8_UINT:
        return DXGI_FORMAT_R8G8B8A8_UINT;
    case RHIPixelFormat::PF_R8G8B8A8_SNORM:
        return DXGI_FORMAT_R8G8B8A8_SNORM;
    case RHIPixelFormat::PF_R8G8B8A8_UNORM:
        return DXGI_FORMAT_R8G8B8A8_UNORM;
    case RHIPixelFormat::PF_R8G8B8A8_SRGB:
        // D3D11 有专门的 SRGB 格式，应该使用这个
        return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;

        // 1通道 - 16位
    case RHIPixelFormat::PF_R16_SINT:
        return DXGI_FORMAT_R16_SINT;
    case RHIPixelFormat::PF_R16_UINT:
        return DXGI_FORMAT_R16_UINT;
    case RHIPixelFormat::PF_R16_SNORM:
        return DXGI_FORMAT_R16_SNORM;
    case RHIPixelFormat::PF_R16_UNORM:
        return DXGI_FORMAT_R16_UNORM;
    case RHIPixelFormat::PF_R16_FLOAT:
        return DXGI_FORMAT_R16_FLOAT;

        // 2通道 - 16位
    case RHIPixelFormat::PF_R16G16_SINT:
        return DXGI_FORMAT_R16G16_SINT;
    case RHIPixelFormat::PF_R16G16_UINT:
        return DXGI_FORMAT_R16G16_UINT;
    case RHIPixelFormat::PF_R16G16_SNORM:
        return DXGI_FORMAT_R16G16_SNORM;
    case RHIPixelFormat::PF_R16G16_UNORM:
        return DXGI_FORMAT_R16G16_UNORM;
    case RHIPixelFormat::PF_R16G16_FLOAT:
        return DXGI_FORMAT_R16G16_FLOAT;

        // 3通道 - 16位
    case RHIPixelFormat::PF_R16G16B16_SINT:
        // D3D11 不支持 R16G16B16，使用 R16G16B16A16
        return DXGI_FORMAT_R16G16B16A16_SINT;
    case RHIPixelFormat::PF_R16G16B16_UINT:
        return DXGI_FORMAT_R16G16B16A16_UINT;
    case RHIPixelFormat::PF_R16G16B16_SNORM:
        return DXGI_FORMAT_R16G16B16A16_SNORM;
    case RHIPixelFormat::PF_R16G16B16_UNORM:
        return DXGI_FORMAT_R16G16B16A16_UNORM;
    case RHIPixelFormat::PF_R16G16B16_FLOAT:
        return DXGI_FORMAT_R16G16B16A16_FLOAT;

        // 4通道 - 16位
    case RHIPixelFormat::PF_R16G16B16A16_SINT:
        return DXGI_FORMAT_R16G16B16A16_SINT;
    case RHIPixelFormat::PF_R16G16B16A16_UINT:
        return DXGI_FORMAT_R16G16B16A16_UINT;
    case RHIPixelFormat::PF_R16G16B16A16_SNORM:
        return DXGI_FORMAT_R16G16B16A16_SNORM;
    case RHIPixelFormat::PF_R16G16B16A16_UNORM:
        return DXGI_FORMAT_R16G16B16A16_UNORM;
    case RHIPixelFormat::PF_R16G16B16A16_FLOAT:
        return DXGI_FORMAT_R16G16B16A16_FLOAT;

        // 1通道 - 32位
    case RHIPixelFormat::PF_R32_SINT:
        return DXGI_FORMAT_R32_SINT;
    case RHIPixelFormat::PF_R32_UINT:
        return DXGI_FORMAT_R32_UINT;
    case RHIPixelFormat::PF_R32_FLOAT:
        return DXGI_FORMAT_R32_FLOAT;

        // 2通道 - 32位
    case RHIPixelFormat::PF_R32G32_SINT:
        return DXGI_FORMAT_R32G32_SINT;
    case RHIPixelFormat::PF_R32G32_UINT:
        return DXGI_FORMAT_R32G32_UINT;
    case RHIPixelFormat::PF_R32G32_FLOAT:
        return DXGI_FORMAT_R32G32_FLOAT;

        // 3通道 - 32位
    case RHIPixelFormat::PF_R32G32B32_SINT:
        // D3D11 支持 R32G32B32 格式（用于顶点缓冲区等）
        // 但对于纹理，可能需要注意硬件支持情况
        return DXGI_FORMAT_R32G32B32_SINT;
    case RHIPixelFormat::PF_R32G32B32_UINT:
        return DXGI_FORMAT_R32G32B32_UINT;
    case RHIPixelFormat::PF_R32G32B32_FLOAT:
        return DXGI_FORMAT_R32G32B32_FLOAT;

        // 4通道 - 32位
    case RHIPixelFormat::PF_R32G32B32A32_SINT:
        return DXGI_FORMAT_R32G32B32A32_SINT;
    case RHIPixelFormat::PF_R32G32B32A32_UINT:
        return DXGI_FORMAT_R32G32B32A32_UINT;
    case RHIPixelFormat::PF_R32G32B32A32_FLOAT:
        return DXGI_FORMAT_R32G32B32A32_FLOAT;

    default:
        return DXGI_FORMAT_UNKNOWN;
    }
}

// 着色器类型转换
inline const char* ToD3D11ShaderType(RHIShaderType Type, std::uint32_t ShaderModel = 5)
{
    switch (Type)
    {
    case RHIShaderType::Vertex:
        return "vs_5_0";
    case RHIShaderType::Fragment:
        return "ps_5_0";
    case RHIShaderType::Geometry:
        return "gs_5_0";
    case RHIShaderType::TessellationControl:
        return "hs_5_0";
    case RHIShaderType::TessellationEvaluation:
        return "ds_5_0";
    case RHIShaderType::Compute:
        return "cs_5_0";
    default:
        return "vs_5_0";
    }
}

inline UINT RHIPixelFormatToBytesPerPixel(RHIPixelFormat PF)
{
    switch (PF)
    {
    // 深度模板格式
    case RHIPixelFormat::PF_DepthStencil:
        return 4; // D24_UNORM_S8_UINT 通常是4字节

    // 1通道 - 8位 (1字节)
    case RHIPixelFormat::PF_R8_SINT:
    case RHIPixelFormat::PF_R8_UINT:
    case RHIPixelFormat::PF_R8_SNORM:
    case RHIPixelFormat::PF_R8_UNORM:
    case RHIPixelFormat::PF_R8_SRGB:
        return 1;

    // 2通道 - 8位 (2字节)
    case RHIPixelFormat::PF_R8G8_SINT:
    case RHIPixelFormat::PF_R8G8_UINT:
    case RHIPixelFormat::PF_R8G8_SNORM:
    case RHIPixelFormat::PF_R8G8_UNORM:
    case RHIPixelFormat::PF_R8G8_SRGB:
        return 2;

    // 3通道 - 8位 (3字节，但注意D3D11可能用4字节对齐)
    case RHIPixelFormat::PF_R8G8B8_SINT:
    case RHIPixelFormat::PF_R8G8B8_UINT:
    case RHIPixelFormat::PF_R8G8B8_SNORM:
    case RHIPixelFormat::PF_R8G8B8_UNORM:
    case RHIPixelFormat::PF_R8G8B8_SRGB:
        return 3;  // 实际存储可能用4字节对齐，但这里是像素数据本身的大小

    // 4通道 - 8位 (4字节)
    case RHIPixelFormat::PF_R8G8B8A8_SINT:
    case RHIPixelFormat::PF_R8G8B8A8_UINT:
    case RHIPixelFormat::PF_R8G8B8A8_SNORM:
    case RHIPixelFormat::PF_R8G8B8A8_UNORM:
    case RHIPixelFormat::PF_R8G8B8A8_SRGB:
        return 4;

    // 1通道 - 16位 (2字节)
    case RHIPixelFormat::PF_R16_SINT:
    case RHIPixelFormat::PF_R16_UINT:
    case RHIPixelFormat::PF_R16_SNORM:
    case RHIPixelFormat::PF_R16_UNORM:
    case RHIPixelFormat::PF_R16_FLOAT:
        return 2;

    // 2通道 - 16位 (4字节)
    case RHIPixelFormat::PF_R16G16_SINT:
    case RHIPixelFormat::PF_R16G16_UINT:
    case RHIPixelFormat::PF_R16G16_SNORM:
    case RHIPixelFormat::PF_R16G16_UNORM:
    case RHIPixelFormat::PF_R16G16_FLOAT:
        return 4;

    // 3通道 - 16位 (6字节)
    case RHIPixelFormat::PF_R16G16B16_SINT:
    case RHIPixelFormat::PF_R16G16B16_UINT:
    case RHIPixelFormat::PF_R16G16B16_SNORM:
    case RHIPixelFormat::PF_R16G16B16_UNORM:
    case RHIPixelFormat::PF_R16G16B16_FLOAT:
        return 6;

    // 4通道 - 16位 (8字节)
    case RHIPixelFormat::PF_R16G16B16A16_SINT:
    case RHIPixelFormat::PF_R16G16B16A16_UINT:
    case RHIPixelFormat::PF_R16G16B16A16_SNORM:
    case RHIPixelFormat::PF_R16G16B16A16_UNORM:
    case RHIPixelFormat::PF_R16G16B16A16_FLOAT:
        return 8;

    // 1通道 - 32位 (4字节)
    case RHIPixelFormat::PF_R32_SINT:
    case RHIPixelFormat::PF_R32_UINT:
    case RHIPixelFormat::PF_R32_FLOAT:
        return 4;

    // 2通道 - 32位 (8字节)
    case RHIPixelFormat::PF_R32G32_SINT:
    case RHIPixelFormat::PF_R32G32_UINT:
    case RHIPixelFormat::PF_R32G32_FLOAT:
        return 8;

    // 3通道 - 32位 (12字节)
    case RHIPixelFormat::PF_R32G32B32_SINT:
    case RHIPixelFormat::PF_R32G32B32_UINT:
    case RHIPixelFormat::PF_R32G32B32_FLOAT:
        return 12;

    // 4通道 - 32位 (16字节)
    case RHIPixelFormat::PF_R32G32B32A32_SINT:
    case RHIPixelFormat::PF_R32G32B32A32_UINT:
    case RHIPixelFormat::PF_R32G32B32A32_FLOAT:
        return 16;

    case RHIPixelFormat::PF_Unknown:
    default:
        return 0;
    }
}

// 视口转换
inline D3D11_VIEWPORT ToD3D11Viewport(const RHIViewport& Viewport)
{
    D3D11_VIEWPORT viewport;
    viewport.TopLeftX = Viewport.X();
    viewport.TopLeftY = Viewport.Y();
    viewport.Width    = Viewport.Width();
    viewport.Height   = Viewport.Height();
    viewport.MinDepth = Viewport.MinDepth();
    viewport.MaxDepth = Viewport.MaxDepth();
    return viewport;
}
