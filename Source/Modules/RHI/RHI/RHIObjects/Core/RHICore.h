#pragma once
#include "RHI/RHIExport.h"
#include <cstdint>
typedef std::uint32_t RHIBool32;
typedef std::uint64_t RHIDeviceAddress;
typedef std::uint64_t RHIDeviceSize;
typedef std::uint32_t RHIFlags;
typedef std::uint32_t RHISampleMask;
typedef std::uint32_t RHIBool32;

typedef std::int64_t  RHIInt64;
typedef std::uint64_t RHIUInt64;

typedef std::int32_t  RHIInt32;
typedef std::uint32_t RHIUInt32;

typedef std::int8_t  RHIInt8;
typedef std::uint8_t RHIUInt8;


typedef struct RHIEXPORT RHIBufferCopy {
	RHIDeviceSize SrcOffset;
	RHIDeviceSize DstOffset;
	RHIDeviceSize Size;
} RHIBufferCopy;


/*
	图像API
*/
enum class RHIEXPORT GraphicsAPI : uint8_t{
	Vulkan,
	OpenGL46,
	OpenGL33,
	ES32,
	ES31,
	ES30,
	ES20,
	D3D12,
	D3D11,
	D3D10,
	D3D9,
	Metal
};


/*
	索引类型
*/
enum class RHIEXPORT RHIIndexFormat {
	IndexUInt16,
	IndexUInt32
};

enum class RHIEXPORT RHITopology
{
	Points,
	Lines,
	LineStrip,
	Triangles,
	TriangleStrip,
	TriangleFan,
	LinesWithAdjacency,
	LineStripWithAdjacency,
	TrianglesWithAdjacency,
	TriangleStripWithAdjacency,
	Patches
};

enum class RHIEXPORT RHICullMode : uint8_t
{
	CullModeNone,
	Front,
	Back,
	Front_Back
};

enum class RHIEXPORT RHIFrontFace
{
	CW,
	CCW
};

enum class RHIEXPORT RHIPolygonMode
{
	Fill,
	Line,
	Point
};

enum class RHIEXPORT RHICompareOp
{
	Never,
	CompareOpAlways,
	Equal,
	NotEqual,
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual
};

enum class RHIEXPORT RHIStencilOp
{
	Keep,
	Zero,
	Replace,
	Incr,
	IncrWrap,
	Decr,
	DecrWrap,
	Invert
};

enum class RHIEXPORT RHIStencilFace
{
	Front,
	Back,
	FrontAndBack
};

enum class RHIEXPORT RHIBlendFactor : uint8_t
{
	Zero,
	One,
	SrcColor,
	OneMinusSrcColor,
	DstColor,
	OneMinusDstColor,
	SrcAlpha,
	OneMinusSrcAlpha,
	DstAlpha,
	OneMinusDstAlpha,
	ConstantColor,
	OneMinusConstantColor,
	ConstantAlpha,
	OneMinusConstantAlpha,
	SrcAlphaSaturate,
	Src1Color,
	OneMinusSrc1Color,
	Src1Alpha,
	OneMinusSrc1Alpha,
};

enum class RHIEXPORT RHIBlendOp : uint8_t
{
	Add,
	Sub,
	Min,
	Max,
	Reverse_Sub
};

enum class RHIEXPORT RHILogicOp : uint8_t
{
	CLEAR,
	SET,
	COPY,
	COPY_INVERTED,
	NOOP,
	INVERT,
	AND,
	NAND,
	OR,
	NOR,
	XOR,
	EQUIV,
	AND_REVERSE,
	AND_INVERTED,
	OR_REVERSE,
	OR_INVERTED
};

enum class RHIEXPORT RHIPixelFormat : std::int32_t
{
	// 深度模板
	PF_DepthStencil = 0,	   // DepthStencil
	PF_DepthStencil_D24_S8,    // 明确要求 24位深度+8位模板
	PF_DepthStencil_D32_S8,    // 明确要求 32位深度+8位模板
	PF_DepthOnly_D32,          // 仅32位深度
	PF_DepthOnly_D16,          // 仅16位深度

	// 1通道
	// 1 byte per component
	PF_R8_SINT,				//   8 bit signed byte			R
	PF_R8_UINT,				//   8 bit unsigned byte		R
	PF_R8_SNORM,			//   8 bit signed byte			R
	PF_R8_UNORM,			//   8 bit unsigned byte		R
	PF_R8_SRGB,				//   8 bit SRGB					R

