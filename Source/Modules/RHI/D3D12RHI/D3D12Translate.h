#pragma once
#include "RHITranslate.h"
#include "RHIObjects/Shader/RHIShaderResourceBinding.h"
#include <iostream>

// Windows Í·ÎÄ¼þ
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <D3Dcompiler.h>

inline DXGI_FORMAT ToD3D12IndexFormat(RHIIndexFormat RHIIndexFormat)
{
    switch (RHIIndexFormat)
    {
    case RHIIndexFormat::IndexUInt16:
        return DXGI_FORMAT_R16_UINT;
    case RHIIndexFormat::IndexUInt32:
        return DXGI_FORMAT_R32_UINT;
    default:
        return DXGI_FORMAT_R16_UINT;
    }
}

/*
    D3D12_FILL_MODE
*/
inline D3D12_FILL_MODE ToD3D12FillMode(RHIPolygonMode RHIPolygonMode)
{
    switch (RHIPolygonMode)
    {
    case RHIPolygonMode::Fill:
        return D3D12_FILL_MODE_SOLID;
    case RHIPolygonMode::Line:
        return D3D12_FILL_MODE_WIREFRAME;
    case RHIPolygonMode::Point:
        // D3D12 doesn't directly support point fill mode, use wireframe as fallback
        return D3D12_FILL_MODE_WIREFRAME;
    default:
        return D3D12_FILL_MODE_SOLID;
    }
}

/*
    D3D12_CULL_MODE
*/
inline D3D12_CULL_MODE ToD3D12CullMode(RHICullMode RHICullMode)
{
    switch (RHICullMode)
    {
    case RHICullMode::Front:
        return D3D12_CULL_MODE_FRONT;
    case RHICullMode::Back:
        return D3D12_CULL_MODE_BACK;
    case RHICullMode::Front_Back:
        return D3D12_CULL_MODE_NONE;
    default:
        return D3D12_CULL_MODE_BACK;
    }
}

/*
    D3D12_CULL_MODE doesn't have direct front face control,
    but we can handle it in pipeline state creation
*/
inline bool ToD3D12FrontCounterClockwise(RHIFrontFace RHIFrontFace)
{
    switch (RHIFrontFace)
    {
    case RHIFrontFace::CW:
        return false; // D3D12 default is clockwise
    case RHIFrontFace::CCW:
        return true;
    default:
        return true; // D3D12 typically uses counter-clockwise
    }
}

/*
    Depth Comparison Function
*/
inline D3D12_COMPARISON_FUNC ToD3D12ComparisonFunc(RHICompareOp RHICompareOp)
{
    switch (RHICompareOp)
    {
    case RHICompareOp::Never:
        return D3D12_COMPARISON_FUNC_NEVER;
    case RHICompareOp::Always:
        return D3D12_COMPARISON_FUNC_ALWAYS;
    case RHICompareOp::Equal:
        return D3D12_COMPARISON_FUNC_EQUAL;
    case RHICompareOp::NotEqual:
        return D3D12_COMPARISON_FUNC_NOT_EQUAL;
    case RHICompareOp::Less:
        return D3D12_COMPARISON_FUNC_LESS;
    case RHICompareOp::LessOrEqual:
        return D3D12_COMPARISON_FUNC_LESS_EQUAL;
    case RHICompareOp::Greater:
        return D3D12_COMPARISON_FUNC_GREATER;
    case RHICompareOp::GreaterOrEqual:
        return D3D12_COMPARISON_FUNC_GREATER_EQUAL;
    default:
        return D3D12_COMPARISON_FUNC_LESS;
    }
}

