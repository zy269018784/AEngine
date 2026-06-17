// Provided by VK_VERSION_1_0
typedef struct VkSubpassDescription {
    VkSubpassDescriptionFlags       flags;
    VkPipelineBindPoint             pipelineBindPoint;
    uint32_t                        inputAttachmentCount;
    const VkAttachmentReference*    pInputAttachments;
    uint32_t                        colorAttachmentCount;
    const VkAttachmentReference*    pColorAttachments;
    const VkAttachmentReference*    pResolveAttachments;
    const VkAttachmentReference*    pDepthStencilAttachment;
    uint32_t                        preserveAttachmentCount;
    const uint32_t*                 pPreserveAttachments;
} VkSubpassDescription;


// Provided by VK_VERSION_1_2
typedef struct VkSubpassDescription2 {
    VkStructureType                  sType;
    const void*                      pNext;
    VkSubpassDescriptionFlags        flags;
    /*
    * 绑定点: 图形, 计算    
    */
    VkPipelineBindPoint              pipelineBindPoint;        
    /*
    * 视图
    */
    uint32_t                         viewMask;
    /*
    * 输入附件    
    */
    uint32_t                         inputAttachmentCount;
    const VkAttachmentReference2*    pInputAttachments;
    /*
    * 颜色附件    
    */
    uint32_t                         colorAttachmentCount;
    /*
    * colorAttachmentCount个颜色附件
    */
    const VkAttachmentReference2*    pColorAttachments;
    /*
    * colorAttachmentCount个Resolve附件    
    */
    const VkAttachmentReference2*    pResolveAttachments;
    /*
    * 深度模板附件
    */
    const VkAttachmentReference2*    pDepthStencilAttachment;
    /*
    *
    */
    uint32_t                         preserveAttachmentCount;
    const uint32_t*                  pPreserveAttachments;
} VkSubpassDescription2;