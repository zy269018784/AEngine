#include "RHI/RHIObjects/Texture/RHITexture.h"

#include <iostream>
#include <ostream>

RHITexture::RHITexture(RHITextureType InType, RHIPixelFormat InFormat, std::uint32_t InX, std::uint32_t InY, std::uint32_t InZ, std::uint32_t InNumMips, std::uint32_t InArraySize, void *InData)
	: TextureType(InType), Format(InFormat), X(InX), Y(InY), Z(InZ), ArraySize(InArraySize), NumMips(InNumMips), Data(InData)
{
}

RHITexture::~RHITexture() {

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

void *RHITexture::GetData() const
{
	return Data;
}

void RHITexture::UpdateImageData()
{
	if (GetData())
	{
		auto Width	= GetX();
		auto Height	= GetY();
		auto Depth   = GetZ();
		std::uint32_t Offset = 0;
		std::uint8_t *Pixels = nullptr;
		if (GetType() == RHITextureType::Texture1D)
		{
			Pixels = ((std::uint8_t *)GetData());
			this->Update(0, 0, 0, 0, Width, 1, 1, Pixels);
		}
		else if (GetType() == RHITextureType::Texture2D)
		{
			Pixels = ((std::uint8_t *)GetData());
			std::cout << "this->Update start"  << std::endl;
			this->Update(0, 0, 0, 0, Width, Height, 1, Pixels);
			std::cout << "this->Update end" << std::endl;
		}
		else if (GetType() == RHITextureType::Texture2DArray)
		{
			for (int ArrayIndex = 0; ArrayIndex < GetArraySize(); ArrayIndex++)
			{
				Offset = GetX() * GetY() * 4 * ArrayIndex;
				Pixels = ((std::uint8_t *)GetData()) + Offset;
				this->Update(0, 0, 0, ArrayIndex, Width, Height, 1, Pixels);
			}
		}
		else if (GetType() == RHITextureType::Texture3D)
		{
			Pixels = ((std::uint8_t *)GetData());
			this->Update(0, 0, 0, 0, Width, Height, Depth, Pixels);
		}
		else if (GetType() == RHITextureType::TextureCubeMap)
		{
			Pixels = ((std::uint8_t *)GetData()) + 0 * (GetX() * GetY() * 4);
			this->Update(0, 0, 0, (int)RHICubeMapFace::CUBE_MAP_POSITIVE_X, Width, Height, 1,  Pixels);
			Pixels = ((std::uint8_t *)GetData()) + 1 * (GetX() * GetY() * 4);
			this->Update(0, 0, 0,(int)RHICubeMapFace::CUBE_MAP_NEGATIVE_X, Width, Height, 1,  Pixels);
			Pixels = ((std::uint8_t *)GetData()) + 2 * (GetX() * GetY() * 4);
			this->Update(0, 0, 0,(int)RHICubeMapFace::CUBE_MAP_POSITIVE_Y, Width, Height, 1,  Pixels);
			Pixels = ((std::uint8_t *)GetData()) + 3 * (GetX() * GetY() * 4);
			this->Update(0, 0, 0,(int)RHICubeMapFace::CUBE_MAP_NEGATIVE_Y, Width, Height, 1,  Pixels);
			Pixels = ((std::uint8_t *)GetData()) + 4 * (GetX() * GetY() * 4);
			this->Update(0, 0, 0,       (int)RHICubeMapFace::CUBE_MAP_POSITIVE_Z, Width, Height, 1,  Pixels);
			Pixels = ((std::uint8_t *)GetData()) + 5 * (GetX() * GetY() * 4);
			this->Update(0, 0, 0,       (int)RHICubeMapFace::CUBE_MAP_NEGATIVE_Z, Width, Height, 1,  Pixels);
		}
		else if (GetType() == RHITextureType::TextureCubeMapArray)
		{
			for (int ArrayIndex = 0; ArrayIndex < GetArraySize() / 6; ArrayIndex++)
			{
				Pixels = ((std::uint8_t *)GetData()) + (6 * ArrayIndex + 0) * (GetX() * GetY() * 4);
				this->Update(0, 0, 0, 6 * ArrayIndex + (int)RHICubeMapFace::CUBE_MAP_POSITIVE_X, Width, Height, 1,  Pixels);
				Pixels = ((std::uint8_t *)GetData()) + (6 * ArrayIndex + 1) * (GetX() * GetY() * 4);
				this->Update(0, 0, 0,6 * ArrayIndex + (int)RHICubeMapFace::CUBE_MAP_NEGATIVE_X, Width, Height, 1,  Pixels);
				Pixels = ((std::uint8_t *)GetData()) + (6 * ArrayIndex + 2) * (GetX() * GetY() * 4);
				this->Update(0, 0, 0,6 * ArrayIndex + (int)RHICubeMapFace::CUBE_MAP_POSITIVE_Y, Width, Height, 1,  Pixels);
				Pixels = ((std::uint8_t *)GetData()) + (6 * ArrayIndex + 3) * (GetX() * GetY() * 4);
				this->Update(0, 0, 0,6 * ArrayIndex + (int)RHICubeMapFace::CUBE_MAP_NEGATIVE_Y, Width, Height, 1,  Pixels);
				Pixels = ((std::uint8_t *)GetData()) + (6 * ArrayIndex + 4) * (GetX() * GetY() * 4);
				this->Update(0, 0, 0,6 * ArrayIndex + (int)RHICubeMapFace::CUBE_MAP_POSITIVE_Z, Width, Height, 1,  Pixels);
				Pixels = ((std::uint8_t *)GetData()) + (6 * ArrayIndex + 5) * (GetX() * GetY() * 4);
				this->Update(0, 0, 0,6 * ArrayIndex + (int)RHICubeMapFace::CUBE_MAP_NEGATIVE_Z, Width, Height, 1,  Pixels);
			}
		}
	}
}