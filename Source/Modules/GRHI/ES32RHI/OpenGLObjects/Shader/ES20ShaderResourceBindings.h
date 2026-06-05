#pragma once
#include "ES32RHI/OpenGLObjects/Shader/OpenGLShaderResourceBindings.h"
class OpenGLDevice;
class ES20ShaderResourceBindings : public OpenGLShaderResourceBindings
{
public:
	ES20ShaderResourceBindings(OpenGLDevice* Device);
	~ES20ShaderResourceBindings();
	virtual void CreateUBO(int BindingPoint,  OpenGLBuffer *Buffer) override final;
	virtual void CreateSSBO(int BindingPoint, OpenGLBuffer *Buffer) override final;
	virtual void CreateCombinedImageSampler(int TextureUnit, OpenGLTexture *Texture, OpenGLSampler *Sampler) override final;
};
