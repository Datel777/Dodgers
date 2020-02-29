#pragma once

#include <vulkan/vulkan.h>

#include "Commons.h"

//  PFN_vkCreateDebugUtilsMessengerEXT func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(_instance, "vkCreateDebugUtilsMessengerEXT");
#define VULKAN_PFN_(FUNC_NAME, vkInstance)\
    PFN_##FUNC_NAME FUNC_NAME = (PFN_##FUNC_NAME)vkGetInstanceProcAddr(vkInstance, #FUNC_NAME)

namespace VH
{
    //need to wrap all *CreateInfo structs with helper functions, at least to avoid filling .sType
    inline VkApplicationInfo makeApplicationInfo(const char *applicationName, uint32_t applicationVersion)
    {
        return {
                VK_STRUCTURE_TYPE_APPLICATION_INFO,
                nullptr,
                applicationName,
                applicationVersion,
                "No Engine",
                VK_MAKE_VERSION(1, 0, 0),
                VK_API_VERSION_1_0
        };
    }

    //made reference not const to store data before call vkCreateShaderModule
    inline VkShaderModuleCreateInfo makeShaderModuleCreateInfo(std::vector<char> &shaderFileContent)
    {
        return {
                VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
                nullptr,
                0,
                shaderFileContent.size(),
                reinterpret_cast<const uint32_t*>(shaderFileContent.data())
        };
    }

    inline VkDebugUtilsMessengerCreateInfoEXT makeDebugInfo(PFN_vkDebugUtilsMessengerCallbackEXT debugCallback)
    {
        return VkDebugUtilsMessengerCreateInfoEXT {
                VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
                nullptr,
                0,
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
//                    VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
                    VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                    VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
                VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                    VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                    VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
                debugCallback,
                nullptr
        };
    }

}
