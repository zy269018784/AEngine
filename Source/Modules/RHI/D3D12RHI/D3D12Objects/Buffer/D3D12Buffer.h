#pragma once
#include "RHIObjects/Resource/RHIBuffer.h"
#include "D3D12Objects/Device/D3D12Device.h"
#include "D3D12_Includes.h"

class D3D12Buffer : public RHIBuffer
{
public:
	D3D12Buffer();
	D3D12Buffer(D3D12Device* InDevice, RHIBuffer::RHIBufferType InType, RHIBuffer::RHIBufferUsageFlag InUsage, std::uint32_t InSize, const void* InData);
	~D3D12Buffer();
	ID3D12Resource *GetHandle() const;
private:
	ID3D12Resource *Handle = nullptr;
	D3D12Device* Device = nullptr;
};