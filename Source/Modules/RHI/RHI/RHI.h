#pragma once
#include "RHIPlatform.h"
#include "RHIObjects/Resource/RHIBuffer.h"
#include "RHIObjects/Shader/RHIShader.h"
#include "RHIObjects/CommandBuffer/RHICommandBuffer.h"
#include "RHIObjects/Pipeline/RHIGraphicsPipeline.h"
#include "RHIObjects/Shader/RHIShader.h"
#include "RHIObjects/Texture/RHITexture.h"
#include "RHIObjects/Window/RHIWindow.h"

#ifdef RHI_USE_PLATFORM_WIN32_KHR
#include <windows.h>
#endif

#ifdef RHI_USE_PLATFORM_XCB_KHR
#include <xcb/xcb.h>
#endif
class RHI
{
public:
	/*
		delete RHI会调用VulkanRHI的析构
	*/
	virtual ~RHI() = default;
public:
	/*
		选择GPU
	*/
	/**
		@brief 选择GPU
		@return 
	*/
	virtual void RHIUseGPU(std::uint32_t GPUIndex) = 0;

	/*
		窗口Windows
	*/
	/*
		Win32
	*/
#ifdef RHI_USE_PLATFORM_WIN32_KHR 
	virtual RHIWindow* RHICreateWindow(HINSTANCE Hinstance, HWND Hwnd) = 0;
#endif
	/*
		Wayland
	*/
#ifdef RHI_USE_PLATFORM_WAYLAND_KHR 
	virtual RHIWindow* RHICreateWindow(struct wl_display* display, struct wl_surface* wayland_surface) = 0;
#endif
	/*
		X11
	*/
#ifdef RHI_USE_PLATFORM_XCB_KHR  
	virtual RHIWindow* RHICreateWindow(xcb_connection_t* Connection, xcb_window_t Window) = 0;
#endif

	/*
		管线Pipeline
	*/
	virtual RHIGraphicsPipeline* RHICreateGraphicsPipeline() = 0;

	virtual RHIGraphicsPipeline* RHICreateGraphicsPipeline(RHIWindow *Window) = 0;

	virtual RHIShader* RHICreateShader(RHIShaderType Type, std::uint32_t* Code, size_t CodeSize) = 0;

	/*
		Buffer
	*/
	/**
		@brief 创建Buffer
		@param  InType:			Buffer类型
		@param  InUsage:		Buffer用途
		@param  InSize:			Buffer大小
		@return 返回RHIBuffer
	*/
	virtual RHIBuffer* RHICreateBuffer(RHIBuffer::RHIBufferType InType, RHIBuffer::RHIBufferUsageFlag InUsage, std::uint32_t InSize) = 0;

	/**
		@brief 创建Buffer
		@param  InType:			Buffer类型
		@param  InUsage:		Buffer用途
		@param  InSize:			Buffer大小
		@param  InData:			Buffer数据
		@return 返回RHIBuffer
	*/
	virtual RHIBuffer* RHICreateBuffer(RHIBuffer::RHIBufferType InType, RHIBuffer::RHIBufferUsageFlag InUsage, std::uint32_t InSize, const void* InData) = 0;

	/*
		纹理Texture
	*/
	/**
		@brief 创建1D纹理
		@param  RHIPixelFormat:	像素格式
		@param  NumMips:		mipmap
		@param  SizeX:			纹理长度
		@return 返回RHITexture
	*/
	virtual RHITexture* RHICreateTexture1D(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX) = 0;

	/**
		@brief 创建1D纹理数组
		@param  RHIPixelFormat:	像素格式
		@param  NumMips:		mipmap
		@param  SizeX:			纹理长度
		@param  ArraySize:		纹理宽度
		@return 返回RHITexture
	*/
	virtual RHITexture* RHICreateTexture1DArray(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX,  std::uint32_t ArraySize) = 0;

