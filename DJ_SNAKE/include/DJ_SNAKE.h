// DJ_SNAKE.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#pragma region Libraries

//Default system libs.
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <queue>
#include <mutex>
#include <thread>
#include <queue>
#include <functional>
#include <tchar.h>
#include <map>
#include <fcntl.h>
#include <io.h>

#pragma region WIN_ENV
// Windows Debug
#include <Windows.h>
#include <windows.h>

int win_SetConsolePage();
#pragma endregion

#pragma region POSIX_ENV
#pragma endregion

#pragma endregion