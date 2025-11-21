#include "ES32.h"
#include "OpenGLObjects/Shader/OpenGLShaderResourceBindings.h"
#include "OpenGLObjects/Resource/OpenGLSampler.h"
#include "OpenGLObjects/Texture/OpenGLTexture.h"

#include <iostream>

OpenGLShaderResourceBindings::OpenGLShaderResourceBindings(OpenGLDevice* InDevice)

{

}

OpenGLShaderResourceBindings::~OpenGLShaderResourceBindings()
{

}

void OpenGLShaderResourceBindings::Create()
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
#define OpenGL
#ifdef OpenGL
				glBindTextureUnit(TextureUnit, TextureHandle);
#else
				glActiveTexture(GL_TEXTURE0 + TextureUnit);
				glBindTexture(GL_TEXTURE_2D, TextureHandle);
#endif
				glBindSampler(TextureUnit, SamplerHandle);
				ActiveTextureUnits++;
			}
		}
	}
	std::cout << "OpenGLShaderResourceBindings ActiveTextureUnits " << ActiveTextureUnits << std::endl;
}

