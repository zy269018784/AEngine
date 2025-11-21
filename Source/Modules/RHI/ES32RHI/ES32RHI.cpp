#include "ES32RHI.h"
#include "OpenGLObjects/Buffer/OpenGLBuffer.h"
#include "OpenGLObjects/Pipeline/OpenGLGraphicsPipeline.h"
#include "OpenGLObjects/Shader/OpenGLShader.h"
#include "OpenGLObjects/Shader/OpenGLShaderResourceBindings.h"
#include "OpenGLObjects/Window/OpenGLWindow.h"
#include "OpenGLObjects/Texture/OpenGLTexture.h"
#include "OpenGLObjects/Resource/OpenGLSampler.h"
#include "RHIObjects/Core/RHICore.h"
#include <iostream>

ES32RHI::ES32RHI()
{
	std::cout << "ES32RHI::ES32RHI() gladLoadGL" << std::endl;
	if (!gladLoadGL()) 
	{
		std::cout << "gladLoadGL failed AA" << std::endl;
		return;
	}
}

ES32RHI::~ES32RHI()
{

}

void ES32RHI::RHIUseGPU(std::uint32_t GPUIndex)
{

}

//RHIWindow* ES32RHI::RHICreateWindow(GLFWwindow* Window)
//{ 
//	return new OpenGLWindow();
//}

#if RHI_USE_PLATFORM_WIN32_KHR 
RHIWindow* ES32RHI::RHICreateWindow(HINSTANCE Hinstance, HWND Hwnd)
{
	return new OpenGLWindow();
}
#endif

#if RHI_USE_PLATFORM_WAYLAND_KHR 
RHIWindow* ES32RHI::RHICreateWindow(struct wl_display* display, struct wl_surface* wayland_surface)
{
	return nullptr;
}
#endif

#if RHI_USE_PLATFORM_XCB_KHR  
RHIWindow* ES32RHI::RHICreateWindow(xcb_connection_t* Connection, xcb_window_t Window)
{
	return new OpenGLWindow();
}
#endif

RHIBuffer* ES32RHI::RHICreateBuffer(RHIBuffer::RHIBufferType InType, RHIBuffer::RHIBufferUsageFlag InUsage, std::uint32_t InSize)
{ 
	return nullptr;
}

RHIBuffer* ES32RHI::RHICreateBuffer(RHIBuffer::RHIBufferType InType, RHIBuffer::RHIBufferUsageFlag InUsage, std::uint32_t InSize, const void* InData)
{ 
	OpenGLBuffer* Buffer = new OpenGLBuffer(InType, InUsage, InSize, InData);
	return Buffer;
}

RHIGraphicsPipeline* ES32RHI::RHICreateGraphicsPipeline()
{ 
	OpenGLGraphicsPipeline* Pipeline = new OpenGLGraphicsPipeline();
	return Pipeline;
}

RHIGraphicsPipeline* ES32RHI::RHICreateGraphicsPipeline(RHIWindow* Window)
{ 
	OpenGLGraphicsPipeline* Pipeline;
	Pipeline = new OpenGLGraphicsPipeline();
	//((OpenGLWindow *)Window)->CommandBuffer->GraphicsPipeline = Pipeline;
	return Pipeline;
}

RHIShader* ES32RHI::RHICreateShader(RHIShaderType Type, std::uint32_t* Code, size_t CodeSize)
{ 
	OpenGLShader* Shader = new OpenGLShader(Type, Code, CodeSize);
	return Shader;
}

RHITexture* ES32RHI::RHICreateTexture1D(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX)
{ 
	RHITextureType Type = RHITextureType::Texture1D;
	std::uint32_t ArraySize = 1;
	std::uint32_t SizeY = 1;
	std::uint32_t SizeZ = 1;
	return new OpenGLTexture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ);
}

