#include "D3D12Pipeline.h"

D3D12Pipeline::D3D12Pipeline(D3D12Device* InDevice) : Device(InDevice)
{

}

D3D12Pipeline::~D3D12Pipeline()
{
	delete Handle;
}

ID3D12PipelineState *D3D12Pipeline::GetHandle() {
	return Handle;
}