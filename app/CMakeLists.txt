if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# adds compiler flags
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -flto")

# adds compile directory
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")

# compiles executable
add_executable(run_sim run_sim.cpp)
target_link_libraries(run_sim PRIVATE src)
target_compile_features(run_sim PRIVATE cxx_std_14)

add_executable(test test.cpp)
target_link_libraries(test PRIVATE src)
target_compile_features(test PRIVATE cxx_std_14)
