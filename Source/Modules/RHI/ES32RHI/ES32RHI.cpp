#include "ES32RHI.h"
#include "ES32RHI/OpenGLObjects/Buffer/OpenGLBuffer.h"
#include "ES32RHI/OpenGLObjects/Pipeline/OpenGLGraphicsPipeline.h"
#include "ES32RHI/OpenGLObjects/Window/OpenGLWindow.h"


#include "ES32RHI/OpenGLObjects/Pipeline/OpenGLGraphicsPipeline.h"
#include "ES32RHI/OpenGLObjects/Pipeline/OpenGL46GraphicsPipeline.h"
#include "ES32RHI/OpenGLObjects/Pipeline/OpenGL33GraphicsPipeline.h"
#include "ES32RHI/OpenGLObjects/Pipeline/ES32GraphicsPipeline.h"
#include "ES32RHI/OpenGLObjects/Pipeline/ES31GraphicsPipeline.h"
#include "ES32RHI/OpenGLObjects/Pipeline/ES30GraphicsPipeline.h"
#include "ES32RHI/OpenGLObjects/Pipeline/ES20GraphicsPipeline.h"

#include "ES32RHI/OpenGLObjects/Shader/OpenGLShader.h"
#include "ES32RHI/OpenGLObjects/Shader/OpenGL46Shader.h"
#include "ES32RHI/OpenGLObjects/Shader/OpenGL33Shader.h"
#include "ES32RHI/OpenGLObjects/Shader/ES32Shader.h"
#include "ES32RHI/OpenGLObjects/Shader/ES31Shader.h"
#include "ES32RHI/OpenGLObjects/Shader/ES30Shader.h"
#include "ES32RHI/OpenGLObjects/Shader/ES20Shader.h"

#include "ES32RHI/OpenGLObjects/Shader/OpenGLShaderResourceBindings.h"
#include "ES32RHI/OpenGLObjects/Shader/OpenGL46ShaderResourceBindings.h"
#include "ES32RHI/OpenGLObjects/Shader/OpenGL33ShaderResourceBindings.h"
#include "ES32RHI/OpenGLObjects/Shader/ES32ShaderResourceBindings.h"
#include "ES32RHI/OpenGLObjects/Shader/ES31ShaderResourceBindings.h"
#include "ES32RHI/OpenGLObjects/Shader/ES30ShaderResourceBindings.h"
#include "ES32RHI/OpenGLObjects/Shader/ES20ShaderResourceBindings.h"

#include "ES32RHI/OpenGLObjects/Texture/OpenGLTexture.h"
#include "ES32RHI/OpenGLObjects/Texture/OpenGL33Texture.h"
#include "ES32RHI/OpenGLObjects/Texture/OpenGL46Texture.h"
#include "ES32RHI/OpenGLObjects/Texture/ES32Texture.h"
#include "ES32RHI/OpenGLObjects/Texture/ES31Texture.h"
#include "ES32RHI/OpenGLObjects/Texture/ES30Texture.h"
#include "ES32RHI/OpenGLObjects/Texture/ES20Texture.h"

#include "ES32RHI/OpenGLObjects/Resource/OpenGLSampler.h"
#include "ES32RHI/OpenGLObjects/Resource/OpenGL46Sampler.h"
#include "ES32RHI/OpenGLObjects/Resource/OpenGL33Sampler.h"
#include "ES32RHI/OpenGLObjects/Resource/ES32Sampler.h"
#include "ES32RHI/OpenGLObjects/Resource/ES31Sampler.h"
#include "ES32RHI/OpenGLObjects/Resource/ES30Sampler.h"
#include "ES32RHI/OpenGLObjects/Resource/ES20Sampler.h"

