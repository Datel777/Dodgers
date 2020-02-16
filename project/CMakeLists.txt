cmake_minimum_required(VERSION 3.5)

set(TARGET Dodgers)
set(SRC src)

project(${TARGET} LANGUAGES CXX)
SET(CMAKE_EXE_LINKER_FLAGS "-static")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${TARGET} ${SRC}/main.cpp)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/Modules/")


find_package(Vulkan REQUIRED)
find_package(GLFW3 REQUIRED)

#target_compile_definitions(${TARGET} PRIVATE VK_USE_PLATFORM_WIN32_KHR)

target_include_directories(${TARGET} PRIVATE Vulkan::Vulkan)
target_link_libraries(${TARGET} PRIVATE Vulkan::Vulkan)

target_include_directories(${TARGET} PRIVATE GLFW3::GLFW3)
target_link_libraries(${TARGET} PRIVATE GLFW3::GLFW3)