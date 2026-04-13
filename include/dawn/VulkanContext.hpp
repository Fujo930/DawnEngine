#pragma once
#include <vulkan/vulkan.h>
#include <SDL.h>
#include <vector>
#include <stdexcept>

namespace dawn {

struct QueueFamilyIndices {
    uint32_t graphics = UINT32_MAX;
    uint32_t present  = UINT32_MAX;

    bool isComplete() const {
        return graphics != UINT32_MAX && present != UINT32_MAX;
    }
};

class VulkanContext {
public:
    explicit VulkanContext(SDL_Window* window);
    ~VulkanContext();

    VulkanContext(const VulkanContext&)            = delete;
    VulkanContext& operator=(const VulkanContext&) = delete;

    VkDevice         device()         const { return m_device; }
    VkPhysicalDevice physicalDevice() const { return m_physicalDevice; }
    VkQueue          graphicsQueue()  const { return m_graphicsQueue; }

    void waitIdle() const;

private:
    void createInstance(SDL_Window* window);
    void createSurface(SDL_Window* window);
    void pickPhysicalDevice();
    void createLogicalDevice();

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) const;
    bool               isDeviceSuitable(VkPhysicalDevice device)  const;

    VkInstance       m_instance       = VK_NULL_HANDLE;
    VkSurfaceKHR     m_surface        = VK_NULL_HANDLE;
    VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
    VkDevice         m_device         = VK_NULL_HANDLE;
    VkQueue          m_graphicsQueue  = VK_NULL_HANDLE;
    VkQueue          m_presentQueue   = VK_NULL_HANDLE;

#ifdef NDEBUG
    static constexpr bool ENABLE_VALIDATION = false;
#else
    static constexpr bool ENABLE_VALIDATION = true;
#endif
};

} // namespace dawn