#include <RHIObjects/RHIClearColor.h>

RHIClearColor::RHIClearColor()
{

}

RHIClearColor::RHIClearColor(RHIClearColor& ClearColor)
{
	_R = ClearColor.R();
	_G = ClearColor.G();
	_B = ClearColor.B();
	_A = ClearColor.A();
}

RHIClearColor::RHIClearColor(float r, float g, float b, float a)
	: _R(r), _G(g), _B(b), _A(a)
{
	
}

float RHIClearColor::R()
{
	return _R;
}

float RHIClearColor::G()
{
	return _G;
}

float RHIClearColor::B()
{
	return _B;
}

float RHIClearColor::A()
{
	return _A;
}
