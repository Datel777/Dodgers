#pragma once

#include <vector>
#include <cstring>
#include <iostream>
#include <fstream>
#include <stdexcept>

#define DEBUG(a) std::cout << #a << " = " << a << std::endl

//just little helper to get size of array made by "type var[] {...};"
//template<class T, size_t N>
//constexpr size_t sizeOfArray(T (&)[N]) {return N;}

std::vector<char> readFile(const std::string &filename);
