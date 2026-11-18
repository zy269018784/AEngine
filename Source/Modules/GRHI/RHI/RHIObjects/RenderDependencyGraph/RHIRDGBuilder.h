#pragma once

#include <string>
#include <cstdint>

class RHIRDGBuilder
{
public:
    enum class PassFlag : std::uint32_t
    {
        Graphics,
        Compute,
        Swapchain
    };
public:
    RHIRDGBuilder();
    virtual ~RHIRDGBuilder();
public:
    virtual void AddPass(std::string PassName, RHIRDGBuilder::PassFlag Flag) = 0;
};



