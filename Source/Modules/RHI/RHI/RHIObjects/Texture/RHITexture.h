#pragma once
#include "RHIObjects/Core/RHICore.h"
#include <cstdint>
class RHITexture
{
public:
	//enum Type
	//{
	//	Texture1D,
	//	Texture2D,
	//	Texture3D,
	//	Texture1DArray,
	//	Texture2DArray,
	//	Texture3DArray,
	//	TextureCubeMap,
	//	TextureCubeMapArray
	//};

	enum RHIPixelFormat2
	{
		PF_Unknown = 0,
		PF_R8_SBYTE,			//  8 bit signed byte			R
		PF_R8_UBYTE,			//  8 bit unsigned byte			R
		PF_R16_SINT,			// 16 bit signed short			R
		PF_R16_UINT,			// 16 bit unsigned short		R
		PF_R32_SINT,			// 32 bit signed int			R
		PF_R32_UINT,			// 32 bit unsigned int			R
		PF_R16_FLOAT,			// 16 bit half float			R
		PF_R32_FLOAT,			// 32 bit float					R
		PF_DepthStencil,		// DepthStencil
		PF_R8G8_SBYTE,			//  8 bit signed byte			R	G
		PF_R8G8_UBYTE,			//  8 bit unsigned byte			R	G
		PF_R16G16_SINT,			// 16 bit signed short			R	G
		PF_R16G16_UINT,			// 16 bit unsigned short		R	G
		PF_R32G32_SINT,			// 32 bit signed int			R	G
		PF_R32G32_UINT,			// 32 bit unsigned int			R	G
		PF_R16G16_FLOAT,		// 16 bit half float			R	G
		PF_R32G32_FLOAT,		// 32 bit float					R	G
		PF_R8G8B8_SBYTE,		//  8 bit signed byte			R	G	B	
		PF_R8G8B8_UBYTE,		//  8 bit unsigned byte			R	G	B	
		PF_R16G16B16_SINT,		// 16 bit signed short			R	G	B	
		PF_R16G16B16_UINT,		// 16 bit unsigned short		R	G	B	
		PF_R32G32B32_SINT,		// 32 bit signed int			R	G	B	
		PF_R32G32B32_UINT,		// 32 bit unsigned int			R	G	B	
		PF_R16G16B16_FLOAT,		// 16 bit half float			R	G	B	
		PF_R32G32B32_FLOAT,		// 32 bit float					R	G	B	
		PF_R8G8B8A8_SRGB,		// RGBA	for swapchain			R	G	B	A 

		PF_B8G8R8A8_SRGB,		// BGRA	for swapchain			B	G	R	A 
		PF_R8G8B8A8_SBYTE,		//  8 bit signed byte			R	G	B	A	
		PF_R8G8B8A8_UBYTE,		//  8 bit unsigned byte			R	G	B	A	
		PF_R16G16B16A16_SINT,	// 16 bit signed short			R	G	B	A	
		PF_R16G16B16A16_UINT,	// 16 bit unsigned short		R	G	B	A	
		PF_R32G32B32A32_SINT,	// 32 bit signed int			R	G	B	A	
		PF_R32G32B32A32_UINT,	// 32 bit unsigned int			R	G	B	A	
		PF_R16G16B16A16_FLOAT,	// 16 bit half float			R	G	B	A	
		PF_R32G32B32A32_FLOAT,	// 32 bit float					R	G	B	A	
		//PF_MAX
	};
public:
	//RHITexture();
	RHITexture(RHITextureType InType, RHIPixelFormat InFormat, std::uint32_t InX, std::uint32_t InY, std::uint32_t InZ, std::uint32_t InNumMips, std::uint32_t InArraySize);
	RHITextureType		GetType();
	RHIPixelFormat			GetFormat();
	std::uint32_t			GetX();
	std::uint32_t			GetY();
	std::uint32_t			GetZ();

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
