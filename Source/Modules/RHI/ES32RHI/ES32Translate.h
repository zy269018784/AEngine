#pragma once
#include "RHIObjects/Core/RHICore.h"
#include "RHIObjects/Shader/RHIShaderResourceBinding.h"
#include "ES32.h"
#include <iostream>

inline GLenum  ToOpenGLIndexType(RHIIndexFormat RHIIndexFormat)
{
	GLenum Type = GL_UNSIGNED_SHORT;
	switch (RHIIndexFormat)
	{
	case RHIIndexFormat::IndexUInt16:
		Type = GL_UNSIGNED_SHORT;
		break;
	case RHIIndexFormat::IndexUInt32:
		Type = GL_UNSIGNED_INT;
		break;
	default:
		break;
	}
	return Type;
}

/*
	Polygon Mode API:
		glPolygonMode 
	glIsEnabled with argument GL_CULL_FACE
	glGet with argument GL_CULL_FACE_MODE
*/
inline GLenum  ToOpenGLPolygonMode(RHIPolygonMode RHIPolygonMode)
{
	/*
		The initial value is GL_FILL
	*/
	GLenum Mode = GL_FILL;
	switch (RHIPolygonMode)
	{
	case RHIPolygonMode::Fill:
		Mode = GL_FILL;
		break;
	case RHIPolygonMode::Line:
		Mode = GL_LINE;
		break;
	case RHIPolygonMode::Point:
		Mode = GL_POINT;
		break;
	default:
		break;
	}
	return Mode;
}

/*
	Cull Mode
			Face culling is initially disabled
			glEnable(GL_CULL_FACE)
			glDisable(GL_CULL_FACE)
			glCullFace
			glFrontFace
	glGet with argument GL_POLYGON_MODE
*/
inline GLenum ToOpenGLCullMode(RHICullMode RHICullMode)
{
	/*
		The initial value is GL_BACK
	*/
	GLenum Mode = GL_BACK;
	switch (RHICullMode)
	{
	case RHICullMode::Front:
		Mode = GL_FRONT;
		break;
	case RHICullMode::Back:
		Mode = GL_BACK;
		break;
	case RHICullMode::Front_Back:
		Mode = GL_FRONT_AND_BACK;
		break;
	default:
		break;
	}
	return Mode;
}

/*
	glGet with argument GL_FRONT_FACE
*/
inline GLenum ToOpenGLFrontFace(RHIFrontFace RHIFrontFace)
{
	/*
		The initial value is GL_CCW
	*/
	GLenum Mode = GL_CCW;
	switch (RHIFrontFace)
	{
	case RHIFrontFace::CW:
		Mode = GL_CW;
		break;
	case RHIFrontFace::CCW:
		Mode = GL_CCW;
		break;
	default:
		break;
	}
	return Mode;
}

/*
	Depth Test
			glEnable(GL_DEPTH_TEST);
			glDisable(GL_DEPTH_TEST);
			glDepthMask
			glDepthFunc
*/
inline GLenum ToOpenGLCompareOp(RHICompareOp RHICompareOp)
{
	/*
		The initial value is GL_LESS.
	*/
	GLenum Mode = GL_LESS;
	switch (RHICompareOp)
	{
	case RHICompareOp::Never:
		Mode = GL_NEVER;
		break;
	case RHICompareOp::Always:
		Mode = GL_ALWAYS;
		break;
	case RHICompareOp::Equal:
		Mode = GL_EQUAL;
		break;
	case RHICompareOp::NotEqual:
		Mode = GL_NOTEQUAL;
		break;
	case RHICompareOp::Less:
		Mode = GL_LESS;
		break;
	case RHICompareOp::LessOrEqual:
		Mode = GL_LEQUAL;
		break;
	case RHICompareOp::Greater:
		Mode = GL_GREATER;
		break;
	case RHICompareOp::GreaterOrEqual:
		Mode = GL_GEQUAL;
		break;
	default:
		break;
	}
	return Mode;
}
/*
	Stencil Test
		glStencilMask
		glStencilFunc
		glStencilOp
*/
inline GLenum ToOpenGLStencilOp(RHIStencilOp RHIStencilOp)
{
	/*
		The initial value is GL_KEEP
	*/
	GLenum Op = GL_KEEP;
	switch (RHIStencilOp)
	{
	case RHIStencilOp::Keep:
		Op = GL_KEEP;
		break;
	case RHIStencilOp::Zero:
		Op = GL_ZERO;
		break;
	case RHIStencilOp::Replace:
		Op = GL_REPLACE;
		break;
	case RHIStencilOp::Incr:
		Op = GL_INCR;
		break;
	case RHIStencilOp::IncrWrap:
		Op = GL_INCR_WRAP;
		break;
	case RHIStencilOp::Decr:
		Op = GL_DECR;
		break;
	case RHIStencilOp::DecrWrap:
		Op = GL_DECR_WRAP;
		break;
	case RHIStencilOp::Invert:
		Op = GL_INVERT;
		break;
	default:
		break;
	}
	return Op;
}

