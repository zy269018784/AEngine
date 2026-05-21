#include "ES32RHI/ES32.h"
#include "ES32RHI/OpenGLObjects/Shader/ES21ShaderResourceBindings.h"
#include "ES32RHI/OpenGLObjects/Resource/OpenGLSampler.h"
#include "ES32RHI/OpenGLObjects/Texture/OpenGLTexture.h"
#include "ES32RHI/OpenGLObjects/Core/OpenGLCore.h"
#include <iostream>

ES21ShaderResourceBindings::ES21ShaderResourceBindings(OpenGLDevice* InDevice)

{

}

ES21ShaderResourceBindings::~ES21ShaderResourceBindings()
{

}

void ES21ShaderResourceBindings::Create()
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

				OpenGLSampler *Sampler = dynamic_cast<OpenGLSampler *>(Bindings[BindingIndex].d.u.stex.texSamplers->sampler);
				std::cout << "aaaa" << std::endl;
				auto SamplerHandle = Sampler->GetHandle();
			//	auto SamplerHandle = ((OpenGLSampler*)Bindings[BindingIndex].d.u.stex.texSamplers->sampler)->GetHandle();

				// 要求opengl 4.5以上
				//glBindTextureUnit(TextureUnit, TextureHandle);

				// 要求es 2.0以上	都支持
				glActiveTexture(GL_TEXTURE0 + TextureUnit);
				glBindTexture(GL_TEXTURE_2D, TextureHandle);

				// 要求opengl 3.3以上, es 3.0以上
			//	glBindSampler(TextureUnit, SamplerHandle);
#if 1
				std::cout << "test ES21ShaderResourceBindings !!!!!!!!!" << std::endl;
				auto AddressModeU = ToOpenGLSamplerAddressMode(Sampler->GetAddressModeU());
				auto AddressModeV = ToOpenGLSamplerAddressMode(Sampler->GetAddressModeV());
				auto AddressModeW = ToOpenGLSamplerAddressMode(Sampler->GetAddressModeW());
				auto MinFilter = ToOpenGLFilter(Sampler->GetMinFilter());
				auto MagFilter = ToOpenGLFilter(Sampler->GetMagFilter());

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, MinFilter);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, MagFilter);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, AddressModeU);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, AddressModeV);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, AddressModeW);
#endif
				ActiveTextureUnits++;
			}
		}
	}
	std::cout << "ES21ShaderResourceBindings ActiveTextureUnits " << ActiveTextureUnits << std::endl;
}

