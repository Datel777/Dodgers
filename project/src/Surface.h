#pragma once

#include "Core.h"
#include "RecursiveDestroyer.h"

class Surface : public RecursiveDestroyer
{
public:
    Surface(GLFWwindow* window);
    ~Surface();

    inline const VkSurfaceKHR &vkSurface() const    {return _surface;}

private:
    VkSurfaceKHR _surface {VK_NULL_HANDLE};
};