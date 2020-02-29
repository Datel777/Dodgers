#include "Surface.h"

Surface::Surface(GLFWwindow* window)
{
    if (glfwCreateWindowSurface(Core::vkInstance(), window, nullptr, &_surface) != VK_SUCCESS)
        throw std::runtime_error("Surface: constructor error");
}


Surface::~Surface()
{
    if (_surface)
        vkDestroySurfaceKHR(Core::vkInstance(), _surface, nullptr);
}