# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("DJ_SNAKE")

# Include sub-projects.
add_subdirectory(libconfig)
add_subdirectory ("DJ_SNAKE")

