#include "Objects.h"

HANDLE hStdin;
DWORD fdwSaveOldMode;

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

void ErrorExit(LPCSTR lpszMessage)
{
    fprintf(stderr, "%s\n", lpszMessage);

    // Restore input mode on exit.

    SetConsoleMode(hStdin, fdwSaveOldMode);

    ExitProcess(0);
}

// Executed when the event input handling system is fired. This function maps the virtual keys with the controls enum interface.
KeyBind KeyEventProc(KEY_EVENT_RECORD ker, bool &_pressedReleased, Snake *___snake)
{
    KeyBind returnBind;
    WORD recordedKeyCode = ker.wVirtualKeyCode;

    // Virtual key mapping.
    switch (recordedKeyCode)
    {
        case 38: returnBind = UP;  break;
        case 40: returnBind = DOWN; break;
        case 37: returnBind = LEFT; break;
        case 39: returnBind = RIGHT; break;
        default: returnBind = ___snake->direction; break;
    }

    // Write key status.
    _pressedReleased = ker.bKeyDown;

    return returnBind;
}

// Executed every time the game cycle is up.
int TimeStep(DWORD &_cNumRead, KeyBind &_nextMove, clock_t _since, int ticks, Snake *__snake) {
    INPUT_RECORD irInBuf[N];
    if (WaitForInputIdle(hStdin, GAME_SPEED_S) != WAIT_TIMEOUT) {
        // Buffering the input events. 
        ReadConsoleInput(
            hStdin,      // input buffer handle 
            irInBuf,    // buffer to read into 
            N,           // size of read buffer 
            &_cNumRead
        ); // number of records read 
        

        // Getting the last key press.
        for (auto i : irInBuf)
        {
            switch (i.EventType)
            {
            case KEY_EVENT: // Is a keyboard input?
                bool pressedReleased;
                _nextMove = KeyEventProc(i.Event.KeyEvent, pressedReleased, __snake);
                break;
            }
        }
    }
    bool endCycle = false;
    while(!endCycle)
        if (clock() - _since >= ticks)
            // End of time cycle.
            endCycle = true;
        else
            // If not the end of time cycle, just let it keep goin!
            endCycle = false;
    return 0;
}

#pragma endregion

#pragma region Game Logic

// Executed when the game cycle is ended by the major flag.
int GameOver(Snake *_snake) {
    delete(_snake);
    return 0;
}

// After the initialization, the application is ready to start the game logics'n'loops.
int StartGame(Snake *_snake) {

    // Input buffer.
    DWORD cNumRead, fdwMode;
    

    // Time start.
    float delay = GAME_SPEED_S;
    int ticks = delay * CLOCKS_PER_SEC;

    // Get the standard input handle. 
    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    if (hStdin == INVALID_HANDLE_VALUE)
        ErrorExit("GetStdHandle");

    // Save the current input mode, to be restored on exit. 
    if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
        ErrorExit("GetConsoleMode");

    // Enable window input events. 
    fdwMode = ENABLE_WINDOW_INPUT | ENABLE_INSERT_MODE | ENABLE_EXTENDED_FLAGS;
    if (!SetConsoleMode(hStdin, fdwMode))
        ErrorExit("SetConsoleMode");

    // Scoped misc variables and flags.
    bool endGame = false;
    Status gameStats;
    
    // The game cycle starts here. It only stops with the major flag condition.
    while (endGame == false) {
        clock_t now = clock();
        KeyBind nextMove = _snake->direction; // The default input resets to the snake default/latest direction.
        TimeStep(cNumRead, nextMove, now, ticks, _snake);
        printf(".\n");
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