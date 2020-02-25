#pragma once

#include <iostream>
#include <stdexcept>
#include <cstring>
#include <vector>
#include <map>
//#include <optional>


#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE


#include "Device.h"


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

    inline void showWindow() const  {glfwShowWindow(_window);}

    void mainloop();

private:
    GLFWwindow* _window = nullptr;
    VkInstance _instance;
    VkSurfaceKHR _surface;
    Device _device;
    Swapchain _swapchain;
    std::vector<VkImage> _swapChainImages;
    ImageViewContainer _imageViewContainer;
    VkShaderModule _shaderModuleVertex = VK_NULL_HANDLE;
    VkShaderModule _shaderModuleFragment = VK_NULL_HANDLE;
    VkPipelineLayout _pipelineLayout = VK_NULL_HANDLE;

    void initGLFW(int width, int height, const char* title);
    void initVulkan(const char *applicationName, uint32_t applicationVersion);
    void getRequiredExtensions(const uint32_t &count, const char* const* names);

    PhysicalDevice pickPhysicalDevice();

    void createSurface();


#ifndef NDEBUG
    VkDebugUtilsMessengerEXT _debugMessenger;

    void getRequiredLayers(const uint32_t &count, const char* const* &names);
    void setupDebugMessenger(const VkDebugUtilsMessengerCreateInfoEXT *debugCreateInfo);
    VkDebugUtilsMessengerCreateInfoEXT createDebugInfo();

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData);
#endif

};
