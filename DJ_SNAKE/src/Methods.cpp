#include "Objects.h"

int ClearScreen() {
    system("cls");
    return 0;
}

// Initializes snake object.
Snake SpawnSnake(bool _print = false) {

    return (_print)?Snake(_print):Snake();
}

#pragma region Input Handling

#pragma region WIN_ENV
DWORD fdwMode, fdwOldMode;
#pragma endregion

// Executed when the event input handling system is fired. This function maps the virtual keys with the controls enum interface.
KeyBind KeyEventProc(KEY_EVENT_RECORD ker, Snake *___snake)
{
    KeyBind returnBind = ___snake->direction;
    WORD recordedKeyCode = ker.wVirtualKeyCode;

    // Virtual key mapping.
    switch (recordedKeyCode)
    {
        case 37: returnBind = LEFT; break;
        case 38: returnBind = UP;  break;
        case 39: returnBind = RIGHT; break;
        case 40: returnBind = DOWN; break;
    }
    
    return returnBind;
}

#pragma region WIN_ENV
// Executed every time the game cycle is up.
int win32_TimeStep(KeyBind &_nextMove, Snake *__snake, HANDLE _hStdIn, DWORD &_cNumRead, INPUT_RECORD (&_irInBuf)[N]) {

    switch (WaitForSingleObject(_hStdIn, GAME_SPEED_S * 1000)) {
        case WAIT_OBJECT_0:
            ReadConsoleInput(
                _hStdIn,
                _irInBuf,
                N, 
                &_cNumRead
            );
            if (_irInBuf[_cNumRead-1].Event.KeyEvent.bKeyDown)
                    _nextMove = KeyEventProc(_irInBuf[_cNumRead - 1].Event.KeyEvent, __snake);
            break;
        case WAIT_TIMEOUT:
            break;
    };

    return 0;
}
#pragma endregion

#pragma endregion

#pragma region Game Logic

// Executed when the game cycle is ended by the major flag.
int GameOver(Snake *_snake) {
    delete(_snake);
    return 0;
}

// After the initialization, the application is ready to start the game logics'n'loops.
int StartGame(Snake *_snake) {

#pragma region WIN_ENV
    HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD irInBuf[N];
    DWORD cNumRead;
    GetConsoleMode(hStdIn, &fdwOldMode);
    // disable mouse and window input
    fdwMode = ENABLE_INSERT_MODE || ENABLE_WINDOW_INPUT;
    SetConsoleMode(hStdIn, fdwMode);
#pragma endregion

    // Scoped misc variables and flags.
    bool endGame = false;
    Status gameStats;
    
    // The game cycle starts here. It only stops with the major flag condition.
    while (endGame == false) {
        KeyBind nextMove = _snake->direction; // The default input resets to the snake default/latest direction.

#pragma region WIN_ENV
        win32_TimeStep(nextMove, _snake, hStdIn, cNumRead, irInBuf);
        FlushConsoleInputBuffer(hStdIn);
#pragma endregion

        endGame = _snake->Move(nextMove); // This step processes the whole snake movement and game status.
    }
    
    // Redirecting to the game over screen.
    GameOver(_snake);
    return 0;
}

#pragma endregion


void Initialize()
{
    Snake newSnake = SpawnSnake(true);
    StartGame(&newSnake);
}