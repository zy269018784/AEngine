#pragma once
#include "RHIObjects/Core/RHICore.h"
#include "RHIObjects/Core/RHIVertexInputAttribute.h"
#include "RHIObjects/Shader/RHIShaderResourceBinding.h"
#include "RHIObjects/Shader/RHIShader.h"
#include "Vulkan.h"
#include <cstdint>

inline VkIndexType ToVulkanIndexType(RHIIndexFormat RHIIndexFormat)
{
	VkIndexType Type = VK_INDEX_TYPE_UINT16;
	switch (RHIIndexFormat)
	{
	case RHIIndexFormat::IndexUInt16:
		Type = VK_INDEX_TYPE_UINT16;
		break;
	case RHIIndexFormat::IndexUInt32:
		Type = VK_INDEX_TYPE_UINT32;
		break;
	default:
		break;
	}
	return Type;
}

inline VkCompareOp ToVulkanCompareOp(RHICompareOp RHICompareOp)
{
	/*
		The initial value is GL_LESS.
	*/
	VkCompareOp Mode = VK_COMPARE_OP_LESS;
	switch (RHICompareOp)
	{
	case RHICompareOp::Never:
		Mode = VK_COMPARE_OP_NEVER;
		break;
	case RHICompareOp::CompareOpAlways:
		Mode = VK_COMPARE_OP_ALWAYS;
		break;
	case RHICompareOp::Equal:
		Mode = VK_COMPARE_OP_EQUAL;
		break;
	case RHICompareOp::NotEqual:
		Mode = VK_COMPARE_OP_NOT_EQUAL;
		break;
	case RHICompareOp::Less:
		Mode = VK_COMPARE_OP_LESS;
		break;
	case RHICompareOp::LessOrEqual:
		Mode = VK_COMPARE_OP_LESS_OR_EQUAL;
		break;
	case RHICompareOp::Greater:
		Mode = VK_COMPARE_OP_GREATER;
		break;
	case RHICompareOp::GreaterOrEqual:
		Mode = VK_COMPARE_OP_GREATER_OR_EQUAL;
		break;
	default:
		break;
	}
	return Mode;
}

inline VkSamplerAddressMode ToVkSamplerAddressMode(RHIAddressMode Mode)
{
	VkSamplerAddressMode vkmode;
	switch (Mode)
	{
	case RHIAddressMode::REPEAT:
		vkmode = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		break;
	case RHIAddressMode::MIRRORED_REPEAT:
		vkmode = VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
		break;
	case RHIAddressMode::CLAMP_TO_EDGE:
		vkmode = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
		break;
	case RHIAddressMode::CLAMP_TO_BORDER:
		vkmode = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
		break;
	default:
		break;
	}

	return vkmode;
}

inline VkFilter ToVkFilter(RHIFilter Filter)
{
	VkFilter vkFilter;
	switch (Filter)
	{
	case RHIFilter::NEAREST:
		vkFilter = VK_FILTER_NEAREST;
		break;
	case RHIFilter::LINEAR:
		vkFilter = VK_FILTER_LINEAR;
		break;
	default:
		break;
	}

	return vkFilter;
}

inline VkImageViewType ToVulkanImageViewType(RHITextureType InType)
{
	VkImageViewType OutType;
	switch (InType)
	{
	case RHITextureType::Texture1D:
		OutType = VK_IMAGE_VIEW_TYPE_1D;
		break;
	case RHITextureType::Texture2D:
		OutType = VK_IMAGE_VIEW_TYPE_2D;
		break;
	case RHITextureType::Texture3D:
		OutType = VK_IMAGE_VIEW_TYPE_3D;
		break;
	case RHITextureType::Texture1DArray:
		OutType = VK_IMAGE_VIEW_TYPE_1D_ARRAY;
		break;
	case RHITextureType::Texture2DArray:
		OutType = VK_IMAGE_VIEW_TYPE_2D_ARRAY;
		break;
	case RHITextureType::Texture3DArray:
		break;
	case RHITextureType::TextureCubeMap:
		OutType = VK_IMAGE_VIEW_TYPE_CUBE;
		break;
	case RHITextureType::TextureCubeMapArray:
		OutType = VK_IMAGE_VIEW_TYPE_CUBE_ARRAY;
		break;
	default:
		break;
	}
	return OutType;
}

