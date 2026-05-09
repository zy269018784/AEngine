#include "RHI/RHI.h"
#include "VulkanRHI/VulkanRHI.h"
#include "ES32RHI/ES32RHI.h"
#include "D3D9RHI/D3D9RHI.h"
#include "D3D10RHI/D3D10RHI.h"
#include "D3D11RHI/D3D11RHI.h"
#include "D3D12RHI/D3D12RHI.h"


RHI *CreateVulkanRHI()
{
    return new VulkanRHI();
}

RHI *CreateES32RHI()
{
    return new ES32RHI();
}
RHI *CreateD3D12RHI()
{
    return new D3D12RHI();
}
RHI *CreateD3D11RHI()
{return nullptr;
    //return new D3D11RHI();
}
RHI *CreateD3D10RHI()
{return nullptr;
    //return new D3D10RHI();
}
RHI *CreateD3D9RHI()
{
    return nullptr;
    //return new D3D9RHI();
}

