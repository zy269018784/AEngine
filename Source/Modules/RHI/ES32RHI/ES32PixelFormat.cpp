#include "Source/ES32PixelFormat.h"

OpenGLPixelFormatInfo OpenGLPixelFormats[static_cast<size_t>(RHIPixelFormat::PF_MAX_)] = {
	//					PixelFormat								InternalFormat			Format				Type		
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_Unknown,			GL_NONE,				GL_NONE,			GL_NONE),

	// 深度模板
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_DepthStencil,		GL_DEPTH24_STENCIL8,	GL_DEPTH_STENCIL,	GL_UNSIGNED_INT_24_8),

	// 1通道 - 8位
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R8_SINT,			GL_R8I,					GL_RG_INTEGER,		GL_BYTE),
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R8_UINT,			GL_R8UI,				GL_RG_INTEGER,		GL_UNSIGNED_BYTE),
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R8_SNORM,			GL_R8_SNORM,			GL_RED,				GL_BYTE),
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R8_UNORM,			GL_R8,					GL_RED,				GL_UNSIGNED_BYTE),
	/*
		To do : fix me. 
		opengl 不支持这个
	*/
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R8_SRGB,			GL_R8_SNORM,			GL_RED,				GL_UNSIGNED_BYTE),

	// 2通道 - 8位
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R8G8_SINT,			GL_RG8I,				GL_RG_INTEGER,		GL_BYTE),
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R8G8_UINT,			GL_RG8UI,				GL_RG_INTEGER,		GL_UNSIGNED_BYTE),
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R8G8_SNORM,		GL_RG8_SNORM,			GL_RG,				GL_BYTE),
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R8G8_UNORM,		GL_RG8,					GL_RG,				GL_UNSIGNED_BYTE),
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R8G8_SRGB,			GL_SRGB8,				GL_RG,				GL_UNSIGNED_BYTE),

	// 3通道 - 8位
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R8G8B8_SINT,		GL_RGB8I,				GL_RGB_INTEGER,		GL_BYTE),
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R8G8B8_UINT,		GL_RGB8UI,				GL_RGB_INTEGER,		GL_UNSIGNED_BYTE),
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R8G8B8_SNORM,		GL_RGB8_SNORM,			GL_RGB,				GL_BYTE),
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R8G8B8_UNORM,		GL_RGB8,				GL_RGB,				GL_UNSIGNED_BYTE),
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R8G8B8_SRGB,		GL_SRGB8,				GL_RGB,				GL_UNSIGNED_BYTE),

	// 4通道 - 8位
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R8G8B8A8_SINT,		GL_RGBA8I,				GL_RGBA_INTEGER,	GL_BYTE),
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R8G8B8A8_UINT,		GL_RGBA8UI,				GL_RGBA_INTEGER,	GL_UNSIGNED_BYTE),
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R8G8B8A8_SNORM,	GL_RGBA8_SNORM,			GL_RGBA,			GL_BYTE),
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R8G8B8A8_UNORM,	GL_RGBA8,				GL_RGBA,			GL_UNSIGNED_BYTE),
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R8G8B8A8_SRGB,		GL_SRGB8_ALPHA8,		GL_RGBA,			GL_UNSIGNED_BYTE),

	// 1通道 - 16位
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R16_SINT,			GL_R16I,				GL_RED_INTEGER,		GL_SHORT),
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R16_UINT,			GL_R16UI,				GL_RED_INTEGER,		GL_UNSIGNED_SHORT),
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R16_SNORM,			GL_R16_SNORM,			GL_RED,				GL_SHORT),
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R16_UNORM,			GL_R16,					GL_RED,				GL_UNSIGNED_SHORT),
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R16_FLOAT,			GL_R16F,				GL_RED,				GL_HALF_FLOAT),

	// 2通道 - 16位
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R16G16_SINT,		GL_RG16I,				GL_RG_INTEGER,		GL_SHORT),
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R16G16_UINT,		GL_RG16UI,				GL_RG_INTEGER,		GL_UNSIGNED_SHORT),
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R16G16_SNORM,		GL_RG16_SNORM,			GL_RG,				GL_SHORT),
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R16G16_UNORM,		GL_RG16,				GL_RG,				GL_UNSIGNED_SHORT),
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R16G16_FLOAT,		GL_RG16F,				GL_RG,				GL_HALF_FLOAT),

	// 3通道 - 16位
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R16G16B16_SINT,	GL_RGB16I,				GL_RGB_INTEGER,		GL_SHORT),
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R16G16B16_UINT,	GL_RGB16UI,				GL_RGB_INTEGER,		GL_UNSIGNED_SHORT),
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R16G16B16_SNORM,	GL_RGB16_SNORM,			GL_RGB,				GL_SHORT),
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R16G16B16_UNORM,	GL_RGB16,				GL_RGB,				GL_UNSIGNED_SHORT),
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R16G16B16_FLOAT,	GL_RGB16F,				GL_RGB,				GL_HALF_FLOAT),

	// 4通道 - 16位
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R16G16B16A16_SINT,	GL_RGBA16I,			GL_RGBA_INTEGER,	GL_SHORT),
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R16G16B16A16_UINT,	GL_RGBA16UI,		GL_RGBA_INTEGER,	GL_UNSIGNED_SHORT),
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R16G16B16A16_SNORM,	GL_RGBA16_SNORM,	GL_RGBA,			GL_SHORT),
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R16G16B16A16_UNORM,	GL_RGBA16,			GL_RGBA,			GL_UNSIGNED_SHORT),
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R16G16B16A16_FLOAT,	GL_RGBA16F,		GL_RGBA,			GL_HALF_FLOAT),

	// 1通道 - 32位
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R32_SINT,			GL_R32I,				GL_RED_INTEGER,		GL_INT),
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R32_UINT,			GL_R32UI,				GL_RED_INTEGER,		GL_UNSIGNED_INT),
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R32_FLOAT,			GL_R32F,				GL_RED,				GL_FLOAT),

	// 2通道 - 32位
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R32G32_SINT,		GL_RG32I,				GL_RG_INTEGER,		GL_INT),
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R32G32_UINT,		GL_RG32UI,				GL_RG_INTEGER,		GL_UNSIGNED_INT),
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R32G32_FLOAT,		GL_RG32F,				GL_RG,				GL_FLOAT),

	// 3通道 - 32位
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R32G32B32_SINT,	GL_RGB32I,				GL_RGB_INTEGER,		GL_INT),
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R32G32B32_UINT,	GL_RGB32UI,				GL_RGB_INTEGER,		GL_UNSIGNED_INT),
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R32G32B32_FLOAT,	GL_RGB32F,				GL_RGB,				GL_FLOAT),

	// 4通道 - 32位
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R32G32B32A32_SINT,	GL_RGBA32I,			GL_RGBA_INTEGER,	GL_INT),
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R32G32B32A32_UINT,	GL_RGBA32UI,		GL_RGBA_INTEGER,	GL_UNSIGNED_INT),
	OpenGLPixelFormatInfo(RHIPixelFormat::PF_R32G32B32A32_FLOAT,	GL_RGBA32F,		GL_RGBA,			GL_FLOAT)
};