#include "Application.h"

Application::Application(const char *applicationName, uint32_t version)
{
    //Init GLFW
    if (!glfwInit())
        throw std::runtime_error("GLFW Init");

    //Init Vulkan
    VkApplicationInfo appInfo{
        VK_STRUCTURE_TYPE_APPLICATION_INFO,
        nullptr,
        applicationName,
        version,
        "No Engine",
        VK_MAKE_VERSION(1, 0, 0),
        VK_API_VERSION_1_0
    };

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.ppEnabledExtensionNames = glfwGetRequiredInstanceExtensions(&createInfo.enabledExtensionCount);

    if (vkCreateInstance(&createInfo, nullptr, &_instance) != VK_SUCCESS)
        throw std::runtime_error("Vulkan Init");

    //Check Vulkan Extensions
    /*
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    VkExtensionProperties extensionsProperties[extensionCount];
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensionsProperties);

    std::cout << "available extensions:" << std::endl;
    for (const auto& extension : extensionsProperties)
        std::cout << "\t" << extension.extensionName << std::endl;
    */

    const char* validationLayers[] {
        "VK_LAYER_KHRONOS_validation"
    };

//    uint32_t layerCount;
//    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
//    std::vector<VkLayerProperties> availableLayers(layerCount);
//    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

}

Application::~Application()
{
    vkDestroyInstance(_instance, nullptr);

    if (_window)
        glfwDestroyWindow(_window);

    glfwTerminate();
}

void Application::initWindow(int width, int height, const char* title)
{
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    if (!(_window = glfwCreateWindow(width, height, title, NULL, NULL)))
        throw std::runtime_error("Window Init");

    glfwMakeContextCurrent(_window);
}

void Application::mainloop()
{
    if (_window)
    {
        while (!glfwWindowShouldClose(_window))
            glfwPollEvents();
    }
}