/*
    Stencil Operations
*/
inline D3D12_STENCIL_OP ToD3D12StencilOp(RHIStencilOp RHIStencilOp)
{
    switch (RHIStencilOp)
    {
    case RHIStencilOp::Keep:
        return D3D12_STENCIL_OP_KEEP;
    case RHIStencilOp::Zero:
        return D3D12_STENCIL_OP_ZERO;
    case RHIStencilOp::Replace:
        return D3D12_STENCIL_OP_REPLACE;
    case RHIStencilOp::Incr:
        return D3D12_STENCIL_OP_INCR_SAT;
    case RHIStencilOp::IncrWrap:
        return D3D12_STENCIL_OP_INCR;
    case RHIStencilOp::Decr:
        return D3D12_STENCIL_OP_DECR_SAT;
    case RHIStencilOp::DecrWrap:
        return D3D12_STENCIL_OP_DECR;
    case RHIStencilOp::Invert:
        return D3D12_STENCIL_OP_INVERT;
    default:
        return D3D12_STENCIL_OP_KEEP;
    }
}

/*
    Blend Operations
*/
inline D3D12_BLEND_OP ToD3D12BlendOp(RHIBlendOp RHIBlendOp)
{
    switch (RHIBlendOp)
    {
    case RHIBlendOp::Add:
        return D3D12_BLEND_OP_ADD;
    case RHIBlendOp::Sub:
        return D3D12_BLEND_OP_SUBTRACT;
    case RHIBlendOp::Min:
        return D3D12_BLEND_OP_MIN;
    case RHIBlendOp::Max:
        return D3D12_BLEND_OP_MAX;
    case RHIBlendOp::Reverse_Sub:
        return D3D12_BLEND_OP_REV_SUBTRACT;
    default:
        return D3D12_BLEND_OP_ADD;
    }
}

/*
    Blend Factors
*/
inline D3D12_BLEND ToD3D12BlendFactor(RHIBlendFactor RHIBlendFactor)
{
    switch (RHIBlendFactor)
    {
    case RHIBlendFactor::Zero:
        return D3D12_BLEND_ZERO;
    case RHIBlendFactor::One:
        return D3D12_BLEND_ONE;
    case RHIBlendFactor::SrcColor:
        return D3D12_BLEND_SRC_COLOR;
    case RHIBlendFactor::OneMinusSrcColor:
        return D3D12_BLEND_INV_SRC_COLOR;
    case RHIBlendFactor::DstColor:
        return D3D12_BLEND_DEST_COLOR;
    case RHIBlendFactor::OneMinusDstColor:
        return D3D12_BLEND_INV_DEST_COLOR;
    case RHIBlendFactor::SrcAlpha:
        return D3D12_BLEND_SRC_ALPHA;
    case RHIBlendFactor::OneMinusSrcAlpha:
        return D3D12_BLEND_INV_SRC_ALPHA;
    case RHIBlendFactor::DstAlpha:
        return D3D12_BLEND_DEST_ALPHA;
    case RHIBlendFactor::OneMinusDstAlpha:
        return D3D12_BLEND_INV_DEST_ALPHA;
    case RHIBlendFactor::ConstantColor:
        return D3D12_BLEND_BLEND_FACTOR;
    case RHIBlendFactor::OneMinusConstantColor:
        return D3D12_BLEND_INV_BLEND_FACTOR;
    case RHIBlendFactor::ConstantAlpha:
        return D3D12_BLEND_BLEND_FACTOR;
    case RHIBlendFactor::OneMinusConstantAlpha:
        return D3D12_BLEND_INV_BLEND_FACTOR;
    case RHIBlendFactor::SrcAlphaSaturate:
        return D3D12_BLEND_SRC_ALPHA_SAT;
    case RHIBlendFactor::Src1Color:
        return D3D12_BLEND_SRC1_COLOR;
    case RHIBlendFactor::OneMinusSrc1Color:
        return D3D12_BLEND_INV_SRC1_COLOR;
    case RHIBlendFactor::Src1Alpha:
        return D3D12_BLEND_SRC1_ALPHA;
    case RHIBlendFactor::OneMinusSrc1Alpha:
        return D3D12_BLEND_INV_SRC1_ALPHA;
    default:
        return D3D12_BLEND_ONE;
    }
}

/*
    Sample Count
*/
inline UINT ToD3D12SampleCount(int Count)
{
    return static_cast<UINT>(Count);
}

