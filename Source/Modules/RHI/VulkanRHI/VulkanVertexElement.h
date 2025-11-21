#pragma once
#include "Vulkan.h"
//#include <RHIVertexElement.h>
#include <vector>
#include <cstdint>
#if 0
struct VulkanVertexElement
{
	std::uint32_t		AttributeIndex;					// attribute index
	std::uint32_t		StreamIndex;					// bing index
	std::uint32_t		Type;							// type
	std::uint32_t		Offset;							// offset
	std::uint32_t		Size;							// size
	std::uint32_t		Divisor;						// divisor
	bool	ShouldConvertToFloat;
	std::uint8_t		Normalized;

	VulkanVertexElement()
	{
	}

	VulkanVertexElement(const VulkanVertexElement& elem)
	{
		AttributeIndex = elem.AttributeIndex;
		StreamIndex = elem.StreamIndex;
		Type = elem.Type;
		Offset = elem.Offset;
		Size = elem.Size;
		Divisor = elem.Divisor;
		ShouldConvertToFloat = elem.ShouldConvertToFloat;
		Normalized = elem.Normalized;
	}

	VulkanVertexElement& operator =(const VulkanVertexElement& elem)
	{
		AttributeIndex = elem.AttributeIndex;
		StreamIndex = elem.StreamIndex;
		Type = elem.Type;
		Offset = elem.Offset;
		Size = elem.Size;
		Divisor = elem.Divisor;
		ShouldConvertToFloat = elem.ShouldConvertToFloat;
		Normalized = elem.Normalized;
	}
};

enum
{
	MaxVertexElementCount = 17,
};
typedef std::vector<RHIVertexElement> VulkanVertexElements;

#endif