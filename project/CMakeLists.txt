cmake_minimum_required(VERSION 3.5)

set(TARGET Dodgers)
set(SRC src)

project(${TARGET}
        VERSION 0.1
        DESCRIPTION "Test project to make arcade game"
        LANGUAGES CXX)

SET(CMAKE_EXE_LINKER_FLAGS "-static")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADERS
    ${SRC}/Application.h)

set(SOURCES
        ${SRC}/Application.cpp
        ${SRC}/main.cpp)

add_executable(${TARGET} ${HEADERS} ${SOURCES})

#if(WIN32)
#    target_link_options(${TARGET} PRIVATE -mwindows) #remove console and all "std::cout <<" debugging
#endif()

#----Modules----
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

#Vulkan
find_package(Vulkan REQUIRED)
#target_compile_definitions(${TARGET} PRIVATE VK_USE_PLATFORM_WIN32_KHR)
#target_include_directories(${TARGET} PRIVATE Vulkan::Vulkan)
target_link_libraries(${TARGET} PRIVATE Vulkan::Vulkan)

#GLFW3
find_package(GLFW3 REQUIRED)
#target_include_directories(${TARGET} PRIVATE GLFW3::GLFW3)
target_link_libraries(${TARGET} PRIVATE GLFW3::GLFW3)

#GLM
find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})
