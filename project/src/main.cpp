#include <iostream>

#include "Application.h"


//using namespace std;

#define DEBUG(a) std::cout << #a << " = " << a << std::endl

int main()
{
    try {
        Application application("Dodgers test", VK_MAKE_VERSION(1, 0, 0));
        application.initWindow(800, 600, "Dodgers test");
        application.mainloop();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
