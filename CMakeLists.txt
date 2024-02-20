# 
# @file CMakeLists.txt
# @author Brothers.AI (brothers.ai.local@gmail.com)
# @brief CMake for Logger Library
# @version 0.1
# @date 2024-01-25
# 
cmake_minimum_required(VERSION 3.1)

# Settings Cmake
include(${CMAKE_SOURCE_DIR}/cmake/Settings.cmake)

# Project
project(CustomCppLogger)

# Build Option CMake
include(${CMAKE_SOURCE_DIR}/cmake/BuildOptions.cmake)

# Info
message(STATUS "Logger Directory -> ${LOGGER_DIR}")
message(STATUS "Logger Examples Directory -> ${LOGGER_EXAMPLES_DIR}")
message(STATUS "Install to -> ${CMAKE_INSTALL_PREFIX}")

# Building Library
add_subdirectory(${LOGGER_DIR})

# Building Examples
if(${BUILD_EXAMPLES})
    message(STATUS "Building Examples")
    add_subdirectory(${LOGGER_EXAMPLES_DIR})
endif()
