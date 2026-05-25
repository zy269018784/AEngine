#include "ES32RHI/ES32.h"
#include "ES32RHI/OpenGLObjects/Shader/ES21ShaderResourceBindings.h"
#include "ES32RHI/OpenGLObjects/Resource/OpenGLSampler.h"
#include "ES32RHI/OpenGLObjects/Texture/OpenGLTexture.h"
#include "ES32RHI/OpenGLObjects/Buffer/OpenGLBuffer.h"
#include "ES32RHI/OpenGLObjects/Core/OpenGLCore.h"
#include <iostream>

ES21ShaderResourceBindings::ES21ShaderResourceBindings(OpenGLDevice* InDevice)
: OpenGLShaderResourceBindings(InDevice)
{

}

ES21ShaderResourceBindings::~ES21ShaderResourceBindings()
{

}

void ES21ShaderResourceBindings::CreateUBO(int BindingPoint, OpenGLBuffer *Buffer)
{
	GLuint Handle = Buffer->GetHandle();
	/*
	 * es 2.0 不支持glBindBufferBase
	 * GL_UNIFORM_BUFFER 要求es 3.0或以上
	 */
	//glBindBufferBase(GL_UNIFORM_BUFFER, BindingPoint, Handle);
}

void ES21ShaderResourceBindings::CreateSSBO(int BindingPoint,OpenGLBuffer *Buffer)
{
	GLuint Handle = Buffer->GetHandle();
	/*
	 * es 2.0 不支持glBindBufferBase
	 * GL_SHADER_STORAGE_BUFFER 要求es 3.1或以上
	 */
	//glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BindingPoint, Handle);
}


void ES21ShaderResourceBindings::CreateCombinedImageSampler(int TextureUnit, OpenGLTexture *Texture, OpenGLSampler *Sampler)
{
	auto TextureHandle = Texture->GetHandle();
	auto SamplerHandle = Sampler->GetHandle();
	auto AddressModeU = ToOpenGLSamplerAddressMode(Sampler->GetAddressModeU());
	auto AddressModeV = ToOpenGLSamplerAddressMode(Sampler->GetAddressModeV());
	auto AddressModeW = ToOpenGLSamplerAddressMode(Sampler->GetAddressModeW());
	auto MinFilter = ToOpenGLFilter(Sampler->GetMinFilter());
	auto MagFilter = ToOpenGLFilter(Sampler->GetMagFilter());
	/*
		不可以超过最大纹理单元
	*/
	if (TextureUnit < MaxTextureUnits)
	{
		// 要求es 2.0以上	都支持
		glActiveTexture(GL_TEXTURE0 + TextureUnit);
		glBindTexture(Texture->GetHandle(), TextureHandle);

		if (GL_TEXTURE_2D == Texture->GetHandle())
		{
			//glBindTexture(GL_TEXTURE_2D, TextureHandle);

			// 要求opengl 3.3以上, es 3.0以上
			//glBindSampler(TextureUnit, SamplerHandle);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, MinFilter);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, MagFilter);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, AddressModeU);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, AddressModeV);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, AddressModeW);
		}
	}
}