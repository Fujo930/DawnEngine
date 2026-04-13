#include "dawn/VulkanContext.hpp"
#include <SDL_vulkan.h>
#include <stdexcept>
#include <vector>
#include <set>
#include <iostream>

namespace dawn {

VulkanContext::VulkanContext(SDL_Window* window) {
    createInstance(window);
    createSurface(window);
    pickPhysicalDevice();
    createLogicalDevice();
    std::cout << "[Dawn] Vulkan context ready.\n";
}

VulkanContext::~VulkanContext() {
    waitIdle();
    if (m_device)   vkDestroyDevice(m_device, nullptr);
    if (m_surface)  vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
    if (m_instance) vkDestroyInstance(m_instance, nullptr);
}

void VulkanContext::waitIdle() const {
    if (m_device) vkDeviceWaitIdle(m_device);
}

void VulkanContext::createInstance(SDL_Window* window) {
    uint32_t extCount = 0;
    SDL_Vulkan_GetInstanceExtensions(window, &extCount, nullptr);
    std::vector<const char*> extensions(extCount);
    SDL_Vulkan_GetInstanceExtensions(window, &extCount, extensions.data());

    VkApplicationInfo appInfo{};
    appInfo.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName   = "Dawn Engine";
    appInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
    appInfo.pEngineName        = "Dawn";
    appInfo.engineVersion      = VK_MAKE_VERSION(0, 1, 0);
    appInfo.apiVersion         = VK_API_VERSION_1_3;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo        = &appInfo;
    createInfo.enabledExtensionCount   = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };
    if (ENABLE_VALIDATION) {
        createInfo.enabledLayerCount   = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
        std::cout << "[Dawn] Validation layers enabled.\n";
    }

    if (vkCreateInstance(&createInfo, nullptr, &m_instance) != VK_SUCCESS)
        throw std::runtime_error("vkCreateInstance failed");
}

void VulkanContext::createSurface(SDL_Window* window) {
    if (!SDL_Vulkan_CreateSurface(window, m_instance, &m_surface))
        throw std::runtime_error("SDL_Vulkan_CreateSurface failed");
}

void VulkanContext::pickPhysicalDevice() {
    uint32_t count = 0;
    vkEnumeratePhysicalDevices(m_instance, &count, nullptr);
    if (count == 0)
        throw std::runtime_error("No Vulkan-capable GPU found");

    std::vector<VkPhysicalDevice> devices(count);
    vkEnumeratePhysicalDevices(m_instance, &count, devices.data());

    for (const auto& d : devices) {
        if (isDeviceSuitable(d)) {
            m_physicalDevice = d;
            VkPhysicalDeviceProperties props;
            vkGetPhysicalDeviceProperties(d, &props);
            std::cout << "[Dawn] GPU: " << props.deviceName << "\n";
            return;
        }
    }
    throw std::runtime_error("No suitable GPU found");
}

bool VulkanContext::isDeviceSuitable(VkPhysicalDevice device) const {
    return findQueueFamilies(device).isComplete();
}

QueueFamilyIndices VulkanContext::findQueueFamilies(VkPhysicalDevice device) const {
    QueueFamilyIndices indices;

    uint32_t count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &count, nullptr);
    std::vector<VkQueueFamilyProperties> families(count);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &count, families.data());

    for (uint32_t i = 0; i < count; ++i) {
        if (families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
            indices.graphics = i;

        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, m_surface, &presentSupport);
        if (presentSupport)
            indices.present = i;

        if (indices.isComplete()) break;
    }
    return indices;
}

void VulkanContext::createLogicalDevice() {
    QueueFamilyIndices indices = findQueueFamilies(m_physicalDevice);

    std::set<uint32_t> uniqueFamilies = {
        indices.graphics,
        indices.present
    };

    float priority = 1.0f;
    std::vector<VkDeviceQueueCreateInfo> queueInfos;
    for (uint32_t family : uniqueFamilies) {
        VkDeviceQueueCreateInfo qi{};
        qi.sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        qi.queueFamilyIndex = family;
        qi.queueCount       = 1;
        qi.pQueuePriorities = &priority;
        queueInfos.push_back(qi);
    }

    const std::vector<const char*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    VkPhysicalDeviceFeatures features{};

    VkDeviceCreateInfo createInfo{};
    createInfo.sType                   = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.queueCreateInfoCount    = static_cast<uint32_t>(queueInfos.size());
    createInfo.pQueueCreateInfos       = queueInfos.data();
    createInfo.enabledExtensionCount   = static_cast<uint32_t>(deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = deviceExtensions.data();
    createInfo.pEnabledFeatures        = &features;

    if (vkCreateDevice(m_physicalDevice, &createInfo, nullptr, &m_device) != VK_SUCCESS)
        throw std::runtime_error("vkCreateDevice failed");

    vkGetDeviceQueue(m_device, indices.graphics, 0, &m_graphicsQueue);
    vkGetDeviceQueue(m_device, indices.present,  0, &m_presentQueue);
}

} // namespace dawn