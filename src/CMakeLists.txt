# gets all hpp files in inc
FILE(GLOB ALL_HPPS "${PROJECT_SOURCE_DIR}/inc/*.hpp")

# includes all headers
set(HEADER_LIST ALL_HPPS)

# gets all cpp files in src
FILE(GLOB ALL_CPPS "${PROJECT_SOURCE_DIR}/src/*.cpp")

# creates source library
add_library(src ${ALL_CPPS})

# gets include paths
target_include_directories(src PUBLIC ../inc)

# links SDL to my library
target_link_libraries(src PRIVATE ${SDL2_LIBRARIES})

# sets c++ version
target_compile_features(src PUBLIC cxx_std_14)
