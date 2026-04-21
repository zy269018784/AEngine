#pragma once
#include "ES32.h"
#include "RHIObjects/Texture/RHITexture.h"
#include "RHIObjects/Device/RHIDevice.h"

class OpenGLTexture : public RHITexture
{
public:
	OpenGLTexture(RHIDevice* InDevice, RHITextureType InType, RHIPixelFormat InFormat, std::uint32_t InNumMips, std::uint32_t InArraySize, std::uint32_t InX, std::uint32_t InY, std::uint32_t InZ, void *InData = nullptr);
	~OpenGLTexture();
	//void Update(const void* InData, std::uint32_t InSize);
	void Update(int MipmapLevel, int XOffset, int YOffset, int ZOffset, int Width, int Height, int Depth, const void* InData) override;
	GLuint GetHandle() const;
	void TransitionImageLayout(int dir) override final;
private:
	GLuint Handle;
	RHIDevice* Device;
};

