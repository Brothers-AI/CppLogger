# 
# @file BuildOptions.cmake
# @author Brothers.AI (brothers.ai.local@gmail.com)
# @brief Build options for Logger Building
# @version 0.1
# @date 2024-01-25
# 
# Options for Building Logger
cmake_minimum_required(VERSION 3.1)

# Build Options

# For Building Shared or Static Library
set(BUILD_SHARED_LIBS    ON                            CACHE BOOL   "Build shared libraries (.dll / .so)")
# For Building Examples for Logger
set(BUILD_EXAMPLES       OFF                           CACHE BOOL   "Build Examples")
# For Building for Release or Debug
set(CMAKE_BUILD_TYPE     "Release"                     CACHE STRING "Build Type")
# For Installing Logger to specific folder
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH   "Installation Directory")