#include "Objects.h"

std::thread *_gTimerPointer;

#pragma region Board Management

char DrawInBoard(int _object)
{
    char returning;
    switch (_object)
    {
    case 0:
        returning = BLANK;
        break;
    case 1:
        returning = SNAKE_BODY_HORIZONTAL;
        break;
    case 2:
        returning = SNAKE_BODY_VERTICAL;
        break;
    case 3:
        returning = SNAKE_HEAD;
        break;
    case 4:
        returning = SNAKE_TAIL_HORIZONTAL;
        break;
    case 5:
        returning = SNAKE_TAIL_VERTICAL;
        break;
    case 10:
        returning = APPLE;
        break;
    default:
        returning = UNKNOWN;
        break;
    }
    return returning;
}

int PrintBoard() {
    //Top Border
    printf(" ");
    for(int i=0;i<GAME_WIDTH;i++)
        printf("%c", BORDER_HORIZONTAL);
    //L&R Borders w/Board
    for(int i=0;i<GAME_HEIGHT;i++)
    {
        printf("\n%c",BORDER_VERTICAL);
        for(int j=0;j<GAME_WIDTH;j++)
            printf("%c", DrawInBoard(gMATRIX[i][j]));
        printf("%c",BORDER_VERTICAL);
    }
    //Bottom Border
    printf("\n ");
    for(int i=0;i<GAME_WIDTH;i++)
        printf("%c", BORDER_HORIZONTAL);
    return 0;
}

int ClearBoard(bool _print = false) {
    for(int i=0;i<GAME_WIDTH;i++)
        for(int j=0;j<GAME_HEIGHT;j++)
            gMATRIX[i][j]=0;
    
    if(_print)
        return PrintBoard();
    return 0;
}
#pragma endregion

int ClearScreen() {
    system("cls");
    return 0;
}

// Initializes snake object.
Snake SpawnSnake(bool _print = false) {
    Snake newSnake = Snake();
    if(_print)
        PrintBoard();
    return newSnake;
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
        case 38: returnBind = UP;  break;
        case 40: returnBind = DOWN; break;
        case 37: returnBind = LEFT; break;
        case 39: returnBind = RIGHT; break;
    }
    
    return returnBind;
}

int ThreadTimer(clock_t _since, int _ticks) {
    bool endCycle = false;
    while (endCycle == false)
        if (clock() - _since >= _ticks)
            // End of time cycle.
            endCycle = true;
        else
            // If not the end of time cycle, just let it keep goin!
            endCycle = false;
    return 0;
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
            for (auto i : _irInBuf)
                if (i.Event.KeyEvent.bKeyDown)
                    _nextMove = KeyEventProc(i.Event.KeyEvent, __snake);
            break;
        case WAIT_TIMEOUT:
            break;
    };
    _gTimerPointer->join();

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


    // Time start.
    float delay = GAME_SPEED_S;
    int ticks = delay * CLOCKS_PER_SEC;

    // Scoped misc variables and flags.
    bool endGame = false;
    Status gameStats;
    
    // The game cycle starts here. It only stops with the major flag condition.
    while (endGame == false) {
        clock_t now = clock();
        KeyBind nextMove = _snake->direction; // The default input resets to the snake default/latest direction.
        std::thread timeThread(ThreadTimer, now, ticks);
        _gTimerPointer = &timeThread;

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
    ClearBoard();
    Snake newSnake = SpawnSnake();
    StartGame(&newSnake);
}