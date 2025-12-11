#include "VulkanObjects/Resource/VulkanImage.h"
#include "VulkanObjects/Core/VulkanCore.h"
#include "VulkanObjects/Core/VulkanCore.h"
#include <iostream>
#include <cstring>
VulkanImage::VulkanImage(VulkanDevice* InDevice, RHITextureType InType, RHIPixelFormat InPixelFormat,
	std::uint32_t InSizeX, std::uint32_t InSizeY, std::uint32_t InSizeZ, std::uint32_t InArraySize, std::uint32_t InNumMips, std::uint32_t InSampleCount, const void* InData)
	: Device(InDevice), Type(InType), ArraySize(InArraySize)
{
    DeviceMemory = new VulkanDeviceMemory(InDevice);
    VkImageViewType InResourceType = ToVulkanImageViewType(InType);
    std::cout << "VulkanImage InPixelFormat " << (int)InPixelFormat << " "
              << "VulkanImage ToVkFormat(InPixelFormat) " << ToVkFormat(InPixelFormat) << " "
              << "InArraySize " << InArraySize << " "
              << std::endl;
	VkImageCreateInfo CreateInfo{};
    CreateInfo.sType            = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    CreateInfo.flags            = ImageViewTypeToImageCreateFlagBits(InResourceType);
    CreateInfo.imageType        = ImageViewTypeToImageType(InResourceType);
    CreateInfo.extent           = { InSizeX, InSizeY, InSizeZ };
    CreateInfo.format           = ToVkFormat(InPixelFormat);
    CreateInfo.mipLevels        = InNumMips;
    CreateInfo.arrayLayers      = InArraySize;
    CreateInfo.samples          = ToSampleCountFlagBits(InSampleCount);
    CreateInfo.tiling           = VK_IMAGE_TILING_OPTIMAL;
    CreateInfo.usage            = VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;// usage; todo... 
    CreateInfo.sharingMode      = VK_SHARING_MODE_EXCLUSIVE;
    /*
        texture array报错
    */
    CreateInfo.initialLayout    = VK_IMAGE_LAYOUT_UNDEFINED;
    //CreateInfo.initialLayout    = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

    VkResult Result = CreateImage(&CreateInfo, nullptr);
    if (VK_SUCCESS != Result)
    {
        throw std::runtime_error("Failed to create texture image!");
    }
    std::cout << "Handle: " << Handle << " Device " << Device << std::endl;
    GetImageMemoryRequirements(&MemoryRequirements);
    std::cout << "MemoryRequirements.size: " <<   MemoryRequirements.size << std::endl;
    VkMemoryAllocateInfo AllocateInfo = {
        VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        nullptr,
        MemoryRequirements.size,
        //Device->pPhysicalDevice->HostVisibleIndex
        1
        //Device->GetPhysicalDevice()->HostVisibleIndex // why crash
    };

    std::cout << "Device->GetPhysicalDevice()->HostVisibleIndex: " << Device->GetPhysicalDevice()->HostVisibleIndex << std::endl;

    std::cout << "InPixelFormat: " <<   (int)InPixelFormat  << std::endl;
    std::cout << "InSizeX: " <<   InSizeX << " " << InSizeY << " " << InSizeZ<< std::endl;

    Result = DeviceMemory->AllocateMemory(&AllocateInfo, nullptr);
    if (VK_SUCCESS != Result)
        std::cout << "AllocateMemory failed : " << Result << std::endl;

    Result = BindImageMemory(DeviceMemory->GetHandle(), 0);
    if (VK_SUCCESS != Result)
        std::cout << "BindBufferMemory failed : " << Result << std::endl;

    if (InData)
    {
        std::uint8_t* p;
        Result = DeviceMemory->MapMemory(0, MemoryRequirements.size, 0, reinterpret_cast<void**>(&p));
        if (VK_SUCCESS != Result)
            std::cout << "MapMemory failed : " << Result << std::endl;

        auto InSize = InSizeX * InSizeY * InSizeZ * PixelFormatToSize(InPixelFormat);
        std::memcpy(p, InData, InSize);
        DeviceMemory->UnmapMemory();
    }


    std::cout << "CreateImage ok " << Handle << std::endl;
}

VulkanImage::VulkanImage(VulkanDevice* InDevice, VkImage InHandle)
    : Device(InDevice), Handle(InHandle)
{

}

VulkanImage::~VulkanImage()
{
    std::cout << "VulkanImage::~VulkanImage() " << Handle << std::endl;
    Device->FreeMemory(StagingBufferMemory, nullptr);
    Device->DestroyBuffer(StagingBuffer, nullptr);
    DestroyImage(nullptr);

    delete DeviceMemory;
}

VkImage VulkanImage::GetHandle()
{
    return Handle;
}

