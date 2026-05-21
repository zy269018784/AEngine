#include "ES32RHI/OpenGLObjects/Resource/OpenGL33Sampler.h"
#include "ES32RHI/OpenGLObjects/Core/OpenGLCore.h"

OpenGL33Sampler::OpenGL33Sampler(OpenGLDevice* InDevice, RHIFilter InMinFilter, RHIFilter InMagFilter, RHIAddressMode InAddressModeU, RHIAddressMode InAddressModeV, RHIAddressMode InAddressModeW)
: RHISampler(InMinFilter, InMagFilter, InAddressModeU, InAddressModeV, InAddressModeW)
{
    glGenSamplers(1, &Handle);

    auto AddressModeU = ToOpenGLSamplerAddressMode(InAddressModeU);
    auto AddressModeV = ToOpenGLSamplerAddressMode(InAddressModeV);
    auto AddressModeW = ToOpenGLSamplerAddressMode(InAddressModeW);
    auto MinFilter = ToOpenGLFilter(InMinFilter);
    auto MagFilter = ToOpenGLFilter(InMagFilter);

    //glBindSampler(0, Handle);
    glSamplerParameteri(Handle, GL_TEXTURE_MIN_FILTER, MinFilter);
    glSamplerParameteri(Handle, GL_TEXTURE_MAG_FILTER, MagFilter);
    glSamplerParameteri(Handle, GL_TEXTURE_WRAP_S, AddressModeU);
    glSamplerParameteri(Handle, GL_TEXTURE_WRAP_T, AddressModeV);
    glSamplerParameteri(Handle, GL_TEXTURE_WRAP_R, AddressModeW);
    //glSamplerParameterf(Handle, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
}


OpenGL33Sampler::~OpenGL33Sampler()
{
    glDeleteSamplers(1, &Handle);
}

GLuint OpenGL33Sampler::GetHandle()
{
    return Handle;
}

void OpenGL33Sampler::BindTextureUnit(int Unit)
{
    glBindSampler(Unit, Handle);
}