#pragma once
#include "ES32RHI/OpenGLObjects/Shader/OpenGLShaderResourceBindings.h"
class OpenGLDevice;
class ES33ShaderResourceBindings : public OpenGLShaderResourceBindings
{
public:
	ES33ShaderResourceBindings(OpenGLDevice* Device);
	~ES33ShaderResourceBindings();
	virtual void CreateUBO(int BindingPoint, GLuint Handle) override final;
	virtual void CreateSSBO(int BindingPoint, GLuint Handle) override final;
	virtual void CreateCombinedImageSampler(int TextureUnit, OpenGLTexture *Texture, OpenGLSampler *Sampler) override final;
};
