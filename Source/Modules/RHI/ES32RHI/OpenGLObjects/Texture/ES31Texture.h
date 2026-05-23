#pragma once
#include "ES32RHI/OpenGLObjects/Texture/OpenGLTexture.h"
class RHIDevice;
class ES31Texture : public OpenGLTexture
{
public:
	ES31Texture(RHIDevice* InDevice, RHITextureType InType, RHIPixelFormat InFormat, std::uint32_t InNumMips, std::uint32_t InArraySize, std::uint32_t InX, std::uint32_t InY, std::uint32_t InZ, void *InData = nullptr);
	~ES31Texture();
	virtual void Update(int MipmapLevel, int XOffset, int YOffset, int ZOffset, int Width, int Height, int Depth, const void* InData) override final;
	virtual void TransitionImageLayout(int dir) override final;
};

