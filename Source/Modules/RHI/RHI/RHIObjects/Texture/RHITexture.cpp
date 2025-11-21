#include "RHIObjects/Texture/RHITexture.h"



//RHITexture::RHITexture()
//{
//
//}

RHITexture::RHITexture(RHITextureType InType, RHIPixelFormat InFormat, std::uint32_t InX, std::uint32_t InY, std::uint32_t InZ, std::uint32_t InNumMips, std::uint32_t InArraySize)
	: TextureType(InType), Format(InFormat), X(InX), Y(InY), Z(InZ), ArraySize(InArraySize), NumMips(InNumMips)
{
}

RHITextureType RHITexture::GetType() { return TextureType; }
RHIPixelFormat	 RHITexture::GetFormat() { return this->Format; }
std::uint32_t	 RHITexture::GetX() { return X; }
std::uint32_t	 RHITexture::GetY() { return Y; }
std::uint32_t	 RHITexture::GetZ() { return Z; }