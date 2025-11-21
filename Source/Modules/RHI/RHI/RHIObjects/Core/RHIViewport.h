#pragma once
#include <array>
#include <cstdint>
class RHIViewport
{
public:
	RHIViewport();
	RHIViewport(float x, float y, float w, float h, float minDepth = 0.0f, float maxDepth = 1.0f);
	float MaxDepth() const;
	float MinDepth() const;
	void SetMaxDepth(float maxDepth);
	void SetMinDepth(float minDepth);
	void SetViewport(float x, float y, float w, float h);
	std::array<float, 4> Viewport() const;
	std::int32_t X() const;
	std::int32_t Y() const;
	std::uint32_t Width() const;
	std::uint32_t Height() const;
private:
	float _x;
	float _y;
	float _w;
	float _h;
	float _minDepth;
	float _maxDepth;
};
