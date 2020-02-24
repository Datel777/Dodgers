#pragma once

#include <vulkan/vulkan.h>
#include <cstring>
#include <vector>
#include <unordered_map>

#include "Commons.h"


class PhysicalDevice
{
public:
    PhysicalDevice();
    PhysicalDevice(const VkPhysicalDevice& vkPhysicalDevice);

    inline const VkPhysicalDevice &vkPhysicalDevice() const         {return _vkPhysicalDevice;}
    inline const VkPhysicalDeviceProperties &properties() const     {return _properties;}
    inline const VkPhysicalDeviceFeatures &features() const         {return _features;}

    inline const VkPhysicalDeviceType &type() const                 {return _properties.deviceType;}

    //should be more complex in future
    inline uint32_t getRating() const                               {return _properties.limits.maxImageDimension2D;}
    bool isSupportsExtensions() const;  //const uint32_t &count, const char* extensions[]
//    maybe i'll make common useful function later
//    bool initQueueFamilies(const VkQueueFlags &flags, bool needPresent);
    bool initQueueFamilies(const VkSurfaceKHR &surface);

    inline uint32_t graphicsFamily() const      {return _graphicsFamily;}
    inline uint32_t presentFamily() const       {return _presentFamily;}

    bool querySwapChainSupport(const VkSurfaceKHR &surface);

    inline const VkSurfaceCapabilitiesKHR &capabilities() const {return _capabilities;}
    inline const VkSurfaceFormatKHR &format() const             {return _format;}
    inline const VkPresentModeKHR &presentMode() const          {return _presentMode;}

    VkExtent2D chooseSwapExtent(uint32_t width, uint32_t height);

private:
    VkPhysicalDevice _vkPhysicalDevice;
    VkPhysicalDeviceProperties _properties;
    VkPhysicalDeviceFeatures _features;

    uint32_t _graphicsFamily = UINT32_MAX;
    uint32_t _presentFamily = UINT32_MAX;

    VkSurfaceCapabilitiesKHR _capabilities;
    VkSurfaceFormatKHR _format;
    VkPresentModeKHR _presentMode;

    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
};
