#include "ES32RHI/OpenGLObjects/Core/OpenGLCore.h"
#include "ES32RHI/OpenGLObjects/Resource/ES20Sampler.h"

ES20Sampler::ES20Sampler(OpenGLDevice* InDevice, RHIFilter InMinFilter, RHIFilter InMagFilter, RHIAddressMode InAddressModeU, RHIAddressMode InAddressModeV, RHIAddressMode InAddressModeW)
: RHISampler(InMinFilter, InMagFilter, InAddressModeU, InAddressModeV, InAddressModeW) {
}


ES20Sampler::~ES20Sampler()
{

}

GLuint ES20Sampler::GetHandle()
{
    return Handle;
}

void ES20Sampler::BindTextureUnit(int Unit)
{

}