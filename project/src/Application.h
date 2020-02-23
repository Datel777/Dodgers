#pragma once

#include <iostream>
#include <stdexcept>
#include <cstring>
#include <vector>
#include <map>
//#include <optional>
#include <set>

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

//  PFN_vkCreateDebugUtilsMessengerEXT func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(_instance, "vkCreateDebugUtilsMessengerEXT");
#define VULKAN_PFN_(FUNC_NAME)\
    PFN_##FUNC_NAME FUNC_NAME = (PFN_##FUNC_NAME)vkGetInstanceProcAddr(_instance, #FUNC_NAME)

class Application
{
//    struct QueueFamilyIndices {
//        std::optional<uint32_t> graphicsFamily;
//        std::optional<uint32_t> presentFamily;
//
//        inline bool isComplete() const  {return graphicsFamily.has_value() && presentFamily.has_value();}
//    };

public:
    Application(const char *applicationName, uint32_t version, int width, int height);
    ~Application();

    void showWindow();

    void mainloop();

private:
    GLFWwindow* _window = nullptr;
    VkInstance _instance;
    VkSurfaceKHR _surface;
    VkPhysicalDevice _physicalDevice = VK_NULL_HANDLE;
    uint32_t _graphicsFamily = UINT32_MAX;
    uint32_t _presentFamily = UINT32_MAX;
//    QueueFamilyIndices _queueFamilies;

    VkDevice _device = VK_NULL_HANDLE;
    VkQueue _graphicsQueue = VK_NULL_HANDLE;
    VkQueue _presentQueue = VK_NULL_HANDLE;

    void initGLFW(int width, int height, const char* title);
    void initVulkan(const char *applicationName, uint32_t applicationVersion);
    void getRequiredExtensions(const uint32_t &count, const char* const* names);

    void pickPhysicalDevice();
    int rateDeviceSuitability(const VkPhysicalDevice &device);

    void findQueueFamily(const VkQueueFlagBits &flags);
    inline bool isQueueFamilySuitable(const VkQueueFamilyProperties &queueFamily, const VkQueueFlagBits &flags) const
        {return !((queueFamily.queueFlags & flags) ^ flags);}

    void createDevice();
    void createSurface();

#ifndef NDEBUG
    VkDebugUtilsMessengerEXT _debugMessenger;

    static const char* _requiredLayers[];
    static uint32_t _requiredLayersCount;

    void getRequiredLayers(const uint32_t &count, const char* const* &names);
    void setupDebugMessenger(const VkDebugUtilsMessengerCreateInfoEXT *debugCreateInfo);
    VkDebugUtilsMessengerCreateInfoEXT createDebugInfo();

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData);

    //just little helper to get size of array made by "type var[] {...};"
    template<class T, size_t N>
    static constexpr size_t sizeOfArray(T (&)[N]) {return N;}
#endif
};
