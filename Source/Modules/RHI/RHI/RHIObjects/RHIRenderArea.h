#pragma once
#include <cstdint>
class RHIRenderArea
{
public:
	RHIRenderArea();
	RHIRenderArea(RHIRenderArea &RenderArea);
	RHIRenderArea(std::int32_t OffsetX, std::int32_t OffsetY, std::uint32_t Width, std::uint32_t Height);
	std::int32_t  OffsetX();
	std::int32_t  OffsetY();
	std::uint32_t Width();
	std::uint32_t Height();
private:
	std::int32_t  _OffsetX;
	std::int32_t  _OffsetY;
	std::uint32_t _Width;
	std::uint32_t _Height;
};