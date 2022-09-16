// DJ_SNAKE.cpp : Defines the entry point for the application.

#include "../include/Objects.h"
#include "../include/Methods.h"

int main()
{

	_setmode(_fileno(stdout), _O_U8TEXT);
	ReadConfig();
	Initialize();
	return 0;
}
