#pragma once

class RHIClearColor
{
public:
	RHIClearColor();
	RHIClearColor(RHIClearColor &ClearColor);
	RHIClearColor(float r, float g, float b, float a);
	float R();
	float G();
	float B();
	float A();
private:
	float _R;
	float _G;
	float _B;
	float _A;
};