#pragma once
#include "ES32RHI/OpenGLObjects/Shader/OpenGLShaderResourceBindings.h"
class OpenGLDevice;
class ES32ShaderResourceBindings : public OpenGLShaderResourceBindings
{
public:
	ES32ShaderResourceBindings(OpenGLDevice* Device);
	~ES32ShaderResourceBindings();
	virtual void CreateUBO(int BindingPoint, GLuint Handle) override final;
	virtual void CreateSSBO(int BindingPoint, GLuint Handle) override final;
	virtual void CreateCombinedImageSampler(int TextureUnit, OpenGLTexture *Texture, OpenGLSampler *Sampler) override final;
};
