#include "ES32RHI/OpenGLObjects/Core/OpenGLCore.h"
#include "ES32RHI/OpenGLObjects/Resource/ES21Sampler.h"

ES21Sampler::ES21Sampler(OpenGLDevice* InDevice, RHIFilter InMinFilter, RHIFilter InMagFilter, RHIAddressMode InAddressModeU, RHIAddressMode InAddressModeV, RHIAddressMode InAddressModeW)
{

}


ES21Sampler::~ES21Sampler()
{

}

GLuint ES21Sampler::GetHandle()
{
    return Handle;
}

void ES21Sampler::BindTextureUnit(int Unit)
{

}