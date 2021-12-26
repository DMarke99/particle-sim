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
add_executable(main main.cpp)
target_include_directories(main PUBLIC "${PROJECT_SOURCE_DIR}/inc")
target_link_libraries(main PRIVATE src)
target_compile_features(main PRIVATE cxx_std_14)