	PF_R8G8_SINT,			//   8 bit signed byte			R	G
	PF_R8G8_UINT,			//   8 bit unsigned byte		R	G
	PF_R8G8_SNORM,			//   8 bit signed byte			R	G
	PF_R8G8_UNORM,			//   8 bit unsigned byte		R	G
	PF_R8G8_SRGB,			//   8 bit SRGB					R	G	

	PF_R8G8B8_SINT,			//   8 bit signed byte			R	G	B
	PF_R8G8B8_UINT,			//   8 bit unsigned byte		R	G	B
	PF_R8G8B8_SNORM,		//   8 bit signed byte			R	G	B
	PF_R8G8B8_UNORM,		//   8 bit unsigned byte		R	G	B
	PF_R8G8B8_SRGB,			//   8 bit SRGB					R	G	B

	PF_R8G8B8A8_SINT,		//   8 bit signed byte			R	G	B	A
	PF_R8G8B8A8_UINT,		//   8 bit unsigned byte		R	G	B	A
	PF_R8G8B8A8_SNORM,		//   8 bit signed byte			R	G	B	A
	PF_R8G8B8A8_UNORM,		//   8 bit unsigned byte		R	G	B	A
	PF_R8G8B8A8_SRGB,		//   8 bit SRGB					R	G	B	A

	PF_B8G8R8A8_UNORM,		//   8 bit unsigned byte		R	G	B	A

	// 16 bit per component
	PF_R16_SINT,			//  16 bit signed int			R
	PF_R16_UINT,			//  16 bit unsigned int			R
	PF_R16_SNORM,			//  16 bit signed int			R
	PF_R16_UNORM,			//  16 bit unsigned int			R
	PF_R16_FLOAT,			//  16 bit half float			R

	PF_R16G16_SINT,			//  16 bit signed int			R	G
	PF_R16G16_UINT,			//  16 bit unsigned int			R	G
	PF_R16G16_SNORM,		//  16 bit signed int			R	G
	PF_R16G16_UNORM,		//  16 bit unsigned int			R	G
	PF_R16G16_FLOAT,		//  16 bit half float			R	G

	PF_R16G16B16_SINT,		//  16 bit signed int			R	G	B
	PF_R16G16B16_UINT,		//  16 bit unsigned int			R	G	B
	PF_R16G16B16_SNORM,		//  16 bit signed int			R	G	B
	PF_R16G16B16_UNORM,		//  16 bit unsigned int			R	G	B
	PF_R16G16B16_FLOAT,		//  16 bit half float			R	G	B

	PF_R16G16B16A16_SINT,	//  16 bit signed int			R	G	B	A
	PF_R16G16B16A16_UINT,	//  16 bit unsigned int			R	G	B	A
	PF_R16G16B16A16_SNORM,	//  16 bit signed int			R	G	B	A
	PF_R16G16B16A16_UNORM,	//  16 bit unsigned int			R	G	B	A
	PF_R16G16B16A16_FLOAT,	//  16 bit half float			R	G	B	A

	// 32 bit per component
	PF_R32_SINT,			//  32 bit signed int			R
	PF_R32_UINT,			//  32 bit unsigned int			R
	PF_R32_FLOAT,			//  32 bit half float			R

	PF_R32G32_SINT,			//  32 bit signed int			R	G
	PF_R32G32_UINT,			//  32 bit unsigned int			R	G
	PF_R32G32_FLOAT,		//  32 bit half float			R	G

	PF_R32G32B32_SINT,		//  32 bit signed int			R	G	B
	PF_R32G32B32_UINT,		//  32 bit unsigned int			R	G	B
	PF_R32G32B32_FLOAT,		//  32 bit half float			R	G	B

	PF_R32G32B32A32_SINT,	//  32 bit signed int			R	G	B	A
	PF_R32G32B32A32_UINT,	//  32 bit unsigned int			R	G	B	A
	PF_R32G32B32A32_FLOAT,	//  32 bit half float			R	G	B	A
	PF_MAX_,
	PF_Unknown
};

enum class RHIEXPORT RHIFilter : uint8_t
{
	NEAREST,
	LINEAR
};

enum class RHIEXPORT RHIAddressMode : uint8_t
{
	REPEAT,
	MIRRORED_REPEAT,
	CLAMP_TO_EDGE,
	CLAMP_TO_BORDER,
};

enum class RHIEXPORT RHICubeMapFace : int
{
	CUBE_MAP_POSITIVE_X = 0,
	CUBE_MAP_NEGATIVE_X,
	CUBE_MAP_POSITIVE_Y,
	CUBE_MAP_NEGATIVE_Y,
	CUBE_MAP_POSITIVE_Z,
	CUBE_MAP_NEGATIVE_Z
};