inline VkImageType ImageViewTypeToImageType(VkImageViewType ResourceType)
{
    VkImageType ImageType;
    switch (ResourceType)
    {

    case VK_IMAGE_VIEW_TYPE_1D:
    case VK_IMAGE_VIEW_TYPE_1D_ARRAY:
        ImageType = VK_IMAGE_TYPE_1D;
        break;
    case VK_IMAGE_VIEW_TYPE_2D:
    case VK_IMAGE_VIEW_TYPE_2D_ARRAY:
        ImageType = VK_IMAGE_TYPE_2D;
        break;
    case VK_IMAGE_VIEW_TYPE_3D:
        ImageType = VK_IMAGE_TYPE_3D;
        break;
    case VK_IMAGE_VIEW_TYPE_CUBE:
    case VK_IMAGE_VIEW_TYPE_CUBE_ARRAY:
        ImageType = VK_IMAGE_TYPE_2D;
        break;
    default:
        break;
    }
    return ImageType;
}

inline VkImageCreateFlagBits ImageViewTypeToImageCreateFlagBits(VkImageViewType ResourceType)
{
    VkImageCreateFlagBits FlagBits = (VkImageCreateFlagBits)0x00000000;
    switch (ResourceType)
    {
    case VK_IMAGE_VIEW_TYPE_CUBE:
    case VK_IMAGE_VIEW_TYPE_CUBE_ARRAY:
        FlagBits = VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT;
        break;
    case VK_IMAGE_VIEW_TYPE_1D:
        break;
    case VK_IMAGE_VIEW_TYPE_2D:
        break;
    case VK_IMAGE_VIEW_TYPE_3D:
        break;
    case VK_IMAGE_VIEW_TYPE_1D_ARRAY:
        break;
    case VK_IMAGE_VIEW_TYPE_2D_ARRAY:
        break;
    default:
        FlagBits = VK_IMAGE_CREATE_PROTECTED_BIT;
        break;
    }
    return FlagBits;
}

inline VkSampleCountFlagBits ToSampleCountFlagBits(std::uint32_t InSampleCount)
{
    VkSampleCountFlagBits FlagBit = VK_SAMPLE_COUNT_1_BIT;
    switch (InSampleCount)
    {
    case 1:
        FlagBit = VK_SAMPLE_COUNT_1_BIT;
        break;
    case 2:
        FlagBit = VK_SAMPLE_COUNT_2_BIT;
        break;
    case 4:
        FlagBit = VK_SAMPLE_COUNT_4_BIT;
        break;
    case 8:
        FlagBit = VK_SAMPLE_COUNT_8_BIT;
        break;
    case 16:
        FlagBit = VK_SAMPLE_COUNT_16_BIT;
        break;
    case 32:
        FlagBit = VK_SAMPLE_COUNT_32_BIT;
        break;
    case 64:
        FlagBit = VK_SAMPLE_COUNT_64_BIT;
        break;
    default:
        break;
    }
    return FlagBit;
}

/*
	Polygon Mode
		vkCmdSetPolygonModeEXT: VkPolygonMode
*/
inline VkPolygonMode ToVkPolygonMode(RHIPolygonMode RHIPolygonMode)
{
	VkPolygonMode Mode;
	switch (RHIPolygonMode)
	{
	case RHIPolygonMode::Fill:
		Mode = VK_POLYGON_MODE_FILL;
		break;
	case RHIPolygonMode::Line:
		Mode = VK_POLYGON_MODE_LINE;
		break;
	case RHIPolygonMode::Point:
		Mode = VK_POLYGON_MODE_POINT;
		break;
	default:
		break;
	}
	return Mode;
}
/*
	Cull Mode
		vkCmdSetCullMode: VkCullModeFlags
		vkCmdSetFrontFace: VkFrontFace
*/
inline VkCullModeFlags ToVkCullModeFlags(RHICullMode RHICullMode)
{
	VkCullModeFlags Flag = VK_CULL_MODE_NONE;
	switch (RHICullMode)
	{
	case RHICullMode::Front:
		Flag = VK_CULL_MODE_FRONT_BIT;
		break;
	case RHICullMode::Back:
		Flag = VK_CULL_MODE_BACK_BIT;
		break;
	case RHICullMode::Front_Back:
		Flag = VK_CULL_MODE_FRONT_AND_BACK;
		break;
	default:
		Flag = VK_CULL_MODE_NONE;
		break;
	}
	return Flag;
}

