#include "RHI/RHI.h"
#include  <iostream>
#if USE_VULKAN_RHI
    #include "VulkanRHI/VulkanRHI.h"
#endif
#if USE_ES32_RHI
    #include "ES32RHI/ES32RHI.h"
#endif
#if USE_D3D9_RHI
    #include "D3D9RHI/D3D9RHI.h"
#endif
#if USE_D3D10_RHI
    #include "D3D10RHI/D3D10RHI.h"
#endif
#if USE_D3D11_RHI
    #include "D3D11RHI/D3D11RHI.h"
#endif
#if USE_D3D12_RHI
    #include "D3D12RHI/D3D12RHI.h"
#endif

RHI::RHI(GraphicsAPI Index)
    : APIIndex(Index)
{

}

RHI *CreateRHI(GraphicsAPI API) {
    RHI *pRHI = nullptr;

#if USE_VULKAN_RHI
    if (GraphicsAPI::Vulkan == API)
    {
        pRHI = new VulkanRHI(GraphicsAPI::Vulkan);
        std::cout << "new VulkanRHI" << std::endl;
    }
#endif

#if USE_ES32_RHI
    if (GraphicsAPI::ES32 == API)
    {
        pRHI = new ES32RHI(GraphicsAPI::ES20);
        std::cout << "glGetString " << glGetString(GL_VERSION) << std::endl;
    }
#endif

#if USE_D3D12_RHI
    if (GraphicsAPI::D3D12 == API)
    {
        pRHI = new D3D12RHI();
    }
#endif

#if USE_D3D11_RHI
    if (GraphicsAPI::D3D11 == API)
    {
       // pRHI = new D3D11RHI();
    }
#endif

#if USE_D3D10_RHI
    if (GraphicsAPI::D3D10 == API)
    {
        //pRHI = new D3D10RHI();
    }
#endif

#if USE_D3D9_RHI
    if (GraphicsAPI::D3D9 == API)
    {
        //pRHI = new D3D9RHI();
    }
#endif

    return pRHI;
}
