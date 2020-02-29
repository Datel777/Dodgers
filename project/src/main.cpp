#include <iostream>

#include "Core.h"
#include "MyApplication.h"


//for all classes would be better to use common variables (stack) not with "classname *a = new classname()" (heap)
//this thing can increase performance of program

//also better to use inline for little functions

//Initialization here
const char *    Core::applicationName {"Dodgers test"};
const uint32_t  Core::applicationVersion {VK_MAKE_VERSION(1, 0, 0)};

const std::vector<const char*> Core::requiredInstanceExtensions;
const std::vector<const char*> Core::requiredDeviceExtensions {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
};



int main()
{
    try {
        Core core;
        MyApplication application;
//        application.mainloop();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
