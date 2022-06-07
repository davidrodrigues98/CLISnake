# CMakeList.txt : CMake project for DJ_SNAKE, include source and define
# project specific logic here.
#

cmake_minimum_required (VERSION 3.8)

include_directories("include" "src")

add_executable(
	DJSnake
	"src/DJ_SNAKE.cpp"
	"src/Methods.cpp"
	"include/DJ_SNAKE.h"
	"include/Global.h"
	"include/Objects.h"
	"include/Methods.h"
)
