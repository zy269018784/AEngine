#include "ES32RHI/ES32.h"
#include "ES32RHI/OpenGLObjects/Shader/ES33ShaderResourceBindings.h"
#include "ES32RHI/OpenGLObjects/Resource/OpenGLSampler.h"
#include "ES32RHI/OpenGLObjects/Texture/OpenGLTexture.h"

#include <iostream>

ES33ShaderResourceBindings::ES33ShaderResourceBindings(OpenGLDevice* InDevice)
: OpenGLShaderResourceBindings(InDevice)
{

}

ES33ShaderResourceBindings::~ES33ShaderResourceBindings()
{

}

void ES33ShaderResourceBindings::CreateUBO(int BindingPoint, GLuint Handle)
{
	glBindBufferBase(GL_UNIFORM_BUFFER, BindingPoint, Handle);
}

void ES33ShaderResourceBindings::CreateSSBO(int BindingPoint, GLuint Handle)
{
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

#if 0
void ES33ShaderResourceBindings::Create()
{
	int MaxUBOBindings  = 0;
	int MaxSSBOBindings = 0;
	int MaxTextureUnits = 0;

	glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, &MaxUBOBindings);
	glGetIntegerv(GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS, &MaxSSBOBindings);
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &MaxTextureUnits);

	std::cout << "MaxUBOBindings " << MaxUBOBindings << std::endl;
	std::cout << "MaxSSBOBindings " << MaxSSBOBindings << std::endl;
	std::cout << "MaxTextureUnits " << MaxTextureUnits << std::endl;

	int ActiveTextureUnits = 0;
	for (int BindingIndex = 0; BindingIndex < Bindings.size(); BindingIndex++)
	{
		if (Bindings[BindingIndex].d.type == RHIShaderResourceBinding::Type::SampledImage)
		{
			/*
				暂时没实现
			*/
		}
		else if (Bindings[BindingIndex].d.type == RHIShaderResourceBinding::Type::CombinedImageSampler)
		{
			int TextureUnit = Bindings[BindingIndex].d.binding;
			/*
				不可以超过最大纹理单元
			*/
			if (TextureUnit < MaxTextureUnits)
			{
				auto TextureHandle = ((OpenGLTexture*)Bindings[BindingIndex].d.u.stex.texSamplers->tex)->GetHandle();
				auto SamplerHandle = ((OpenGLSampler*)Bindings[BindingIndex].d.u.stex.texSamplers->sampler)->GetHandle();

				// 要求opengl 4.5以上
				//glBindTextureUnit(TextureUnit, TextureHandle);

				// 要求es 2.0以上	都支持
				glActiveTexture(GL_TEXTURE0 + TextureUnit);
				glBindTexture(GL_TEXTURE_2D, TextureHandle);

				// 要求opengl 3.3以上, es 3.0以上
				glBindSampler(TextureUnit, SamplerHandle);
				ActiveTextureUnits++;
			}
		}
	}
	std::cout << "ES33ShaderResourceBindings ActiveTextureUnits " << ActiveTextureUnits << std::endl;
}
#endif