RHITexture* ES32RHI::RHICreateTexture1DArray(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t ArraySize)
{ 
	RHITextureType Type = RHITextureType::Texture1DArray;
	std::uint32_t SizeY = ArraySize;
	std::uint32_t SizeZ = 1;
	return new OpenGLTexture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ);
}

RHITexture* ES32RHI::RHICreateTexture2D(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY)
{ 
	RHITextureType Type = RHITextureType::Texture2D;
	std::uint32_t ArraySize = 1;
	std::uint32_t SizeZ = 1;
	return new OpenGLTexture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ);
}


RHITexture* ES32RHI::RHICreateTexture2DArray(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, std::uint32_t ArraySize)
{ 
	RHITextureType Type = RHITextureType::Texture2DArray;
	std::uint32_t SizeZ = 1;
	return new OpenGLTexture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ);
}

RHITexture* ES32RHI::RHICreateTexture3D(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, std::uint32_t SizeZ)
{ 
	RHITextureType Type = RHITextureType::Texture3D;
	std::uint32_t ArraySize = 1;
	return new OpenGLTexture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ);
}

RHITexture* ES32RHI::RHICreateTextureCube(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY)
{
	RHITextureType Type = RHITextureType::TextureCubeMap;
	std::uint32_t ArraySize = 1;
	/*
		实际没用到
	*/
	std::uint32_t SizeZ = 0;
	return new OpenGLTexture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ);
}

RHITexture* ES32RHI::RHICreateTextureCubeArray(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, std::uint32_t ArraySize)
{ 
	RHITextureType Type = RHITextureType::TextureCubeMapArray;
	/*
		实际没用到
	*/
	std::uint32_t SizeZ = 0;
	ArraySize *= 6;
	return new OpenGLTexture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ);
}

void ES32RHI::RHIUpdateTexture(RHITexture* InTexture, const void* InData, std::uint32_t InSize)
{
	OpenGLTexture* Texture = ((OpenGLTexture*)InTexture);
	//Texture->Update(InData, InSize);
}

RHISampler* ES32RHI::RHICreateSampler(RHIFilter MinFilter,
	RHIFilter MagFilter,
	RHIAddressMode AddressModeU,
	RHIAddressMode AddressModeV,
	RHIAddressMode AddressModeW)
{ 
	OpenGLSampler* Sampler = new OpenGLSampler(nullptr, MinFilter, MagFilter, AddressModeU, AddressModeV, AddressModeW);
	return Sampler;
}

RHIShaderResourceBindings* ES32RHI::RHICreateShaderResourceBindings() 
{
	return new OpenGLShaderResourceBindings(nullptr);
}

GLenum ToOpenGLFormat(RHIVertexInputAttribute::Format Format)
{
	GLenum OpenGLFormat = GL_INT;
	switch (Format)
	{
	case RHIVertexInputAttribute::Float4:
	case RHIVertexInputAttribute::Float3:
	case RHIVertexInputAttribute::Float2:
	case RHIVertexInputAttribute::Float:
		OpenGLFormat = GL_FLOAT;
		break;
	case RHIVertexInputAttribute::UNormByte4:
		break;
	case RHIVertexInputAttribute::UNormByte2:
		break;
	case RHIVertexInputAttribute::UNormByte:
		break;
	case RHIVertexInputAttribute::UInt4:
		break;
	case RHIVertexInputAttribute::UInt3:
		break;
	case RHIVertexInputAttribute::UInt2:
		break;
	case RHIVertexInputAttribute::UInt:
		break;
	case RHIVertexInputAttribute::SInt4:
		break;
	case RHIVertexInputAttribute::SInt3:
		break;
	case RHIVertexInputAttribute::SInt2:
		break;
	case RHIVertexInputAttribute::SInt:
		break;
	case RHIVertexInputAttribute::Half4:
		break;
	case RHIVertexInputAttribute::Half3:
		break;
	case RHIVertexInputAttribute::Half2:
		break;
	case RHIVertexInputAttribute::Half:
		break;
	default:
		break;
	}
	return OpenGLFormat;
}