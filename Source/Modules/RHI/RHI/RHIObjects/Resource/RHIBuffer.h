#pragma once
#include "RHI/RHIExport.h"
#include "RHI/RHIObjects/Core/RHICore.h"
class RHIEXPORT RHIBuffer
{
public:
	RHIBuffer() = default;
	RHIBuffer(RHIBufferType InType, RHIBufferUsageFlag InUsage, std::uint32_t InSize);
	virtual ~RHIBuffer();
	std::uint32_t GetSize() const;
	RHIBufferType GetType() const;
	virtual void Update(std::uint32_t InSize, const void* InData) = 0;
private:
	RHIBufferType		Type{};
	RHIBufferUsageFlag	Usage{};
	std::uint32_t		Size{};
};