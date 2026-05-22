#pragma once
#include "ES32RHI/OpenGLObjects/Shader/OpenGLShaderResourceBindings.h"
class OpenGLDevice;
class ES21ShaderResourceBindings : public OpenGLShaderResourceBindings
{
public:
	ES21ShaderResourceBindings(OpenGLDevice* Device);
	~ES21ShaderResourceBindings();
	virtual void CreateUBO(int BindingPoint, GLuint Handle) override final;
	virtual void CreateSSBO(int BindingPoint, GLuint Handle) override final;
	virtual void CreateCombinedImageSampler(int TextureUnit, OpenGLTexture *Texture, OpenGLSampler *Sampler) override final;
};
