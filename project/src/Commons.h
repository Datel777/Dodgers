#pragma once

#include <vulkan/vulkan.h>

#include <vector>
#include <fstream>

//just little helper to get size of array made by "type var[] {...};"
template<class T, size_t N>
constexpr size_t sizeOfArray(T (&)[N]) {return N;}

std::vector<char> readFile(const std::string &filename);


//  PFN_vkCreateDebugUtilsMessengerEXT func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(_instance, "vkCreateDebugUtilsMessengerEXT");
#define VULKAN_PFN_(FUNC_NAME)\
    PFN_##FUNC_NAME FUNC_NAME = (PFN_##FUNC_NAME)vkGetInstanceProcAddr(_instance, #FUNC_NAME)



#ifndef NDEBUG
//like namespace but namespace did not work
class Layers
{
public:
    static const char *required[];
    static const uint32_t count;
};
#endif

class DeviceExtensions
{
public:
    static const char* required[];
    static const uint32_t count;
};
