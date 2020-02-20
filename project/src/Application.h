#pragma once

#include <iostream>
#include <stdexcept>

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

class Application
{
    VkInstance _instance;
    GLFWwindow* _window = nullptr;

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

public:
    Application(const char *applicationName, uint32_t version);
    ~Application();

    void initWindow(int width, int height, const char* title);

    void mainloop();
};