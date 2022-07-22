#include "Global.h"
#pragma once

typedef struct Status {
    int score = 0;
    int timesEaten = 0;
    int timeMoved = 0;
} Status;

enum KeyBind {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

const char DEBUG_KeyBind_PrintString[4][6] =
{
    stringify(UP),
    stringify(DOWN),
    stringify(LEFT),
    stringify(RIGHT)
};

enum Prefabs {
    SNAKE_BODY,
    BORDER_HORIZONTAL,
    BORDER_VERTICAL,
    BLANK,
    UNKNOWN,
    APPLE,
    CARRIAGE_RETURN,
    LINE_FEED
};

typedef struct SnakeLL {
    int x;
    int y;
    SnakeLL* next = NULL;
} SnakeLL;

class Board {
protected:
    Prefabs _matrix[GAME_WIDTH][GAME_HEIGHT];
    std::map<Prefabs, wchar_t> _translator;
public:
    Board() {
        _translator[SNAKE_BODY] = L'\u2588';
        _translator[BORDER_HORIZONTAL]= L'\u2550';
        _translator[BORDER_VERTICAL] = L'\u2551';
        _translator[BLANK] = L'\u00A0';
        _translator[UNKNOWN] = L'?';
        _translator[APPLE] = L'\u2666';
        _translator[CARRIAGE_RETURN] = L'\u000D';
        _translator[LINE_FEED] = L'\u000A';
        this->ClearBoard();
    }

    /*wchar_t* NewLine() {
        wchar_t returning[2];
        swprintf(returning, sizeof(returning), L"%lc%lc", _translator[CARRIAGE_RETURN], _translator[LINE_FEED]);
        return returning;
    }*/

    int GetSetBoard(int x, int y, Prefabs object) {
        _matrix[x][y] = object;
        return (int)_matrix[x][y];
    }
    Prefabs GetSetBoard(int x, int y)
    {
        return _matrix[x][y];
    }

#pragma region Board Management

    int PrintBoard() {
#pragma region WIN_ENV
        system("cls");
#pragma endregion
        //Top Border
        wprintf(L"%lc", _translator[BLANK]);
        for (int i = 0; i < GAME_WIDTH; i++)
            wprintf(L"%lc",  _translator[BORDER_HORIZONTAL]);
        //L&R Borders w/Board
        for (int i = 0; i < GAME_HEIGHT; i++)
        {
            wprintf(L"\n%lc", _translator[BORDER_VERTICAL]);
            for (int j = 0; j < GAME_WIDTH; j++)
                wprintf(L"%lc", _translator[GetSetBoard(i ,j)]);
            wprintf(L"%lc", _translator[BORDER_VERTICAL]);
        }
        //Bottom Border
        wprintf(L"\n%lc", _translator[BLANK]);
        for (int i = 0; i < GAME_WIDTH; i++)
            wprintf(L"%lc", _translator[BORDER_HORIZONTAL]);
        return 0;
    }

    int ClearBoard(bool _print = false) {
        for (int i = 0; i < GAME_WIDTH; i++)
            for (int j = 0; j < GAME_HEIGHT; j++)
                GetSetBoard(i, j, BLANK);

        if (_print)
            return PrintBoard();
        return 0;
    }
#pragma endregion
};

class Snake
{
private:

    // Game logic platform.
    Board _snakeBoard;
    Status _snakeStatus;
    SnakeLL _snakeLL;

    // Wether a step happens, validate if the given controls are valid..
    bool ValidateControls(KeyBind bind) {
        bool flag = true;
        if (
            (this->direction == RIGHT && bind == LEFT) ||
            (this->direction == UP && bind == DOWN) ||
            (this->direction == DOWN && bind == UP) ||
            (this->direction == LEFT && bind == RIGHT)
            )
            flag = false;
        //printf("%s -> %s\t[%c]\n", DEBUG_KeyBind_PrintString[this->direction], DEBUG_KeyBind_PrintString[bind], (flag==true) ? 'X' : ' ');
        return flag;
    }

    // Start the board when the snake initializes
    int StartBoard() {
        _snakeBoard = Board(); // Initialized board.
        SnakeLL* aux;

#pragma region Drawing snake body.

        // Draw head.
        _snakeBoard.GetSetBoard(STARTING_POINT_X, STARTING_POINT_Y, SNAKE_BODY);
        _snakeLL.x = STARTING_POINT_X;
        _snakeLL.y = STARTING_POINT_Y;
        aux = &_snakeLL;
        // Draw main body.
        for (int i = 1; i < STARTING_LENGTH - 1; i++) {
            _snakeBoard.GetSetBoard(STARTING_POINT_X, STARTING_POINT_Y - i, SNAKE_BODY);
            aux->next = (struct SnakeLL*)malloc(sizeof(struct SnakeLL));
            aux = aux->next;
            aux->x = STARTING_POINT_X;
            aux->y = STARTING_POINT_Y;
        }
        // Draw tail.
        _snakeBoard.GetSetBoard(STARTING_POINT_X, STARTING_POINT_Y - STARTING_LENGTH + 1, SNAKE_BODY);
        aux->next = (struct SnakeLL*)malloc(sizeof(struct SnakeLL));
        aux = aux->next;
        aux->x = STARTING_POINT_X;
        aux->y = STARTING_POINT_Y;
        aux->next = NULL;
#pragma endregion
        // Set starting direction.
        direction = RIGHT;
        return 0;
    }

    // Updating Linked List nodes and Game Board
    int ProcessMove(KeyBind _direction) {
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
                _snakeLL.x--;
            break;
            case DOWN:
                _snakeLL.x++;
            break;
        }
        // Updates head position in-board.
        _snakeBoard.GetSetBoard(_snakeLL.x, _snakeLL.y, SNAKE_BODY);
        
        // Verifies if the size of the snake will increment by 1.
        if (_snakeBoard.GetSetBoard(_snakeLL.x, _snakeLL.y) == APPLE)
            scored = true;

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

            /*TBD: Add score points here...*/

        }
        // Normal movement.
        else
        {
            // The snake tail goes to the gap between the snake head and the rest of its body.
            SnakeLL* tail = &_snakeLL;
            SnakeLL* secondNode = _snakeLL.next;
            SnakeLL* beforeTail;
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
            if(beforeTail != NULL)
                beforeTail->next = NULL;
        }
        return 0;
    }

public:
    KeyBind direction;

    Snake(bool _print=false) {
        
        StartBoard();
        if (_print)
            _snakeBoard.PrintBoard();
    }

    // Move entry function.
    int Move(KeyBind _direction) {
        if (ValidateControls(_direction))
            ProcessMove(_direction);
        _snakeBoard.PrintBoard();
        return 0;
    }
};