enum class RHIEXPORT RHITextureType : uint8_t
{
	Texture1D,
	Texture2D,
	Texture3D,
	Texture1DArray,
	Texture2DArray,
	Texture3DArray,
	TextureCubeMap,
	TextureCubeMapArray
};

enum class RHIEXPORT RHIShaderType : uint8_t
{
	Vertex, 
	Fragment, 
	Compute, 
	Geometry,
	TessellationControl, 
	TessellationEvaluation, 
	/*
		Mesh Shaders
	*/
	Mesh,
	/*
		Task Shaders
	*/
	Task,
	/*
		Ray Tracing
	*/
	RayGeneration,
	Intersection,
	AnyHit,
	ClosestHit,
	Miss 
};

/*
	RHI特性
 */
enum class RHIEXPORT RHIFeatures : std::uint32_t {
	/*
	 * Shader Features
	 */
	VertexShader,
	FragmentShader,
	ComputeShader,
	GeometryShader,
	TessellationControlShader,
	TessellationEvaluationShader,
	/*
	 * Texture Features
	 */
	Texture1D,
	Texture2D,
	Texture3D,
	TextureCubeMap,
	Texture1DArray,
	Texture2DArray,
	Texture3DArray,
	TextureCubeMapArray,
	/*
	 * Depth Bound Feature
	 */
	DepthBoundsTest,
	/*
	 *  Viewport Features
	 */
	MultiViewport,
};

enum class RHIEXPORT RHIAttachmentType: std::uint32_t
{
	Color1 = 0,
	Color2,
	Color3,
	Color4,
	Color5,
	Color6,
	Color7,
	Color8,
	Color9,
	Color10,
	Color11,
	Color12,
	Color13,
	Color14,
	Color15,
	Color16,
	//DepthStencil,
	DepthStencil_D24_S8,    // 明确要求 24位深度+8位模板
	DepthStencil_D32_S8,    // 明确要求 32位深度+8位模板
	DepthOnly_D32,          // 仅32位深度
	DepthOnly_D16,          // 仅16位深度
	NoneAttachmentType,
	Unknown
};

enum class RHIPresentMode: std::uint32_t {
	RHI_PRESENT_MODE_IMMEDIATE_KHR = 0,
	RHI_PRESENT_MODE_MAILBOX_KHR = 1,
	RHI_PRESENT_MODE_FIFO_KHR = 2,
	RHI_PRESENT_MODE_FIFO_RELAXED_KHR = 3,
	RHI_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR = 1000111000,
	RHI_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR = 1000111001,
	RHI_PRESENT_MODE_FIFO_LATEST_READY_KHR = 1000361000,
	RHI_PRESENT_MODE_FIFO_LATEST_READY_EXT = RHI_PRESENT_MODE_FIFO_LATEST_READY_KHR,
	RHI_PRESENT_MODE_MAX_ENUM_KHR = 0x7FFFFFFF
};

enum RHIColorSpace : std::uint32_t {
	RHI_COLOR_SPACE_SRGB_NONLINEAR_KHR = 0,
	RHI_COLOR_SPACE_DISPLAY_P3_NONLINEAR_EXT = 1000104001,
	RHI_COLOR_SPACE_EXTENDED_SRGB_LINEAR_EXT = 1000104002,
	RHI_COLOR_SPACE_DISPLAY_P3_LINEAR_EXT = 1000104003,
	RHI_COLOR_SPACE_DCI_P3_NONLINEAR_EXT = 1000104004,
	RHI_COLOR_SPACE_BT709_LINEAR_EXT = 1000104005,
	RHI_COLOR_SPACE_BT709_NONLINEAR_EXT = 1000104006,
	RHI_COLOR_SPACE_BT2020_LINEAR_EXT = 1000104007,
	RHI_COLOR_SPACE_HDR10_ST2084_EXT = 1000104008,
  // RHI_COLOR_SPACE_DOLBYVISION_EXT is deprecated, but no reason was given in the API XML
	RHI_COLOR_SPACE_DOLBYVISION_EXT = 1000104009,
	RHI_COLOR_SPACE_HDR10_HLG_EXT = 1000104010,
	RHI_COLOR_SPACE_ADOBERGB_LINEAR_EXT = 1000104011,
	RHI_COLOR_SPACE_ADOBERGB_NONLINEAR_EXT = 1000104012,
	RHI_COLOR_SPACE_PASS_THROUGH_EXT = 1000104013,
	RHI_COLOR_SPACE_EXTENDED_SRGB_NONLINEAR_EXT = 1000104014,
	RHI_COLOR_SPACE_DISPLAY_NATIVE_AMD = 1000213000,
  // RHI_COLORSPACE_SRGB_NONLINEAR_KHR is a deprecated alias
	RHI_COLORSPACE_SRGB_NONLINEAR_KHR = RHI_COLOR_SPACE_SRGB_NONLINEAR_KHR,
  // RHI_COLOR_SPACE_DCI_P3_LINEAR_EXT is a deprecated alias
	RHI_COLOR_SPACE_DCI_P3_LINEAR_EXT = RHI_COLOR_SPACE_DISPLAY_P3_LINEAR_EXT,
	RHI_COLOR_SPACE_MAX_ENUM_KHR = 0x7FFFFFFF
};

