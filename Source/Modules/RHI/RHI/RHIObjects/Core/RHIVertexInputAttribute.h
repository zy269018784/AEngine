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
	RHIVertexInputAttribute(int binding, int location, RHIVertexInputAttribute::Format format, std::uint32_t offset, int matrixSlice = -1);
	void SetBinding(int b);
	int GetBinding() const;
	void SetLocation(int loc);
	int GetLocation() const;	
	void SetOffset(std::uint32_t ofs);
	std::uint32_t GetOffset() const;
	void SetFormat(RHIVertexInputAttribute::Format f);
	RHIVertexInputAttribute::Format GetFormat() const;
	//void SetMatrixSlice(int slice);
	//int GetMatrixSlice() const;
private:
	int Binding;
	int Location;
	std::uint32_t Offset;
	RHIVertexInputAttribute::Format Format_;
};