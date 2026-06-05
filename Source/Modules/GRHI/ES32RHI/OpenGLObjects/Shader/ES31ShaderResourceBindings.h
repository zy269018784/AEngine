#pragma once
#include "ES32RHI/OpenGLObjects/Shader/OpenGLShaderResourceBindings.h"
class OpenGLDevice;
class ES31ShaderResourceBindings : public OpenGLShaderResourceBindings
{
public:
	ES31ShaderResourceBindings(OpenGLDevice* Device);
	~ES31ShaderResourceBindings();
	virtual void CreateUBO(int BindingPoint,  OpenGLBuffer *Buffer) override final;
	virtual void CreateSSBO(int BindingPoint, OpenGLBuffer *Buffer) override final;
	virtual void CreateCombinedImageSampler(int TextureUnit, OpenGLTexture *Texture, OpenGLSampler *Sampler) override final;
};
