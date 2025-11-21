#include "RHIObjects/Core/RHIViewport.h"
RHIViewport::RHIViewport()
{

}

RHIViewport::RHIViewport(float x, float y, float w, float h, float minDepth, float maxDepth)
{
	_x = x;
	_y = y;
	_w = w;
	_h = h;
	_minDepth = minDepth;
	_maxDepth = maxDepth;
}

float RHIViewport::MaxDepth() const
{
	return _maxDepth;
}

float RHIViewport::MinDepth() const
{
	return _minDepth;
}

void RHIViewport::SetMaxDepth(float maxDepth)
{
	_maxDepth = maxDepth;
}

void RHIViewport::SetMinDepth(float minDepth)
{
	_minDepth = minDepth;
}

void RHIViewport::SetViewport(float x, float y, float w, float h)
{
	_x = x;
	_y = y;
	_w = w;
	_h = h;
}

std::array<float, 4> RHIViewport::Viewport() const
{
	return {_x, _y, _w, _h};
}


std::int32_t RHIViewport::X() const
{
	return _x;
}

std::int32_t RHIViewport::Y() const
{
	return _y;
}

std::uint32_t RHIViewport::Width() const
{
	return _w;
}

std::uint32_t RHIViewport::Height() const
{
	return _h;
}