inline VkFrontFace ToVkFrontFace(RHIFrontFace RHIFrontFace)
{
	VkFrontFace Face = VK_FRONT_FACE_COUNTER_CLOCKWISE;
	switch (RHIFrontFace)
	{
	case RHIFrontFace::CW:
		Face = VK_FRONT_FACE_CLOCKWISE;
		break;
	case RHIFrontFace::CCW:
		Face = VK_FRONT_FACE_COUNTER_CLOCKWISE;
		break;
	default:
		break;
	}
	return Face;
}
/*
		Depth Test
			vkCmdSetDepthTestEnable
			vkCmdSetDepthBoundsTestEnable
			vkCmdSetDepthWriteEnable
			vkCmdSetDepthBiasEnable
			vkCmdSetDepthBias
			vkCmdSetDepthBounds	
			vkCmdSetDepthCompareOp: VkCompareOp
*/
inline VkCompareOp ToVkCompareOp(RHICompareOp RHICompareOp)
{
	VkCompareOp Op = VK_COMPARE_OP_LESS;
	switch (RHICompareOp)
	{
	case RHICompareOp::Never:
		Op = VK_COMPARE_OP_NEVER;
		break;
	case RHICompareOp::CompareOpAlways:
		Op = VK_COMPARE_OP_ALWAYS;
		break;
	case RHICompareOp::Equal:
		Op = VK_COMPARE_OP_EQUAL;
		break;
	case RHICompareOp::NotEqual:
		Op = VK_COMPARE_OP_NOT_EQUAL;
		break;
	case RHICompareOp::Less:
		Op = VK_COMPARE_OP_LESS;
		break;
	case RHICompareOp::LessOrEqual:
		Op = VK_COMPARE_OP_LESS_OR_EQUAL;
		break;
	case RHICompareOp::Greater:
		Op = VK_COMPARE_OP_GREATER;
		break;
	case RHICompareOp::GreaterOrEqual:
		Op = VK_COMPARE_OP_GREATER_OR_EQUAL;
		break;
	default:
		break;
	}
	return Op;
}

inline VkStencilOp ToVkStencilOp(RHIStencilOp RHIStencilOp)
{
	VkStencilOp Op;
	switch (RHIStencilOp)
	{
	case RHIStencilOp::Keep:
		Op = VK_STENCIL_OP_KEEP;
		break;
	case RHIStencilOp::Zero:
		Op = VK_STENCIL_OP_ZERO;
		break;
	case RHIStencilOp::Replace:
		Op = VK_STENCIL_OP_REPLACE;
		break;
	case RHIStencilOp::Incr:
		Op = VK_STENCIL_OP_INCREMENT_AND_CLAMP;
		break;
	case RHIStencilOp::IncrWrap:
		Op = VK_STENCIL_OP_INCREMENT_AND_WRAP;
		break;
	case RHIStencilOp::Decr:
		Op = VK_STENCIL_OP_DECREMENT_AND_CLAMP;
		break;
	case RHIStencilOp::DecrWrap:
		Op = VK_STENCIL_OP_DECREMENT_AND_WRAP;
		break;
	case RHIStencilOp::Invert:
		Op = VK_STENCIL_OP_INVERT;
		break;
	default:
		break;
	}
	return Op;
}
/*
	Blending
		vkCmdSetBlendConstants
*/
inline VkBlendOp ToVkBlendOp(RHIBlendOp RHIBlendOp)
{
	VkBlendOp Op;
	switch (RHIBlendOp)
	{
	case RHIBlendOp::Add:
		Op = VK_BLEND_OP_ADD;
		break;
	case RHIBlendOp::Sub:
		Op = VK_BLEND_OP_SUBTRACT;
		break;
	case RHIBlendOp::Min:
		Op = VK_BLEND_OP_MIN;
		break;
	case RHIBlendOp::Max:
		Op = VK_BLEND_OP_MAX;
		break;
	case RHIBlendOp::Reverse_Sub:
		Op = VK_BLEND_OP_REVERSE_SUBTRACT;
		break;
	default:
		break;
	}
	return Op;
}