void CreateBuffer1(VulkanDevice* Device, VkDeviceSize Size, VkBufferUsageFlags Usage, VkMemoryPropertyFlags Properties, VkBuffer& Buffer, VkDeviceMemory& BufferMemory)
{
    VkResult Result = VK_SUCCESS;

    VkBufferCreateInfo CreateInfo{};
    CreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    CreateInfo.size = Size;
    CreateInfo.usage = Usage;
    CreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    Result = Device->CreateBuffer(&CreateInfo, nullptr, &Buffer);
    if (VK_SUCCESS != Result)
    {
        throw std::runtime_error("failed to create buffer!");
    }

    VkMemoryRequirements MemoryRequirements;
    Device->GetBufferMemoryRequirements(Buffer, &MemoryRequirements);

    std::cout
        << "memRequirements.size " << MemoryRequirements.size << " "
        << "memRequirements.memoryTypeBits " << MemoryRequirements.memoryTypeBits << " "
        << "Buffer " << Buffer << " "
        << std::endl;

    std::uint32_t MemoryTypeIndex = Device->GetPhysicalDevice()->FindMemoryType(MemoryRequirements.memoryTypeBits, Properties);
    std::cout << "Requeired Memory Type Index " << MemoryTypeIndex << std::endl;


    VkMemoryAllocateInfo AllocateInfo{};
    AllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    AllocateInfo.allocationSize = MemoryRequirements.size;
    AllocateInfo.memoryTypeIndex = MemoryTypeIndex;
    Result = Device->AllocateMemory(&AllocateInfo, nullptr, &BufferMemory);
    if (VK_SUCCESS != Result)
    {
        throw std::runtime_error("failed to allocate buffer memory!");
    }

    Result = Device->BindBufferMemory(Buffer, BufferMemory, 0);
    if (VK_SUCCESS != Result)
    {
        throw std::runtime_error("failed to allocate buffer memory!");
    }

    std::cout << "VulkanImage::createBuffer ok" << std::endl;
}

void VulkanImage::Update(const void* InData, std::uint32_t InSize)
{
    std::cout << "VulkanImage::Update start " << InSize << std::endl;

    //CreateBuffer(InSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, StagingBuffer, StagingBufferMemory);

    CreateBuffer1(Device, InSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, StagingBuffer, StagingBufferMemory);

    void* OutData;

    auto ret = Device->MapMemory(StagingBufferMemory, 0, InSize, 0, &OutData);

    memcpy(OutData, (char *)InData, static_cast<size_t>(InSize));

    Device->UnmapMemory(StagingBufferMemory);

    std::cout << "VulkanImage::Update end " << InSize << std::endl;
}

void VulkanImage::CreateBuffer(VkDeviceSize Size, VkBufferUsageFlags Usage, VkMemoryPropertyFlags Properties, VkBuffer& Buffer, VkDeviceMemory& BufferMemory) 
{
    VkResult Result = VK_SUCCESS;

    VkBufferCreateInfo CreateInfo{};
    CreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    CreateInfo.size = Size;
    CreateInfo.usage = Usage;
    CreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    Result = Device->CreateBuffer(&CreateInfo, nullptr, &Buffer);
    if (VK_SUCCESS != Result)
    {
        throw std::runtime_error("failed to create buffer!");
    }

    VkMemoryRequirements MemoryRequirements;
    Device->GetBufferMemoryRequirements(Buffer, &MemoryRequirements);

    std::cout 
        << "memRequirements.size " << MemoryRequirements.size << " "
        << "memRequirements.memoryTypeBits " << MemoryRequirements.memoryTypeBits << " "
        << "Buffer " << Buffer << " "
        << std::endl;
    
    std::uint32_t MemoryTypeIndex = Device->GetPhysicalDevice()->FindMemoryType(MemoryRequirements.memoryTypeBits, Properties);
    std::cout << "Requeired Memory Type Index " << MemoryTypeIndex << std::endl;


    VkMemoryAllocateInfo AllocateInfo{};
    AllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    AllocateInfo.allocationSize = MemoryRequirements.size;
    AllocateInfo.memoryTypeIndex = MemoryTypeIndex;
    Result = Device->AllocateMemory(&AllocateInfo, nullptr, &BufferMemory);
    if (VK_SUCCESS != Result)
    {
        throw std::runtime_error("failed to allocate buffer memory!");
    }

    Result = Device->BindBufferMemory(Buffer, BufferMemory, 0);
    if (VK_SUCCESS != Result)
    {
        throw std::runtime_error("failed to allocate buffer memory!");
    }

    std::cout << "VulkanImage::createBuffer ok" << std::endl;
}

