#include "Swapchain.h"

Swapchain::Swapchain()
{}


Swapchain::Swapchain(const VkDevice &vkDevice,
        const VkSwapchainKHR &vkSwapchain,
        uint32_t imageCount,
        const VkFormat &format,
        const VkExtent2D &extent) :
        _vkDevice(vkDevice),
        _vkSwapchain(vkSwapchain),
        _imageCount(imageCount),
        _format(format),
        _extent(extent)
{}


void Swapchain::destroy()
{
    if (_vkSwapchain != VK_NULL_HANDLE)
        vkDestroySwapchainKHR(_vkDevice, _vkSwapchain, nullptr);
}


ImageViewContainer Swapchain::createImageViews()
{
    //why we should get imageCount if we already create swapchain with that value?
//    uint32_t imageCount;
//    vkGetSwapchainImagesKHR(_vkDevice, _vkSwapchain, &imageCount, nullptr);
    std::vector<VkImage> images(_imageCount);
    vkGetSwapchainImagesKHR(_vkDevice, _vkSwapchain, &_imageCount, images.data());

    return ImageViewContainer(_vkDevice, images, _format);
}