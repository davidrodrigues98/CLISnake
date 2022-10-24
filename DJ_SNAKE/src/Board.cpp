#include "Board.h"

Board::Board() {
    _matrix = (enum Prefabs**)malloc(gGameRules.GAME_WIDTH * sizeof(enum Prefabs*));
    for (int i = 0; i < gGameRules.GAME_WIDTH; i++)
        _matrix[i] = (enum Prefabs*)malloc(gGameRules.GAME_HEIGHT * sizeof(enum Prefabs));

    ClearBoard();

    // RNG Setup
    std::random_device os_seed;
    const u32 seed = os_seed();
    engine generator(seed);
    _engine = &generator;

    SpawnApple();
   
}

int Board::GetSetBoard(int x, int y, Prefabs object) {
    _matrix[x][y] = object;
    return (int)_matrix[x][y];
}

Prefabs Board::GetSetBoard(int x, int y)
{
    return _matrix[x][y];
}

int Board::PrintBoard() {
    system("cls");
    //Top Border

    /*Size calculation goes as follows:
    * 7 -> All border corners and end of line null and the two required newliners.
    * GW x 2 + GH x 3 -> borders and newliners.
    * GW x GH -> board.
    */
    wchar_t* outputWrite = (wchar_t*)malloc((7 + (gGameRules.GAME_WIDTH * 2 + gGameRules.GAME_HEIGHT * 3) + (gGameRules.GAME_WIDTH * gGameRules.GAME_HEIGHT)) * sizeof(wchar_t));
    int index = 0;
    outputWrite[index++] = _translator[BORDER_TOP_LEFT];
    for (int i = 0; i < gGameRules.GAME_WIDTH; i++)
        outputWrite[index++] = _translator[BORDER_HORIZONTAL];
    outputWrite[index++] = _translator[BORDER_TOP_RIGHT];
    outputWrite[index++] = L'\n';
    //L&R Borders w/Board
    for (int i = gGameRules.GAME_HEIGHT - 1; i >= 0; i--)
    {
        outputWrite[index++] = _translator[BORDER_VERTICAL];
        for (int j = gGameRules.GAME_WIDTH - 1; j >= 0; j--)
            outputWrite[index++] = _translator[GetSetBoard(i, j)];
        outputWrite[index++] = _translator[BORDER_VERTICAL];
        outputWrite[index++] = L'\n';
    }
    //Bottom Border
    outputWrite[index++] = _translator[BORDER_BOTTOM_LEFT];
    for (int i = 0; i < gGameRules.GAME_WIDTH; i++)
        outputWrite[index++] = _translator[BORDER_HORIZONTAL];
    outputWrite[index++] = _translator[BORDER_BOTTOM_RIGHT];
    outputWrite[index++] = L'\n';

    //End of line.
    outputWrite[index++] = '\0';

    wprintf(L"%s", outputWrite);

    free(outputWrite);
    return 0;
}

int Board::ClearBoard(bool _print) {
    for (int i = 0; i < gGameRules.GAME_WIDTH; i++)
        for (int j = 0; j < gGameRules.GAME_HEIGHT; j++)
            GetSetBoard(i, j, BLANK);

    if (_print)
        return PrintBoard();
    return 0;
}

bool Board::SpawnAppleValidation(int _posX, int _posY) {
    if(_matrix[_posX][_posY] != SNAKE_BODY)
        return true;
    return false;
}

/*
 Spawn rules:
 Cannot be in the snake body.
 Randomly generate x,y coords.
*/
int Board::SpawnApple() {

    int posX = -1, posY = -1;

    do
    {
        std::uniform_int_distribution< u32 > distributeX(0, gGameRules.GAME_WIDTH - 1);
        posX = distributeX(*_engine);
        std::uniform_int_distribution< u32 > distributeY(0, gGameRules.GAME_HEIGHT - 1);
        posY = distributeY(*_engine); 
    } while (!SpawnAppleValidation(posX, posY));

    _matrix[posX][posY] = APPLE;

    return 0;
}
