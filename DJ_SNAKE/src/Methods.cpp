#include "Objects.h"

// Setting up Gainput
gainput::InputManager gManager;
const gainput::DeviceId gKeyboardId = gManager.CreateDevice<gainput::InputDeviceKeyboard>();
gainput::InputMap gMap(gManager);


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

bool GameStep(Snake *_snake) {
    // Check for user input.
    gManager.Update();
    DBOUT("" << gMap.GetBool(UP) << "\n");
    /*if (gMap.GetBoolWasDown(UP))
    {
        DBOUT("Up");
    }
    if (gMap.GetBoolWasDown(DOWN))
    {
        DBOUT("Up");
    }
    if (gMap.GetBoolWasDown(LEFT))
    {
        DBOUT("Up");
    }
    if (gMap.GetBoolWasDown(RIGHT))
    {
        DBOUT("Up");
    }*/
    // Get snake direction.
    //KeyBind direction = _snake->direction;
    // Make it move.
    //_snake->Move(direction);
    // Respect game speed.
    return true;
}

int GameOver(Snake *_snake) {
    delete(_snake);
    return 0;
}

int StartGame(Snake *_snake) {
    
    Status newStatus;
    while(GameStep(_snake));
    GameOver(_snake);
    return 0;
}

void Initialize()
{
    ClearBoard();
    gManager.SetDisplaySize(GAME_WIDTH, GAME_HEIGHT);
    gMap.MapBool(KeyBind::UP, gKeyboardId, gainput::Key0);
    Snake newSnake = SpawnSnake();
    StartGame(&newSnake);
}