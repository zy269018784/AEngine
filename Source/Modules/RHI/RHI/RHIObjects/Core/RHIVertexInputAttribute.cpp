#include "RHIObjects/Core/RHIVertexInputAttribute.h"

RHIVertexInputAttribute::RHIVertexInputAttribute()
{

}

RHIVertexInputAttribute::RHIVertexInputAttribute(int binding, int location, RHIVertexInputAttribute::Format format, std::uint32_t offset, int matrixSlice)
	: Binding(binding), Location(location), Format_(format), Offset(offset)
{

}

void RHIVertexInputAttribute::SetBinding(int b)
{
	Binding = b;
}

int RHIVertexInputAttribute::GetBinding() const
{
	return Binding;
}

void RHIVertexInputAttribute::SetLocation(int loc)
{
	Location = loc;
}

int RHIVertexInputAttribute::GetLocation() const
{
	return Location;
}

void RHIVertexInputAttribute::SetOffset(std::uint32_t ofs)
{
	Offset = ofs;
}

std::uint32_t RHIVertexInputAttribute::GetOffset() const
{
	return Offset;
}

void RHIVertexInputAttribute::SetFormat(RHIVertexInputAttribute::Format f)
{
	Format_ = f;
}

RHIVertexInputAttribute::Format RHIVertexInputAttribute::GetFormat() const
{
	return Format_;
}