void VulkanImage::TransitionImageLayout(VkFormat Format, VkImageLayout OldLayout, VkImageLayout NewLayout)
{
    VulkanCommandBuffer* CommandBuffer = CommandPool->BeginSingleTimeCommands();
    VkImageMemoryBarrier Barrier{};
    Barrier.sType                           = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    Barrier.oldLayout                       = OldLayout;
    Barrier.newLayout                       = NewLayout;
    Barrier.srcQueueFamilyIndex             = VK_QUEUE_FAMILY_IGNORED;
    Barrier.dstQueueFamilyIndex             = VK_QUEUE_FAMILY_IGNORED;
    Barrier.image                           = Handle;
    Barrier.subresourceRange.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
    Barrier.subresourceRange.baseMipLevel   = 0;
    Barrier.subresourceRange.levelCount     = 1;
    Barrier.subresourceRange.baseArrayLayer = 0;
    Barrier.subresourceRange.layerCount     = ArraySize;

    VkPipelineStageFlags SourceStage;
    VkPipelineStageFlags DestinationStage;

    if (OldLayout == VK_IMAGE_LAYOUT_UNDEFINED && NewLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL)
    {
        Barrier.srcAccessMask = 0;
        Barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

        SourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        DestinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    }
    else if (OldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && NewLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) 
    {
        Barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

        SourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
        DestinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    }
    else {
        //throw std::invalid_argument("unsupported layout transition!");
    }

    CommandBuffer->CmdPipelineBarrier(
        SourceStage, DestinationStage,
        0,
        0, nullptr,
        0, nullptr,
        1, &Barrier
    );

    EndSingleTimeCommands(CommandBuffer);
}


void VulkanImage::CopyBufferToImage(VkBuffer Buffer, uint32_t Width, uint32_t Height) 
{
    VulkanCommandBuffer* CommandBuffer = CommandPool->BeginSingleTimeCommands();

    VkBufferImageCopy Region{};
    Region.bufferOffset = 0;
    Region.bufferRowLength = 0;
    Region.bufferImageHeight = 0;
    Region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    Region.imageSubresource.mipLevel = 0;
    Region.imageSubresource.baseArrayLayer = 0;
    Region.imageSubresource.layerCount = ArraySize;
    Region.imageOffset = { 0, 0, 0 };
    Region.imageExtent = { Width, Height, 1 };
    std::cout  << " CopyBufferToImage " << Width << " " << Height << " " << ArraySize << std::endl;
    CommandBuffer->CmdCopyBufferToImage(Buffer, Handle, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &Region);

    EndSingleTimeCommands(CommandBuffer);
}

void VulkanImage::CopyBufferToImage(VkBuffer Buffer, uint32_t MipLevel, int XOffset, int YOffset, int ZOffset, uint32_t Width, uint32_t Height, uint32_t Depth)
{
    VulkanCommandBuffer* CommandBuffer = CommandPool->BeginSingleTimeCommands();

    uint32_t LayerCount = 1;
    uint32_t BaseArrayLayer = 0;
    switch (Type)
    {
    case RHITextureType::Texture1D:
        LayerCount = 1;
        break;
    case RHITextureType::Texture1DArray:
        LayerCount = Height;
        break;
    case RHITextureType::Texture2D:
        LayerCount = 1;
        BaseArrayLayer = 0;
        break;
    case RHITextureType::Texture2DArray:
        LayerCount = Depth;
        BaseArrayLayer = ZOffset;
        ZOffset = 0;
        break;
    case RHITextureType::TextureCubeMap:
        LayerCount = 1;
        BaseArrayLayer = ZOffset;
        ZOffset = 0;
        break;
    case RHITextureType::TextureCubeMapArray:
        LayerCount = 1;
        BaseArrayLayer = ZOffset;
        ZOffset = 0;
        break;
    case RHITextureType::Texture3D:
        LayerCount = 1;
        break;
    }

    std::cout << " CopyBufferToImage "
        << " XOffset " << XOffset
        << " YOffset " << YOffset
        << " ZOffset " << ZOffset
        << " Width " << Width
        << " Height " << Height
        << " Depth " << Depth
        << " ArraySize " << ArraySize

        << " LayerCount " << LayerCount
        << " BaseArrayLayer " << BaseArrayLayer
        << " MipLevel " << MipLevel
        << std::endl;

    VkBufferImageCopy Region{};
    Region.bufferOffset = 0;
    Region.bufferRowLength = 0;
    Region.bufferImageHeight = 0;
    Region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    Region.imageSubresource.mipLevel = MipLevel;
    Region.imageSubresource.baseArrayLayer = BaseArrayLayer;
    Region.imageSubresource.layerCount = LayerCount;
    Region.imageOffset = { XOffset, YOffset, ZOffset };
    Region.imageExtent = { Width, Height, Depth };

    CommandBuffer->CmdCopyBufferToImage(Buffer, Handle, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &Region);

    EndSingleTimeCommands(CommandBuffer);
}