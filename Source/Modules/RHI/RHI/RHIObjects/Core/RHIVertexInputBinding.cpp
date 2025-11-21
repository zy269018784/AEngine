#include "RHIObjects/Core/RHIVertexInputBinding.h"

RHIVertexInputBinding::RHIVertexInputBinding()
{

}

RHIVertexInputBinding::RHIVertexInputBinding(std::uint32_t stride, RHIVertexInputBinding::Classification cls, std::uint32_t stepRate)
	: Stride(stride), Classification_(cls), StepRate(stepRate)
{

}

void RHIVertexInputBinding::SetClassification(RHIVertexInputBinding::Classification c)
{
	Classification_ = c;
}

RHIVertexInputBinding::Classification RHIVertexInputBinding::GetClassification() const
{
	return Classification_;
}

void RHIVertexInputBinding::SetInstanceStepRate(std::uint32_t rate)
{
	StepRate = rate;
}

std::uint32_t RHIVertexInputBinding::GetInstanceStepRate() const
{
	return StepRate;
}

void RHIVertexInputBinding::SetStride(std::uint32_t s)
{
	Stride = s;
}

std::uint32_t RHIVertexInputBinding::GetStride() const
{
	return Stride;
}
