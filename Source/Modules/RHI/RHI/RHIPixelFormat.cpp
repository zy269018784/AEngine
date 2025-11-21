#include <RHIPixelFormat.h>

RHIPixelFormatInfo::RHIPixelFormatInfo(
	RHIPixelFormat InUnrealFormat,
	const char* InName,
	std::int32_t InBlockSizeX,
	std::int32_t InBlockSizeY,
	std::int32_t InBlockSizeZ,
	std::int32_t InBlockBytes,
	std::int32_t InNumComponents)
	: Name(InName)
	, UnrealFormat(InUnrealFormat)
	, BlockSizeX(InBlockSizeX)
	, BlockSizeY(InBlockSizeY)
	, BlockSizeZ(InBlockSizeZ)
	, BlockBytes(InBlockBytes)
	, NumComponents(InNumComponents)
{

}
/*
			   pixel			shader 读出的		采样器类型			过滤支持			采样函数
	  SNORM:   [-128, 127] ->   [-1, 1]				sampler1D				
	   SINT:   [   0，255] ->   [ 0, 1]				sampler1D			支持线性过滤		texture
	   UINT:   [   0，255] ->   [ 0, 255]			usampler1D			仅支持最近邻		texelFetch

	   SINT：自动归一化，用于"颜色"数据，支持插值
	   UINT：保持原始整数，用于"数据"存储，不支持插值
	   需要平滑过渡的视觉效果用 SINT，需要精确整数数据用 UINT。
*/
RHIPixelFormatInfo    GPixelFormats[static_cast<size_t>(RHIPixelFormat::PF_MAX_)] =
{
	//					PixelFormat							Name					BlockSizeX	BlockSizeY	BlockSizeZ	BlockBytes	NumComponents 
	RHIPixelFormatInfo(RHIPixelFormat::PF_Unknown,              "Unknown",              0,          0,          0,          0,          0),

	// 深度模板
	RHIPixelFormatInfo(RHIPixelFormat::PF_DepthStencil,         "DepthStencil",         1,          1,          1,          4,          1),

	// 1通道 - 8位
	RHIPixelFormatInfo(RHIPixelFormat::PF_R8_SINT,              "R8_SINT",              1,          1,          1,          1,          1),
	RHIPixelFormatInfo(RHIPixelFormat::PF_R8_UINT,              "R8_UINT",              1,          1,          1,          1,          1),
	RHIPixelFormatInfo(RHIPixelFormat::PF_R8_SNORM,             "R8_SNORM",             1,          1,          1,          1,          1),
	RHIPixelFormatInfo(RHIPixelFormat::PF_R8_UNORM,             "R8_UNORM",             1,          1,          1,          1,          1),
	RHIPixelFormatInfo(RHIPixelFormat::PF_R8_SRGB,              "R8_SRGB",              1,          1,          1,          1,          1),

	// 2通道 - 8位
	RHIPixelFormatInfo(RHIPixelFormat::PF_R8G8_SINT,            "R8G8_SINT",            1,          1,          1,          2,          2),
	RHIPixelFormatInfo(RHIPixelFormat::PF_R8G8_UINT,            "R8G8_UINT",            1,          1,          1,          2,          2),
	RHIPixelFormatInfo(RHIPixelFormat::PF_R8G8_SNORM,           "R8G8_SNORM",           1,          1,          1,          2,          2),
	RHIPixelFormatInfo(RHIPixelFormat::PF_R8G8_UNORM,           "R8G8_UNORM",           1,          1,          1,          2,          2),
	RHIPixelFormatInfo(RHIPixelFormat::PF_R8G8_SRGB,            "R8G8_SRGB",            1,          1,          1,          2,          2),

	// 3通道 - 8位
	RHIPixelFormatInfo(RHIPixelFormat::PF_R8G8B8_SINT,          "R8G8B8_SINT",          1,          1,          1,          3,          3),
	RHIPixelFormatInfo(RHIPixelFormat::PF_R8G8B8_UINT,          "R8G8B8_UINT",          1,          1,          1,          3,          3),
	RHIPixelFormatInfo(RHIPixelFormat::PF_R8G8B8_SNORM,         "R8G8B8_SNORM",         1,          1,          1,          3,          3),
	RHIPixelFormatInfo(RHIPixelFormat::PF_R8G8B8_UNORM,         "R8G8B8_UNORM",         1,          1,          1,          3,          3),
	RHIPixelFormatInfo(RHIPixelFormat::PF_R8G8B8_SRGB,          "R8G8B8_SRGB",          1,          1,          1,          3,          3),

	// 4通道 - 8位
	RHIPixelFormatInfo(RHIPixelFormat::PF_R8G8B8A8_SINT,        "R8G8B8A8_SINT",        1,          1,          1,          4,          4),
	RHIPixelFormatInfo(RHIPixelFormat::PF_R8G8B8A8_UINT,        "R8G8B8A8_UINT",        1,          1,          1,          4,          4),
	RHIPixelFormatInfo(RHIPixelFormat::PF_R8G8B8A8_SNORM,       "R8G8B8A8_SNORM",       1,          1,          1,          4,          4),
	RHIPixelFormatInfo(RHIPixelFormat::PF_R8G8B8A8_UNORM,       "R8G8B8A8_UNORM",       1,          1,          1,          4,          4),
	RHIPixelFormatInfo(RHIPixelFormat::PF_R8G8B8A8_SRGB,        "R8G8B8A8_SRGB",        1,          1,          1,          4,          4),

	// 1通道 - 16位
	RHIPixelFormatInfo(RHIPixelFormat::PF_R16_SINT,             "R16_SINT",             1,          1,          1,          2,          1),
	RHIPixelFormatInfo(RHIPixelFormat::PF_R16_UINT,             "R16_UINT",             1,          1,          1,          2,          1),
	RHIPixelFormatInfo(RHIPixelFormat::PF_R16_SNORM,            "R16_SNORM",            1,          1,          1,          2,          1),
	RHIPixelFormatInfo(RHIPixelFormat::PF_R16_UNORM,            "R16_UNORM",            1,          1,          1,          2,          1),
	RHIPixelFormatInfo(RHIPixelFormat::PF_R16_FLOAT,            "R16_FLOAT",            1,          1,          1,          2,          1),

	// 2通道 - 16位
	RHIPixelFormatInfo(RHIPixelFormat::PF_R16G16_SINT,          "R16G16_SINT",          1,          1,          1,          4,          2),
	RHIPixelFormatInfo(RHIPixelFormat::PF_R16G16_UINT,          "R16G16_UINT",          1,          1,          1,          4,          2),
	RHIPixelFormatInfo(RHIPixelFormat::PF_R16G16_SNORM,         "R16G16_SNORM",         1,          1,          1,          4,          2),
	RHIPixelFormatInfo(RHIPixelFormat::PF_R16G16_UNORM,         "R16G16_UNORM",         1,          1,          1,          4,          2),
	RHIPixelFormatInfo(RHIPixelFormat::PF_R16G16_FLOAT,         "R16G16_FLOAT",         1,          1,          1,          4,          2),

	// 3通道 - 16位
	RHIPixelFormatInfo(RHIPixelFormat::PF_R16G16B16_SINT,       "R16G16B16_SINT",       1,          1,          1,          6,          3),
	RHIPixelFormatInfo(RHIPixelFormat::PF_R16G16B16_UINT,       "R16G16B16_UINT",       1,          1,          1,          6,          3),
	RHIPixelFormatInfo(RHIPixelFormat::PF_R16G16B16_SNORM,      "R16G16B16_SNORM",      1,          1,          1,          6,          3),
	RHIPixelFormatInfo(RHIPixelFormat::PF_R16G16B16_UNORM,      "R16G16B16_UNORM",      1,          1,          1,          6,          3),
	RHIPixelFormatInfo(RHIPixelFormat::PF_R16G16B16_FLOAT,      "R16G16B16_FLOAT",      1,          1,          1,          6,          3),

	// 4通道 - 16位
	RHIPixelFormatInfo(RHIPixelFormat::PF_R16G16B16A16_SINT,    "R16G16B16A16_SINT",    1,          1,          1,          8,          4),
	RHIPixelFormatInfo(RHIPixelFormat::PF_R16G16B16A16_UINT,    "R16G16B16A16_UINT",    1,          1,          1,          8,          4),
	RHIPixelFormatInfo(RHIPixelFormat::PF_R16G16B16A16_SNORM,   "R16G16B16A16_SNORM",   1,          1,          1,          8,          4),
	RHIPixelFormatInfo(RHIPixelFormat::PF_R16G16B16A16_UNORM,   "R16G16B16A16_UNORM",   1,          1,          1,          8,          4),
	RHIPixelFormatInfo(RHIPixelFormat::PF_R16G16B16A16_FLOAT,   "R16G16B16A16_FLOAT",   1,          1,          1,          8,          4),

	// 1通道 - 32位
	RHIPixelFormatInfo(RHIPixelFormat::PF_R32_SINT,             "R32_SINT",             1,          1,          1,          4,          1),
	RHIPixelFormatInfo(RHIPixelFormat::PF_R32_UINT,             "R32_UINT",             1,          1,          1,          4,          1),
	RHIPixelFormatInfo(RHIPixelFormat::PF_R32_FLOAT,            "R32_FLOAT",            1,          1,          1,          4,          1),

	// 2通道 - 32位
	RHIPixelFormatInfo(RHIPixelFormat::PF_R32G32_SINT,          "R32G32_SINT",          1,          1,          1,          8,          2),
	RHIPixelFormatInfo(RHIPixelFormat::PF_R32G32_UINT,          "R32G32_UINT",          1,          1,          1,          8,          2),
	RHIPixelFormatInfo(RHIPixelFormat::PF_R32G32_FLOAT,         "R32G32_FLOAT",         1,          1,          1,          8,          2),

	// 3通道 - 32位
	RHIPixelFormatInfo(RHIPixelFormat::PF_R32G32B32_SINT,       "R32G32B32_SINT",       1,          1,          1,          12,         3),
	RHIPixelFormatInfo(RHIPixelFormat::PF_R32G32B32_UINT,       "R32G32B32_UINT",       1,          1,          1,          12,         3),
	RHIPixelFormatInfo(RHIPixelFormat::PF_R32G32B32_FLOAT,      "R32G32B32_FLOAT",      1,          1,          1,          12,         3),

	// 4通道 - 32位
	RHIPixelFormatInfo(RHIPixelFormat::PF_R32G32B32A32_SINT,    "R32G32B32A32_SINT",    1,          1,          1,          16,         4),
	RHIPixelFormatInfo(RHIPixelFormat::PF_R32G32B32A32_UINT,    "R32G32B32A32_UINT",    1,          1,          1,          16,         4),
	RHIPixelFormatInfo(RHIPixelFormat::PF_R32G32B32A32_FLOAT,   "R32G32B32A32_FLOAT",   1,          1,          1,          16,         4)
};

