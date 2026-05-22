#include "ES32RHI/ES32.h"
#include "ES32RHI/OpenGLObjects/Shader/ES33ShaderResourceBindings.h"
#include "ES32RHI/OpenGLObjects/Resource/OpenGLSampler.h"
#include "ES32RHI/OpenGLObjects/Texture/OpenGLTexture.h"
#include "ES32RHI/OpenGLObjects/Buffer/OpenGLBuffer.h"

#include <iostream>

ES33ShaderResourceBindings::ES33ShaderResourceBindings(OpenGLDevice* InDevice)
: OpenGLShaderResourceBindings(InDevice)
{

}

ES33ShaderResourceBindings::~ES33ShaderResourceBindings()
{

}

void ES33ShaderResourceBindings::CreateUBO(int BindingPoint, OpenGLBuffer *Buffer)
{
	GLuint Handle = Buffer->GetHandle();
	glBindBufferBase(GL_UNIFORM_BUFFER, BindingPoint, Handle);
}

void ES33ShaderResourceBindings::CreateSSBO(int BindingPoint,OpenGLBuffer *Buffer)
{
	GLuint Handle = Buffer->GetHandle();
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BindingPoint, Handle);
}


void ES33ShaderResourceBindings::CreateCombinedImageSampler(int TextureUnit, OpenGLTexture *Texture, OpenGLSampler *Sampler)
{
	auto TextureHandle = Texture->GetHandle();
	auto SamplerHandle = Sampler->GetHandle();
	/*
		不可以超过最大纹理单元
	*/
	if (TextureUnit < MaxTextureUnits)
	{
		// 要求es 2.0以上	都支持
		glActiveTexture(GL_TEXTURE0 + TextureUnit);
		glBindTexture(GL_TEXTURE_2D, TextureHandle);

		// 要求opengl 3.3以上, es 3.0以上
		glBindSampler(TextureUnit, SamplerHandle);
	}
}
