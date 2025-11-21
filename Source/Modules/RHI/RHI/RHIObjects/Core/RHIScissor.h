#pragma once
#include <array>
#include <cstdint>
class RHIScissor
{
public:
	RHIScissor();
	RHIScissor(std::int32_t x, std::int32_t y, std::uint32_t w, std::uint32_t h);
	std::int32_t X() const;
	std::int32_t Y() const;
	std::uint32_t Width() const;
	std::uint32_t Height() const;
private:
	std::int32_t _x;
	std::int32_t _y;
	std::uint32_t _w;
	std::uint32_t _h;
};
