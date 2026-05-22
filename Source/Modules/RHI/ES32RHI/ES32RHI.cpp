#include "ES32RHI.h"
#include "ES32RHI/OpenGLObjects/Buffer/OpenGLBuffer.h"
#include "ES32RHI/OpenGLObjects/Pipeline/OpenGLGraphicsPipeline.h"
#include "ES32RHI/OpenGLObjects/Window/OpenGLWindow.h"
#include "ES32RHI/OpenGLObjects/Shader/OpenGLShader.h"

#include "ES32RHI/OpenGLObjects/Shader/OpenGLShaderResourceBindings.h"
#include "ES32RHI/OpenGLObjects/Shader/OpenGL46ShaderResourceBindings.h"
#include "ES32RHI/OpenGLObjects/Shader/OpenGL33ShaderResourceBindings.h"
#include "ES32RHI/OpenGLObjects/Shader/ES33ShaderResourceBindings.h"
#include "ES32RHI/OpenGLObjects/Shader/ES32ShaderResourceBindings.h"
#include "ES32RHI/OpenGLObjects/Shader/ES31ShaderResourceBindings.h"
#include "ES32RHI/OpenGLObjects/Shader/ES30ShaderResourceBindings.h"
#include "ES32RHI/OpenGLObjects/Shader/ES21ShaderResourceBindings.h"

#include "ES32RHI/OpenGLObjects/Texture/OpenGLTexture.h"
#include "ES32RHI/OpenGLObjects/Texture/OpenGL33Texture.h"
#include "ES32RHI/OpenGLObjects/Texture/OpenGL46Texture.h"
#include "ES32RHI/OpenGLObjects/Texture/ES32Texture.h"
#include "ES32RHI/OpenGLObjects/Texture/ES31Texture.h"
#include "ES32RHI/OpenGLObjects/Texture/ES30Texture.h"
#include "ES32RHI/OpenGLObjects/Texture/ES20Texture.h"

#include "ES32RHI/OpenGLObjects/Resource/OpenGLSampler.h"
#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGLSwapChainRenderTarget.h"
#include "RHI/RHIObjects/Core/RHICore.h"
#include "RHI/RHIObjects/RenderTarget/RHIRenderTarget.h"

#include <iostream>

#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGLSwapChainRenderTarget.h"

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

#if RHI_USE_WIN32_KHR
RHISurface* ES32RHI::RHICreateSurface(HINSTANCE Hinstance, HWND Hwnd)
{
	return nullptr;
}
#endif

#if RHI_USE_PLATFORM_WAYLAND_KHR
RHISurface* ES32RHI::RHICreateSurface(struct wl_display* display, struct wl_surface* wayland_surface)
{
	return nullptr;
}
#endif

#if RHI_USE_XCB_KHR
RHISurface* ES32RHI::RHICreateSurface(xcb_connection_t* Connection, xcb_window_t Window)
{
	return nullptr;
}
#endif

#if RHI_USE_Xlib_KHR
RHISurface* ES32RHI::RHICreateSurface(Display* Disp, Window Win)
{
	return nullptr;
}
#endif

//RHIRenderTarget *ES32RHI::RHICreateSwapchainRenderTarget(RHISurface *InSurface)
RHIRenderTarget *ES32RHI::RHICreateSwapchainRenderTarget(RHISurface *InSurface)
{
	return new OpenGLSwapChainRenderTarget(nullptr, nullptr);
}

RHIRenderTarget *ES32RHI::RHICreateTextureRenderTarget(RHITexture *InTexture)
{
	return nullptr;
}

RHIBuffer* ES32RHI::RHICreateBuffer(RHIBufferType InType, RHIBufferUsageFlag InUsage, std::uint32_t InSize)
{ 
	return nullptr;
}

RHIBuffer* ES32RHI::RHICreateBuffer(RHIBufferType InType, RHIBufferUsageFlag InUsage, std::uint32_t InSize, const void* InData)
{ 
	OpenGLBuffer* Buffer = new OpenGLBuffer(InType, InUsage, InSize, InData);
	return Buffer;
}

RHIGraphicsPipeline* ES32RHI::RHICreateGraphicsPipeline(RHIRenderPass *RenderPass)
{
	OpenGLGraphicsPipeline* Pipeline = new OpenGLGraphicsPipeline();
	return Pipeline;
}

RHIShader* ES32RHI::RHICreateShader(RHIShaderType Type, std::uint32_t* Code, size_t CodeSize)
{ 
	OpenGLShader* Shader = new OpenGLShader(Type, Code, CodeSize);
	return Shader;
}

RHITexture* ES32RHI::RHICreateTexture1D(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, void *Data)
{ 
	RHITextureType Type = RHITextureType::Texture1D;
	std::uint32_t ArraySize = 1;
	std::uint32_t SizeY = 1;
	std::uint32_t SizeZ = 1;
	return new OpenGLTexture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
}

RHITexture* ES32RHI::RHICreateTexture1DArray(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t ArraySize, void *Data)
{ 
	RHITextureType Type = RHITextureType::Texture1DArray;
	std::uint32_t SizeY = ArraySize;
	std::uint32_t SizeZ = 1;
	return new OpenGLTexture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
}

RHITexture* ES32RHI::RHICreateTexture2D(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, void *Data)
{ 
	RHITextureType Type = RHITextureType::Texture2D;
	std::uint32_t ArraySize = 1;
	std::uint32_t SizeZ = 1;
	return new ES20Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
}


RHITexture* ES32RHI::RHICreateTexture2DArray(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, std::uint32_t ArraySize, void *Data)
{ 
	RHITextureType Type = RHITextureType::Texture2DArray;
	std::uint32_t SizeZ = 1;
	return new OpenGLTexture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
}

RHITexture* ES32RHI::RHICreateTexture3D(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, std::uint32_t SizeZ, void *Data)
{ 
	RHITextureType Type = RHITextureType::Texture3D;
	std::uint32_t ArraySize = 1;
	return new OpenGLTexture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
}

RHITexture* ES32RHI::RHICreateTextureCube(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, void *Data)
{
	RHITextureType Type = RHITextureType::TextureCubeMap;
	std::uint32_t ArraySize = 1;
	/*
		实际没用到
	*/
	std::uint32_t SizeZ = 0;
	return new OpenGLTexture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
}

RHITexture* ES32RHI::RHICreateTextureCubeArray(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, std::uint32_t ArraySize, void *Data)
{ 
	RHITextureType Type = RHITextureType::TextureCubeMapArray;
	/*
		实际没用到
	*/
	std::uint32_t SizeZ = 0;
	ArraySize *= 6;
	return new OpenGLTexture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
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
	std::cout << "RHICreateSampler" <<std::endl;
	OpenGLSampler* Sampler = new OpenGLSampler(nullptr, MinFilter, MagFilter, AddressModeU, AddressModeV, AddressModeW);
	return Sampler;
}

RHIShaderResourceBindings* ES32RHI::RHICreateShaderResourceBindings() 
{
	return new OpenGL46ShaderResourceBindings(nullptr);
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