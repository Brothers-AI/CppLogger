# 
# @file Settings.cmake
# @author Brothers.AI (brothers.ai.local@gmail.com)
# @brief Settings for Logger Building
# @version 0.1
# @date 2024-01-25
# 
cmake_minimum_required(VERSION 3.1)

# Project Structure

# Logger Directory
set(LOGGER_DIR          ${CMAKE_SOURCE_DIR}/Logger)
# Logger Examples Directory
set(LOGGER_EXAMPLES_DIR ${CMAKE_SOURCE_DIR}/Examples)

# Project Binary Directory
# Library Directory
set(PROJECT_LIBRARY_DIR      ${CMAKE_BINARY_DIR}/lib)
# Binary / Executable Directory
set(PROJECT_EXE_DIR          ${CMAKE_BINARY_DIR}/bin)
# Examples Executable Directory
set(PROJECT_EXAMPLES_EXE_DIR ${PROJECT_EXE_DIR}/Examples)