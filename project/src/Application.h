#pragma once

#include <iostream>
#include <stdexcept>
#include <cstring>
#include <vector>
#include <map>
//#include <optional>

#include "Core.h"
#include "RecursiveDestroyer.h"

#include "Window.h"
#include "Device.h"


class Application : public RecursiveDestroyer
{
public:
    Window *createWindow(int width, int height, const char* title, const std::initializer_list<std::pair<int,int>> &hints = {});

/*
public:
    Application();
    ~Application();

    virtual constexpr void mainloop() = 0;

private:
//    GLFWwindow* _window = nullptr;
    VkInstance _instance;
    VkSurfaceKHR _surface;
    Device _device;
    Swapchain _swapchain;
    std::vector<VkImage> _swapChainImages;
    ImageViewContainer _imageViewContainer;
//    VkShaderModule _shaderModuleVertex = VK_NULL_HANDLE;
//    VkShaderModule _shaderModuleFragment = VK_NULL_HANDLE;
//    VkPipelineLayout _pipelineLayout = VK_NULL_HANDLE;
//    VkRenderPass _renderPass = VK_NULL_HANDLE;

    VkPipeline _pipeline = VK_NULL_HANDLE;

    void initGLFW(int width, int height, const char* title);
    void initVulkan(const char *applicationName, uint32_t applicationVersion);


    PhysicalDevice pickPhysicalDevice();

    void createSurface();
*/
};
