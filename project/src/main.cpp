#include <iostream>

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"
#include "glm/vec2.hpp"

#include "test.h"

using namespace std;

int main()
{
    Test a(1,2);

    glm::vec2 v;

    if (!glfwInit())
        return -1;

    VkInstanceCreateInfo info{}; //initialize with zeros

    VkInstance instance;

    if (vkCreateInstance(&info, nullptr, &instance) == VK_SUCCESS)
    {
        cout << "SUCCESS!!!" << endl;
    } else {
        cout << "SOMETHING GOES WRONG" << endl;
    }

    GLFWwindow* window;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
//        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
//        glfwSwapBuffers(window);

        /* Poll for and process events */
//        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
}
