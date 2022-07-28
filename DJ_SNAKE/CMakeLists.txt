# CMakeList.txt : CMake project for DJ_SNAKE, include source and define
# project specific logic here.
#

cmake_minimum_required (VERSION 3.8)

include_directories("include" "src")

add_executable(
	DJSnake
	"src/DJ_SNAKE.cpp"
	"src/Methods.cpp"
	"src/Board.cpp"
	"src/Snake.cpp"
	
	"include/DJ_SNAKE.h"
	"include/Global.h"
	"include/Objects.h"
	"include/Methods.h"
	"include/Board.h"
	"include/Snake.h"
)
