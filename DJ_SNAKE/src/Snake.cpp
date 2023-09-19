#include "Snake.h"

// Wether a step happens, validate if the given controls are valid..
bool Snake::ValidateControls(KeyBind bind) {
    bool flag = true;
    if (
        (direction == RIGHT && bind == LEFT) ||
        (direction == UP && bind == DOWN) ||
        (direction == DOWN && bind == UP) ||
        (direction == LEFT && bind == RIGHT)
        )
        flag = false;
    //printf("%s -> %s\t[%c]\n", DEBUG_KeyBind_PrintString[this->direction], DEBUG_KeyBind_PrintString[bind], (flag==true) ? 'X' : ' ');
    return flag;
}

// Start the board when the snake initializes
int Snake::StartBoard() {
    _snakeBoard = Board(); // Initialized board.
    SnakeLL* aux;

#pragma region Drawing snake body.

    // Draw head.
    _snakeBoard.GetSetBoard(gGameRules.STARTING_POINT_X, gGameRules.STARTING_POINT_Y, SNAKE_BODY);
    _snakeLL.x = gGameRules.STARTING_POINT_X;
    _snakeLL.y = gGameRules.STARTING_POINT_Y;
    aux = &_snakeLL;
    // Draw main body.
    for (int i = 1; i < gGameRules.STARTING_LENGTH - 1; i++) {
        _snakeBoard.GetSetBoard(gGameRules.STARTING_POINT_X, gGameRules.STARTING_POINT_Y + i, SNAKE_BODY);
        aux->next = (struct SnakeLL*)malloc(sizeof(struct SnakeLL));
        aux = aux->next;
        aux->x = gGameRules.STARTING_POINT_X;
        aux->y = gGameRules.STARTING_POINT_Y + i;
    }
    // Draw tail.
    _snakeBoard.GetSetBoard(gGameRules.STARTING_POINT_X, gGameRules.STARTING_POINT_Y + gGameRules.STARTING_LENGTH - 1, SNAKE_BODY);
    aux->next = (struct SnakeLL*)malloc(sizeof(struct SnakeLL));
    aux = aux->next;
    aux->x = gGameRules.STARTING_POINT_X;
    aux->y = gGameRules.STARTING_POINT_Y + gGameRules.STARTING_LENGTH - 1;
    aux->next = NULL;
#pragma endregion
    // Set starting direction.
    direction = RIGHT;
    return 0;
}

// Updating Linked List nodes and Game Board
bool Snake::ProcessMove(KeyBind _direction) {
    int oldX = _snakeLL.x, oldY = _snakeLL.y; // Saving coordinates before updating.
    bool scored = false;

    // Increments head position based on the given direction.
    switch (_direction)
    {
    case RIGHT:
        _snakeLL.y--;
        break;
    case LEFT:
        _snakeLL.y++;
        break;
    case UP:
        _snakeLL.x++;
        break;
    case DOWN:
        _snakeLL.x--;
        break;
    }

    // Verifies if the game is over: Snake hits itself or hits the borders.
    if (
        (0 > _snakeLL.x || _snakeLL.x >= gGameRules.GAME_WIDTH) ||
        (0 > _snakeLL.y || _snakeLL.y >= gGameRules.GAME_HEIGHT)
        )
        return true; // Game over ;(
    if (_snakeBoard.GetSetBoard(_snakeLL.x, _snakeLL.y) == SNAKE_BODY) 
        return true; // Game over :(

    // Verifies if the size of the snake will increment by 1.
    if (_snakeBoard.GetSetBoard(_snakeLL.x, _snakeLL.y) == APPLE)
        scored = true;
    // Updates head position in-board.
    _snakeBoard.GetSetBoard(_snakeLL.x, _snakeLL.y, SNAKE_BODY);



    // Score!
    if (scored)
    {
        // Creates a new node in the gap between the snake head and the rest of its body.
        SnakeLL* secondNode = _snakeLL.next;
        SnakeLL* newNode = (struct SnakeLL*)malloc(sizeof(struct SnakeLL));
        newNode->x = oldX;
        newNode->y = oldY;
        newNode->next = secondNode;
        _snakeLL.next = newNode;

        // Spawns new apple.
        _snakeBoard.SpawnApple();

        // Update score and times eaten status.
        _snakeStatus.score += SCOREPOINTS;
        _snakeStatus.timesEaten++;


    }
    // Normal movement.
    else
    {
        // The snake tail goes to the gap between the snake head and the rest of its body.
        SnakeLL* tail = &_snakeLL;
        SnakeLL* secondNode = _snakeLL.next;
        SnakeLL* beforeTail = NULL;
        while (tail->next != NULL) // Navigating to the tail.
        {
            if (tail->next->next == NULL)
                beforeTail = tail; // Saving before tail position to assign ->next=NULL later. This is the new tail.
            tail = tail->next;
        }
        _snakeBoard.GetSetBoard(tail->x, tail->y, BLANK); // Updating Game Board.
        tail->x = oldX;
        tail->y = oldY;
        _snakeLL.next = tail;
        tail->next = secondNode;
        if (beforeTail != NULL)
            beforeTail->next = NULL;
    }
    // Updates snake direction and times moved status.
    _snakeStatus.timeMoved++;
    direction = _direction;
    return false;
}

Snake::Snake(bool _print) {
    StartBoard();
    if (_print)
        _snakeBoard.PrintBoard(_snakeStatus.score);
    direction = RIGHT;
}


// Move entry function.
bool Snake::Move(KeyBind _direction) {
    bool gameOver = false;
    if (ValidateControls(_direction))
        gameOver = ProcessMove(_direction);
    _snakeBoard.PrintBoard(_snakeStatus.score);
    return gameOver;
}

void Snake::FreeMalloc() {
    _snakeBoard.ClearBoard();
}
