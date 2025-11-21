#include "RHIObjects/Core/RHIScissor.h"

RHIScissor::RHIScissor()
{

}

RHIScissor::RHIScissor(std::int32_t x, std::int32_t y, std::uint32_t w, std::uint32_t h)
{
	_x = x;
	_y = y;
	_w = w;
	_h = h;
}

std::int32_t RHIScissor::X() const
{
	return _x;
}

std::int32_t RHIScissor::Y() const
{
	return _y;
}

std::uint32_t RHIScissor::Width() const
{
	return _w;
}

std::uint32_t RHIScissor::Height() const
{
	return _h;
}