#pragma once
#include "ES32.h"
#include "RHIPixelFormat.h"

struct OpenGLPixelFormatInfo
{
	//OpenGLPixelFormatInfo() = delete;
	OpenGLPixelFormatInfo(
		RHIPixelFormat InPixelFormat,
		GLenum		   InInternalFormat,
		GLenum		   InFormat,
		GLenum		   InType) :
		PixelFormat(InPixelFormat), InternalFormat(InInternalFormat), Format(InFormat), Type(InType)
	{

	}
	RHIPixelFormat	PixelFormat;
	GLenum			InternalFormat;
	GLenum			Format;
	GLenum			Type;
};

extern OpenGLPixelFormatInfo OpenGLPixelFormats[static_cast<size_t>(RHIPixelFormat::PF_MAX_)];