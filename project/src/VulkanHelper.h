#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace VH
{
    //need to wrap all *CreateInfo structs with helper functions, at least to avoid filling .sType

    inline VkShaderModuleCreateInfo makeShaderModuleCreateInfo(const std::vector<char> &shaderFileContent)
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
