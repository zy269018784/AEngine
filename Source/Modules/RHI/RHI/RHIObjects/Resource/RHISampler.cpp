#include "RHI/RHIObjects/Resource/RHISampler.h"

RHISampler::RHISampler(RHIFilter InMinFilter,
                       RHIFilter InMagFilter,
                       RHIAddressMode InAddressModeU,
                       RHIAddressMode InAddressModeV,
                       RHIAddressMode InAddressModeW)
        :   MinFilter(InMinFilter),
            MagFilter(InMagFilter),
            AddressModeU(InAddressModeU),
            AddressModeV(InAddressModeV),
            AddressModeW(InAddressModeW)

{

}

RHISampler::~RHISampler() {

}

RHIFilter RHISampler::GetMinFilter() const {
    return MinFilter;
}

RHIFilter RHISampler::GetMagFilter() const {
    return MagFilter;
}

RHIAddressMode RHISampler::GetAddressModeU() const {
    return AddressModeU;
}

RHIAddressMode RHISampler::GetAddressModeV() const {
    return AddressModeV;
}

RHIAddressMode RHISampler::GetAddressModeW() const {
    return AddressModeW;
}

