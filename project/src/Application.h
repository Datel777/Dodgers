#pragma once

#include <iostream>
#include <stdexcept>
#include <cstring>
#include <vector>

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

//  PFN_vkCreateDebugUtilsMessengerEXT func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(_instance, "vkCreateDebugUtilsMessengerEXT");
#define VULKAN_PFN_(FUNC_NAME)\
    PFN_##FUNC_NAME FUNC_NAME = (PFN_##FUNC_NAME)vkGetInstanceProcAddr(_instance, #FUNC_NAME)

class Application
{
public:
    Application(const char *applicationName, uint32_t version);
    ~Application();

    void initWindow(int width, int height, const char* title);

    void mainloop();

private:
    VkInstance _instance;
    GLFWwindow* _window = nullptr;

    void initGLFW();
    void initVulkan(const char *applicationName, uint32_t applicationVersion);
    void getRequiredExtensions(const uint32_t &count, const char* const* names);

#ifndef NDEBUG
    VkDebugUtilsMessengerEXT _debugMessenger;

    void getRequiredLayers(const uint32_t &count, const char* const* &names);
    void setupDebugMessenger();

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData);

    //just little helper to get size of array made by "type var[] {...};"
    template<class T, size_t N>
    constexpr size_t sizeOfArray(T (&)[N]) {return N;}
#endif
};
