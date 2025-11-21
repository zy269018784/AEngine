#pragma once
#include <ES32.h>
#include "RHIObjects/Resource/RHIBuffer.h"
#include <cstdint>

class OpenGLBuffer : public RHIBuffer
{
public:
	OpenGLBuffer();
	OpenGLBuffer(RHIBuffer::RHIBufferType InType, RHIBuffer::RHIBufferUsageFlag InUsage, std::uint32_t InSize, const void* InData);
	~OpenGLBuffer();
	void Bind();
	bool IsDynamic() const;
	GLenum GetAccess() const;
public:
	GLuint Handle;			// Buffer Object
	GLenum Type;				// Target
	bool bStreamDraw;
};