/*
    Primitive Topology
*/
inline D3D12_PRIMITIVE_TOPOLOGY_TYPE ToD3D12PrimitiveTopologyType(RHITopology RHITopology)
{
    switch (RHITopology)
    {
    case RHITopology::Points:
        return D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT;
    case RHITopology::Lines:
    case RHITopology::LineStrip:
        return D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE;
    case RHITopology::Triangles:
    case RHITopology::TriangleStrip:
    case RHITopology::TriangleFan:
        return D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    case RHITopology::LinesWithAdjacency:
    case RHITopology::LineStripWithAdjacency:
    case RHITopology::TrianglesWithAdjacency:
    case RHITopology::TriangleStripWithAdjacency:
        return D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE; // D3D12 doesn't support adjacency directly
    case RHITopology::Patches:
        return D3D12_PRIMITIVE_TOPOLOGY_TYPE_PATCH;
    default:
        return D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    }
}

/*
    Primitive Topology for IASetPrimitiveTopology
*/
inline D3D_PRIMITIVE_TOPOLOGY ToD3D12PrimitiveTopology(RHITopology RHITopology)
{
    switch (RHITopology)
    {
    case RHITopology::Points:
        return D3D_PRIMITIVE_TOPOLOGY_POINTLIST;
    case RHITopology::Lines:
        return D3D_PRIMITIVE_TOPOLOGY_LINELIST;
    case RHITopology::LineStrip:
        return D3D_PRIMITIVE_TOPOLOGY_LINESTRIP;
    case RHITopology::Triangles:
        return D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    case RHITopology::TriangleStrip:
        return D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
    case RHITopology::TriangleFan:
        // D3D12 doesn't support triangle fan natively, need to emulate
        return D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    case RHITopology::Patches:
        // For tessellation, you'll need to specify the control points
        return D3D_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST;
    default:
        return D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    }
}

/*
    Input Classification (Vertex Input Rate)
*/
inline D3D12_INPUT_CLASSIFICATION ToD3D12InputClassification(std::uint32_t StepRate)
{
    return (StepRate == 0) ? D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA
        : D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA;
}

/*
    Shader Visibility for Root Signature
*/
inline D3D12_SHADER_VISIBILITY ToD3D12ShaderVisibility(RHIShaderResourceBinding::StageFlags Flag)
{
    switch (Flag)
    {
    case RHIShaderResourceBinding::StageFlags::VertexStage:
        return D3D12_SHADER_VISIBILITY_VERTEX;
    case RHIShaderResourceBinding::StageFlags::TessellationControlStage:
        return D3D12_SHADER_VISIBILITY_HULL;
    case RHIShaderResourceBinding::StageFlags::TessellationEvaluationStage:
        return D3D12_SHADER_VISIBILITY_DOMAIN;
    case RHIShaderResourceBinding::StageFlags::FragmentStage:
        return D3D12_SHADER_VISIBILITY_PIXEL;
    case RHIShaderResourceBinding::StageFlags::ComputeStage:
        return D3D12_SHADER_VISIBILITY_ALL; // Compute uses all visibility
    case RHIShaderResourceBinding::StageFlags::GeometryStage:
        return D3D12_SHADER_VISIBILITY_GEOMETRY;
    default:
        return D3D12_SHADER_VISIBILITY_ALL;
    }
}

/*
    Logic Operations
*/
inline D3D12_LOGIC_OP ToD3D12LogicOp(RHILogicOp RHILogicOp)
{
    switch (RHILogicOp)
    {
    case RHILogicOp::CLEAR:
        return D3D12_LOGIC_OP_CLEAR;
    case RHILogicOp::SET:
        return D3D12_LOGIC_OP_SET;
    case RHILogicOp::COPY:
        return D3D12_LOGIC_OP_COPY;
    case RHILogicOp::COPY_INVERTED:
        return D3D12_LOGIC_OP_COPY_INVERTED;
    case RHILogicOp::NOOP:
        return D3D12_LOGIC_OP_NOOP;
    case RHILogicOp::INVERT:
        return D3D12_LOGIC_OP_INVERT;
    case RHILogicOp::AND:
        return D3D12_LOGIC_OP_AND;
    case RHILogicOp::NAND:
        return D3D12_LOGIC_OP_NAND;
    case RHILogicOp::OR:
        return D3D12_LOGIC_OP_OR;
    case RHILogicOp::NOR:
        return D3D12_LOGIC_OP_NOR;
    case RHILogicOp::XOR:
        return D3D12_LOGIC_OP_XOR;
    case RHILogicOp::EQUIV:
        return D3D12_LOGIC_OP_EQUIV;
    case RHILogicOp::AND_REVERSE:
        return D3D12_LOGIC_OP_AND_REVERSE;
    case RHILogicOp::AND_INVERTED:
        return D3D12_LOGIC_OP_AND_INVERTED;
    case RHILogicOp::OR_REVERSE:
        return D3D12_LOGIC_OP_OR_REVERSE;
    case RHILogicOp::OR_INVERTED:
        return D3D12_LOGIC_OP_OR_INVERTED;
    default:
        return D3D12_LOGIC_OP_COPY;
    }
}

