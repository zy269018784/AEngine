#include "RHIObjects/Shader/RHIShaderResourceBindings.h"
#include <iostream>
RHIShaderResourceBindings::RHIShaderResourceBindings()
{
	Bindings.reserve(0);
	Bindings.resize(0);
}

RHIShaderResourceBindings::~RHIShaderResourceBindings()
{

}

void RHIShaderResourceBindings::SetBindings(std::initializer_list<RHIShaderResourceBinding> list)
{
	Bindings = list;
}

std::vector<RHIShaderResourceBinding>& RHIShaderResourceBindings::GetBindings()
{
	return Bindings;
}