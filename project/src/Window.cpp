#include "Window.h"

Window::Window(int width, int height, const char* title, const std::initializer_list<std::pair<int,int>> &hints)
{
    glfwDefaultWindowHints();

    //default no API, because we are using Vulkan's API
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    for (const std::pair<int,int> &p : hints)
        glfwWindowHint(p.first, p.second);

    if (!(_glfwWindow = glfwCreateWindow(width, height, title, NULL, NULL)))
        throw std::runtime_error("Window: Init");
}


Window::~Window()
{
    if (_glfwWindow)
        glfwDestroyWindow(_glfwWindow);
}


Surface *Window::createSurface()
{
    Surface *s = new Surface(_glfwWindow);
    addToDestroy(s);
    return s;
}