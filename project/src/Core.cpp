#include "Core.h"

VkInstance Core::_vkInstance {VK_NULL_HANDLE};
bool Core::_exists = false;

#ifndef NDEBUG
//hardcoded layers
const std::vector<const char*> Core::requiredLayers {
        "VK_LAYER_KHRONOS_validation"
};

VkDebugUtilsMessengerEXT Core::_debugMessenger {VK_NULL_HANDLE};
#endif


Core::Core()
{
    //UNIQUE CHECKING
    if (_exists)
        throw std::runtime_error("Core: core is not unique");

    _exists = true;

    //GLFW
    if (!glfwInit())
        throw std::runtime_error("GLFW: Init error");

    //VULKAN
    VkApplicationInfo appInfo{VH::makeApplicationInfo(applicationName, applicationVersion)};

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    //EXTENSIONS
    std::vector<const char *> extensions;

    {//Getting extensions from GLFW
        uint32_t count;
        const char *const *names = glfwGetRequiredInstanceExtensions(&count);
        extensions = std::vector<const char *>(names, names + count);
    }

    //add debug extension
#ifndef NDEBUG
    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif
    //add requiredInstanceExtensions from main.cpp
    extensions.insert(extensions.end(), requiredInstanceExtensions.begin(), requiredInstanceExtensions.end());

    //checking is all extensions supported
    checkRequiredExtensions(extensions);

    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    //LAYERS
    //add layers only in debug mode
#ifndef NDEBUG
    checkRequiredLayers(requiredLayers);

    createInfo.enabledLayerCount = static_cast<uint32_t>(requiredLayers.size());
    createInfo.ppEnabledLayerNames = requiredLayers.data();

    //additional debug
    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo {VH::makeDebugInfo(debugCallback)};
    createInfo.pNext = &debugCreateInfo;
#endif

    if (vkCreateInstance(&createInfo, nullptr, &_vkInstance) != VK_SUCCESS)
        throw std::runtime_error("Vulkan: Init");

#ifndef NDEBUG
    setupDebugMessenger(&debugCreateInfo);
#endif
}


Core::~Core()
{
#ifndef NDEBUG
    if (_debugMessenger) {
        if (VULKAN_PFN_(vkDestroyDebugUtilsMessengerEXT, _vkInstance))
            vkDestroyDebugUtilsMessengerEXT(_vkInstance, _debugMessenger, nullptr);
        _debugMessenger = VK_NULL_HANDLE;
    }
#endif
    if (_vkInstance) {
        vkDestroyInstance(_vkInstance, nullptr);
        _vkInstance = VK_NULL_HANDLE;
    }

    glfwTerminate();
    _exists = false;
}


void Core::checkRequiredExtensions(const std::vector<const char*> &extensionNames)
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

//    get all supported extensions names for debug
//    for (const VkExtensionProperties &p : supportedExtensions)
//        std::cout << p.extensionName << std::endl;

    for (const char *extensionName : extensionNames)
    {
        notSupported = true;

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
void Core::checkRequiredLayers(const std::vector<const char*> &layerNames)
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

    for (const char *layerName : layerNames)
    {
        notSupported = true;

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


void Core::setupDebugMessenger(const VkDebugUtilsMessengerCreateInfoEXT *debugCreateInfo)
{
    VULKAN_PFN_(vkCreateDebugUtilsMessengerEXT, _vkInstance);

    if (!(vkCreateDebugUtilsMessengerEXT && (vkCreateDebugUtilsMessengerEXT(_vkInstance, debugCreateInfo, nullptr, &_debugMessenger) == VK_SUCCESS)))
        throw std::runtime_error("Vulkan: Set up debug messenger");
}


VKAPI_ATTR VkBool32 VKAPI_CALL Core::debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData)
{
    std::cerr << "validation layer [" << pCallbackData->pMessageIdName << "]: " << pCallbackData->pMessage << std::endl;
    return VK_FALSE;
}
#endif