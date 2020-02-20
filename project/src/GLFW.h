#pragma once

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include "Window.h"

class GLFW
{
    bool _initialized = false;
    Window *_window = nullptr;
public:
    GLFW()
    {
        if (glfwInit())
            _initialized = true;
        else {
            _initialized = false;
            throw std::runtime_error("GLFW Init");
        }
    }

    ~GLFW()
    {
        std::cout << "~GLFW" << std::endl;
        if (_initialized)
            glfwTerminate();
    }

    inline bool initialized() const                               {return _initialized;}

    void setWindow(Window *window)
    {
        _window = window;
        glfwMakeContextCurrent(_window->glfwWindow());
    }

    inline bool looping() const     {return !glfwWindowShouldClose(_window->glfwWindow());}

    inline void pollEvents() const  {glfwPollEvents();}
};