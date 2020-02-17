# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

#[=======================================================================[.rst:
FindGLFW3
----------
JUST COPIED AND REWRITED FindVulkan.cmake


IMPORTED Targets
^^^^^^^^^^^^^^^^

This module defines :prop_tgt:`IMPORTED` target ``GLFW3::GLFW3``, if
GLFW3 has been found.

Result Variables
^^^^^^^^^^^^^^^^

This module defines the following variables::

  GLFW3_FOUND          - "True" if GLFW3 was found
  GLFW3_INCLUDE_DIRS   - include directories for GLFW3
  GLFW3_LIBRARIES      - link against this library to use GLFW3

The module will also define two cache variables::

  GLFW3_INCLUDE_DIR    - the GLFW3 include directory
  GLFW3_LIBRARY        - the path to the GLFW3 library

#]=======================================================================]


if(WIN32)
  find_path(GLFW3_INCLUDE_DIR
          NAMES GLFW/glfw3.h
          PATHS
          "$ENV{GLFW3x64}/include")

  if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    find_library(GLFW3_LIBRARY
            NAMES libglfw3
            PATHS
            "$ENV{GLFW3x64}/lib-mingw-w64")
  elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    find_library(GLFW3_LIBRARY
            NAMES libglfw3
            PATHS
            "$ENV{GLFW3x86}/lib-mingw-w64")
  endif()
else()
  message(GLFW3: Download libs for unix)
endif()


set(GLFW3_LIBRARIES ${GLFW3_LIBRARY})
set(GLFW3_INCLUDE_DIRS ${GLFW3_INCLUDE_DIR})

find_package(PackageHandleStandardArgs)

#include(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
find_package_handle_standard_args(GLFW3
  DEFAULT_MSG
        GLFW3_LIBRARY GLFW3_INCLUDE_DIR)

mark_as_advanced(GLFW3_INCLUDE_DIR GLFW3_LIBRARY)

if(GLFW3_FOUND AND NOT TARGET GLFW3::GLFW3)
  add_library(GLFW3::GLFW3 UNKNOWN IMPORTED)
  set_target_properties(GLFW3::GLFW3 PROPERTIES
    IMPORTED_LOCATION "${GLFW3_LIBRARIES}"
    INTERFACE_INCLUDE_DIRECTORIES "${GLFW3_INCLUDE_DIRS}")
endif()
