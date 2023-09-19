#include "Board.h"

/*Size calculation goes as follows:
* 7 -> All border corners and end of line null and the two required newliners.
* 11 -> Top Score Border
* 11 -> Score + Border
* 11 -> Bottom Score Border
* GW x 2 + GH x 3 -> borders and newliners.
* GW x GH -> board.
*/
wchar_t* gOutputWrite;

Board::Board() {
    _matrix = (enum Prefabs**)malloc(gGameRules.GAME_WIDTH * sizeof(enum Prefabs*));
    for (int i = 0; i < gGameRules.GAME_WIDTH; i++)
        _matrix[i] = (enum Prefabs*)malloc(gGameRules.GAME_HEIGHT * sizeof(enum Prefabs));

    gOutputWrite = (wchar_t*)malloc((7 + 11 + 11 + 11 + (gGameRules.GAME_WIDTH * 2 + gGameRules.GAME_HEIGHT * 3) + (gGameRules.GAME_WIDTH * gGameRules.GAME_HEIGHT)) * sizeof(wchar_t));

    ClearBoard();

    // RNG Setup
    std::mt19937 generator(time(NULL));
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

int Board::PrintBoard(int _score = 0) {
    system("cls");
    
    // Prepare score format.
    wchar_t scoreContent[SCOREAREA+1];
    std::wstring score_str = L"Score:";
    std::wstringstream numberpad;
    numberpad << std::setfill(L'0') << std::setw(4) << std::to_wstring(_score);
    score_str += numberpad.str();
    wcscpy(scoreContent, score_str.c_str());

    int index = 0;
    // Top Border
    gOutputWrite[index++] = _translator[BORDER_TOP_LEFT];
    for (int i = 0; i < gGameRules.GAME_WIDTH + SCOREAREA + 1; i++)
        gOutputWrite[index++] = _translator[BORDER_HORIZONTAL];
    gOutputWrite[index++] = _translator[BORDER_TOP_RIGHT];
    gOutputWrite[index++] = L'\n';
    // L&R Borders w/Board
    for (int i = gGameRules.GAME_HEIGHT - 1; i >= 0; i--)
    {
        gOutputWrite[index++] = _translator[BORDER_VERTICAL];
        for (int j = gGameRules.GAME_WIDTH - 1; j >= 0; j--)
            gOutputWrite[index++] = _translator[GetSetBoard(i, j)];
        gOutputWrite[index++] = _translator[BORDER_VERTICAL];
        if (i == gGameRules.GAME_HEIGHT - 1) {
            for (int k = 0; k < SCOREAREA; k++)
                gOutputWrite[index++] = scoreContent[k];
            gOutputWrite[index++] = _translator[BORDER_VERTICAL];
        }
        else
            if (i == gGameRules.GAME_HEIGHT - 2) {
                for (int l = 0; l < SCOREAREA; l++)
                    gOutputWrite[index++] = _translator[BORDER_HORIZONTAL];
                gOutputWrite[index++] = _translator[BORDER_BOTTOM_RIGHT];
            }
        gOutputWrite[index++] = L'\n';
    }
    // Bottom Border
    gOutputWrite[index++] = _translator[BORDER_BOTTOM_LEFT];
    for (int i = 0; i < gGameRules.GAME_WIDTH; i++)
        gOutputWrite[index++] = _translator[BORDER_HORIZONTAL];
    gOutputWrite[index++] = _translator[BORDER_BOTTOM_RIGHT];
    gOutputWrite[index++] = L'\n';
    // End of line.
    gOutputWrite[index++] = '\0';

    wprintf(L"%s", gOutputWrite);

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
        std::uniform_int_distribution<int> distributeX(0, gGameRules.GAME_WIDTH - 1);
        posX = distributeX(*_engine);
        std::uniform_int_distribution<int> distributeY(0, gGameRules.GAME_HEIGHT - 1);
        posY = distributeY(*_engine); 
    } while (!SpawnAppleValidation(posX, posY));

    _matrix[posX][posY] = APPLE;

    return 0;
}
