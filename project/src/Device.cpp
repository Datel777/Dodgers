#include "Device.h"


Device::Device(const PhysicalDevice &physicalDevice) :
        _physicalDevice(physicalDevice)
{
    //vector array of create infos for queues
    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    //set of unique family indices
    std::set<uint32_t> uniqueQueueFamilies{physicalDevice.graphicsFamily(), physicalDevice.presentFamily()};

    float queuePriority = 1.0f;

    for (uint32_t queueFamily : uniqueQueueFamilies)
    {
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    //should i use empty features?
//    VkPhysicalDeviceFeatures deviceFeatures{};
//    createInfo.pEnabledFeatures = &deviceFeatures;
    //or maybe
    createInfo.pEnabledFeatures = &physicalDevice.features();
    createInfo.enabledExtensionCount = DeviceExtensions::count;
    createInfo.ppEnabledExtensionNames = DeviceExtensions::required;

#ifndef NDEBUG
    createInfo.enabledLayerCount = Layers::count;
    createInfo.ppEnabledLayerNames = Layers::required;
#endif

    if (vkCreateDevice(physicalDevice.vkPhysicalDevice(), &createInfo, nullptr, &_vkDevice) != VK_SUCCESS)
        throw std::runtime_error("Vulkan: failed to create logical device!");

    //get queues handles
    vkGetDeviceQueue(_vkDevice, physicalDevice.graphicsFamily(), 0, &_graphicsQueue);
    vkGetDeviceQueue(_vkDevice, physicalDevice.presentFamily(), 0, &_presentQueue);
}


void Device::destroy()
{
    if (_vkDevice != VK_NULL_HANDLE)
        vkDestroyDevice(_vkDevice, nullptr);
}


Swapchain Device::createSwapChain(uint32_t width, uint32_t height, const VkSurfaceKHR &surface)
{
    VkExtent2D extent = _physicalDevice.chooseSwapExtent(width, height);

    uint32_t imageCount = _physicalDevice.capabilities().minImageCount + 1;

    if (_physicalDevice.capabilities().maxImageCount > 0 && imageCount > _physicalDevice.capabilities().maxImageCount)
        imageCount = _physicalDevice.capabilities().maxImageCount;

    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = surface;

    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = _physicalDevice.format().format;
    createInfo.imageColorSpace = _physicalDevice.format().colorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    uint32_t queueFamilyIndices[] {_physicalDevice.graphicsFamily(), _physicalDevice.presentFamily()};

    if (_physicalDevice.graphicsFamily() != _physicalDevice.presentFamily())
    {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    } else
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE; //This option offers the best performance

    createInfo.preTransform = _physicalDevice.capabilities().currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR; //do not need to blend with other windows, so ignore
    createInfo.presentMode = _physicalDevice.presentMode();
    createInfo.clipped = VK_TRUE; //if true, we do not care about pixels which (for example) under other window
    createInfo.oldSwapchain = VK_NULL_HANDLE; //need when window size changed, and need create new swap chain

    VkSwapchainKHR vkSwapChain;
    if (vkCreateSwapchainKHR(_vkDevice, &createInfo, nullptr, &vkSwapChain) != VK_SUCCESS)
        throw std::runtime_error("Vulkan: failed to create swap chain!");

    return Swapchain(_vkDevice, vkSwapChain, createInfo.minImageCount, createInfo.imageFormat, createInfo.imageExtent);
}