enum class RHIEXPORT RHITextureUsageFlag: std::uint32_t
{
	TransferSRC,
	TransferDst,
	ColorAttachment,
	DepthStencilAttachment,
	SampledTexture,
	StorageTexture,
};

enum class RHIEXPORT RHITImageUsageFlag: std::uint32_t
{
	TransferSRC,
	TransferDst,
	ColorAttachment,
	DepthStencilAttachment,
	SampledTexture,
	StorageTexture,
};

enum class RHIEXPORT RHIBufferUsageFlag: std::uint32_t
{
#if 0
	Immutable,
	Stream,
	Stream_DRAW,
	Stream_READ,
	Stream_COPY,
	Static,
	Static_DRAW,
	Static_READ,
	Static_COPY,
	Dynamic,
	Dynamic_DRAW,
	Dynamic_READ,
	Dynamic_COPY,
#endif
	TransferSrcBuffer,
	TransferDstBuffer,
	VertexBuffer,
	IndexBuffer,
	UniformBuffer,
	StorageBuffer,
	IndirectBuffer,
};

enum class RHIEXPORT RHIBufferType : std::uint32_t
{
	VertexBuffer,
	IndexBuffer,
	UniformBuffer,
	StorageBuffer,
	IndirectBuffer,
	TransferSrcBuffer,
	TransferDstBuffer,
};


