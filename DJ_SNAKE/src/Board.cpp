#include "Board.h"

Board::Board() {
    ClearBoard();
}

/*wchar_t* NewLine() {
    wchar_t returning[2];
    swprintf(returning, sizeof(returning), L"%lc%lc", _translator[CARRIAGE_RETURN], _translator[LINE_FEED]);
    return returning;
}*/

int Board::GetSetBoard(int x, int y, Prefabs object) {
    _matrix[x][y] = object;
    return (int)_matrix[x][y];
}

Prefabs Board::GetSetBoard(int x, int y)
{
    return _matrix[x][y];
}

int Board::PrintBoard() {
#pragma region WIN_ENV
    system("cls");
#pragma endregion
    //Top Border
    wprintf(L"%lc", _translator[BLANK]);
    for (int i = 0; i < GAME_WIDTH; i++)
        wprintf(L"%lc", _translator[BORDER_HORIZONTAL]);
    //L&R Borders w/Board
    for (int i = GAME_HEIGHT - 1; i >= 0; i--)
    {
        wprintf(L"\n%lc", _translator[BORDER_VERTICAL]);
        for (int j = GAME_WIDTH - 1; j >= 0; j--)
            wprintf(L"%lc", _translator[GetSetBoard(i, j)]);
        wprintf(L"%lc", _translator[BORDER_VERTICAL]);
    }
    //Bottom Border
    wprintf(L"\n%lc", _translator[BLANK]);
    for (int i = 0; i < GAME_WIDTH; i++)
        wprintf(L"%lc", _translator[BORDER_HORIZONTAL]);
    return 0;
}

int Board::ClearBoard(bool _print) {
    for (int i = 0; i < GAME_WIDTH; i++)
        for (int j = 0; j < GAME_HEIGHT; j++)
            GetSetBoard(i, j, BLANK);

    if (_print)
        return PrintBoard();
    return 0;
}