inline VkBlendFactor ToVkBlendFactor(RHIBlendFactor RHIBlendFactor)
{
	VkBlendFactor Factor;
	switch (RHIBlendFactor)
	{
	case RHIBlendFactor::Zero:
		Factor = VK_BLEND_FACTOR_ZERO;
		break;
	case RHIBlendFactor::One:
		Factor = VK_BLEND_FACTOR_ONE;
		break;
	case RHIBlendFactor::SrcColor:
		Factor = VK_BLEND_FACTOR_SRC_COLOR;
		break;
	case RHIBlendFactor::OneMinusSrcColor:
		Factor = VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR;
		break;
	case RHIBlendFactor::DstColor:
		Factor = VK_BLEND_FACTOR_DST_COLOR;
		break;
	case RHIBlendFactor::OneMinusDstColor:
		Factor = VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR;
		break;
	case RHIBlendFactor::SrcAlpha:
		Factor = VK_BLEND_FACTOR_SRC_ALPHA;
		break;
	case RHIBlendFactor::OneMinusSrcAlpha:
		Factor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
		break;
	case RHIBlendFactor::DstAlpha:
		Factor = VK_BLEND_FACTOR_DST_ALPHA;
		break;
	case RHIBlendFactor::OneMinusDstAlpha:
		Factor = VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA;
		break;
	case RHIBlendFactor::ConstantColor:
		Factor = VK_BLEND_FACTOR_SRC_COLOR;
		break;
	case RHIBlendFactor::OneMinusConstantColor:
		Factor = VK_BLEND_FACTOR_SRC_COLOR;
		break;
	case RHIBlendFactor::ConstantAlpha:
		Factor = VK_BLEND_FACTOR_CONSTANT_ALPHA;
		break;
	case RHIBlendFactor::OneMinusConstantAlpha:
		Factor = VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA;
		break;
	case RHIBlendFactor::SrcAlphaSaturate:
		Factor = VK_BLEND_FACTOR_SRC_ALPHA_SATURATE;
		break;
	case RHIBlendFactor::Src1Color:
		Factor = VK_BLEND_FACTOR_SRC1_COLOR;
		break;
	case RHIBlendFactor::OneMinusSrc1Color:
		Factor = VK_BLEND_FACTOR_ONE_MINUS_SRC1_COLOR;
		break;
	case RHIBlendFactor::Src1Alpha:
		Factor = VK_BLEND_FACTOR_SRC1_ALPHA;
		break;
	case RHIBlendFactor::OneMinusSrc1Alpha:
		Factor = VK_BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA;
		break;
	default:
		break;
	}
	return Factor;
}
/*
	Primitives
		vkCmdSetPrimitiveTopology: VkPrimitiveTopology
*/
inline VkPrimitiveTopology ToVkPrimitiveTopology(RHITopology RHITopology)
{
	VkPrimitiveTopology T = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	switch (RHITopology)
	{
	case RHITopology::Points:
		T = VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
		break;
	case RHITopology::Lines:
		T = VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
		break;
	case RHITopology::LineStrip:
		T = VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
		break;
	case RHITopology::Triangles:
		T = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		break;
	case RHITopology::TriangleStrip:
		T = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
		break;
	case RHITopology::TriangleFan:
		T = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN;
		break;
	case RHITopology::LinesWithAdjacency:
		T = VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY;
		break;
	case RHITopology::LineStripWithAdjacency:
		T = VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY;
		break;
	case RHITopology::TrianglesWithAdjacency:
		T = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY;
		break;
	case RHITopology::TriangleStripWithAdjacency:
		T = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY;
		break;
	case RHITopology::Patches:
		T = VK_PRIMITIVE_TOPOLOGY_PATCH_LIST;
		break;
	default:
		break;
	}
	return T;
}