/*
	Blending
		glBlendColor
		glBlendFunc
		glBlendEquation
*/
inline GLenum ToOpenGLBlendOp(RHIBlendOp RHIBlendOp)
{
	GLenum Op;
	switch (RHIBlendOp)
	{
	case RHIBlendOp::Add:
		Op = GL_FUNC_ADD;
		break;
	case RHIBlendOp::Sub:
		Op = GL_FUNC_SUBTRACT;
		break;
	case RHIBlendOp::Min:
		Op = GL_MIN;
		break;
	case RHIBlendOp::Max:
		Op = GL_MAX;
		break;
	case RHIBlendOp::Reverse_Sub:
		Op = GL_FUNC_REVERSE_SUBTRACT;
		break;
	default:
		break;
	}
	return Op;
}

inline GLenum ToOpenGLBlendFactor(RHIBlendFactor RHIBlendFactor)
{
	/*
		 The initial value is GL_ONE
	*/
	GLenum Fatcor = GL_ONE;
	switch (RHIBlendFactor)
	{
	case RHIBlendFactor::Zero:
		Fatcor = GL_ONE;
		break;
	case RHIBlendFactor::One:
		Fatcor = GL_ONE;
		break;
	case RHIBlendFactor::SrcColor:
		Fatcor = GL_SRC_COLOR;
		break;
	case RHIBlendFactor::OneMinusSrcColor:
		Fatcor = GL_ONE_MINUS_SRC_COLOR;
		break;
	case RHIBlendFactor::DstColor:
		Fatcor = GL_DST_COLOR;
		break;
	case RHIBlendFactor::OneMinusDstColor:
		Fatcor = GL_ONE_MINUS_DST_COLOR;
		break;
	case RHIBlendFactor::SrcAlpha:
		Fatcor = GL_SRC_ALPHA;
		break;
	case RHIBlendFactor::OneMinusSrcAlpha:
		Fatcor = GL_ONE_MINUS_SRC_ALPHA;
		break;
	case RHIBlendFactor::DstAlpha:
		Fatcor = GL_DST_ALPHA;
		break;
	case RHIBlendFactor::OneMinusDstAlpha:
		Fatcor = GL_ONE_MINUS_DST_ALPHA;
		break;
	case RHIBlendFactor::ConstantColor:
		Fatcor = GL_CONSTANT_COLOR;
		break;
	case RHIBlendFactor::OneMinusConstantColor:
		Fatcor = GL_ONE_MINUS_CONSTANT_COLOR;
		break;
	case RHIBlendFactor::ConstantAlpha:
		Fatcor = GL_CONSTANT_ALPHA;
		break;
	case RHIBlendFactor::OneMinusConstantAlpha:
		Fatcor = GL_ONE_MINUS_CONSTANT_ALPHA;
		break;
	case RHIBlendFactor::SrcAlphaSaturate:
		std::cout << "OpenGL 3.3 does not support SrcAlphaSaturate" << std::endl;
		break;
	case RHIBlendFactor::Src1Color:
		std::cout << "OpenGL 3.3 does not support Src1Color" << std::endl;
		break;
	case RHIBlendFactor::OneMinusSrc1Color:
		std::cout << "OpenGL 3.3 does not support OneMinusSrc1Color" << std::endl;
		break;
	case RHIBlendFactor::Src1Alpha:
		std::cout << "OpenGL 3.3 does not support Src1Alpha" << std::endl;
		break;
	case RHIBlendFactor::OneMinusSrc1Alpha:
		std::cout << "OpenGL 3.3 does not support OneMinusSrc1Alpha" << std::endl;
		break;
	default:
		break;
	}
	return Fatcor;
}

inline GLenum ToOpenGLSampleCountFlagBits(int Count)
{
	GLenum Mode;

	return Mode;
}

/*
	Primitives
		glDrawArrays
*/
inline GLenum ToOpenGLPrimitiveTopology(RHITopology RHITopology)
{
	GLenum Mode;
	switch (RHITopology)
	{
	case RHITopology::Points:
		Mode = GL_POINTS;
		break;
	case RHITopology::Lines:
		Mode = GL_LINES;
		break;
	case RHITopology::LineStrip:
		Mode = GL_LINE_STRIP;
		break;
	case RHITopology::Triangles:
		Mode = GL_TRIANGLES;
		break;
	case RHITopology::TriangleStrip:
		Mode = GL_TRIANGLE_STRIP;
		break;
	case RHITopology::TriangleFan:
		Mode = GL_TRIANGLE_FAN;
		break;
	case RHITopology::LinesWithAdjacency:
		Mode = GL_LINES_ADJACENCY;
		break;
	case RHITopology::LineStripWithAdjacency:
		Mode = GL_LINE_STRIP_ADJACENCY;
		break;
	case RHITopology::TrianglesWithAdjacency:
		Mode = GL_TRIANGLES_ADJACENCY;
		break;
	case RHITopology::TriangleStripWithAdjacency:
		Mode = GL_TRIANGLE_STRIP_ADJACENCY;
		break;
	case RHITopology::Patches:
		std::cout << "OpenGL 3.3 does not support Patches" << std::endl;
		break;
	default:
		break;
	}
	return Mode;
}

