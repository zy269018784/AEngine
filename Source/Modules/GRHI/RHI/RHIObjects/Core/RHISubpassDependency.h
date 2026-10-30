#pragma once
#include "RHI/RHIExport.h"
#include <cstdint>
`
class RHIEXPORT RHISubpassDependency
{
    std::uint32_t   SrcSubpass;
    std::uint32_t   DstSubpass;
    std::uint32_t   SrcStageMask;
    std::uint32_t   DstStageMask;
    std::uint32_t   SrcAccessMask;
    std::uint32_t   DstAccessMask;
    std::uint32_t   DependencyFlags;
};

class RHIEXPORT RHISubpassDependency2
{
    std::uint32_t   SrcSubpass;
    std::uint32_t   DstSubpass;
    std::uint32_t   SrcStageMask;
    std::uint32_t   DstStageMask;
    std::uint32_t   SrcAccessMask;
    std::uint32_t   DstAccessMask;
    std::uint32_t   DependencyFlags;
    std::int32_t    ViewOffset;
};

