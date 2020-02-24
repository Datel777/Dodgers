#pragma once

#include <set>

#include "PhysicalDevice.h"


class Device
{
public:
    Device() {}
    Device(const PhysicalDevice &physicalDevice);

    void destroy();

    void createSwapChain(uint32_t width, uint32_t height, const VkSurfaceKHR &surface);

//    inline const PhysicalDevice &physicalDevice() const       {return _physicalDevice;}
    inline const VkDevice &vkDevice() const             {return _vkDevice;}
    inline const VkQueue &graphicsQueue() const         {return _graphicsQueue;}
    inline const VkQueue &presentQueue() const          {return _presentQueue;}
    inline const VkSwapchainKHR &swapChain() const      {return _swapChain;}

private:
    PhysicalDevice _physicalDevice;
    VkDevice _vkDevice = VK_NULL_HANDLE;
    VkQueue _graphicsQueue = VK_NULL_HANDLE;
    VkQueue _presentQueue = VK_NULL_HANDLE;
    VkSwapchainKHR _swapChain = VK_NULL_HANDLE;
};
