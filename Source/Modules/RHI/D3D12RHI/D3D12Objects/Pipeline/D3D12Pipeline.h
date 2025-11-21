#pragma once
#include "D3D12_Includes.h"
#include "D3D12Objects/Device/D3D12Device.h"
class D3D12Pipeline
{
public:
	D3D12Pipeline(D3D12Device *InDevice);
	virtual ~D3D12Pipeline();
protected:
	/*
		句柄
	*/
	ID3D12PipelineState* Handle;
	/*
		设备
	*/
	D3D12Device* Device;
	/*
		根签名
	*/
	ID3D12RootSignature* RootSignature;
};