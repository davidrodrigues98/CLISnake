# CMakeList.txt : CMake project for DJ_SNAKE, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

include_directories("include" "src")

find_package(unofficial-gainput CONFIG REQUIRED)

add_executable(
	DJSnake
	"src/DJ_SNAKE.cpp"
	"src/Methods.cpp"
	"include/DJ_SNAKE.h"
	"include/Global.h"
	"include/Objects.h"
	"include/Methods.h"
)

target_link_libraries(DJSnake PRIVATE unofficial::gainput::gainput)