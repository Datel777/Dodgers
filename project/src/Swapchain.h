#pragma once

#include <vector>

#include "vulkan/vulkan.h"

#include "ImageViewContainer.h"


class Swapchain
{
public:
    Swapchain();
    Swapchain(const VkDevice &vkDevice,
              const VkSwapchainKHR &vkSwapchain,
              uint32_t imageCount,
              const VkFormat &format,
              const VkExtent2D &_extend);


    void destroy();

//    inline const VkSwapchainKHR &vkSwapchain() const      {return _vkSwapchain;}

    ImageViewContainer createImageViews();

    VkPipelineLayout createGraphicsPipelineLayout(const VkShaderModule &shaderModuleVertex, const VkShaderModule &shaderModuleFragment);

private:
    VkDevice _vkDevice = VK_NULL_HANDLE;
    VkSwapchainKHR _vkSwapchain = VK_NULL_HANDLE;

    uint32_t _imageCount;
    VkFormat _format;
    VkExtent2D _extent;
};
