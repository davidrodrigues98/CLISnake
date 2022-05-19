# CMakeList.txt : CMake project for DJ_SNAKE, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (DJ_SNAKE "DJ_SNAKE.cpp" "DJ_SNAKE.h")

# TODO: Add tests and install targets if needed.
find_package(unofficial-gainput CONFIG REQUIRED)
target_link_libraries(DJ_SNAKE PRIVATE unofficial::gainput::gainput)