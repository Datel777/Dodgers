#pragma once

#include "GLFW/glfw3.h"

class Window
{
    bool _initialized = false;
    GLFWwindow* _window = nullptr;
public:
    int a = 0;

    Window(int width, int height, const char* title)
    {
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        if (_window = glfwCreateWindow(width, height, title, NULL, NULL))
            _initialized = true;
        else
            _initialized = false;
    }
    ~Window()
    {
        std::cout << "~Window" << std::endl;
        if (_initialized)
            glfwTerminate();
        glfwDestroyWindow(_window);
    }

    inline bool initialized() const         {return _initialized;}
    inline GLFWwindow* glfwWindow() const   {return _window;}
};