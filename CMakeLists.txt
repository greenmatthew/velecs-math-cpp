cmake_minimum_required(VERSION 3.14)
project(velecs-math VERSION 0.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Option to control whether to build the test executable
option(VELECS_MATH_BUILD_TESTS "Build test executable for velecs-math" OFF)

# Source files for the library
set(LIB_SOURCES
    src/vec2.cpp
    src/vec3.cpp
)

# Always build the library
add_library(velecs-math ${LIB_SOURCES})
target_include_directories(velecs-math 
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# # Link dependencies
# find_package(glm REQUIRED)
# target_link_libraries(velecs-math PUBLIC glm::glm)

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