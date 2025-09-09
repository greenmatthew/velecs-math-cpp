cmake_minimum_required(VERSION 3.14)

# Check if VCPKG_ROOT is set
if(NOT DEFINED ENV{VCPKG_ROOT})
    message(FATAL_ERROR "VCPKG_ROOT environment variable not set. Please install vcpkg and set VCPKG_ROOT.")
endif()

project(velecs-math VERSION 0.1.0)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set output directories to bin if its the cmake build source
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    # Only set output directories when building this library standalone
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
endif()

# Option to control whether to build the test executable
option(VELECS_MATH_BUILD_TESTS "Build test executable for velecs-math" OFF)

# Source files for the library
set(LIB_SOURCES
    src/Vec2.cpp
    src/Vec3.cpp
    src/Vec4.cpp
    src/Mat4.cpp
    src/Quat.cpp
)

# Always build the library
add_library(velecs-math ${LIB_SOURCES})
target_include_directories(velecs-math 
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Find and link GLM using vcpkg
find_package(glm CONFIG REQUIRED)
target_link_libraries(velecs-math PUBLIC glm::glm)

# Set GLM compile definitions for Vulkan compatibility
target_compile_definitions(velecs-math PUBLIC GLM_FORCE_DEPTH_ZERO_TO_ONE)

# Installation rules for the library
install(TARGETS velecs-math
    EXPORT velecs-math-targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)
install(DIRECTORY include/ DESTINATION include)

# Conditionally build the test executable
if(VELECS_MATH_BUILD_TESTS)
    add_executable(velecs-math-test src/test/main.cpp)
    target_link_libraries(velecs-math-test PRIVATE velecs-math)
endif()
