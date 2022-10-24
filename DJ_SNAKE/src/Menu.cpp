#include "Menu.h"

/// <summary>
/// Default constructor.
/// </summary>
Menu::Menu() {

}

wchar_t* Menu::MainMenu() {
	return L"CLISnake\nDeveloped by David Rodrigues\n\nGame Options:\n[1] Start Game\n[2] Import your board. (Not developed yet)\n[3] Quit\n\nSelect your option: ";
}

MenuOptions Menu::ParseMainMenuSelection(int _selectedOption) {

	switch (_selectedOption)
	{
		case 1:
			return STARTGAME;
			break;
		case 2:
			return INVALID; // Not yet developed.
			break;
		case 3:
			return QUIT;
			break;
		default:
			return INVALID;
			break;
	}
}