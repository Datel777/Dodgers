#pragma once

#include "vulkan/vulkan.h"

class Vulkan
{
    VkInstance _instance;
public:
    Vulkan(const char *applicationName, uint32_t version)
    {
        VkApplicationInfo appInfo{
            VK_STRUCTURE_TYPE_APPLICATION_INFO,
            nullptr,
            applicationName,
            version,
            "No Engine",
            VK_MAKE_VERSION(1, 0, 0),
            VK_API_VERSION_1_0
        };

        VkInstanceCreateInfo createInfo{}; //initialize with zeros
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        if (vkCreateInstance(&createInfo, nullptr, &_instance) != VK_SUCCESS)
            throw std::runtime_error("Vulkan Init");
    }

    ~Vulkan()
    {
        std::cout << "~Vulkan" << std::endl;
    }
};