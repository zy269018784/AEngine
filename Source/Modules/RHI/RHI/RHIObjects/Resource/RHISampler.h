#pragma once
#include "RHI/RHIExport.h"
#include "RHI/RHIObjects/Core/RHICore.h"
class RHIEXPORT RHISampler
{
public:
	RHISampler(RHIFilter InMinFilter, RHIFilter InMagFilter, RHIAddressMode InAddressModeU, RHIAddressMode InAddressModeV, RHIAddressMode InAddressModeW);
	virtual ~RHISampler();
	RHIFilter GetMinFilter() const;
	RHIFilter GetMagFilter() const;
	RHIAddressMode GetAddressModeU() const;
	RHIAddressMode GetAddressModeV() const;
	RHIAddressMode GetAddressModeW() const;
protected:
	RHIFilter MinFilter;
	RHIFilter MagFilter;
	RHIAddressMode AddressModeU;
	RHIAddressMode AddressModeV;
	RHIAddressMode AddressModeW;
};