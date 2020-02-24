#include "ImageViewContainer.h"

ImageViewContainer::ImageViewContainer()
{}


ImageViewContainer::ImageViewContainer(const VkDevice &vkDevice, const std::vector<VkImage> &images, const VkFormat &format) :
        _vkDevice(vkDevice)
{
    _imageViews.resize(images.size());

    VkImageViewCreateInfo createInfo{
            VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
            nullptr,
            0,
            VK_NULL_HANDLE,
            VK_IMAGE_VIEW_TYPE_2D,
            format,
            {VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY},
            {VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1}
    };

    for (size_t i=0; i<images.size(); ++i)
    {
        createInfo.image = images[i];

        if (vkCreateImageView(_vkDevice, &createInfo, nullptr, &_imageViews[i]) != VK_SUCCESS)
            throw std::runtime_error("Vulkan: failed to create image views!");
    }
}


void ImageViewContainer::destroy()
{
    for (auto imageView : _imageViews)
        vkDestroyImageView(_vkDevice, imageView, nullptr);
}