#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGL46SwapChainRenderTarget.h"
#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGL33SwapChainRenderTarget.h"
#include "ES32RHI/OpenGLObjects/RenderTarget/ES32SwapChainRenderTarget.h"
#include "ES32RHI/OpenGLObjects/RenderTarget/ES31SwapChainRenderTarget.h"
#include "ES32RHI/OpenGLObjects/RenderTarget/ES30SwapChainRenderTarget.h"
#include "ES32RHI/OpenGLObjects/RenderTarget/ES20SwapChainRenderTarget.h"

#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGL46TextureRenderTarget.h"
#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGL33TextureRenderTarget.h"
#include "ES32RHI/OpenGLObjects/RenderTarget/ES32TextureRenderTarget.h"
#include "ES32RHI/OpenGLObjects/RenderTarget/ES31TextureRenderTarget.h"
#include "ES32RHI/OpenGLObjects/RenderTarget/ES30TextureRenderTarget.h"
#include "ES32RHI/OpenGLObjects/RenderTarget/ES20TextureRenderTarget.h"


#include "RHI/RHIObjects/Core/RHICore.h"
#include "RHI/RHIObjects/RenderTarget/RHIRenderTarget.h"

#include <iostream>

#include "OpenGLObjects/Surface/OpenGLSurface.h"
#include "RHI/RHIObjects/Surface/RHISurface.h"

#if defined(_WIN32) || defined(__CYGWIN__)
#else
	#include <dlfcn.h>
#endif

#include "ES32RHI/OpenGLObjects/RenderTarget/OpenGLSwapChainRenderTarget.h"

