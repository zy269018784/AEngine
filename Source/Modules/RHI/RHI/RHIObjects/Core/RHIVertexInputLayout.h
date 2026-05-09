#pragma once
#include "RHI/RHIObjects/Core/RHIVertexInputBinding.h"
#include "RHI/RHIObjects/Core/RHIVertexInputAttribute.h"
#include "RHI/RHIExport.h"

#include <initializer_list>
#include <vector>
class RHIEXPORT RHIVertexInputLayout
{
public:
	RHIVertexInputLayout();
	void SetAttributes(std::initializer_list<RHIVertexInputAttribute> list);
	void SetBindings(std::initializer_list<RHIVertexInputBinding> list);
public:
	std::vector<RHIVertexInputAttribute> Attributes;
	std::vector<RHIVertexInputBinding> Bindings;
};