#include "ES32RHI/ES32.h"
#include "ES32RHI/OpenGLObjects/Shader/OpenGLShaderResourceBindings.h"
#include "ES32RHI/OpenGLObjects/Resource/OpenGLSampler.h"
#include "ES32RHI/OpenGLObjects/Texture/OpenGLTexture.h"
#include "ES32RHI/OpenGLObjects/Buffer/OpenGLBuffer.h"
#include <iostream>


OpenGLShaderResourceBindings::OpenGLShaderResourceBindings(OpenGLDevice* InDevice)

{

}

OpenGLShaderResourceBindings::~OpenGLShaderResourceBindings()
{

}

void OpenGLShaderResourceBindings::Create()
{
	//int MaxUBOBindings  = 0;
	//int MaxSSBOBindings = 0;
	//int MaxTextureUnits = 0;

	glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, &MaxUBOBindings);
	glGetIntegerv(GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS, &MaxSSBOBindings);
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &MaxTextureUnits);

	std::cout << "MaxUBOBindings " << MaxUBOBindings << std::endl;
	std::cout << "MaxSSBOBindings " << MaxSSBOBindings << std::endl;
	std::cout << "MaxTextureUnits " << MaxTextureUnits << std::endl;

	int ActiveTextureUnits = 0;
	for (int BindingIndex = 0; BindingIndex < Bindings.size(); BindingIndex++)
	{
		const RHIShaderResourceBinding::Type  BindingType = Bindings[BindingIndex].d.type;
		int BindingPoint = Bindings[BindingIndex].d.binding;
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
				//auto TextureHandle = ((OpenGLTexture*)Bindings[BindingIndex].d.u.stex.texSamplers->tex)->GetHandle();
				//auto SamplerHandle = ((OpenGLSampler*)Bindings[BindingIndex].d.u.stex.texSamplers->sampler)->GetHandle();

				OpenGLTexture* Texture = dynamic_cast<OpenGLTexture*>(Bindings[BindingIndex].d.u.stex.texSamplers->tex);
				OpenGLSampler* Sampler = dynamic_cast<OpenGLSampler *>(Bindings[BindingIndex].d.u.stex.texSamplers->sampler);

				CreateCombinedImageSampler(TextureUnit, Texture, Sampler);

				ActiveTextureUnits++;
			}
		}
		else if (RHIShaderResourceBinding::Type::UniformBuffer == BindingType) {
			auto Handle = ((OpenGLBuffer*)Bindings[BindingIndex].d.u.ubuf.buf)->GetHandle();

			// 绑定 Uniform Buffer 到指定的 binding point
			//glBindBufferBase(GL_UNIFORM_BUFFER, BindingPoint, Handle);

			CreateUBO(Handle, BindingPoint);
		}
		else if (RHIShaderResourceBinding::Type::StorageBuffer == BindingType) {
			auto Handle = ((OpenGLBuffer*)Bindings[BindingIndex].d.u.ubuf.buf)->GetHandle();

			// 绑定 Storage Buffer 到指定的 binding point
			//glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BindingPoint, Handle);

			CreateSSBO(Handle, BindingPoint);
		}
		else if (RHIShaderResourceBinding::Type::StorageImage == BindingType) {

			//glBindImageTexture(imageUnit, textureHandle, 0, GL_FALSE, 0, access, GL_RGBA8);
		}
	}
	std::cout << "OpenGLShaderResourceBindings ActiveTextureUnits " << ActiveTextureUnits << std::endl;
}

