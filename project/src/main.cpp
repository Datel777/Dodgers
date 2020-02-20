#include <iostream>

#include "GLFW.h"
#include "Vulkan.h"

//using namespace std;

#define DEBUG(a) std::cout << #a << " = " << a << std::endl

int main()
{
    try {
        GLFW g;
        Vulkan v("Dodgers test", VK_MAKE_VERSION(1, 0, 0));
        Window w(400, 200, "Test");

//        uint32_t extensionCount = 0;
//        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
//        std::cout << extensionCount << " extensions supported" << std::endl;
//
//
//        VkExtensionProperties properties[extensionCount];
//        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, properties);
//
//        for(const VkExtensionProperties &p : properties)
//            std::cout << p.extensionName << std::endl;

        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
//        createInfo.enabledExtensionCount = glfwExtensionCount;
//        createInfo.ppEnabledExtensionNames = glfwExtensions;

        //NEED TO CHANGE CONCEPT OF CLASSES

        DEBUG(glfwExtensionCount);
        for (int i=0; i<glfwExtensionCount; ++i)
            DEBUG(glfwExtensions[i]);

        if (w.initialized())
        {
            g.setWindow(&w);

            while(g.looping())
                g.pollEvents();
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
