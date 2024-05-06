# 
# @file CMakeLists.txt
# @author Brothers.AI (brothers.ai.local@gmail.com)
# @brief CMake for Logger Library
# @version 0.1
# @date 2024-01-25
# 
cmake_minimum_required(VERSION 3.1)

# Project
project(CppLogger)

# Build Options

# For Building Shared or Static Library
set(BUILD_SHARED_LIBS    ON                            CACHE BOOL   "Build shared libraries (.dll / .so)")
# For Building Examples for Logger
set(BUILD_EXAMPLES       OFF                           CACHE BOOL   "Build Examples")
# For Building for Release or Debug
set(CMAKE_BUILD_TYPE     "Release"                     CACHE STRING "Build Type")
# For Installing Logger to specific folder
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH   "Installation Directory")

# Logger Directory
set(LOGGER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Logger)
# Logger Examples Directory
set(LOGGER_EXAMPLES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Examples)

# Project Binary Directory
# Library Directory
set(PROJECT_LIBRARY_DIR      ${CMAKE_CURRENT_BINARY_DIR}/lib)
# Binary / Executable Directory
set(PROJECT_EXE_DIR          ${CMAKE_CURRENT_BINARY_DIR}/bin)
# Examples executable directory
set(PROJECT_EXAMPLES_EXE_DIR ${PROJECT_EXE_DIR}/Examples)

# Build Flags for Windows MSVC Compiler
if (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /wd4710 /wd4711 /wd4774 /wd4820 /wd4996") 
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /wd4571 /wd4625 /wd4626 /wd5026 /wd5027 /wd5039") 
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4710 /wd4711 /wd4774 /wd4820 /wd4996") 
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4571 /wd4625 /wd4626 /wd5026 /wd5027 /wd5039") 
endif()

# Info
message(STATUS "Logger Directory -> ${LOGGER_DIR}")
message(STATUS "Logger Examples Directory -> ${LOGGER_EXAMPLES_DIR}")
message(STATUS "Install to -> ${CMAKE_INSTALL_PREFIX}")

# Build Library
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_LIBRARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_LIBRARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_LIBRARY_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Include folders for CppLogger
include_directories(
    ${LOGGER_DIR}/include
)

# Set the Source files for CppLogger
set(SRC_FILES
    ${LOGGER_DIR}/src/CppLogger.cpp
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

    # For Static Library (If this library needs to link to any shared library)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)

    add_library(
        ${PROJECT_NAME} STATIC
        ${SRC_FILES}
    )
endif()

# Building Examples
if(${BUILD_EXAMPLES})
    message(STATUS "Building Examples")

    # Executable name
    set(EXE_NAME testLogger)

    # Set Runtime Directory
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_EXAMPLES_EXE_DIR})

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
    install(DIRECTORY ${PROJECT_EXE_DIR} DESTINATION ${CMAKE_INSTALL_PREFIX})
endif()

# Copy Include folder to install directory
install(DIRECTORY ${LOGGER_DIR}/include DESTINATION ${CMAKE_INSTALL_PREFIX}/)

# Copy lib folder to install directory
install(DIRECTORY ${PROJECT_LIBRARY_DIR} DESTINATION ${CMAKE_INSTALL_PREFIX})
