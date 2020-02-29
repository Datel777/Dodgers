#pragma once
//this is user's application class

#include <tuple>

#include "Application.h"

class MyApplication : public Application
{
    //struct with all data what i need
    struct PhysicalDeviceProperties
    {
        VkSurfaceCapabilitiesKHR capabilities;
        VkSurfaceFormatKHR format;
        VkPresentModeKHR presentMode;

        uint32_t graphicsFamily = UINT32_MAX;
        uint32_t presentFamily = UINT32_MAX;
    };

public:
    MyApplication();

    void mainloop();

private:
    Window *_window;
    Surface *_surface;

    PhysicalDeviceProperties _physicalDeviceProperties{};
    PhysicalDevice _physicalDevice;

    void pickPhysicalDevice();
    bool isSuitable(const PhysicalDevice &physicalDevice, PhysicalDeviceProperties &properties);
    inline uint32_t getRating(const PhysicalDevice &physicalDevice) const       {return physicalDevice.properties().limits.maxImageDimension2D;}
    bool initQueueFamilies(const PhysicalDevice &physicalDevice, Surface *surface, PhysicalDeviceProperties &properties);
    bool querySwapChainSupport(const PhysicalDevice &physicalDevice, Surface *surface, PhysicalDeviceProperties &properties);

    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &formats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &presentModes);
};