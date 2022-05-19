# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("DJ_SNAKE")

#set(CMAKE_PREFIX_PATH "C:\\dev\\vcpkg\\packages\\gainput_x86-windows\\share\\unofficial-gainput")

# Include sub-projects.
#add_subdirectory ("DJ_SNAKE")
find_package(unofficial-gainput CONFIG REQUIRED)

add_executable(DJSnake "DJ_SNAKE/DJ_SNAKE.cpp" "DJ_SNAKE/DJ_SNAKE.h" "DJ_SNAKE/Objects.h")

target_link_libraries(DJSnake PRIVATE unofficial::gainput::gainput)
