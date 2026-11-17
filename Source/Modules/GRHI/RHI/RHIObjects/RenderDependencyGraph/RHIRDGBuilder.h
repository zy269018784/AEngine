#pragma once

#include <string>
#include <cstdint>

class RHIRDGBuilder
{
public:
    enum class PassFlag : std::uint32_t
    {
        Graphics,
        Compute
    };
public:
    RHIRDGBuilder();
    ~RHIRDGBuilder();
public:
    void AddPass(std::string PassName, RHIRDGBuilder::PassFlag Flag);
};



