# sets up CMake project
cmake_minimum_required(VERSION 3.0.0)
project(particle-sim VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# adds libraries
add_subdirectory(src)
add_subdirectory(app)