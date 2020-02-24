#include "PhysicalDevice.h"


PhysicalDevice::PhysicalDevice() :
    _vkPhysicalDevice(VK_NULL_HANDLE), _properties{}, _features{}
{}


PhysicalDevice::PhysicalDevice(const VkPhysicalDevice& vkPhysicalDevice) :
    _vkPhysicalDevice(vkPhysicalDevice)
{
    vkGetPhysicalDeviceProperties(_vkPhysicalDevice, &_properties);
    vkGetPhysicalDeviceFeatures(_vkPhysicalDevice, &_features);
}


bool PhysicalDevice::isSupportsExtensions() const //const uint32_t &count, const char* extensions[]
{
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(_vkPhysicalDevice, nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(_vkPhysicalDevice, nullptr, &extensionCount, availableExtensions.data());


    bool notSupported;
    const char *extensionName;

    for (int i=0; i<DeviceExtensions::count; ++i)
    {
        notSupported = true;
        extensionName = DeviceExtensions::required[i];

        for (const VkExtensionProperties &p : availableExtensions)
            if (strcmp(extensionName, p.extensionName) == 0)
            {
                notSupported = false;
                break;
            }

        if (notSupported)
            return false;
    }

    return true;
}


bool PhysicalDevice::initQueueFamilies(const VkSurfaceKHR &surface)
{
    uint32_t queueFamilyCount;
    vkGetPhysicalDeviceQueueFamilyProperties(_vkPhysicalDevice, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(_vkPhysicalDevice, &queueFamilyCount, queueFamilies.data());

    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;
    VkBool32 presentSupport;

    //for now i'll try to choose random families
    //but sometimes choosing same families could improve performance
    for (uint32_t i = 0; i<queueFamilyCount && (!graphicsFamily.has_value() || !presentFamily.has_value()); ++i)
    {
        if (!graphicsFamily.has_value() && queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
            graphicsFamily = i;

        if (!presentFamily.has_value())
        {
            vkGetPhysicalDeviceSurfaceSupportKHR(_vkPhysicalDevice, i, surface, &presentSupport);

            if (presentSupport)
                presentFamily = i;
        }
    }

    if (graphicsFamily.has_value() && presentFamily.has_value())
    {
        _graphicsFamily = graphicsFamily.value();
        _presentFamily = presentFamily.value();

        return true;
    }

    return false;
}


bool PhysicalDevice::querySwapChainSupport(const VkSurfaceKHR &surface)
{
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(_vkPhysicalDevice, surface, &_capabilities);

    uint32_t formatCount;
    uint32_t presentModeCount;

    vkGetPhysicalDeviceSurfaceFormatsKHR(_vkPhysicalDevice, surface, &formatCount, nullptr);
    vkGetPhysicalDeviceSurfacePresentModesKHR(_vkPhysicalDevice, surface, &presentModeCount, nullptr);

    if (!(formatCount && presentModeCount))
        return false;


    std::vector<VkSurfaceFormatKHR> formats(formatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(_vkPhysicalDevice, surface, &formatCount, formats.data());

    _format = chooseSwapSurfaceFormat(formats);


    std::vector<VkPresentModeKHR> presentModes(presentModeCount);
    vkGetPhysicalDeviceSurfacePresentModesKHR(_vkPhysicalDevice, surface, &presentModeCount, presentModes.data());

    _presentMode = chooseSwapPresentMode(presentModes);

    return true;
}


VkSurfaceFormatKHR PhysicalDevice::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats)
{
    for (const VkSurfaceFormatKHR &availableFormat : availableFormats)
        if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
            return availableFormat;

    return availableFormats[0];
}


VkPresentModeKHR PhysicalDevice::chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes)
{
    for (const VkPresentModeKHR &availablePresentMode : availablePresentModes)
        if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
            return availablePresentMode;

    return VK_PRESENT_MODE_FIFO_KHR;
}


VkExtent2D PhysicalDevice::chooseSwapExtent(uint32_t width, uint32_t height)
{
    if (_capabilities.currentExtent.width != UINT32_MAX)
        return _capabilities.currentExtent;
    else
        return {
            std::max(_capabilities.minImageExtent.width, std::min(_capabilities.maxImageExtent.width, width)),
            std::max(_capabilities.minImageExtent.height, std::min(_capabilities.maxImageExtent.height, height))
        };
}
