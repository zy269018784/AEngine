#include <RHI/RHIObjects/RenderPass/RHISubPass.h>



RHISubPass::RHISubPass(std::vector< std::uint32_t> InColorAttachmentIndex, std::uint32_t InDepthAttachmentIndex)
    : ColorAttachmentIndex(InColorAttachmentIndex), DepthAttachmentIndex(InDepthAttachmentIndex)
{

}