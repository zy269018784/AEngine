#ifndef VULKAN_WINDOW_H
#define VULKAN_WINDOW_H

#include <QWindow>
#include <QVulkanInstance>
#include <QVulkanFunctions>
#include <QWidget>

class VulkanRenderer;

class VulkanWindow : public QWindow
{
Q_OBJECT

public:
explicit VulkanWindow(QWindow *parent = nullptr);
~VulkanWindow();

    void initialize();
    void render();

protected:
void exposeEvent(QExposeEvent *event) override;
void resizeEvent(QResizeEvent *event) override;
bool event(QEvent *event) override;

private:
void initVulkan();
void initSwapchain();
void initRenderPass();
void initFramebuffers();
void initPipeline();
void recordCommandBuffer();

    QVulkanInstance *m_instance;
    VkSurfaceKHR m_surface;
    VkDevice m_device;
    VkPhysicalDevice m_physicalDevice;
    VkQueue m_graphicsQueue;
    VkQueue m_presentQueue;
    VkSwapchainKHR m_swapchain;
    VkRenderPass m_renderPass;
    VkPipelineLayout m_pipelineLayout;
    VkPipeline m_graphicsPipeline;
    std::vector<VkFramebuffer> m_swapchainFramebuffers;
    std::vector<VkImage> m_swapchainImages;
    std::vector<VkImageView> m_swapchainImageViews;
    VkCommandPool m_commandPool;
    std::vector<VkCommandBuffer> m_commandBuffers;

    std::vector<VkSemaphore> m_imageAvailableSemaphores;
    std::vector<VkSemaphore> m_renderFinishedSemaphores;
    std::vector<VkFence> m_inFlightFences;
    
    uint32_t m_currentFrame = 0;
    bool m_frameBufferResized = false;

    QVulkanDeviceFunctions *m_devFuncs;
};

class VulkanWidget : public QWidget
{
Q_OBJECT

public:
VulkanWidget(QWidget *parent = nullptr);
~VulkanWidget();

private:
VulkanWindow *m_vulkanWindow;
QWidget *m_container;
};

#endif // VULKAN_WINDOW_H