#pragma once
#include "RHI/RHIObjects/Pipeline/RHIComputePipeline.h"
#include "VulkanRHI/VulkanObjects/Pipeline/VulkanPipeline.h"
class VulkanDevice;
class VulkanComputePipeline : public RHIComputePipeline, public VulkanPipeline
{
public:
    VulkanComputePipeline(VulkanDevice* InDevice = nullptr);
    ~VulkanComputePipeline();
public:
    virtual void Create() final override;
};