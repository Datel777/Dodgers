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