/*
	Shade Stage
*/
inline VkShaderStageFlagBits ToVkShaderStageFlagBits(RHIShaderType Type)
{
	VkShaderStageFlagBits Flag = VK_SHADER_STAGE_VERTEX_BIT;
	switch (Type)
	{
	case RHIShaderType::Vertex:
		Flag = VK_SHADER_STAGE_VERTEX_BIT;
		break;
	case RHIShaderType::TessellationControl:
		Flag = VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
		break;
	case RHIShaderType::TessellationEvaluation:
		Flag = VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
		break;
	case RHIShaderType::Fragment:
		Flag = VK_SHADER_STAGE_FRAGMENT_BIT;
		break;
	case RHIShaderType::Compute:
		Flag = VK_SHADER_STAGE_COMPUTE_BIT;
		break;
	case RHIShaderType::Geometry:
		Flag = VK_SHADER_STAGE_GEOMETRY_BIT;
		break;
	
	case RHIShaderType::Mesh:
		Flag = VK_SHADER_STAGE_MESH_BIT_EXT;
		break;
	case RHIShaderType::Task:
		Flag = VK_SHADER_STAGE_TASK_BIT_EXT;
		break;
	case RHIShaderType::RayGeneration:
		Flag = VK_SHADER_STAGE_RAYGEN_BIT_KHR;
		break;
	case RHIShaderType::Intersection:
		Flag = VK_SHADER_STAGE_INTERSECTION_BIT_KHR;
		break;
	case RHIShaderType::AnyHit:
		Flag = VK_SHADER_STAGE_ANY_HIT_BIT_KHR;
		break;
	case RHIShaderType::ClosestHit:
		Flag = VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR;
		break;
	case RHIShaderType::Miss:
		Flag = VK_SHADER_STAGE_MISS_BIT_KHR;
		break;
	default:
		break;
	}

	return Flag;
}

inline VkShaderStageFlagBits ToVkShaderStageFlagBits(RHIShaderResourceBinding::StageFlags Stage)
{
	VkShaderStageFlagBits Flag = VK_SHADER_STAGE_VERTEX_BIT;
	switch (Stage)
	{
	case RHIShaderResourceBinding::StageFlags::VertexStage:
		Flag = VK_SHADER_STAGE_VERTEX_BIT;
		break;
	case RHIShaderResourceBinding::StageFlags::TessellationControlStage:
		Flag = VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
		break;
	case RHIShaderResourceBinding::StageFlags::TessellationEvaluationStage:
		Flag = VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
		break;
	case RHIShaderResourceBinding::StageFlags::FragmentStage:
		Flag = VK_SHADER_STAGE_FRAGMENT_BIT;
		break;
	case RHIShaderResourceBinding::StageFlags::ComputeStage:
		Flag = VK_SHADER_STAGE_COMPUTE_BIT;
		break;
	case RHIShaderResourceBinding::StageFlags::GeometryStage:
		Flag = VK_SHADER_STAGE_GEOMETRY_BIT;
		break;
	default:
		break;
	}
	return Flag;
}
/*
	Logiacl Operations
*/
inline VkLogicOp ToVkLogicOp(RHILogicOp RHILogicOp)
{
	VkLogicOp Op;
	switch (RHILogicOp)
	{
	case RHILogicOp::CLEAR:
		Op = VK_LOGIC_OP_CLEAR;
		break;
	case RHILogicOp::SET:
		Op = VK_LOGIC_OP_SET;
		break;
	case RHILogicOp::COPY:
		Op = VK_LOGIC_OP_COPY;
		break;
	case RHILogicOp::COPY_INVERTED:
		Op = VK_LOGIC_OP_COPY_INVERTED;
		break;
	case RHILogicOp::NOOP:
		Op = VK_LOGIC_OP_CLEAR;
		break;
	case RHILogicOp::INVERT:
		Op = VK_LOGIC_OP_CLEAR;
		break;
	case RHILogicOp::AND:
		Op = VK_LOGIC_OP_AND;
		break;
	case RHILogicOp::NAND:
		Op = VK_LOGIC_OP_AND_REVERSE;
		break;
	case RHILogicOp::OR:
		Op = VK_LOGIC_OP_OR;
		break;
	case RHILogicOp::NOR:
		Op = VK_LOGIC_OP_NOR;
		break;
	case RHILogicOp::XOR:
		Op = VK_LOGIC_OP_XOR;
		break;
	case RHILogicOp::EQUIV:
		Op = VK_LOGIC_OP_EQUIVALENT;
		break;
	case RHILogicOp::AND_REVERSE:
		Op = VK_LOGIC_OP_AND_REVERSE;
		break;
	case RHILogicOp::AND_INVERTED:
		Op = VK_LOGIC_OP_AND_INVERTED;
		break;
	case RHILogicOp::OR_REVERSE:
		Op = VK_LOGIC_OP_OR_REVERSE;
		break;
	case RHILogicOp::OR_INVERTED:
		Op = VK_LOGIC_OP_OR_INVERTED;
		break;
	default:
		break;
	}
	return Op;
}

