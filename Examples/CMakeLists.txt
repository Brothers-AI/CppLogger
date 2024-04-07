# 
# @file CMakeLists.txt
# @author Brothers.AI (brothers.ai.local@gmail.com)
# @brief CMake for Logger test app
# @version 0.1
# @date 2024-01-25
# 
cmake_minimum_required(VERSION 3.1)

# Setting Cmake
include(${CMAKE_SOURCE_DIR}/cmake/Settings.cmake)

# Project
project(ExamplesCppLogger)

# Executable name
set(EXE_NAME testLogger)

# Create Directory
file(MAKE_DIRECTORY ${PROJECT_EXAMPLES_EXE_DIR})

# Set Runtime Directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_EXAMPLES_EXE_DIR})

# Include Folders for test
include_directories(
    ${LOGGER_DIR}/include
)

# Directories where the Library is present
link_directories(
    ${PROJECT_LIBRARY_DIR}/
)

# Create Executable
add_executable(
    ${EXE_NAME}
    ${LOGGER_EXAMPLES_DIR}/src/testLogger.cpp
)

# Linking Libraries
target_link_libraries(
    ${EXE_NAME}
    CppLogger
)

if(${BUILD_SHARED_LIBS})
    # Copy the DLL to Executable folder
    if(WIN32)
        add_custom_command(
            TARGET ${EXE_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${PROJECT_LIBRARY_DIR}/${CMAKE_BUILD_TYPE}/CppLogger.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}
        )
    endif(WIN32)
endif()

# Copy Binary to install directory
install(DIRECTORY ${PROJECT_EXAMPLES_EXE_DIR} DESTINATION ${CMAKE_INSTALL_PREFIX})