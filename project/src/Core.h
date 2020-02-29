#pragma once

#include <stdexcept>
#include <vector>

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include "VulkanHelper.h"


class Core
{
public:
    Core();
    ~Core();

    //need to initialize values in main.cpp
    static const char* applicationName;
    static const uint32_t applicationVersion;

    static const std::vector<const char*> requiredInstanceExtensions;
    static const std::vector<const char*> requiredDeviceExtensions;

    static inline const VkInstance &vkInstance()    {return _vkInstance;}

private:
    static VkInstance _vkInstance;
    static bool _exists; //unique core checking

    static void checkRequiredExtensions(const std::vector<const char*> &extensionNames);

#ifndef NDEBUG
    static const std::vector<const char*> requiredLayers;

    static void checkRequiredLayers(const std::vector<const char*> &layerNames);
    static VkDebugUtilsMessengerEXT _debugMessenger;
    static void setupDebugMessenger(const VkDebugUtilsMessengerCreateInfoEXT *debugCreateInfo);

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData);
#endif
};