#include <RHIObjects/RHIRenderArea.h>

RHIRenderArea::RHIRenderArea()
{

}

RHIRenderArea::RHIRenderArea(RHIRenderArea& RenderArea)
{
	_OffsetX	= RenderArea.OffsetX();
	_OffsetY	= RenderArea.OffsetY();
	_Width		= RenderArea.Width();
	_Height		= RenderArea.Height();
}

RHIRenderArea::RHIRenderArea(std::int32_t OffsetX, std::int32_t OffsetY, std::uint32_t Width, std::uint32_t Height)
	: _OffsetX(OffsetX), _OffsetY(OffsetY), _Width(Width), _Height(Height)
{

}

std::int32_t  RHIRenderArea::OffsetX()
{
	return _OffsetX;
}

std::int32_t  RHIRenderArea::OffsetY()
{
	return _OffsetY;
}

std::uint32_t RHIRenderArea::Width()
{
	return _Width;
}

std::uint32_t RHIRenderArea::Height()
{
	return _Height;
}