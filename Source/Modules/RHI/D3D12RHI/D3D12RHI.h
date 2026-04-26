#pragma once
#include "RHI.h"
#include "D3D12_Includes.h"
#include "D3D12Objects/Device/D3D12Device.h"
#include "D3D12Objects/Queue/D3D12Queue.h"
#include "RHIObjects/Core/RHICore.h"
class D3D12RHI : public RHI
{
public:
	D3D12RHI();
	~D3D12RHI();
public:
	/*
		选择GPU
	*/
	/**
		@brief 选择GPU
		@return
	*/
	virtual void RHIUseGPU(std::uint32_t GPUIndex) final override;
	/**
		@brief 创建RHIWindow
		@return 返回RHIWindow
	*/
	//virtual RHIWindow* RHICreateWindow(GLFWwindow* Window) final override;
	/*
		Win32
	*/
#ifdef RHI_USE_WIN32_KHR
	virtual RHISurface* RHICreateSurface(HINSTANCE Hinstance, HWND Hwnd) final override;
#endif
	/*
		Wayland
	*/
#ifdef RHI_USE_PLATFORM_WAYLAND_KHR
	virtual RHISurface* RHICreateSurface(struct wl_display* display, struct wl_surface* wayland_surface) final override;
#endif
	/*
		XCB
	*/
#ifdef RHI_USE_XCB_KHR
	virtual RHISurface* RHICreateSurface(xcb_connection_t* Connection, xcb_window_t Window) final override;
#endif
	/*
		Xlib
	*/
#ifdef RHI_USE_Xlib_KHR
	virtual RHISurface* RHICreateSurface(Display* Disp, Window Win) final override;
#endif

	/*
	 * RenderTarget
	 */
	virtual RHIRenderTarget *RHICreateSwapchainRenderTarget(RHISurface *InSurface) final override;
	virtual RHIRenderTarget *RHICreateTextureRenderTarget(RHITexture *InTexture) final override;

	virtual RHIBuffer* RHICreateBuffer(RHIBufferType InType, RHIBufferUsageFlag InUsage, std::uint32_t InSize) final override;
	virtual RHIBuffer* RHICreateBuffer(RHIBufferType InType, RHIBufferUsageFlag InUsage, std::uint32_t InSize, const void* InData) final override;

	virtual RHIGraphicsPipeline* RHICreateGraphicsPipeline() final override;

	virtual RHIGraphicsPipeline* RHICreateGraphicsPipeline(RHIWindow* Window) final override;
	virtual RHIGraphicsPipeline* RHICreateGraphicsPipeline(RHIRenderPass *RenderPass) final override;

	virtual RHIShader* RHICreateShader(RHIShaderType Type, std::uint32_t* Code, size_t CodeSize) final override;

	/*
		Texture
	*/

	/**
		@brief 创建1D纹理
		@param  RHIPixelFormat : 像素格式
		@param  NumMips : mipmap
		@param  SizeX : 纹理长度
		@return 返回RHITexture
	*/
	virtual RHITexture* RHICreateTexture1D(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, void *Data = nullptr) final override;

	/**
		@brief 创建1D纹理数组
		@param  RHIPixelFormat : 像素格式
		@param  NumMips : mipmap
		@param  SizeX : 纹理长度
		@param  ArraySize : 纹理宽度
		@return 返回RHITexture
	*/
	virtual RHITexture* RHICreateTexture1DArray(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t ArraySize, void *Data = nullptr) final override;

	/**
		@brief 创建2D纹理
		@param  RHIPixelFormat : 像素格式
		@param  NumMips : mipmap
		@param  SizeX : 纹理长度
		@param  SizeY : 纹理宽度
		@return 返回RHITexture
	*/
	virtual RHITexture* RHICreateTexture2D(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, void *Data = nullptr) final override;


	/**
		@brief 创建2D纹理数组
		@param  RHIPixelFormat : 像素格式
		@param  NumMips : mipmap
		@param  SizeX : 纹理长度
		@param  SizeY : 纹理宽度
		@param  ArraySize : 纹理宽度
		@return 返回RHITexture
	*/
	virtual RHITexture* RHICreateTexture2DArray(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, std::uint32_t ArraySize, void *Data = nullptr) final override;

	/**
		@brief 创建3D纹理
		@param  RHIPixelFormat : 像素格式
		@param  NumMips : mipmap
		@param  SizeX : 纹理长度
		@param  SizeY : 纹理宽度
		@param  SizeZ : 纹理高度
		@return 返回RHITexture
	*/
	virtual RHITexture* RHICreateTexture3D(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, std::uint32_t SizeZ, void *Data = nullptr) final override;

	/**
		@brief 创建CubeMap纹理
		@param  RHIPixelFormat : 像素格式
		@param  NumMips : mipmap
		@param  Size : 纹理长度
		@return 返回RHITexture
	*/
	virtual RHITexture* RHICreateTextureCube(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, void *Data = nullptr) final override;


	/**
		@brief 创建CubeMap纹理数组
		@param  RHIPixelFormat : 像素格式
		@param  NumMips : mipmap
		@param  Size : 纹理长度
		@return 返回RHITexture
	*/
	virtual RHITexture* RHICreateTextureCubeArray(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, std::uint32_t ArraySize, void *Data = nullptr) final override;

	virtual void RHIUpdateTexture(RHITexture* Texture, const void* InData, std::uint32_t InSize) final override;

	virtual RHISampler* RHICreateSampler(RHIFilter MinFilter = RHIFilter::NEAREST,
		RHIFilter MagFilter = RHIFilter::NEAREST,
		RHIAddressMode AddressModeU = RHIAddressMode::REPEAT,
		RHIAddressMode AddressModeV = RHIAddressMode::REPEAT,
		RHIAddressMode AddressModeW = RHIAddressMode::REPEAT) final override;

	virtual RHIShaderResourceBindings* RHICreateShaderResourceBindings() final override;
private:
public:
	D3D12Device* Device = nullptr;
	D3D12Queue* Queue = nullptr;
	std::vector<D3D12Device *>				Devices;						// 多个
};