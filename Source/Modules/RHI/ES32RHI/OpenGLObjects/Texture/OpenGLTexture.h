#pragma once
#include "ES32RHI/ES32.h"
#include "RHI/RHIObjects/Texture/RHITexture.h"
#include "RHI/RHIObjects/Device/RHIDevice.h"

class OpenGLTexture : public RHITexture
{
public:
	OpenGLTexture(RHIDevice* InDevice, RHITextureType InType, RHIPixelFormat InFormat,
										RHITextureUsageFlag InUsage,
										std::uint32_t InNumMips, std::uint32_t InArraySize,
										std::uint32_t InX, std::uint32_t InY, std::uint32_t InZ,
										void *InData = nullptr);
	virtual ~OpenGLTexture();
	virtual GLuint GetHandle() const;
	virtual GLuint GetTarget() const;
	virtual void TransitionImageLayout(int dir);
	virtual void TransitionTo(RHIImageLayout InLayout) override final;
protected:
	GLuint Handle;
	GLuint Target;
	RHIDevice* Device;
};