inline VkVertexInputRate ToVkVertexInputRate(std::uint32_t StepRate)
{
	VkVertexInputRate VertexInputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	switch (StepRate)
	{
	case 0:
		VertexInputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		break;
	case 1:
		VertexInputRate = VK_VERTEX_INPUT_RATE_INSTANCE;
		break;
	default:
		break;
	}
	return VertexInputRate;
}

inline VkSampleCountFlagBits ToVkSampleCountFlagBits(int Count)
{
	VkSampleCountFlagBits Flag = VK_SAMPLE_COUNT_1_BIT;
	switch (Count)
	{
	case 1:
		Flag = VK_SAMPLE_COUNT_1_BIT;
		break;
	case 2:
		Flag = VK_SAMPLE_COUNT_2_BIT;
		break;
	case 4:
		Flag = VK_SAMPLE_COUNT_4_BIT;
		break;
	case 8:
		Flag = VK_SAMPLE_COUNT_8_BIT;
		break;
	case 16:
		Flag = VK_SAMPLE_COUNT_16_BIT;
		break;
	case 32:
		Flag = VK_SAMPLE_COUNT_32_BIT;
		break;
	case 64:
		Flag = VK_SAMPLE_COUNT_64_BIT;
		break;
	default:
		break;
	}
	return Flag;
}

inline VkFormat ToVkFormat(RHIVertexInputAttribute::Format Format)
{
	VkFormat fmt;
	switch (Format)
	{
	case RHIVertexInputAttribute::Float4:
		fmt = VK_FORMAT_R32G32B32A32_SFLOAT;
		break;
	case RHIVertexInputAttribute::Float3:
		fmt = VK_FORMAT_R32G32B32_SFLOAT;
		break;
	case RHIVertexInputAttribute::Float2:
		fmt = VK_FORMAT_R32G32_SFLOAT;
		break;
	case RHIVertexInputAttribute::Float:
		fmt = VK_FORMAT_R32_SFLOAT;
		break;
	case RHIVertexInputAttribute::UNormByte4:
		fmt = VK_FORMAT_R8G8B8A8_SNORM;
		break;
	case RHIVertexInputAttribute::UNormByte2:
		fmt = VK_FORMAT_R8G8_UNORM;
		break;
	case RHIVertexInputAttribute::UNormByte:
		fmt = VK_FORMAT_R8_UNORM;
		break;
	case RHIVertexInputAttribute::UInt4:
		fmt = VK_FORMAT_R32G32B32A32_UINT;
		break;
	case RHIVertexInputAttribute::UInt3:
		fmt = VK_FORMAT_R32G32B32_UINT;
		break;
	case RHIVertexInputAttribute::UInt2:
		fmt = VK_FORMAT_R32G32_UINT;
		break;
	case RHIVertexInputAttribute::UInt:
		fmt = VK_FORMAT_R32_UINT;
		break;
	case RHIVertexInputAttribute::SInt4:
		fmt = VK_FORMAT_R32G32B32A32_SINT;
		break;
	case RHIVertexInputAttribute::SInt3:
		fmt = VK_FORMAT_R32G32B32_SINT;
		break;
	case RHIVertexInputAttribute::SInt2:
		fmt = VK_FORMAT_R32G32_SINT;
		break;
	case RHIVertexInputAttribute::SInt:
		fmt = VK_FORMAT_R32_SINT;
		break;
	case RHIVertexInputAttribute::Half4:
		fmt = VK_FORMAT_R16G16B16A16_SFLOAT;
		break;
	case RHIVertexInputAttribute::Half3:
		fmt = VK_FORMAT_R16G16B16_SFLOAT;
		break;
	case RHIVertexInputAttribute::Half2:
		fmt = VK_FORMAT_R16G16_SFLOAT;
		break;
	case RHIVertexInputAttribute::Half:
		fmt = VK_FORMAT_R16_SFLOAT;
		break;
	default:
		break;
	}
	return fmt;
}
