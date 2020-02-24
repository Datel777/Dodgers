#pragma once

#include <vector>
#include <stdexcept>

#include "vulkan/vulkan.h"

class ImageViewContainer
{
public:
    ImageViewContainer();
    ImageViewContainer(const VkDevice &vkDevice, const std::vector<VkImage> &images, const VkFormat &format);

    void destroy();
private:
    VkDevice _vkDevice = VK_NULL_HANDLE;

    std::vector<VkImageView> _imageViews;
};