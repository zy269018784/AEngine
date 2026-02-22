#pragma once
#include "RHIObjects/Core/RHICore.h"
#include <cstdint>
class RHITexture
{
public:
	RHITexture(RHITextureType InType, RHIPixelFormat InFormat, std::uint32_t InX, std::uint32_t InY, std::uint32_t InZ, std::uint32_t InNumMips, std::uint32_t InArraySize);
	RHITextureType		GetType();
	RHIPixelFormat		GetFormat();
	std::uint32_t		GetX();
	std::uint32_t		GetY();
	std::uint32_t		GetZ();
	std::uint32_t		GetNumMips();

	virtual void Update(int MipmapLevel, int XOffset, int YOffset, int ZOffset, int Width, int Height, int Depth, const void* InData) = 0;

private:
	RHITextureType			TextureType{};
	RHIPixelFormat			Format{};
	std::uint32_t			X{};
	std::uint32_t			Y{};
	std::uint32_t			Z{};
	std::uint32_t			ArraySize{};
	std::uint32_t			NumMips{};
};
