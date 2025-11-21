#pragma once
#include <cstdint>

class RHIVertexInputBinding
{
public:
	enum Classification { PerVertex, PerInstance };
public:
	RHIVertexInputBinding();
	RHIVertexInputBinding(std::uint32_t stride, RHIVertexInputBinding::Classification cls = PerVertex, std::uint32_t stepRate = 1);
	void SetClassification(RHIVertexInputBinding::Classification c);
	RHIVertexInputBinding::Classification GetClassification() const;
	void SetInstanceStepRate(std::uint32_t rate);
	std::uint32_t GetInstanceStepRate() const;
	void SetStride(std::uint32_t s);
	std::uint32_t GetStride() const;
private:
	std::uint32_t Stride;
	std::uint32_t StepRate;
	RHIVertexInputBinding::Classification Classification_;
};