std::uint32_t PixelFormatToSize(RHIPixelFormat InFormat)
{
	std::uint32_t Size = 0;
	switch (InFormat)
	{
	case RHIPixelFormat::PF_Unknown:
		break;
	case RHIPixelFormat::PF_R8_SINT:

	case RHIPixelFormat::PF_R8_UINT:
		Size = 1;
		break;
	case RHIPixelFormat::PF_R16_SINT:
	case RHIPixelFormat::PF_R16_UINT:
		Size = 2;
		break;
	case RHIPixelFormat::PF_R32_SINT:
	case RHIPixelFormat::PF_R32_UINT:
		Size = 4;
		break;
	case RHIPixelFormat::PF_R16_FLOAT:
		Size = 2;
		break;
	case RHIPixelFormat::PF_R32_FLOAT:
		Size = 4;
		break;
	case RHIPixelFormat::PF_DepthStencil:
		break;
	case RHIPixelFormat::PF_R8G8_SINT:
	case RHIPixelFormat::PF_R8G8_UINT:
		Size = 2;
		break;
	case RHIPixelFormat::PF_R16G16_SINT:
	case RHIPixelFormat::PF_R16G16_UINT:
		Size = 4;
		break;
	case RHIPixelFormat::PF_R32G32_SINT:
	case RHIPixelFormat::PF_R32G32_UINT:
		Size = 8;
		break;
	case RHIPixelFormat::PF_R16G16_FLOAT:
		Size = 4;
		break;
	case RHIPixelFormat::PF_R32G32_FLOAT:
		Size = 8;
		break;
	case RHIPixelFormat::PF_R8G8B8_SINT:
	case RHIPixelFormat::PF_R8G8B8_UINT:
		Size = 3;
		break;
	case RHIPixelFormat::PF_R16G16B16_SINT:
	case RHIPixelFormat::PF_R16G16B16_UINT:
		Size = 6;
		break;
	case RHIPixelFormat::PF_R32G32B32_SINT:
	case RHIPixelFormat::PF_R32G32B32_UINT:
		Size = 12;
		break;
	case RHIPixelFormat::PF_R16G16B16_FLOAT:
		Size = 6;
		break;
	case RHIPixelFormat::PF_R32G32B32_FLOAT:
		Size = 12;
		break;
		//case RHIPixelFormat::PF_B8G8R8A8_SRGB:
	case RHIPixelFormat::PF_R8G8B8A8_SINT:
	case RHIPixelFormat::PF_R8G8B8A8_UINT:
		Size = 4;
		break;
	case RHIPixelFormat::PF_R16G16B16A16_SINT:
	case RHIPixelFormat::PF_R16G16B16A16_UINT:
		Size = 8;
		break;
	case RHIPixelFormat::PF_R32G32B32A32_SINT:
	case RHIPixelFormat::PF_R32G32B32A32_UINT:
		Size = 16;
		break;
	case RHIPixelFormat::PF_R16G16B16A16_FLOAT:
		Size = 8;
		break;
	case RHIPixelFormat::PF_R32G32B32A32_FLOAT:
		Size = 16;
		break;
	case RHIPixelFormat::PF_MAX_:
		break;
	default:
		break;
	}
	return Size;
}