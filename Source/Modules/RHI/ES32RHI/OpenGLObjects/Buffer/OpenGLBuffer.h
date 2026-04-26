#pragma once
#include <ES32.h>
#include "RHIObjects/Resource/RHIBuffer.h"

class OpenGLBuffer : public RHIBuffer
{
public:
	OpenGLBuffer();
	OpenGLBuffer(RHIBufferType InType, RHIBufferUsageFlag InUsage, std::uint32_t InSize, const void* InData);
	~OpenGLBuffer();
	void Bind();
	bool IsDynamic() const;
	GLenum GetAccess() const;
	GLuint GetHandle() const;
	virtual void Update(std::uint32_t InSize, const void* InData) final override;
private:
	GLuint Handle;			
	bool bStreamDraw;
	GLenum Target = 0;
};