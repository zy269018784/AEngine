#include "RHIObjects/Texture/RHITexture.h"

RHITexture::RHITexture(RHITextureType InType, RHIPixelFormat InFormat, std::uint32_t InX, std::uint32_t InY, std::uint32_t InZ, std::uint32_t InNumMips, std::uint32_t InArraySize)
	: TextureType(InType), Format(InFormat), X(InX), Y(InY), Z(InZ), ArraySize(InArraySize), NumMips(InNumMips)
{
}

RHITextureType RHITexture::GetType() const
{
	return TextureType;
}

RHIPixelFormat RHITexture::GetFormat() const
{
	return this->Format;
}

std::uint32_t  RHITexture::GetX() const
{
	return X;
}

std::uint32_t  RHITexture::GetY() const
{
	return Y;
}

std::uint32_t  RHITexture::GetZ() const
{
	return Z;
}

std::uint32_t  RHITexture::GetNumMips() const
{
	return NumMips;
}

std::uint32_t RHITexture::GetArraySize() const
{
	return ArraySize;
}