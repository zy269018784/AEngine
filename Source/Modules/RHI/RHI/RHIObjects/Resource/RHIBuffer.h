#pragma once
#include <cstdint>
#include "RHIObjects/Core/RHICore.h"
class RHIBuffer
{
public:



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

	std::uint32_t GetSize() const { return Size; }
private:
	RHIBufferType		Type{};
	RHIBufferUsageFlag	Usage{};
	std::uint32_t		Size{};
};