	/**
		@brief 创建2D纹理
		@param  RHIPixelFormat:	像素格式
		@param  NumMips:		mipmap
		@param  SizeX:			纹理长度
		@param  SizeY:			纹理宽度
		@return 返回RHITexture
	*/
	virtual RHITexture* RHICreateTexture2D(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY) = 0;

	/**
		@brief 创建2D纹理数组
		@param  RHIPixelFormat:	像素格式
		@param  NumMips:		mipmap
		@param  SizeX:			纹理长度
		@param  SizeY:			纹理宽度
		@param  ArraySize :		纹理宽度
		@return 返回RHITexture
	*/
	virtual RHITexture* RHICreateTexture2DArray(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, std::uint32_t ArraySize) = 0;
	
	/**
		@brief 创建3D纹理
		@param  RHIPixelFormat:	像素格式
		@param  NumMips:		mipmap
		@param  SizeX:			纹理长度
		@param  SizeY:			纹理宽度
		@param  SizeZ:			纹理高度
		@return 返回RHITexture
	*/
	virtual RHITexture* RHICreateTexture3D(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, std::uint32_t SizeZ) = 0;

	/**
		@brief 创建CubeMap纹理
		@param  RHIPixelFormat:	像素格式
		@param  NumMips:		mipmap
		@param  Size:			纹理长度
		@return 返回RHITexture
	*/
	virtual RHITexture* RHICreateTextureCube(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY) = 0;

	/**
		@brief 创建CubeMap纹理数组
		@param  RHIPixelFormat:	像素格式
		@param  NumMips:		mipmap
		@param  Size:			纹理长度
		@return 返回RHITexture
	*/
	virtual RHITexture* RHICreateTextureCubeArray(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, std::uint32_t ArraySize) = 0;

	/**
		@brief 更新纹理数据
		@param  Texture:		纹理
		@param  InData:			纹理数据
		@param  InSize:			数据长度
		@return void
	*/
	virtual void RHIUpdateTexture(RHITexture *Texture, const void* InData, std::uint32_t InSize) = 0;

	/*
		采样器Sampler
	*/
	/**
		@brief 创建采样器
		@param  MinFilter:		滤波器
		@param  MagFilter:		滤波器
		@param  AddressModeU:	U寻址模型
		@param  AddressModeV:	V寻址模型
		@param  AddressModeW:	W寻址模型
		@return 返回RHITexture
	*/
	virtual RHISampler* RHICreateSampler(RHIFilter MinFilter = RHIFilter::NEAREST,
		RHIFilter MagFilter = RHIFilter::NEAREST,
		RHIAddressMode AddressModeU = RHIAddressMode::REPEAT,
		RHIAddressMode AddressModeV = RHIAddressMode::REPEAT,
		RHIAddressMode AddressModeW = RHIAddressMode::REPEAT) = 0;

	virtual RHIShaderResourceBindings * RHICreateShaderResourceBindings() = 0;
};

/*
	RHI能力:
		管线:
			图形管线
			计算管线
			光追管线
		着色器:
			顶点着色器
			片元着色器
			几何着色器
			计算着色器
			曲面细分着色器
		纹理:
			1D纹理
			1D纹理数组
			2D纹理
			2D纹理数组
			3D纹理
			CubeMap
			CubeMap数组
		Buffer:
			VBO
			EBO
			UBO
			SSBO
		Device:
		Physical Device:
		Commandbuffer:
		Framebuffer:
		Renderpass:
		Copy Commands:
			copy buffer	 (vkCmdCopyBuffer) (glCopyBufferSubData)
		Clear Commands:
			clear buffer (vkCmdFillBuffer)
		绘制命令:
			Draw			实例绘制
			DrawIndexed		索引实例绘制
		图元:
			point list 
			line list
			line stripe
			line list with adjacency
			triangle list
			triangle list with adjacency
			triangle stripe
			triangle stripe with adjacency
			triangle fan
			patch list
		索引类型:
			uint32
			uint16
		深度测试
		混合
		模板测试
		视口
		裁剪测试
		逻辑操作
		多重采样
*/
