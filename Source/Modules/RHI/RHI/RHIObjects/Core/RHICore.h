#pragma once
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


typedef struct RHIBufferCopy {
	RHIDeviceSize SrcOffset;
	RHIDeviceSize DstOffset;
	RHIDeviceSize Size;
} RHIBufferCopy;


/*
	索引类型
*/
enum class RHIIndexFormat {
	IndexUInt16,
	IndexUInt32
};

enum class RHITopology
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

enum class RHICullMode : uint8_t
{
	CullModeNone,
	Front,
	Back,
	Front_Back
};

enum class RHIFrontFace
{
	CW,
	CCW
};

enum class RHIPolygonMode
{
	Fill,
	Line,
	Point
};

enum class RHICompareOp
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

enum class RHIStencilOp
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

enum class RHIStencilFace
{
	Front,
	Back,
	FrontAndBack
};

enum class RHIBlendFactor : uint8_t
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

enum class RHIBlendOp : uint8_t
{
	Add,
	Sub,
	Min,
	Max,
	Reverse_Sub
};

enum class RHILogicOp : uint8_t
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

enum class RHIPixelFormat : unsigned long long
{
	PF_Unknown = 0,

	// 深度模板
	PF_DepthStencil,		// DepthStencil

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

	PF_MAX_
};

enum class RHIFilter : uint8_t
{
	NEAREST,
	LINEAR
};

enum class RHIAddressMode : uint8_t
{
	REPEAT,
	MIRRORED_REPEAT,
	CLAMP_TO_EDGE,
	CLAMP_TO_BORDER,
};

enum class RHICubeMapFace : int
{
	CUBE_MAP_POSITIVE_X = 0,
	CUBE_MAP_NEGATIVE_X,
	CUBE_MAP_POSITIVE_Y,
	CUBE_MAP_NEGATIVE_Y,
	CUBE_MAP_POSITIVE_Z,
	CUBE_MAP_NEGATIVE_Z
};

enum class RHITextureType : uint8_t
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

enum class RHIShaderType : uint8_t
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