inline std::uint32_t GetRHIPixelFormatSize(RHIPixelFormat format)
{
    switch (format)
    {
        // 深度模板格式
        case RHIPixelFormat::PF_DepthStencil_D24_S8:    return 4;  // 24位深度 + 8位模板 = 32位 = 4字节
        case RHIPixelFormat::PF_DepthStencil_D32_S8:    return 5;  // 32位深度 + 8位模板 = 40位 = 5字节
        case RHIPixelFormat::PF_DepthOnly_D32:          return 4;  // 32位深度 = 4字节
        case RHIPixelFormat::PF_DepthOnly_D16:          return 2;  // 16位深度 = 2字节
        case RHIPixelFormat::PF_DepthStencil:           return 4;  // 默认深度模板格式，通常为4字节

        // 1通道 8位格式
        case RHIPixelFormat::PF_R8_SINT:
        case RHIPixelFormat::PF_R8_UINT:
        case RHIPixelFormat::PF_R8_SNORM:
        case RHIPixelFormat::PF_R8_UNORM:
        case RHIPixelFormat::PF_R8_SRGB:                return 1;  // 1字节

        // 2通道 8位格式
        case RHIPixelFormat::PF_R8G8_SINT:
        case RHIPixelFormat::PF_R8G8_UINT:
        case RHIPixelFormat::PF_R8G8_SNORM:
        case RHIPixelFormat::PF_R8G8_UNORM:
        case RHIPixelFormat::PF_R8G8_SRGB:              return 2;  // 2字节

        // 3通道 8位格式
        case RHIPixelFormat::PF_R8G8B8_SINT:
        case RHIPixelFormat::PF_R8G8B8_UINT:
        case RHIPixelFormat::PF_R8G8B8_SNORM:
        case RHIPixelFormat::PF_R8G8B8_UNORM:
        case RHIPixelFormat::PF_R8G8B8_SRGB:            return 3;  // 3字节

        // 4通道 8位格式
        case RHIPixelFormat::PF_R8G8B8A8_SINT:
        case RHIPixelFormat::PF_R8G8B8A8_UINT:
        case RHIPixelFormat::PF_R8G8B8A8_SNORM:
        case RHIPixelFormat::PF_R8G8B8A8_UNORM:
        case RHIPixelFormat::PF_R8G8B8A8_SRGB:
        case RHIPixelFormat::PF_B8G8R8A8_UNORM:         return 4;  // 4字节

        // 1通道 16位格式
        case RHIPixelFormat::PF_R16_SINT:
        case RHIPixelFormat::PF_R16_UINT:
        case RHIPixelFormat::PF_R16_SNORM:
        case RHIPixelFormat::PF_R16_UNORM:
        case RHIPixelFormat::PF_R16_FLOAT:              return 2;  // 2字节

        // 2通道 16位格式
        case RHIPixelFormat::PF_R16G16_SINT:
        case RHIPixelFormat::PF_R16G16_UINT:
        case RHIPixelFormat::PF_R16G16_SNORM:
        case RHIPixelFormat::PF_R16G16_UNORM:
        case RHIPixelFormat::PF_R16G16_FLOAT:           return 4;  // 2 * 2字节 = 4字节

        // 3通道 16位格式
        case RHIPixelFormat::PF_R16G16B16_SINT:
        case RHIPixelFormat::PF_R16G16B16_UINT:
        case RHIPixelFormat::PF_R16G16B16_SNORM:
        case RHIPixelFormat::PF_R16G16B16_UNORM:
        case RHIPixelFormat::PF_R16G16B16_FLOAT:        return 6;  // 3 * 2字节 = 6字节

        // 4通道 16位格式
        case RHIPixelFormat::PF_R16G16B16A16_SINT:
        case RHIPixelFormat::PF_R16G16B16A16_UINT:
        case RHIPixelFormat::PF_R16G16B16A16_SNORM:
        case RHIPixelFormat::PF_R16G16B16A16_UNORM:
        case RHIPixelFormat::PF_R16G16B16A16_FLOAT:     return 8;  // 4 * 2字节 = 8字节

        // 1通道 32位格式
        case RHIPixelFormat::PF_R32_SINT:
        case RHIPixelFormat::PF_R32_UINT:
        case RHIPixelFormat::PF_R32_FLOAT:              return 4;  // 4字节

        // 2通道 32位格式
        case RHIPixelFormat::PF_R32G32_SINT:
        case RHIPixelFormat::PF_R32G32_UINT:
        case RHIPixelFormat::PF_R32G32_FLOAT:           return 8;  // 2 * 4字节 = 8字节

        // 3通道 32位格式
        case RHIPixelFormat::PF_R32G32B32_SINT:
        case RHIPixelFormat::PF_R32G32B32_UINT:
        case RHIPixelFormat::PF_R32G32B32_FLOAT:        return 12; // 3 * 4字节 = 12字节

        // 4通道 32位格式
        case RHIPixelFormat::PF_R32G32B32A32_SINT:
        case RHIPixelFormat::PF_R32G32B32A32_UINT:
        case RHIPixelFormat::PF_R32G32B32A32_FLOAT:     return 16; // 4 * 4字节 = 16字节

        case RHIPixelFormat::PF_Unknown:
        case RHIPixelFormat::PF_MAX_:
        default:
            return 0;  // 未知格式返回0
    }
}

inline std::uint32_t PixelFormatToSize(RHIPixelFormat InFormat)
{
	std::uint32_t Size = 0;
	switch (InFormat)
	{
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

inline RHIAttachmentType ToRHIAttachmentType(std::uint32_t Index)
{
	RHIAttachmentType Type;
	switch (Index) {
		case 0:
			Type = RHIAttachmentType::Color1;
			break;
		case 1:
			Type = RHIAttachmentType::Color2;
			break;
		case 2:
			Type = RHIAttachmentType::Color3;
			break;
		case 3:
			Type = RHIAttachmentType::Color4;
			break;
		case 4:
			Type = RHIAttachmentType::Color5;
			break;
		case 5:
			Type = RHIAttachmentType::Color6;
			break;
		case 6:
			Type = RHIAttachmentType::Color7;
			break;
		case 7:
			Type = RHIAttachmentType::Color8;
			break;
		case 8:
			Type = RHIAttachmentType::Color9;
			break;
		case 9:
			Type = RHIAttachmentType::Color10;
			break;
		case 10:
			Type = RHIAttachmentType::Color11;
			break;
		case 11:
			Type = RHIAttachmentType::Color12;
			break;
		case 12:
			Type = RHIAttachmentType::Color13;
			break;
		case 13:
			Type = RHIAttachmentType::Color14;
			break;
		case 14:
			Type = RHIAttachmentType::Color15;
			break;
		case 15:
			Type = RHIAttachmentType::Color16;
			break;
	}
	return Type;
}