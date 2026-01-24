#pragma once
#include <cstdint>
class RHIVertexInputAttribute
{
public:
	enum Format
	{
		Float4,
		Float3,
		Float2,
		Float,
		UNormByte4,
		UNormByte2,
		UNormByte,
		UInt4,
		UInt3,
		UInt2,
		UInt,
		SInt4,
		SInt3,
		SInt2,
		SInt,
		Half4,
		Half3,
		Half2,
		Half
	};
public:
	RHIVertexInputAttribute();
	RHIVertexInputAttribute(const char *name, int binding, int location, RHIVertexInputAttribute::Format format, std::uint32_t offset, int matrixSlice = -1);
	void SetName(const char *b);
	const char * GetName() const;
	void SetBinding(int b);
	int GetBinding() const;
	void SetLocation(int loc);
	int GetLocation() const;	
	void SetOffset(std::uint32_t ofs);
	std::uint32_t GetOffset() const;
	void SetFormat(RHIVertexInputAttribute::Format f);
	RHIVertexInputAttribute::Format GetFormat() const;

private:
	const char *Name;
	int Binding;
	int Location;
	std::uint32_t Offset;
	RHIVertexInputAttribute::Format Format_;
};