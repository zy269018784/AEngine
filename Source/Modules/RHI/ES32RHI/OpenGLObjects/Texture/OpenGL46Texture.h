#pragma once
#include "ES32RHI/OpenGLObjects/Texture/OpenGLTexture.h"
class RHIDevice;
class OpenGL46Texture : public OpenGLTexture
{
public:
	OpenGL46Texture(RHIDevice* InDevice, RHITextureType InType, RHIPixelFormat InFormat, RHITextureUsageFlag InUsage,
		std::uint32_t InNumMips, std::uint32_t InArraySize, std::uint32_t InX, std::uint32_t InY, std::uint32_t InZ, void *InData = nullptr);
	~OpenGL46Texture();
	//GLuint GetHandle() const;
	virtual void Update(int MipmapLevel, int XOffset, int YOffset, int ZOffset, int Width, int Height, int Depth, const void* InData) override final;
	virtual void TransitionImageLayout(int dir) override final;
};

