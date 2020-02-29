#pragma once

//#include <vulkan/vulkan.h>
//#include <cstring>
//#include <vector>
#include <optional>

#include "Core.h"
#include "Surface.h"


class PhysicalDevice
{
public:
    PhysicalDevice();
    PhysicalDevice(const VkPhysicalDevice& vkPhysicalDevice);

    static std::vector<PhysicalDevice> getAll();

    inline const VkPhysicalDevice &vkPhysicalDevice() const         {return _vkPhysicalDevice;}
    inline const VkPhysicalDeviceProperties &properties() const     {return _properties;}
    inline const VkPhysicalDeviceFeatures &features() const         {return _features;}

    inline const VkPhysicalDeviceType &type() const                 {return _properties.deviceType;}

    bool isSupportsExtensions() const;  //const uint32_t &count, const char* extensions[] ?

    std::vector<VkQueueFamilyProperties> getQueueFamilyProperties() const;
    std::vector<VkSurfaceFormatKHR> getSupportedFormats(const Surface *surface) const;
    std::vector<VkPresentModeKHR> getSupportedPresentModes(const Surface *surface) const;
    VkSurfaceCapabilitiesKHR getCapabilities(const Surface *surface) const;

    VkExtent2D chooseSwapExtent(uint32_t width, uint32_t height, const VkSurfaceCapabilitiesKHR &capabilities);

private:
    VkPhysicalDevice _vkPhysicalDevice;
    VkPhysicalDeviceProperties _properties;
    VkPhysicalDeviceFeatures _features;
};
