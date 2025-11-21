#pragma once
#include "RHIObjects/Pipeline/RHIGraphicsPipeline.h"
#include "D3D12Objects/Pipeline/D3D12Pipeline.h"
#include "D3D12Objects/Device/D3D12Device.h"
class D3D12GraphicsPipeline : public RHIGraphicsPipeline, public D3D12Pipeline
{
public:
	D3D12GraphicsPipeline(D3D12Device *InDevice);
	~D3D12GraphicsPipeline();
public:
	virtual void Create() final override;
};