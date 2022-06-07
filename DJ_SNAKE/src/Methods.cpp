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

Snake SpawnSnake(bool _print = false) {
    Snake newSnake = Snake();
    if(_print)
        PrintBoard();
    return newSnake;
}

#pragma region Input Handling

VOID ErrorExit(LPCSTR lpszMessage)
{
    fprintf(stderr, "%s\n", lpszMessage);

    // Restore input mode on exit.

    SetConsoleMode(hStdin, fdwSaveOldMode);

    ExitProcess(0);
}

VOID KeyEventProc(KEY_EVENT_RECORD ker)
{
    printf("Key event: ");

    if (ker.bKeyDown)
        printf("key pressed\n");
    else printf("key released\n");
}

#pragma endregion

#pragma region Game Logic

bool GameStep(Snake *_snake, INPUT_RECORD (&_irInBuf)[N], DWORD &_cNumRead) {

    // Wait for the events. 
    if (!ReadConsoleInput(
        hStdin,      // input buffer handle 
        _irInBuf,    // buffer to read into 
        N,           // size of read buffer 
        &_cNumRead)) // number of records read 
        ErrorExit("ReadConsoleInput");


    for (auto i : _irInBuf)
    {
        switch (i.EventType)
        {
            case KEY_EVENT: // keyboard input 
                i.Event.KeyEvent; KeyEventProc(i.Event.KeyEvent);
                break;

            case FOCUS_EVENT:  // disregard focus events 

            case MENU_EVENT:   // disregard menu events 
                break;

            default: break;
        }
    }

    return true;
}

int GameOver(Snake *_snake) {
    delete(_snake);
    return 0;
}

int StartGame(Snake *_snake) {

    // Input buffer.
    DWORD cNumRead, fdwMode;
    INPUT_RECORD irInBuf[N];

    // Get the standard input handle. 
    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    if (hStdin == INVALID_HANDLE_VALUE)
        ErrorExit("GetStdHandle");

    // Save the current input mode, to be restored on exit. 
    if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
        ErrorExit("GetConsoleMode");

    // Enable window input events. 
    fdwMode = ENABLE_WINDOW_INPUT | ENABLE_INSERT_MODE | ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT;
    if (!SetConsoleMode(hStdin, fdwMode))
        ErrorExit("SetConsoleMode");

    Status newStatus;
    while(GameStep(_snake, irInBuf, cNumRead));
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