//GLenum ToOpenGLShaderStageFlagBits(RHIShaderType Type)
//{
//	GLenum Mode;
//
//	return Mode;
//}

inline GLenum ToOpenGLVertexInputRate(std::uint32_t StepRate)
{
	GLenum Mode;

	return Mode;
}

inline GLenum ToOpenGLShaderStageFlagBits(RHIShaderResourceBinding::StageFlags Flag)
{
	GLenum Mode;
	switch (Flag)
	{
	case RHIShaderResourceBinding::StageFlags::VertexStage:
		Mode = GL_VERTEX_SHADER;
		break;
	case RHIShaderResourceBinding::StageFlags::TessellationControlStage:
		std::cout << "OpenGL 3.3 does not support TessellationControlStage" << std::endl;
		//Mode = GL_TESS_CONTROL_SHADER;
		break;
	case RHIShaderResourceBinding::StageFlags::TessellationEvaluationStage:
		std::cout << "OpenGL 3.3 does not support TessellationEvaluationStage" << std::endl;
		//Mode = GL_TESS_EVALUATION_SHADER;
		break;
	case RHIShaderResourceBinding::StageFlags::FragmentStage:
		Mode = GL_FRAGMENT_SHADER;
		break;
	case RHIShaderResourceBinding::StageFlags::ComputeStage:
		std::cout << "OpenGL 3.3 does not support ComputeStage" << std::endl;
		//Mode = GL_COMPUTE_SHADER;
		break;
	case RHIShaderResourceBinding::StageFlags::GeometryStage:
		Mode = GL_GEOMETRY_SHADER;
		break;
	default:
		break;
	}
	return Mode;
}


inline GLenum ToOpenGLLogicOp(RHILogicOp RHILogicOp)
{
	/*
		The initial value is GL_COPY
	*/
	GLenum Op = GL_COPY;
	switch (RHILogicOp)
	{
	case RHILogicOp::CLEAR:
		Op = GL_CLEAR;
		break;
	case RHILogicOp::SET:
		Op = GL_SET;
		break;
	case RHILogicOp::COPY:
		Op = GL_COPY;
		break;
	case RHILogicOp::COPY_INVERTED:
		Op = GL_COPY_INVERTED;
		break;
	case RHILogicOp::NOOP:
		Op = GL_NOOP;
		break;
	case RHILogicOp::INVERT:
		Op = GL_INVERT;
		break;
	case RHILogicOp::AND:
		Op = GL_AND;
		break;
	case RHILogicOp::NAND:
		Op = GL_NAND;
		break;
	case RHILogicOp::OR:
		Op = GL_OR;
		break;
	case RHILogicOp::NOR:
		Op = GL_NOR;
		break;
	case RHILogicOp::XOR:
		Op = GL_XOR;
		break;
	case RHILogicOp::EQUIV:
		Op = GL_EQUIV;
		break;
	case RHILogicOp::AND_REVERSE:
		Op = GL_AND_REVERSE;
		break;
	case RHILogicOp::AND_INVERTED:
		Op = GL_AND_INVERTED;
		break;
	case RHILogicOp::OR_REVERSE:
		Op = GL_OR_REVERSE;
		break;
	case RHILogicOp::OR_INVERTED:
		Op = GL_OR_INVERTED;
		break;
	default:
		break;
	}
	return Op;
}

inline GLenum ToOpenGLTextureType(RHITextureType RHIType)
{
	GLenum Type = GL_TEXTURE_2D;

	switch (RHIType)
	{
	case RHITextureType::Texture1D:
		Type = GL_TEXTURE_1D;
		break;
	case RHITextureType::Texture1DArray:
		Type = GL_TEXTURE_1D_ARRAY;
		break;
	case RHITextureType::Texture2D:
		Type = GL_TEXTURE_2D;
		break;
	case RHITextureType::Texture2DArray:
		Type = GL_TEXTURE_2D_ARRAY;
		break;
	case RHITextureType::Texture3D:
		Type = GL_TEXTURE_3D;
		break;
	case RHITextureType::TextureCubeMap:
		Type = GL_TEXTURE_CUBE_MAP;
		break;
	case RHITextureType::TextureCubeMapArray:
		Type = GL_TEXTURE_CUBE_MAP_ARRAY;
		break;
	default:
		Type = GL_TEXTURE_2D;
		break;
	}

	return Type;
}

