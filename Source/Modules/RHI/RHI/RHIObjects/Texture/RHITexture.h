#pragma once
#include "RHI/RHIExport.h"
#include "RHI/RHIObjects/Core/RHICore.h"
#include <cstdint>
class RHIEXPORT RHITexture
{
public:
	RHITexture(RHITextureType InType, RHIPixelFormat InFormat, RHITextureUsageFlag InUsage,
		std::uint32_t InX, std::uint32_t InY, std::uint32_t InZ, std::uint32_t InNumMips, std::uint32_t InArraySize, void *InData = nullptr);
	virtual ~RHITexture();
	RHITextureType		GetType() const;
	RHIPixelFormat		GetFormat() const;
	RHITextureUsageFlag	GetUsage() const;
	RHIImageLayout      GetLayout() const;
	std::uint32_t		GetX() const;
	std::uint32_t		GetY() const;
	std::uint32_t		GetZ() const;
	std::uint32_t		GetNumMips() const;
	std::uint32_t		GetArraySize() const;
	void *				GetData() const;

	virtual void Update(int MipmapLevel, int XOffset, int YOffset, int ZOffset, int Width, int Height, int Depth, const void* InData) = 0;
	virtual void TransitionImageLayout(int dir) = 0;
	virtual void TransitionTo(RHIImageLayout InLayout) = 0;
protected:
	void UpdateImageData();
private:
	RHITextureType			TextureType{};
	RHIPixelFormat			Format{};
	RHITextureUsageFlag		Usage{};
	RHIImageLayout			Layout{};
	std::uint32_t			X{};
	std::uint32_t			Y{};
	std::uint32_t			Z{};
	std::uint32_t			ArraySize{};
	std::uint32_t			NumMips{};
	void *					Data = nullptr;
};
