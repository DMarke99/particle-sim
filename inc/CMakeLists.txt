# gets all hpp files in inc
FILE(GLOB ALL_INC_HPPS "${PROJECT_SOURCE_DIR}/inc/*.hpp")

add_library(inc ${ALL_INC_HPPS})

target_include_directories(inc PUBLIC "$(CMAKE_CURRENT_SOURCE_DIR)")