inline GLenum ToOpenGLSamplerAddressMode(RHIAddressMode Mode)
{
	switch (Mode)
	{
	case RHIAddressMode::REPEAT:
		return GL_REPEAT;
	case RHIAddressMode::MIRRORED_REPEAT:
		return GL_MIRRORED_REPEAT;
	case RHIAddressMode::CLAMP_TO_EDGE:
		return GL_CLAMP_TO_EDGE;
	case RHIAddressMode::CLAMP_TO_BORDER:
		return GL_CLAMP_TO_BORDER;
	default:
		// 通常我们会返回一个合理的默认值，或者抛出异常
		return GL_REPEAT; // 或者 GL_CLAMP_TO_EDGE
	}
}

inline GLenum ToOpenGLFilter(RHIFilter Filter)
{
	switch (Filter)
	{
	case RHIFilter::NEAREST:
		return GL_NEAREST;
	case RHIFilter::LINEAR:
		return GL_LINEAR;
	default:
		return GL_LINEAR; // 默认使用线性过滤
	}
}

inline GLenum ToOpenGLCubeMapFace(RHICubeMapFace Face)
{
	switch (Face)
	{
	case RHICubeMapFace::CUBE_MAP_POSITIVE_X:  return GL_TEXTURE_CUBE_MAP_POSITIVE_X; break;
	case RHICubeMapFace::CUBE_MAP_NEGATIVE_X:  return GL_TEXTURE_CUBE_MAP_NEGATIVE_X; break;
	case RHICubeMapFace::CUBE_MAP_POSITIVE_Y:  return GL_TEXTURE_CUBE_MAP_POSITIVE_Y; break;
	case RHICubeMapFace::CUBE_MAP_NEGATIVE_Y:  return GL_TEXTURE_CUBE_MAP_NEGATIVE_Y; break;
	case RHICubeMapFace::CUBE_MAP_POSITIVE_Z:  return GL_TEXTURE_CUBE_MAP_POSITIVE_Z; break;
	case RHICubeMapFace::CUBE_MAP_NEGATIVE_Z:  return GL_TEXTURE_CUBE_MAP_NEGATIVE_Z; break;
	default:
		return GL_TEXTURE_CUBE_MAP_POSITIVE_X;
	}
}

inline GLenum ToOpenGLShaderType(RHIShaderType Type)
{
	GLenum ShaderType;
	switch (Type)
	{
	case RHIShaderType::Vertex:
		ShaderType = GL_VERTEX_SHADER;
		break;
	case RHIShaderType::TessellationControl:
		ShaderType = GL_TESS_CONTROL_SHADER;
		break;
	case RHIShaderType::TessellationEvaluation:
		ShaderType = GL_TESS_EVALUATION_SHADER;
		break;
	case RHIShaderType::Fragment:
		ShaderType = GL_FRAGMENT_SHADER;
		break;
	case RHIShaderType::Compute:
		ShaderType = GL_COMPUTE_SHADER;
		break;
	case RHIShaderType::Geometry:
		ShaderType = GL_GEOMETRY_SHADER;
		break;
	default:
		break;
	}
	return ShaderType;
}

//#include <d3d12.h>
//
//inline D3D12_TEXTURE_ADDRESS_MODE ToD3D12SamplerAddressMode(RHIAddressMode Mode)
//{
//	switch (Mode)
//	{
//	case RHIAddressMode::REPEAT:
//		return D3D12_TEXTURE_ADDRESS_MODE_WRAP;
//	case RHIAddressMode::MIRRORED_REPEAT:
//		return D3D12_TEXTURE_ADDRESS_MODE_MIRROR;
//	case RHIAddressMode::CLAMP_TO_EDGE:
//		return D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
//	case RHIAddressMode::CLAMP_TO_BORDER:
//		return D3D12_TEXTURE_ADDRESS_MODE_BORDER;
//	default:
//		return D3D12_TEXTURE_ADDRESS_MODE_WRAP; // 默认使用WRAP
//	}
//}
//
//D3D12_FILTER ToD3D12Filter(RHIFilter Filter)
//{
//	switch (Filter)
//	{
//	case RHIFilter::NEAREST:
//		// D3D12中需要同时指定min、mag、mip过滤
//		return D3D12_FILTER_MIN_MAG_MIP_POINT;
//	case RHIFilter::LINEAR:
//		return D3D12_FILTER_MIN_MAG_MIP_LINEAR;
//	default:
//		return D3D12_FILTER_MIN_MAG_MIP_LINEAR; // 默认使用线性过滤
//	}
//}