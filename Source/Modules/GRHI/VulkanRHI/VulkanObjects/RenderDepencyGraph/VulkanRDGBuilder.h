#pragma once
#include "RHI/RHIObjects/RenderDependencyGraph/RHIRDGBuilder.h"
#include "VulkanRHI/VulkanObjects/Framebuffer/VulkanFrameBuffer.h"
#include <vector>
class VulkanRDGBuilder : public RHIRDGBuilder
{
public:
    VulkanRDGBuilder();
    ~VulkanRDGBuilder();
public:
    virtual void AddPass(std::string PassName, RHIRDGBuilder::PassFlag Flag) override final;
private:
    /*
     * 每个Subpass一个Framebuffer
     */
    std::vector<VulkanFrameBuffer> Framebuffers;
};
