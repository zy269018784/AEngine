#include "D3D12Pipeline.h"

D3D12Pipeline::D3D12Pipeline(D3D12Device* InDevice) : Device(InDevice)
{

}

D3D12Pipeline::~D3D12Pipeline()
{
	delete Handle;
}