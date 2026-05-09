#pragma once
#include "RHI/RHIExport.h"
#include "RHI/RHIObjects/Shader/RHIShaderResourceBinding.h"
#include <initializer_list>
#include <vector>
class RHIEXPORT RHIShaderResourceBindings
{
public:
	RHIShaderResourceBindings();
	virtual ~RHIShaderResourceBindings();
	void SetBindings(std::initializer_list<RHIShaderResourceBinding> list);
	std::vector<RHIShaderResourceBinding>& GetBindings();
	virtual void Create() = 0;
protected:
	std::vector<RHIShaderResourceBinding> Bindings;
};