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
	glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, &MaxUBOBindings);
	glGetIntegerv(GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS, &MaxSSBOBindings);
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &MaxTextureUnits);

	std::cout << "MaxUBOBindings " << MaxUBOBindings << std::endl;
	std::cout << "MaxSSBOBindings " << MaxSSBOBindings << std::endl;
	std::cout << "MaxTextureUnits " << MaxTextureUnits << std::endl;

	int ActiveTextureUnits = 0;
	for (int BindingIndex = 0; BindingIndex < Bindings.size(); BindingIndex++)
	{
		std::cout << "BindingIndex " << BindingIndex << std::endl;
		const RHIShaderResourceBinding::Type  BindingType = Bindings[BindingIndex].d.type;
		std::cout << "debug 1" << std::endl;
		int BindingPoint = Bindings[BindingIndex].d.binding;
		std::cout << "debug 2" << std::endl;
		if (Bindings[BindingIndex].d.type == RHIShaderResourceBinding::Type::SampledImage)
		{
			/*
				暂时没实现
			*/
		}
		else if (Bindings[BindingIndex].d.type == RHIShaderResourceBinding::Type::CombinedImageSampler)
		{
			std::cout << "debug 3" << std::endl;
			int TextureUnit = Bindings[BindingIndex].d.binding;
			std::cout << "debug 4" << std::endl;
			OpenGLTexture* Texture = dynamic_cast<OpenGLTexture*>(Bindings[BindingIndex].d.u.stex.texSamplers->tex);
			std::cout << "debug 5" << std::endl;
			OpenGLSampler* Sampler = dynamic_cast<OpenGLSampler *>(Bindings[BindingIndex].d.u.stex.texSamplers->sampler);
			std::cout << "debug 6" << std::endl;

			std::cout << "CreateCombinedImageSampler start" << std::endl;
			CreateCombinedImageSampler(TextureUnit, Texture, Sampler);
			std::cout << "CreateCombinedImageSampler end" << std::endl;

			ActiveTextureUnits++;
		}
		else if (RHIShaderResourceBinding::Type::UniformBuffer == BindingType) {
			OpenGLBuffer *Buffer = (OpenGLBuffer*)Bindings[BindingIndex].d.u.ubuf.buf;
			CreateUBO(BindingPoint, Buffer);
		}
		else if (RHIShaderResourceBinding::Type::StorageBuffer == BindingType) {
			OpenGLBuffer *Buffer = (OpenGLBuffer*)Bindings[BindingIndex].d.u.ubuf.buf;
			CreateSSBO(BindingPoint, Buffer);
		}
		else if (RHIShaderResourceBinding::Type::StorageImage == BindingType) {

			//glBindImageTexture(imageUnit, textureHandle, 0, GL_FALSE, 0, access, GL_RGBA8);
		}
	}
	std::cout << "OpenGLShaderResourceBindings ActiveTextureUnits " << ActiveTextureUnits << std::endl;
}

