#include "Snake.h"
#include "Menu.h"


// Initializes snake object.
Snake SpawnSnake(bool _print = false) {

    return (_print)?Snake(_print):Snake();
}

#pragma region Input Handling

DWORD fdwMode, fdwOldMode;


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


// Executed every time the game cycle is up.
int win32_TimeStep(KeyBind &_nextMove, Snake *__snake, HANDLE _hStdIn, DWORD &_cNumRead, INPUT_RECORD (&_irInBuf)[N]) {

    switch (WaitForSingleObject(_hStdIn, gGameRules.GAME_SPEED_S * 500)) {
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

#pragma region Game Logic

// Executed when the game cycle is ended by the major flag.
int GameOver(Snake *_snake) {
    _snake->FreeMalloc();
    system("cls");
    return 0;
}

// After the initialization, the application is ready to start the game logics'n'loops.
int StartGame(Snake *_snake) {


    HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD irInBuf[N];
    DWORD cNumRead;
    GetConsoleMode(hStdIn, &fdwOldMode);
    // disable mouse and window input
    fdwMode = ENABLE_INSERT_MODE || ENABLE_WINDOW_INPUT;
    SetConsoleMode(hStdIn, fdwMode);


    // Scoped misc variables and flags.
    bool endGame = false;
    Status gameStats;
    
    // The game cycle starts here. It only stops with the major flag condition.
    while (endGame == false) {
        KeyBind nextMove = _snake->direction; // The default input resets to the snake default/latest direction.
        win32_TimeStep(nextMove, _snake, hStdIn, cNumRead, irInBuf);
        FlushConsoleInputBuffer(hStdIn);
        endGame = _snake->Move(nextMove); // This step processes the whole snake movement and game status.
    }
    
    // Redirecting to the game over screen.
    GameOver(_snake);
    return 0;
}

#pragma endregion

#pragma region Menu option Logic
void StartNewGame() {
    Snake newSnake = SpawnSnake();
    StartGame(&newSnake);
}
#pragma endregion

void Initialize()
{
    bool quitFlag = false;
    while (!quitFlag) {
        wprintf(L"%s", Menu::MainMenu());

        bool continueFlag = false;
        while (!continueFlag)
        {
            char selection;
            scanf("%c", &selection);
            switch (Menu::ParseMainMenuSelection(selection)) {
            case INVALID:
                wprintf(L"\n\nYour option is not valid. Please try again.\n\nSelected option: ");
                break;
            case STARTGAME:
                continueFlag = true;
                StartNewGame();        
                break;
            case QUIT:
                continueFlag = true;
                quitFlag = true;
                break;
            }
        }
    }
}
