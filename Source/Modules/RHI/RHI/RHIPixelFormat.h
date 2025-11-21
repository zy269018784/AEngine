#pragma once
#include <cstdint>
#include <cstddef>

#if defined(PF_MAX)
#undef PF_MAX
#endif

#include "RHIObjects/Core/RHICore.h"

struct RHIPixelFormatInfo
{
	//RHIPixelFormatInfo() = delete;
	RHIPixelFormatInfo() = default;
	RHIPixelFormatInfo(
		RHIPixelFormat InUnrealFormat,
		const char* InName,
		std::int32_t InBlockSizeX,
		std::int32_t InBlockSizeY,
		std::int32_t InBlockSizeZ,
		std::int32_t InBlockBytes,
		std::int32_t InNumComponents);

	const char* Name;
	RHIPixelFormat		UnrealFormat;
	std::int32_t	BlockSizeX;
	std::int32_t	BlockSizeY;
	std::int32_t	BlockSizeZ;
	std::int32_t	BlockBytes;
	std::int32_t	NumComponents;

	uint32_t		PlatformFormat{ 0 }; //VkFormat
};

extern RHIPixelFormatInfo GPixelFormats[static_cast<size_t>(RHIPixelFormat::PF_MAX_)];

std::uint32_t PixelFormatToSize(RHIPixelFormat InFormat);
