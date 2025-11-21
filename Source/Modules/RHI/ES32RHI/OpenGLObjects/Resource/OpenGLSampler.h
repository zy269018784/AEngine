#pragma once
#include "ES32.h"
#include "RHIObjects/Core/RHICore.h"
#include "RHIObjects/Resource/RHISampler.h"
#include "OpenGLObjects/Device/OpenGLDevice.h"
class OpenGLSampler : public RHISampler
{
public:
	OpenGLSampler() = delete;
	OpenGLSampler(OpenGLDevice* Device, RHIFilter MinFilter = RHIFilter::NEAREST,
		RHIFilter MagFilter = RHIFilter::NEAREST,
		RHIAddressMode AddressModeU = RHIAddressMode::REPEAT,
		RHIAddressMode AddressModeV = RHIAddressMode::REPEAT,
		RHIAddressMode AddressModeW = RHIAddressMode::REPEAT);
	~OpenGLSampler();
	GLuint GetHandle();
	void BindTextureUnit(int Unit);
private:
	OpenGLDevice* Device;
	GLuint Handle;
};
