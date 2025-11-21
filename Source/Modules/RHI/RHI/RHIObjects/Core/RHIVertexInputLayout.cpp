#include "RHIObjects/Core/RHIVertexInputLayout.h"
RHIVertexInputLayout::RHIVertexInputLayout()
{

}

void RHIVertexInputLayout::SetAttributes(std::initializer_list<RHIVertexInputAttribute> list)
{
	for (auto iter = list.begin(); iter != list.end(); iter++)
		Attributes.push_back(*iter);
}

void RHIVertexInputLayout::SetBindings(std::initializer_list<RHIVertexInputBinding> list)
{
	for (auto iter = list.begin(); iter != list.end(); iter++)
		Bindings.push_back(*iter);
}