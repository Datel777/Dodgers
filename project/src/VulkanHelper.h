#pragma once

#include <vulkan/vulkan.h>
#include <vector>

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

}
