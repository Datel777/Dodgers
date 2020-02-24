#include "Application.h"


Application::Application(const char *applicationName, uint32_t version, int width, int height)
{
    initGLFW(width, height, applicationName);
    initVulkan(applicationName, version);
    createSurface();
    _device = Device(pickPhysicalDevice());
    _swapchain = _device.createSwapChain(width, height, _surface);
    _imageViewContainer = _swapchain.createImageViews();
}


Application::~Application()
{
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


void Application::mainloop()
{
    if (_window)
    {
        while (!glfwWindowShouldClose(_window))
            glfwPollEvents();
    }
}


void Application::initGLFW(int width, int height, const char* title)
{
    if (!glfwInit())
        throw std::runtime_error("GLFW: Init");

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    //Vulkan need GLFW's window to create context
    //so, i made it invisible until init finished
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    if (!(_window = glfwCreateWindow(width, height, title, NULL, NULL)))
        throw std::runtime_error("Window: Init");

    glfwMakeContextCurrent(_window);
}


void Application::initVulkan(const char *applicationName, uint32_t applicationVersion)
{
    VkApplicationInfo appInfo{
            VK_STRUCTURE_TYPE_APPLICATION_INFO,
            nullptr,
            applicationName,
            applicationVersion,
            "No Engine",
            VK_MAKE_VERSION(1, 0, 0),
            VK_API_VERSION_1_0
    };

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

//EXTENSIONS
    //get required extensions for GLFW
    //just to do not create additional variables
    createInfo.ppEnabledExtensionNames = glfwGetRequiredInstanceExtensions(&createInfo.enabledExtensionCount);

    //fill GLFW required extensions
    std::vector<const char*> requiredExtensions(createInfo.ppEnabledExtensionNames,
            createInfo.ppEnabledExtensionNames + createInfo.enabledExtensionCount);

    //add debug extension
#ifndef NDEBUG
    requiredExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif

    //here should be other extensions with "requiredExtensions.push_back(...);"

    getRequiredExtensions(static_cast<uint32_t>(requiredExtensions.size()), requiredExtensions.data());

    createInfo.enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size());
    createInfo.ppEnabledExtensionNames = requiredExtensions.data();

//LAYERS
    //add layers only in debug mode
#ifndef NDEBUG
    //write required layers directly into instanceInfo
    createInfo.enabledLayerCount = Layers::count;
    createInfo.ppEnabledLayerNames = Layers::required;

    getRequiredLayers(createInfo.enabledLayerCount, createInfo.ppEnabledLayerNames);

    //additional debug
    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = createDebugInfo();
    createInfo.pNext = &debugCreateInfo;
#endif

    if (vkCreateInstance(&createInfo, nullptr, &_instance) != VK_SUCCESS)
        throw std::runtime_error("Vulkan: Init");

#ifndef NDEBUG
    setupDebugMessenger(&debugCreateInfo);
#endif
}


void Application::getRequiredExtensions(const uint32_t &count, const char* const* names)
{
    //get Vulkan supported extensions count
    uint32_t extensionCount;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    //get Vulkan supported extensions
    std::vector<VkExtensionProperties> supportedExtensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, supportedExtensions.data());

    //starting to check is Vulkan supports all extensions from GLFW
    std::vector<const char*> notSupportedExtensionsNames;
    bool notSupported;
    const char *extensionName;

//    get all supported extensions names for debug
//    for (const VkExtensionProperties &p : supportedExtensions)
//        std::cout << p.extensionName << std::endl;

    for (int i=0; i<count; ++i)
    {
        notSupported = true;
        extensionName = names[i];

        for (const VkExtensionProperties &p : supportedExtensions)
            if (std::strcmp(extensionName, p.extensionName) == 0)
            {
                notSupported = false;
                break;
            }

        if (notSupported)
            notSupportedExtensionsNames.push_back(extensionName);
    }

    //if something not supported throw exception
    if (notSupportedExtensionsNames.size())
    {
        std::string str{"Vulkan: Not supported extensions:"};

        for (const char *name : notSupportedExtensionsNames)
        {
            str += "\n\t";
            str += name;
        }

        throw std::runtime_error(str);
    }
}

#ifndef NDEBUG
void Application::getRequiredLayers(const uint32_t &count, const char* const* &names)
{
    //get Vulkan supported layers count
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    //get Vulkan supported layers
    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    //starting to check is Vulkan supports all required layers
    std::vector<const char*> notSupportedLayersNames;
    bool notSupported;
    const char *layerName;

    for (int i=0; i<count; ++i)
    {
        notSupported = true;
        layerName = names[i];

        for (const VkLayerProperties &p : availableLayers)
            if (strcmp(layerName, p.layerName) == 0)
            {
                notSupported = false;
                break;
            }

        if (notSupported)
            notSupportedLayersNames.push_back(layerName);
    }

    //if something not supported throw exception
    if (notSupportedLayersNames.size())
    {
        std::string str{"Vulkan: Not supported layers:"};

        for (const char *name : notSupportedLayersNames)
        {
            str += "\n\t";
            str += name;
        }

        throw std::runtime_error(str);
    }
}


void Application::setupDebugMessenger(const VkDebugUtilsMessengerCreateInfoEXT *debugCreateInfo)
{
    VULKAN_PFN_(vkCreateDebugUtilsMessengerEXT);

    if (!(vkCreateDebugUtilsMessengerEXT && (vkCreateDebugUtilsMessengerEXT(_instance, debugCreateInfo, nullptr, &_debugMessenger) == VK_SUCCESS)))
        throw std::runtime_error("Vulkan: Set up debug messenger");
}


VkDebugUtilsMessengerCreateInfoEXT Application::createDebugInfo()
{
    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
    debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    debugCreateInfo.messageSeverity =
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
//            VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    debugCreateInfo.messageType =
            VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    debugCreateInfo.pfnUserCallback = debugCallback;
    debugCreateInfo.pUserData = nullptr; // Optional

    return debugCreateInfo;
}


VKAPI_ATTR VkBool32 VKAPI_CALL Application::debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData)
{
    std::cerr << "validation layer [" << pCallbackData->pMessageIdName << "]: " << pCallbackData->pMessage << std::endl;
    return VK_FALSE;
}
#endif


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

