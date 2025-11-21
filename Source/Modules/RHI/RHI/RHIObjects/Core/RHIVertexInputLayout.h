#pragma once
#include "RHIObjects/Core/RHIVertexInputBinding.h"
#include "RHIObjects/Core/RHIVertexInputAttribute.h"
#include <initializer_list>
#include <vector>
class RHIVertexInputLayout
{
public:
	RHIVertexInputLayout();
	void SetAttributes(std::initializer_list<RHIVertexInputAttribute> list);
	void SetBindings(std::initializer_list<RHIVertexInputBinding> list);
public:
	std::vector<RHIVertexInputAttribute> Attributes;
	std::vector<RHIVertexInputBinding> Bindings;
};