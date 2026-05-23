#pragma once
#include "ES32RHI/ES32.h"
#include "RHI/RHIObjects/Core/RHICore.h"
#include "RHI/RHIObjects/Resource/RHISampler.h"
#include "ES32RHI/OpenGLObjects/Device/OpenGLDevice.h"
class OpenGLSampler : public RHISampler
{
public:
	OpenGLSampler() = delete;
	OpenGLSampler(OpenGLDevice* Device, RHIFilter MinFilter = RHIFilter::NEAREST,
		RHIFilter MagFilter = RHIFilter::NEAREST,
		RHIAddressMode AddressModeU = RHIAddressMode::REPEAT,
		RHIAddressMode AddressModeV = RHIAddressMode::REPEAT,
		RHIAddressMode AddressModeW = RHIAddressMode::REPEAT);
	virtual ~OpenGLSampler();
	GLuint GetHandle();
	virtual void BindTextureUnit(int Unit) = 0;
protected:
	OpenGLDevice* Device;
	GLuint Handle;
};
