#include "Commons.h"

#ifndef NDEBUG
const char *Layers::required[] {
        "VK_LAYER_KHRONOS_validation"
};
const uint32_t Layers::count = static_cast<uint32_t>(sizeOfArray(required));
#endif

const char* DeviceExtensions::required[] {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
};
const uint32_t DeviceExtensions::count = static_cast<uint32_t>(sizeOfArray(required));


std::vector<char> readFile(const std::string& filename)
{
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open())
        throw std::runtime_error("App: failed to open file!");

    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);
    file.close();

    return buffer;
}
