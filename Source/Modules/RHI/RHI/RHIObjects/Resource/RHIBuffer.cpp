#include "RHIObjects/Resource/RHIBuffer.h"

RHIBuffer::RHIBuffer(RHIBufferType InType, RHIBufferUsageFlag InUsage, std::uint32_t InSize)
    :  Type(InType), Usage(InUsage), Size(InSize)
{
}

RHIBuffer::~RHIBuffer()
{

}

std::uint32_t RHIBuffer::GetSize() const
{
    return Size;
}
RHIBufferType RHIBuffer::GetType() const
{
    return Type;
}