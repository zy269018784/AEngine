#pragma once
#include <RHI.h>
#include <OpenGL330.h>

class OpenGL330RHI : public RHI
{
public:
	OpenGL330RHI();
	~OpenGL330RHI();
public:
	/*
		选择GPU
	*/
	/**
		@brief 选择GPU
		@return
	*/
	virtual void RHIUseGPU(std::uint32_t GPUIndex) final override;

	virtual RHIBuffer* RHICreateBuffer(RHIBuffer::RHIBufferType InType, RHIBuffer::RHIBufferUsageFlag InUsage, std::uint32_t InSize) final override;
	virtual RHIBuffer* RHICreateBuffer(RHIBuffer::RHIBufferType InType, RHIBuffer::RHIBufferUsageFlag InUsage, std::uint32_t InSize, const void* InData) final override;

	virtual RHIGraphicsPipeline* RHICreateGraphicsPipeline() final override;

	virtual RHIGraphicsPipeline* RHICreateGraphicsPipeline(RHIWindow* Window) final override;

	virtual RHIShader* RHICreateShader(RHIShaderType Type, std::uint32_t* Code, size_t CodeSize) final override;

	/*
		Texture
	*/

	/**
		@brief 创建1D纹理
		@param  PixelFormat : 像素格式
		@param  NumMips : mipmap
		@param  SizeX : 纹理长度
		@return 返回RHITexture
	*/
	virtual RHITexture* RHICreateTexture1D(RHIPixelFormat PixelFormat, std::uint32_t NumMips, std::uint32_t SizeX) final override;

	/**
		@brief 创建1D纹理数组
		@param  PixelFormat : 像素格式
		@param  NumMips : mipmap
		@param  SizeX : 纹理长度
		@param  ArraySize : 纹理宽度
		@return 返回RHITexture
	*/
	virtual RHITexture* RHICreateTexture1DArray(RHIPixelFormat PixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t ArraySize) final override;

	/**
		@brief 创建2D纹理
		@param  PixelFormat : 像素格式
		@param  NumMips : mipmap
		@param  SizeX : 纹理长度
		@param  SizeY : 纹理宽度
		@return 返回RHITexture
	*/
	virtual RHITexture* RHICreateTexture2D(RHIPixelFormat PixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY) final override;


	/**
		@brief 创建2D纹理数组
		@param  PixelFormat : 像素格式
		@param  NumMips : mipmap
		@param  SizeX : 纹理长度
		@param  SizeY : 纹理宽度
		@param  ArraySize : 纹理宽度
		@return 返回RHITexture
	*/
	virtual RHITexture* RHICreateTexture2DArray(RHIPixelFormat PixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, std::uint32_t ArraySize) final override;

	/**
		@brief 创建3D纹理
		@param  PixelFormat : 像素格式
		@param  NumMips : mipmap
		@param  SizeX : 纹理长度
		@param  SizeY : 纹理宽度
		@param  SizeZ : 纹理高度
		@return 返回RHITexture
	*/
	virtual RHITexture* RHICreateTexture3D(RHIPixelFormat PixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, std::uint32_t SizeZ) final override;

	/**
		@brief 创建CubeMap纹理
		@param  PixelFormat : 像素格式
		@param  NumMips : mipmap
		@param  Size : 纹理长度
		@return 返回RHITexture
	*/
	virtual RHITexture* RHICreateTextureCube(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY) final override;


	/**
		@brief 创建CubeMap纹理数组
		@param  PixelFormat : 像素格式
		@param  NumMips : mipmap
		@param  Size : 纹理长度
		@return 返回RHITexture
	*/
	virtual RHITexture* RHICreateTextureCubeArray(RHIPixelFormat RHIPixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, std::uint32_t ArraySize) final override;

	virtual void RHIUpdateTexture(RHITexture* Texture, const void* InData, std::uint32_t InSize) final override;

	virtual RHISampler* RHICreateSampler(RHIFilter MinFilter = RHIFilter::NEAREST,
		RHIFilter MagFilter = RHIFilter::NEAREST,
		RHIAddressMode AddressModeU = RHIAddressMode::REPEAT,
		RHIAddressMode AddressModeV = RHIAddressMode::REPEAT,
		RHIAddressMode AddressModeW = RHIAddressMode::REPEAT) final override;

	virtual RHIShaderResourceBindings* RHICreateShaderResourceBindings() final override;
};

GLenum ToOpenGLFormat(RHIVertexInputAttribute::Format Format);