/*
    Texture Dimension
*/
inline D3D12_SRV_DIMENSION ToD3D12SRVDimension(RHITextureType RHIType)
{
    switch (RHIType)
    {
    case RHITextureType::Texture1D:
        return D3D12_SRV_DIMENSION_TEXTURE1D;
    case RHITextureType::Texture1DArray:
        return D3D12_SRV_DIMENSION_TEXTURE1DARRAY;
    case RHITextureType::Texture2D:
        return D3D12_SRV_DIMENSION_TEXTURE2D;
    case RHITextureType::Texture2DArray:
        return D3D12_SRV_DIMENSION_TEXTURE2DARRAY;
    case RHITextureType::Texture3D:
        return D3D12_SRV_DIMENSION_TEXTURE3D;
    case RHITextureType::TextureCubeMap:
        return D3D12_SRV_DIMENSION_TEXTURECUBE;
    case RHITextureType::TextureCubeMapArray:
        return D3D12_SRV_DIMENSION_TEXTURECUBEARRAY;
    default:
        return D3D12_SRV_DIMENSION_TEXTURE2D;
    }
}

/*
    Texture Address Mode
*/
inline D3D12_TEXTURE_ADDRESS_MODE ToD3D12AddressMode(RHIAddressMode Mode)
{
    switch (Mode)
    {
    case RHIAddressMode::REPEAT:
        return D3D12_TEXTURE_ADDRESS_MODE_WRAP;
    case RHIAddressMode::MIRRORED_REPEAT:
        return D3D12_TEXTURE_ADDRESS_MODE_MIRROR;
    case RHIAddressMode::CLAMP_TO_EDGE:
        return D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
    case RHIAddressMode::CLAMP_TO_BORDER:
        return D3D12_TEXTURE_ADDRESS_MODE_BORDER;
    default:
        return D3D12_TEXTURE_ADDRESS_MODE_WRAP;
    }
}

/*
    Filter Mode
*/
inline D3D12_FILTER ToD3D12Filter(RHIFilter Filter)
{
    switch (Filter)
    {
    case RHIFilter::NEAREST:
        return D3D12_FILTER_MIN_MAG_MIP_POINT;
    case RHIFilter::LINEAR:
        return D3D12_FILTER_MIN_MAG_MIP_LINEAR;
    default:
        return D3D12_FILTER_MIN_MAG_MIP_LINEAR;
    }
}

/*
    Cube Map Face (D3D12 doesn't have direct face enum,
    but you can use it for subresource calculation)
*/
inline UINT ToD3D12CubeMapFaceIndex(RHICubeMapFace Face)
{
    switch (Face)
    {
    case RHICubeMapFace::CUBE_MAP_POSITIVE_X:  return 0;
    case RHICubeMapFace::CUBE_MAP_NEGATIVE_X:  return 1;
    case RHICubeMapFace::CUBE_MAP_POSITIVE_Y:  return 2;
    case RHICubeMapFace::CUBE_MAP_NEGATIVE_Y:  return 3;
    case RHICubeMapFace::CUBE_MAP_POSITIVE_Z:  return 4;
    case RHICubeMapFace::CUBE_MAP_NEGATIVE_Z:  return 5;
    default: return 0;
    }
}