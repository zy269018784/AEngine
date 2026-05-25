#pragma once
#include "ES32RHI/ES32.h"
#include "RHI/RHIObjects/Texture/RHITexture.h"
#include "RHI/RHIObjects/Device/RHIDevice.h"

class OpenGLTexture : public RHITexture
{
public:
	OpenGLTexture(RHIDevice* InDevice, RHITextureType InType, RHIPixelFormat InFormat, std::uint32_t InNumMips, std::uint32_t InArraySize, std::uint32_t InX, std::uint32_t InY, std::uint32_t InZ, void *InData = nullptr);
	virtual ~OpenGLTexture();
	virtual GLuint GetHandle() const;
	virtual GLuint GetTarget() const;
	//virtual void Update(int MipmapLevel, int XOffset, int YOffset, int ZOffset, int Width, int Height, int Depth, const void* InData) = 0;
	virtual void TransitionImageLayout(int dir);
protected:
	GLuint Handle;
	GLuint Target;
	RHIDevice* Device;
};

