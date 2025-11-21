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
	/**
		@brief 创建RHIWindow
		@return 返回RHIWindow
	*/
	virtual RHIWindow* RHICreateWindow(GLFWwindow* Window) final override;

	virtual RHIBuffer* RHICreateBuffer(RHIBuffer::RHIBufferType InType, RHIBuffer::RHIBufferUsageFlag InUsage, std::uint32_t InSize) final override;
	virtual RHIBuffer* RHICreateBuffer(RHIBuffer::RHIBufferType InType, RHIBuffer::RHIBufferUsageFlag InUsage, std::uint32_t InSize, const void* InData) final override;

	virtual RHIGraphicsPipeline* RHICreateGraphicsPipeline() final override;

	virtual RHIGraphicsPipeline* RHICreateGraphicsPipeline(RHIWindow* Window) final override;

	virtual RHIShader* RHICreateShader(RHIShader::Type Type, std::uint32_t* Code, size_t CodeSize) final override;

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
	virtual RHITexture* RHICreateTexture1D(RHITexture::PixelFormat PixelFormat, std::uint32_t NumMips, std::uint32_t SizeX) final override;

	/**
		@brief 创建1D纹理数组
		@param  PixelFormat : 像素格式
		@param  NumMips : mipmap
		@param  SizeX : 纹理长度
		@param  ArraySize : 纹理宽度
		@return 返回RHITexture
	*/
	virtual RHITexture* RHICreateTexture1DArray(RHITexture::PixelFormat PixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t ArraySize) final override;

	/**
		@brief 创建2D纹理
		@param  PixelFormat : 像素格式
		@param  NumMips : mipmap
		@param  SizeX : 纹理长度
		@param  SizeY : 纹理宽度
		@return 返回RHITexture
	*/
	virtual RHITexture* RHICreateTexture2D(RHITexture::PixelFormat PixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY) final override;


	/**
		@brief 创建2D纹理数组
		@param  PixelFormat : 像素格式
		@param  NumMips : mipmap
		@param  SizeX : 纹理长度
		@param  SizeY : 纹理宽度
		@param  ArraySize : 纹理宽度
		@return 返回RHITexture
	*/
	virtual RHITexture* RHICreateTexture2DArray(RHITexture::PixelFormat PixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, std::uint32_t ArraySize) final override;

	/**
		@brief 创建3D纹理
		@param  PixelFormat : 像素格式
		@param  NumMips : mipmap
		@param  SizeX : 纹理长度
		@param  SizeY : 纹理宽度
		@param  SizeZ : 纹理高度
		@return 返回RHITexture
	*/
	virtual RHITexture* RHICreateTexture3D(RHITexture::PixelFormat PixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t SizeY, std::uint32_t SizeZ) final override;

	/**
		@brief 创建CubeMap纹理
		@param  PixelFormat : 像素格式
		@param  NumMips : mipmap
		@param  Size : 纹理长度
		@return 返回RHITexture
	*/
	virtual RHITexture* RHICreateTextureCube(RHITexture::PixelFormat PixelFormat, std::uint32_t NumMips, std::uint32_t Size) final override;


	/**
		@brief 创建CubeMap纹理数组
		@param  PixelFormat : 像素格式
		@param  NumMips : mipmap
		@param  Size : 纹理长度
		@return 返回RHITexture
	*/
	virtual RHITexture* RHICreateTextureCubeArray(RHITexture::PixelFormat PixelFormat, std::uint32_t NumMips, std::uint32_t SizeX, std::uint32_t ArraySize) final override;

	virtual void RHIUpdateTexture(RHITexture* Texture, const void* InData, std::uint32_t InSize) final override;

	virtual RHISampler* RHICreateSampler(RHISampler::Filter MinFilter = RHISampler::NEAREST,
		RHISampler::Filter MagFilter = RHISampler::NEAREST,
		RHISampler::AddressMode AddressModeU = RHISampler::REPEAT,
		RHISampler::AddressMode AddressModeV = RHISampler::REPEAT,
		RHISampler::AddressMode AddressModeW = RHISampler::REPEAT) final override;

	virtual RHIShaderResourceBindings* RHICreateShaderResourceBindings() final override;
};

GLenum ToOpenGLFormat(RHIVertexInputAttribute::Format Format);