#pragma once
#include <RHI/RHIObjects/Core/RHICore.h>
#include <cstdint>
#include <vector>
class RHISubPass {
public:
    RHISubPass(std::vector< std::uint32_t> InColorAttachmentIndex, std::uint32_t InDepthAttachmentIndex);
    [[nodiscard]] inline std::vector< std::uint32_t>  GetColorAttachmentIndex() const { return ColorAttachmentIndex; }
    [[nodiscard]] inline std::uint32_t GetDepthAttachmentIndex() const { return DepthAttachmentIndex; }
private:
    std::vector< std::uint32_t>  ColorAttachmentIndex;
    std::uint32_t DepthAttachmentIndex;
    RHIImageLayout Layout;
};


