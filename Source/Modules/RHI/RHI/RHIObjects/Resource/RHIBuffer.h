#pragma once
#include <cstdint>

class RHIBuffer
{
public:
	enum RHIBufferType
	{
		VertexBuffer		= 0x1 << 1,
		IndexBuffer			= 0x1 << 2,
		UniformBuffer		= 0x1 << 3,
		StorageBuffer		= 0x1 << 4,
		IndirectBuffer		= 0x1 << 5,
		TransferSrcBuffer	= 0x1 << 6,
		TransferDstBuffer	= 0x1 << 7,
	};

	enum RHIBufferUsageFlag
	{
		Immutable		= 0,
		Stream,
		Stream_DRAW,
		Stream_READ,
		Stream_COPY,
		Static				,
		Static_DRAW			,
		Static_READ			,
		Static_COPY			,
		Dynamic				,
		Dynamic_DRAW		,
		Dynamic_READ		,
		Dynamic_COPY		,
	};
public:
	RHIBuffer()
	{
	}

	RHIBuffer(RHIBufferType InType, RHIBufferUsageFlag InUsage, std::uint32_t InSize)
		:  Type(InType), Usage(InUsage), Size(InSize)
	{
	}

	virtual ~RHIBuffer()
	{
	}

	virtual void Update(std::uint32_t InSize, const void* InData) = 0;
private:
	RHIBufferType		Type{};
	RHIBufferUsageFlag	Usage{};
	std::uint32_t		Size{};
};