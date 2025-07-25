cmake_minimum_required(VERSION 3.14)
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

# Link dependencies
# Find GLM or create an interface target for it
if(NOT TARGET glm::glm)
    find_package(glm QUIET)
    
    if(NOT glm_FOUND)
        # Create interface library if find_package fails
        add_library(glm INTERFACE)
        
        # Check if VULKAN_SDK environment variable is set
        if(DEFINED ENV{VULKAN_SDK})
            # Specify the include directory for GLM using Vulkan SDK path
            target_include_directories(glm INTERFACE "$ENV{VULKAN_SDK}/Include")
            target_compile_definitions(glm INTERFACE GLM_FORCE_DEPTH_ZERO_TO_ONE)
            add_library(glm::glm ALIAS glm)
        else()
            message(WARNING "VULKAN_SDK environment variable not set. GLM might not be found.")
        endif()
    endif()
endif()

# Link against GLM
target_link_libraries(velecs-math PUBLIC glm::glm)

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