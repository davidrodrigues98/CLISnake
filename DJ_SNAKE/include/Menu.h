#pragma once
#include "Objects.h"

/// <summary>
/// Logic for all of the game menus. This are static interfaces.
/// </summary>
static class Menu {
private:
public:
	Menu();
	static wchar_t* MainMenu();
	static wchar_t* GameOverMenu();
	static MenuOptions ParseMainMenuSelection(char _selectedOption);

};

//DJ_SNAKE / src / Global.cpp