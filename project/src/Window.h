#pragma once

#include <initializer_list>
#include <utility>
#include "GLFW/glfw3.h"

#include "RecursiveDestroyer.h"
#include "Surface.h"


class Window : public RecursiveDestroyer
{
public:
    Window(int width, int height, const char* title, const std::initializer_list<std::pair<int,int>> &hints = {});
    ~Window();

    inline void show() const        {glfwShowWindow(_glfwWindow);}
    inline void hide() const        {glfwHideWindow(_glfwWindow);}
    inline void makeCurrent() const {glfwMakeContextCurrent(_glfwWindow);}
    inline bool shouldClose() const {return glfwWindowShouldClose(_glfwWindow);}
    inline void pollEvents() const  {glfwPollEvents();}

    Surface *createSurface();

private:
    GLFWwindow* _glfwWindow = nullptr;
};
