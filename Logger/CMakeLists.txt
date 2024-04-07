# 
# @file CMakeLists.txt
# @author Brothers.AI (brothers.ai.local@gmail.com)
# @brief CMake for Logger Library
# @version 0.1
# @date 2024-01-25
# 
cmake_minimum_required(VERSION 3.1)

# Settings CMake
include(${CMAKE_SOURCE_DIR}/cmake/Settings.cmake)

# Set the Project Name
project(CppLogger)

# Build Options
include(${CMAKE_SOURCE_DIR}/cmake/BuildOptions.cmake)

# Set Library, Archive and Runtime Output Directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_LIBRARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_LIBRARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_LIBRARY_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Include folders for CppLogger
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Set the Source files for CppLogger
set(SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CppLogger.cpp
)

# Building Shared or Static Library
if(${BUILD_SHARED_LIBS})
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    message(STATUS "Building Shared Library")
    add_library(
        ${PROJECT_NAME} SHARED
        ${SRC_FILES}
    )
else()
    message(STATUS "Building Static Library")
    add_library(
        ${PROJECT_NAME} STATIC
        ${SRC_FILES}
    )
endif()

# Copy Include folder to install directory
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include DESTINATION ${CMAKE_INSTALL_PREFIX}/)

# Copy lib folder to install directory
install(DIRECTORY ${PROJECT_LIBRARY_DIR} DESTINATION ${CMAKE_INSTALL_PREFIX})