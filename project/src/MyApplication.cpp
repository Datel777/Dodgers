#include "MyApplication.h"


MyApplication::MyApplication()
{
    _window = createWindow(
            800,
            600, Core::applicationName,
            //Vulkan need GLFW's window to create context, so i made it invisible until init finished
            {{GLFW_RESIZABLE, GLFW_FALSE}, {GLFW_VISIBLE, GLFW_FALSE}});

    _surface = _window->createSurface();
}


void MyApplication::pickPhysicalDevice() {
    std::vector<PhysicalDevice> physicalDevices = PhysicalDevice::getAll();

    //make list of devices sorted by rating to choose best suitable device
    std::multimap<int, std::tuple<PhysicalDevice, PhysicalDeviceProperties>> ratedDevices;

    for (const PhysicalDevice &physicalDevice : physicalDevices) {
        PhysicalDeviceProperties properties{};

        if (isSuitable(physicalDevice, properties))
            ratedDevices.insert({getRating(physicalDevice), {physicalDevice, properties}});
    }

    //choosing the best one
    if (ratedDevices.size()) {
        const decltype(ratedDevices.rbegin()->second) &t {ratedDevices.rbegin()->second};

        _physicalDevice = std::get<0>(t);
        _physicalDeviceProperties = std::get<1>(t);

        return;
    }

    throw std::runtime_error("Vulkan: failed to find a suitable GPU!");
}


bool MyApplication::isSuitable(const PhysicalDevice &physicalDevice, PhysicalDeviceProperties &properties)
{
    return physicalDevice.type() == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
            physicalDevice.features().geometryShader &&
            physicalDevice.isSupportsExtensions() &&
            initQueueFamilies(physicalDevice, _surface, properties) &&
            querySwapChainSupport(physicalDevice, _surface, properties);
}


bool MyApplication::initQueueFamilies(const PhysicalDevice &physicalDevice, Surface *surface, PhysicalDeviceProperties &properties)
{
    std::vector<VkQueueFamilyProperties> queueFamilies {physicalDevice.getQueueFamilyProperties()};

    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;
    VkBool32 presentSupport;

    //for now i'll try to choose random families
    //but sometimes choosing same families could improve performance
    for (uint32_t i = 0; i<queueFamilies.size() && (!graphicsFamily.has_value() || !presentFamily.has_value()); ++i)
    {
        if (!graphicsFamily.has_value() && queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
            graphicsFamily = i;

        if (!presentFamily.has_value())
        {
            vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice.vkPhysicalDevice(), i, surface->vkSurface(), &presentSupport);

            if (presentSupport)
                presentFamily = i;
        }
    }

    if (graphicsFamily.has_value() && presentFamily.has_value())
    {
        properties.graphicsFamily = graphicsFamily.value();
        properties.presentFamily = presentFamily.value();

        return true;
    }

    return false;
}


bool MyApplication::querySwapChainSupport(const PhysicalDevice &physicalDevice, Surface *surface, PhysicalDeviceProperties &properties)
{
    std::vector<VkSurfaceFormatKHR> supportedFormats        {physicalDevice.getSupportedFormats(surface)};
    std::vector<VkPresentModeKHR> supportedPresentModes     {physicalDevice.getSupportedPresentModes(surface)};

    if (!(supportedFormats.size() && supportedPresentModes.size()))
        return false;

    properties.capabilities = physicalDevice.getCapabilities(surface);
    properties.format = chooseSwapSurfaceFormat(supportedFormats);
    properties.presentMode = chooseSwapPresentMode(supportedPresentModes);

    return true;
}


VkSurfaceFormatKHR MyApplication::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &formats)
{
    for (const VkSurfaceFormatKHR &availableFormat : formats)
        if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
            return availableFormat;

    return formats[0];
}


VkPresentModeKHR MyApplication::chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &presentModes)
{
    for (const VkPresentModeKHR &availablePresentMode : presentModes)
        if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
            return availablePresentMode;

    return VK_PRESENT_MODE_FIFO_KHR;
}


void MyApplication::mainloop()
{
    if (_window)
    {
        while (!_window->shouldClose())
            _window->pollEvents();
    }
}