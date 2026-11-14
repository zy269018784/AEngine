#pragma once
#include "RHI/RHIExport.h"
#include "RHI/RHIObjects/Core/RHICore.h"
#include <cstdint>
class RHIEXPORT RHISubpassDependency
{
public:
    std::uint32_t           SrcSubpass;
    std::uint32_t           DstSubpass;
    RHIPipelineStageFlags   SrcStageMask;
    RHIPipelineStageFlags   DstStageMask;
    RHIAccessFlagBits       SrcAccessMask;
    RHIAccessFlagBits       DstAccessMask;
    RHIDependencyFlags      DependencyFlags;
};

class RHIEXPORT RHISubpassDependency2
{
public:
    std::uint32_t           SrcSubpass;
    std::uint32_t           DstSubpass;
    RHIPipelineStageFlags   SrcStageMask;
    RHIPipelineStageFlags   DstStageMask;
    RHIAccessFlagBits       SrcAccessMask;
    RHIAccessFlagBits       DstAccessMask;
    RHIDependencyFlags      DependencyFlags;
    std::int32_t            ViewOffset;
};

