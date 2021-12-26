# sets up CMake project
cmake_minimum_required(VERSION 3.0.0)
project(particle-sim VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# adds libraries
add_subdirectory(src)

add_subdirectory(app)