ES32RHI::ES32RHI(GraphicsAPI APIIndex)
	: RHI(APIIndex)
{
	if (GraphicsAPI::OpenGL33 == APIIndex || GraphicsAPI::OpenGL46 == APIIndex) {
		if (!gladLoadGL())
		{
			std::cout << "gladLoadGL failed AA" << std::endl;
			return;
		}
	}
	else if (GraphicsAPI::ES20 == APIIndex) {
#if 0
		std::cout << "gladLoadGLES2Loader AAAAA" << std::endl;
#if defined(_WIN32) || defined(__CYGWIN__)
		if (gladLoadGLES2Loader((GLADloadproc)(GetProcAddress))) {
			std::cout << "gladLoadGLES2Loader failed AA" << std::endl;
			return;
		}
#else
		if (gladLoadGLES2Loader((GLADloadproc)(dlsym))) {
			std::cout << "gladLoadGLES2Loader failed BBBBBBBBBBB" << std::endl;
			return;
		}
#endif
		std::cout << "gladLoadGLES2Loader bbbb" << std::endl;
#endif
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
	RHISurface *Surface = nullptr;
	switch (APIIndex) {
		case GraphicsAPI::OpenGL46:
			Surface = new OpenGLSurface(nullptr, Hinstance, Hwnd);
			break;
		case GraphicsAPI::OpenGL33:
			Surface = new OpenGLSurface(nullptr, Hinstance, Hwnd);
			break;
		case GraphicsAPI::ES32:
			Surface = new OpenGLSurface(nullptr, Hinstance, Hwnd);
			break;
		case GraphicsAPI::ES31:
			Surface = new OpenGLSurface(nullptr, Hinstance, Hwnd);
			break;
		case GraphicsAPI::ES30:
			Surface = new OpenGLSurface(nullptr, Hinstance, Hwnd);
			break;
		case GraphicsAPI::ES20:
			Surface = new OpenGLSurface(nullptr, Hinstance, Hwnd);
			break;
	}
	return Surface;
}
#endif

#if RHI_USE_WAYLAND_KHR
RHISurface* ES32RHI::RHICreateSurface(struct wl_display* display, struct wl_surface* wayland_surface)
{
	RHISurface *Surface = nullptr;
	switch (APIIndex) {
		case GraphicsAPI::OpenGL46:
			Surface = new OpenGLSurface(nullptr, display, wayland_surface);
			break;
		case GraphicsAPI::OpenGL33:
			Surface = new OpenGLSurface(nullptr, display, wayland_surface);
			break;
		case GraphicsAPI::ES32:
			Surface = new OpenGLSurface(nullptr, display, wayland_surface);
			break;
		case GraphicsAPI::ES31:
			Surface = new OpenGLSurface(nullptr, display, wayland_surface);
			break;
		case GraphicsAPI::ES30:
			Surface = new OpenGLSurface(nullptr, display, wayland_surface);
			break;
		case GraphicsAPI::ES20:
			Surface = new OpenGLSurface(nullptr, display, wayland_surface);
			break;
	}
	return Surface;
}
#endif

#if RHI_USE_XCB_KHR
RHISurface* ES32RHI::RHICreateSurface(xcb_connection_t* Connection, xcb_window_t Window)
{
	RHISurface *Surface = nullptr;
	switch (APIIndex) {
		case GraphicsAPI::OpenGL46:
			Surface = new OpenGLSurface(nullptr, Connection, Window);
			break;
		case GraphicsAPI::OpenGL33:
			Surface = new OpenGLSurface(nullptr, Connection, Window);
			break;
		case GraphicsAPI::ES32:
			Surface = new OpenGLSurface(nullptr, Connection, Window);
			break;
		case GraphicsAPI::ES31:
			Surface = new OpenGLSurface(nullptr, Connection, Window);
			break;
		case GraphicsAPI::ES30:
			Surface = new OpenGLSurface(nullptr, Connection, Window);
			break;
		case GraphicsAPI::ES20:
			Surface = new OpenGLSurface(nullptr, Connection, Window);
			break;
	}
	return Surface;
}
#endif

#if RHI_USE_Xlib_KHR
RHISurface* ES32RHI::RHICreateSurface(Display* Disp, Window Win)
{
	RHISurface *Surface = nullptr;
	switch (APIIndex) {
		case GraphicsAPI::OpenGL46:
			Surface = new OpenGLSurface(nullptr, Disp, Win);
			break;
		case GraphicsAPI::OpenGL33:
			Surface = new OpenGLSurface(nullptr, Disp, Win);
			break;
		case GraphicsAPI::ES32:
			Surface = new OpenGLSurface(nullptr, Disp, Win);
			break;
		case GraphicsAPI::ES31:
			Surface = new OpenGLSurface(nullptr, Disp, Win);
			break;
		case GraphicsAPI::ES30:
			Surface = new OpenGLSurface(nullptr, Disp, Win);
			break;
		case GraphicsAPI::ES20:
			Surface = new OpenGLSurface(nullptr, Disp, Win);
			break;
	}
	return Surface;
}
#endif

RHIRenderTarget *ES32RHI::RHICreateSwapchainRenderTarget(RHISurface *InSurface)
{
	OpenGLSwapChainRenderTarget *SwapChainRenderTarget;
	switch (APIIndex) {
		case GraphicsAPI::OpenGL46:
			SwapChainRenderTarget = new OpenGL46SwapChainRenderTarget(nullptr, InSurface);
			break;
		case GraphicsAPI::OpenGL33:
			SwapChainRenderTarget = new OpenGL33SwapChainRenderTarget(nullptr, InSurface);
			break;
		case GraphicsAPI::ES32:
			SwapChainRenderTarget = new ES32SwapChainRenderTarget(nullptr, InSurface);
			break;
		case GraphicsAPI::ES31:
			SwapChainRenderTarget = new ES31SwapChainRenderTarget(nullptr, InSurface);
			break;
		case GraphicsAPI::ES30:
			SwapChainRenderTarget = new ES30SwapChainRenderTarget(nullptr, InSurface);
			break;
		case GraphicsAPI::ES20:
			SwapChainRenderTarget = new ES20SwapChainRenderTarget(nullptr, InSurface);
			break;
	}
	SwapChainRenderTarget->Create();
	return SwapChainRenderTarget;
}

RHIRenderTarget *ES32RHI::RHICreateTextureRenderTarget(std::vector<RHITexture *> InColorAttachments,
													  std::vector<RHITexture *> InDepthAttachments)
{
	RHITextureRenderTarget *TextureRenderTarget = nullptr;
	switch (APIIndex) {
		case GraphicsAPI::OpenGL46:
			TextureRenderTarget = new OpenGL46TextureRenderTarget(nullptr, 0, 0);
			break;
		case GraphicsAPI::OpenGL33:
			TextureRenderTarget = new OpenGL33TextureRenderTarget(nullptr, 0, 0);
			break;
		case GraphicsAPI::ES32:
			TextureRenderTarget = new ES32TextureRenderTarget(nullptr, 0, 0);
			break;
		case GraphicsAPI::ES31:
			TextureRenderTarget = new ES31TextureRenderTarget(nullptr, 0, 0);
			break;
		case GraphicsAPI::ES30:
			TextureRenderTarget = new ES30TextureRenderTarget(nullptr, 0, 0);
			break;
		case GraphicsAPI::ES20:
			TextureRenderTarget = new ES20TextureRenderTarget(nullptr, 0, 0);
			break;
	}
	TextureRenderTarget->Create(InColorAttachments, InDepthAttachments);
	return TextureRenderTarget;
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
	RHIGraphicsPipeline *Pipeline = nullptr;
	switch (APIIndex) {
		case GraphicsAPI::OpenGL46:
			Pipeline = new OpenGL46GraphicsPipeline();
			break;
		case GraphicsAPI::OpenGL33:
			Pipeline = new OpenGL33GraphicsPipeline();
			break;
		case GraphicsAPI::ES32:
			Pipeline = new ES32GraphicsPipeline();
			break;
		case GraphicsAPI::ES31:
			Pipeline = new ES31GraphicsPipeline();
			break;
		case GraphicsAPI::ES30:
			Pipeline = new ES30GraphicsPipeline();
			break;
		case GraphicsAPI::ES20:
			Pipeline = new ES20GraphicsPipeline();
			break;
		default:
			Pipeline = nullptr;
			break;
	}
	return Pipeline;
}

RHIShader* ES32RHI::RHICreateShader(RHIShaderType Type, std::uint32_t* Code, size_t CodeSize)
{
	RHIShader *Shader = nullptr;
	switch (APIIndex) {
		case GraphicsAPI::OpenGL46:
			Shader = new OpenGL46Shader(Type, Code, CodeSize);
			break;
		case GraphicsAPI::OpenGL33:
			Shader = new OpenGL33Shader(Type, Code, CodeSize);
			break;
		case GraphicsAPI::ES32:
			Shader = new ES32Shader(Type, Code, CodeSize);
			break;
		case GraphicsAPI::ES31:
			Shader = new ES31Shader(Type, Code, CodeSize);
			break;
		case GraphicsAPI::ES30:
			Shader = new ES30Shader(Type, Code, CodeSize);
			break;
		case GraphicsAPI::ES20:
			Shader = new ES20Shader(Type, Code, CodeSize);
			break;
		default:
			Shader = nullptr;
			break;
	}
	return Shader;
}

RHITexture* ES32RHI::RHICreateTexture1D(RHIPixelFormat RHIPixelFormat, RHITextureUsageFlag InUsage, std::uint32_t NumMips, std::uint32_t SizeX, void *Data)
{ 
	RHITextureType Type = RHITextureType::Texture1D;
	std::uint32_t ArraySize = 1;
	std::uint32_t SizeY = 1;
	std::uint32_t SizeZ = 1;
	RHITexture *Texture;
	switch (APIIndex) {
		case GraphicsAPI::OpenGL46:
			Texture = new OpenGL46Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
		case GraphicsAPI::OpenGL33:
			Texture = new OpenGL33Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
		case GraphicsAPI::ES32:
			Texture = new ES32Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
		case GraphicsAPI::ES31:
			Texture = new ES31Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
		case GraphicsAPI::ES30:
			Texture = new ES30Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
		case GraphicsAPI::ES20:
			Texture = new ES20Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
	}
	return Texture;
}

RHITexture* ES32RHI::RHICreateTexture1DArray(RHIPixelFormat RHIPixelFormat, RHITextureUsageFlag InUsage, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t ArraySize, void *Data)
{ 
	RHITextureType Type = RHITextureType::Texture1DArray;
	std::uint32_t SizeY = ArraySize;
	std::uint32_t SizeZ = 1;
	RHITexture *Texture = nullptr;
	switch (APIIndex) {
		case GraphicsAPI::OpenGL46:
			Texture = new OpenGL46Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
		case GraphicsAPI::OpenGL33:
			Texture = new OpenGL33Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
		case GraphicsAPI::ES32:
			Texture = new ES32Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
		case GraphicsAPI::ES31:
			Texture = new ES31Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
		case GraphicsAPI::ES30:
			Texture = new ES30Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
		case GraphicsAPI::ES20:
			Texture = new ES20Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
	}
	return Texture;
}

RHITexture* ES32RHI::RHICreateTexture2D(RHIPixelFormat RHIPixelFormat, RHITextureUsageFlag InUsage, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, void *Data)
{ 
	RHITextureType Type = RHITextureType::Texture2D;
	std::uint32_t ArraySize = 1;
	std::uint32_t SizeZ = 1;
	RHITexture *Texture = nullptr;
	//return new OpenGL46Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
	//return new OpenGLTexture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
	switch (APIIndex) {
		case GraphicsAPI::OpenGL46:
			Texture = new OpenGL46Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
		case GraphicsAPI::OpenGL33:
			Texture = new OpenGL33Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
		case GraphicsAPI::ES32:
			Texture = new ES32Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
		case GraphicsAPI::ES31:
			Texture = new ES31Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
		case GraphicsAPI::ES30:
			Texture = new ES30Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
		case GraphicsAPI::ES20:
			Texture = new ES20Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
	}
	return Texture;
}


RHITexture* ES32RHI::RHICreateTexture2DArray(RHIPixelFormat RHIPixelFormat, RHITextureUsageFlag InUsage, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, std::uint32_t ArraySize, void *Data)
{ 
	RHITextureType Type = RHITextureType::Texture2DArray;
	std::uint32_t SizeZ = 1;
	RHITexture *Texture;
	switch (APIIndex) {
		case GraphicsAPI::OpenGL46:
			Texture = new OpenGL46Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
		case GraphicsAPI::OpenGL33:
			Texture = new OpenGL33Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
		case GraphicsAPI::ES32:
			Texture = new ES32Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
		case GraphicsAPI::ES31:
			Texture = new ES31Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
		case GraphicsAPI::ES30:
			Texture = new ES30Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
		case GraphicsAPI::ES20:
			Texture = new ES20Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
	}
	return Texture;
}

RHITexture* ES32RHI::RHICreateTexture3D(RHIPixelFormat RHIPixelFormat, RHITextureUsageFlag InUsage, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, std::uint32_t SizeZ, void *Data)
{ 
	RHITextureType Type = RHITextureType::Texture3D;
	std::uint32_t ArraySize = 1;
	RHITexture *Texture;
	switch (APIIndex) {
		case GraphicsAPI::OpenGL46:
			Texture = new OpenGL46Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
		case GraphicsAPI::OpenGL33:
			Texture = new OpenGL33Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
		case GraphicsAPI::ES32:
			Texture = new ES32Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
		case GraphicsAPI::ES31:
			Texture = new ES31Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
		case GraphicsAPI::ES30:
			Texture = new ES30Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
		case GraphicsAPI::ES20:
			Texture = new ES20Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
	}
	return Texture;
}

RHITexture* ES32RHI::RHICreateTextureCube(RHIPixelFormat RHIPixelFormat, RHITextureUsageFlag InUsage, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, void *Data)
{
	RHITextureType Type = RHITextureType::TextureCubeMap;
	std::uint32_t ArraySize = 1;
	/*
		实际没用到
	*/
	std::uint32_t SizeZ = 0;
	RHITexture *Texture;
	switch (APIIndex) {
		case GraphicsAPI::OpenGL46:
			Texture = new OpenGL46Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
		case GraphicsAPI::OpenGL33:
			Texture = new OpenGL33Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
		case GraphicsAPI::ES32:
			Texture = new ES32Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
		case GraphicsAPI::ES31:
			Texture = new ES31Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
		case GraphicsAPI::ES30:
			Texture = new ES30Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
		case GraphicsAPI::ES20:
			Texture = new ES20Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
	}
	return Texture;
}

RHITexture* ES32RHI::RHICreateTextureCubeArray(RHIPixelFormat RHIPixelFormat, RHITextureUsageFlag InUsage, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, std::uint32_t ArraySize, void *Data)
{ 
	RHITextureType Type = RHITextureType::TextureCubeMapArray;
	/*
		实际没用到
	*/
	std::uint32_t SizeZ = 0;
	ArraySize *= 6;
	RHITexture *Texture;
	switch (APIIndex) {
		case GraphicsAPI::OpenGL46:
			Texture = new OpenGL46Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
		case GraphicsAPI::OpenGL33:
			Texture = new OpenGL33Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
		case GraphicsAPI::ES32:
			Texture = new ES32Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
		case GraphicsAPI::ES31:
			Texture = new ES31Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
		case GraphicsAPI::ES30:
			Texture = new ES30Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
		case GraphicsAPI::ES20:
			Texture = new ES20Texture(nullptr, Type, RHIPixelFormat, NumMips, ArraySize, SizeX, SizeY, SizeZ, Data);
			break;
	}
	return Texture;
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
	RHISampler* Sampler = nullptr;
	switch (APIIndex) {
		case GraphicsAPI::OpenGL46:
			Sampler = new OpenGL46Sampler(nullptr, MinFilter, MagFilter, AddressModeU, AddressModeV, AddressModeW);
			break;
		case GraphicsAPI::OpenGL33:
			Sampler = new OpenGL33Sampler(nullptr, MinFilter, MagFilter, AddressModeU, AddressModeV, AddressModeW);
			break;
		case GraphicsAPI::ES32:
			Sampler = new ES32Sampler(nullptr, MinFilter, MagFilter, AddressModeU, AddressModeV, AddressModeW);
			break;
		case GraphicsAPI::ES31:
			Sampler = new ES31Sampler(nullptr, MinFilter, MagFilter, AddressModeU, AddressModeV, AddressModeW);
			break;
		case GraphicsAPI::ES30:
			Sampler = new ES30Sampler(nullptr, MinFilter, MagFilter, AddressModeU, AddressModeV, AddressModeW);
			break;
		case GraphicsAPI::ES20:
			Sampler = new ES20Sampler(nullptr, MinFilter, MagFilter, AddressModeU, AddressModeV, AddressModeW);
			break;
	}
	return Sampler;
}

RHIShaderResourceBindings* ES32RHI::RHICreateShaderResourceBindings() 
{
	RHIShaderResourceBindings* ShaderResourceBindings = nullptr;
	switch (APIIndex) {
		case GraphicsAPI::OpenGL46:
			ShaderResourceBindings = new OpenGL46ShaderResourceBindings(nullptr);
			break;
		case GraphicsAPI::OpenGL33:
			ShaderResourceBindings = new OpenGL33ShaderResourceBindings(nullptr);
			break;
		case GraphicsAPI::ES32:
			ShaderResourceBindings = new ES32ShaderResourceBindings(nullptr);
			break;
		case GraphicsAPI::ES31:
			ShaderResourceBindings = new ES31ShaderResourceBindings(nullptr);
			break;
		case GraphicsAPI::ES30:
			ShaderResourceBindings = new ES30ShaderResourceBindings(nullptr);
			break;
		case GraphicsAPI::ES20:
			ShaderResourceBindings = new ES20ShaderResourceBindings(nullptr);
			break;
	}
	return ShaderResourceBindings;
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