#include "D3D12RHI.h"
#include "D3D12RHI/D3D12Objects/Pipeline/D3D12GraphicsPipeline.h"
#include "D3D12RHI/D3D12Objects/Device/D3D12Device.h"
#include "D3D12RHI/D3D12Objects/Resource/D3D12Buffer.h"
#include "D3D12RHI/D3D12Objects/Shader/D3D12Shader.h"
#include "D3D12RHI/D3D12Objects/Shader/D3D12ShaderResourceBindings.h"
#include "D3D12RHI/D3D12Objects/Window/D3D12Window.h"
#include "D3D12RHI/D3D12Objects/PhysicalDevice/D3D12PhysicalDevice.h"
#include "D3D12RHI/D3D12Objects/Surface/D3D12Surface.h"
#include "D3D12RHI/D3D12Objects/CommandBuffer/D3D12CommandBuffer.h"
#include "D3D12RHI/D3D12Objects/SwapChain/D3D12SwapChain.h"
//#include <spirv_cross/spirv.hpp>
//#include <spirv_cross/spirv_cross.hpp>
//#include <spirv_cross/spirv_hlsl.hpp>
#include <iostream>

#include "ES32RHI/OpenGLObjects/Surface/OpenGLSurface.h"

D3D12RHI::D3D12RHI()
{
//	Device = new D3D12Device();
//	Queue = new D3D12Queue(Device);
	for (int i = 0; i < 1; i++)
	{
		D3D12Device *pDevice = new D3D12Device();
		pDevice->CreateCommandPool();
		pDevice->CreateQueue();
		Devices.emplace_back(pDevice);
	}
}

D3D12RHI::~D3D12RHI()
{

}


void D3D12RHI::RHIUseGPU(std::uint32_t GPUIndex)
{

}

#if RHI_USE_WIN32_KHR
RHISurface* D3D12RHI::RHICreateSurface(HINSTANCE Hinstance, HWND Hwnd)
{
	return nullptr;
}
#endif

#if RHI_USE_WAYLAND_KHR
RHISurface* D3D12RHI::RHICreateSurface(struct wl_display* display, struct wl_surface* wayland_surface)
{
	return nullptr;
}
#endif

#if RHI_USE_XCB_KHR
RHISurface* D3D12RHI::RHICreateSurface(xcb_connection_t* Connection, xcb_window_t Window)
{
	return nullptr;
}
#endif

#if RHI_USE_Xlib_KHR
RHISurface* D3D12RHI::RHICreateSurface(Display* Disp, Window Win)
{
	return nullptr;
}
#endif

RHIRenderTarget *D3D12RHI::RHICreateSwapchainRenderTarget(OpenGLSurface *InSurface)
{
	return nullptr;
}

RHIRenderTarget *D3D12RHI::RHICreateTextureRenderTarget(RHITexture *InTexture)
{
	return nullptr;
}

RHIBuffer* D3D12RHI::RHICreateBuffer(RHIBufferType InType, RHIBufferUsageFlag InUsage, std::uint32_t InSize)
{
	return nullptr;
}

RHIBuffer* D3D12RHI::RHICreateBuffer(RHIBufferType InType, RHIBufferUsageFlag InUsage, std::uint32_t InSize, const void* InData)
{
	D3D12Buffer* Buffer = new D3D12Buffer(Devices[GPUIndex], InType, InUsage, InSize, InData);
	return Buffer;
}


RHIGraphicsPipeline* D3D12RHI::RHICreateGraphicsPipeline(RHIRenderPass *RenderPass)
{
	D3D12GraphicsPipeline* Pipeline = new D3D12GraphicsPipeline(Devices[GPUIndex]);
	return Pipeline;
}

RHIShader* D3D12RHI::RHICreateShader(RHIShaderType Type, std::uint32_t* Code, size_t CodeSize)
{
#if 0
	spirv_cross::CompilerHLSL glsl(Code, CodeSize / 4);

	auto options = glsl.get_hlsl_options();
	// 设置合适的着色器模型版本
	options.shader_model = 50;  // 或 60、61 等
	// 启用现代语义
	glsl.set_hlsl_options(options);

	std::string source = glsl.compile();
	std::cout << source << std::endl;
	D3D12Shader* Shader = new D3D12Shader(Devices[GPUIndex], Type, (std::uint32_t *)source.data(), source.length());
#endif
	D3D12Shader* Shader = new D3D12Shader(Devices[GPUIndex], Type, Code, CodeSize);
	return Shader;
}


RHITexture* D3D12RHI::RHICreateTexture1D(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, void *Data)
{
	return nullptr;
}

/**
	@brief 创建1D纹理数组
	@param  RHIPixelFormat : 像素格式
	@param  NumMips : mipmap
	@param  SizeX : 纹理长度
	@param  ArraySize : 纹理宽度
	@return 返回RHITexture
*/
RHITexture* D3D12RHI::RHICreateTexture1DArray(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t ArraySize, void *Data)
{
	return nullptr;
}

/**
	@brief 创建2D纹理
	@param  RHIPixelFormat : 像素格式
	@param  NumMips : mipmap
	@param  SizeX : 纹理长度
	@param  SizeY : 纹理宽度
	@return 返回RHITexture
*/
RHITexture* D3D12RHI::RHICreateTexture2D(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, void *Data)
{
	return nullptr;
}


/**
	@brief 创建2D纹理数组
	@param  RHIPixelFormat : 像素格式
	@param  NumMips : mipmap
	@param  SizeX : 纹理长度
	@param  SizeY : 纹理宽度
	@param  ArraySize : 纹理宽度
	@return 返回RHITexture
*/
RHITexture* D3D12RHI::RHICreateTexture2DArray(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, std::uint32_t ArraySize, void *Data)
{
	return nullptr;
}

/**
	@brief 创建3D纹理
	@param  RHIPixelFormat : 像素格式
	@param  NumMips : mipmap
	@param  SizeX : 纹理长度
	@param  SizeY : 纹理宽度
	@param  SizeZ : 纹理高度
	@return 返回RHITexture
*/
RHITexture* D3D12RHI::RHICreateTexture3D(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, std::uint32_t SizeZ, void *Data)
{
	return nullptr;
}

/**
	@brief 创建CubeMap纹理
	@param  RHIPixelFormat : 像素格式
	@param  NumMips : mipmap
	@param  Size : 纹理长度
	@return 返回RHITexture
*/
RHITexture* D3D12RHI::RHICreateTextureCube(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, void *Data)
{
	return nullptr;
}


/**
	@brief 创建CubeMap纹理数组
	@param  RHIPixelFormat : 像素格式
	@param  NumMips : mipmap
	@param  Size : 纹理长度
	@return 返回RHITexture
*/
RHITexture* D3D12RHI::RHICreateTextureCubeArray(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, std::uint32_t ArraySize, void *Data)
{
	return nullptr;
}

void D3D12RHI::RHIUpdateTexture(RHITexture* Texture, const void* InData, std::uint32_t InSize)
{
	
}

RHISampler* D3D12RHI::RHICreateSampler(RHIFilter MinFilter, RHIFilter MagFilter, RHIAddressMode AddressModeU, RHIAddressMode AddressModeV, RHIAddressMode AddressModeW )
{
	return nullptr;
}

RHIShaderResourceBindings* D3D12RHI::RHICreateShaderResourceBindings()
{
	return new D3D12ShaderResourceBindings(Devices[GPUIndex]);
}