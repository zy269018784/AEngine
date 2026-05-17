#pragma once
#include "ES32RHI/ES32.h"
#include "RHI/RHIObjects/Texture/RHITexture.h"

class RHIDevice;
class OpenGL33Texture : public RHITexture
{
public:
	OpenGL33Texture(RHIDevice* InDevice, RHITextureType InType, RHIPixelFormat InFormat, std::uint32_t InNumMips, std::uint32_t InArraySize, std::uint32_t InX, std::uint32_t InY, std::uint32_t InZ, void *InData = nullptr);
	~OpenGL33Texture();
	//void Update(const void* InData, std::uint32_t InSize);
	void Update(int MipmapLevel, int XOffset, int YOffset, int ZOffset, int Width, int Height, int Depth, const void* InData) override;
	GLuint GetHandle() const;
	void TransitionImageLayout(int dir) override final;
private:
	GLuint Handle;
	RHIDevice* Device;
};

