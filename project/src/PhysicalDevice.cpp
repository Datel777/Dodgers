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


std::vector<PhysicalDevice> PhysicalDevice::getAll()
{
    uint32_t deviceCount;
    vkEnumeratePhysicalDevices(Core::vkInstance(), &deviceCount, nullptr);

    if (!deviceCount)
        throw std::runtime_error("PhysicalDevice: failed to get all physical devices");

    //get all physical devices
    std::vector<VkPhysicalDevice> vkPhysicalDevices(deviceCount);
    vkEnumeratePhysicalDevices(Core::vkInstance(), &deviceCount, vkPhysicalDevices.data());

    std::vector<PhysicalDevice> physicalDevices(deviceCount);

    for (int i=0; i<deviceCount; ++i)
        physicalDevices[i] = PhysicalDevice(vkPhysicalDevices[i]);

    return physicalDevices;
}


bool PhysicalDevice::isSupportsExtensions() const //const std::vector<const char*> &requiredDeviceExtensions
{
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(_vkPhysicalDevice, nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(_vkPhysicalDevice, nullptr, &extensionCount, availableExtensions.data());

    bool notSupported;

    for (const char *extensionName : Core::requiredDeviceExtensions)
    {
        notSupported = true;

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


std::vector<VkQueueFamilyProperties> PhysicalDevice::getQueueFamilyProperties() const
{
    uint32_t queueFamilyCount;
    vkGetPhysicalDeviceQueueFamilyProperties(_vkPhysicalDevice, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(_vkPhysicalDevice, &queueFamilyCount, queueFamilies.data());

    return queueFamilies;
}


std::vector<VkSurfaceFormatKHR> PhysicalDevice::getSupportedFormats(const Surface *surface) const
{
    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(_vkPhysicalDevice, surface->vkSurface(), &formatCount, nullptr);

    std::vector<VkSurfaceFormatKHR> formats(formatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(_vkPhysicalDevice, surface->vkSurface(), &formatCount, formats.data());

    return formats;
}


std::vector<VkPresentModeKHR> PhysicalDevice::getSupportedPresentModes(const Surface *surface) const
{
    uint32_t presentModeCount;

    vkGetPhysicalDeviceSurfacePresentModesKHR(_vkPhysicalDevice, surface->vkSurface(), &presentModeCount, nullptr);

    std::vector<VkPresentModeKHR> presentModes(presentModeCount);
    vkGetPhysicalDeviceSurfacePresentModesKHR(_vkPhysicalDevice, surface->vkSurface(), &presentModeCount, presentModes.data());

    return presentModes;
}


VkSurfaceCapabilitiesKHR PhysicalDevice::getCapabilities(const Surface *surface) const
{
    VkSurfaceCapabilitiesKHR capabilities;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(_vkPhysicalDevice, surface->vkSurface(), &capabilities);
    return capabilities;
}


VkExtent2D PhysicalDevice::chooseSwapExtent(uint32_t width, uint32_t height, const VkSurfaceCapabilitiesKHR &capabilities)
{
    if (capabilities.currentExtent.width != UINT32_MAX)
        return capabilities.currentExtent;
    else
        return {
            std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, width)),
            std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, height))
        };
}
