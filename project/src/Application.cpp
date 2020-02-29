#include "Application.h"

Window *Application::createWindow(int width, int height, const char* title, const std::initializer_list<std::pair<int,int>> &hints)
{
    Window *w = new Window(width, height, title, hints);
    addToDestroy(w);
    return w;
}


/*
Application::Application()
{
//    initGLFW(width, height, applicationName);
//    initVulkan(applicationName, version);
    createSurface();
    _device = Device(pickPhysicalDevice());
    _swapchain = _device.createSwapChain(width, height, _surface);
    _imageViewContainer = _swapchain.createImageViews();
    _pipeline = _swapchain.createGraphicsPipeline();
}


Application::~Application()
{
    if (_pipeline != VK_NULL_HANDLE)
        vkDestroyPipeline(_device.vkDevice(), _pipeline, nullptr);

    //should create classes for this
//    if (_pipelineLayout != VK_NULL_HANDLE)
//        vkDestroyPipelineLayout(_device.vkDevice(), _pipelineLayout, nullptr);
//
//    if (_renderPass != VK_NULL_HANDLE)
//        vkDestroyRenderPass(_device.vkDevice(), _renderPass, nullptr);
//
//    if (_shaderModuleFragment != VK_NULL_HANDLE)
//        vkDestroyShaderModule(_device.vkDevice(), _shaderModuleFragment, nullptr);
//    if (_shaderModuleVertex != VK_NULL_HANDLE)
//        vkDestroyShaderModule(_device.vkDevice(), _shaderModuleVertex, nullptr);

    _imageViewContainer.destroy();
    _swapchain.destroy();
    _device.destroy();

#ifndef NDEBUG
    if (VULKAN_PFN_(vkDestroyDebugUtilsMessengerEXT))
        vkDestroyDebugUtilsMessengerEXT(_instance, _debugMessenger, nullptr);
#endif

    vkDestroySurfaceKHR(_instance, _surface, nullptr);
    vkDestroyInstance(_instance, nullptr);

    if (_window)
        glfwDestroyWindow(_window);

    glfwTerminate();
}


PhysicalDevice Application::pickPhysicalDevice()
{
    uint32_t deviceCount;
    vkEnumeratePhysicalDevices(_instance, &deviceCount, nullptr);

    if (!deviceCount)
        throw std::runtime_error("Vulkan: failed to find GPUs with Vulkan support!");

    //get all physical devices
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(_instance, &deviceCount, devices.data());

    //make list of devices sorted by rating to choose best suitable device
    std::multimap<int, PhysicalDevice> ratedDevices;
    PhysicalDevice physicalDevice;

    for (const VkPhysicalDevice &device : devices)
    {
        physicalDevice = PhysicalDevice(device);

        if (physicalDevice.type() == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
                physicalDevice.features().geometryShader &&
                physicalDevice.isSupportsExtensions() &&
                physicalDevice.initQueueFamilies(_surface) &&
                physicalDevice.querySwapChainSupport(_surface))
            ratedDevices.insert({physicalDevice.getRating(), physicalDevice});
    }

    //choosing the best one
    if (ratedDevices.size())
        return ratedDevices.rbegin()->second;

    throw std::runtime_error("Vulkan: failed to find a suitable GPU!");
}


void Application::createSurface()
{
    if (glfwCreateWindowSurface(_instance, _window, nullptr, &_surface) != VK_SUCCESS)
        throw std::runtime_error("Vulkan: failed to create window surface!");
}
*/
