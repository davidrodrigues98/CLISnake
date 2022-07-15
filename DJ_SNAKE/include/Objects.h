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

enum Prefabs {
    SNAKE_TAIL_HORIZONTAL,
    SNAKE_BODY_HORIZONTAL,
    SNAKE_TAIL_VERTICAL,
    SNAKE_BODY_VERTICAL,
    SNAKE_HEAD,
    BORDER_HORIZONTAL,
    BORDER_VERTICAL,
    BLANK,
    UNKNOWN,
    APPLE
};

class Board {
protected:
    Prefabs _matrix[GAME_WIDTH][GAME_HEIGHT];
    std::map<Prefabs, char> _translator;
public:
    Board() {
        _translator[SNAKE_TAIL_HORIZONTAL] ='>';
        _translator[SNAKE_BODY_HORIZONTAL] = '-';
        _translator[SNAKE_TAIL_VERTICAL] = 'v';
        _translator[SNAKE_BODY_VERTICAL] = '|';
        _translator[SNAKE_HEAD] = 'O';
        _translator[BORDER_HORIZONTAL]= '_';
        _translator[BORDER_VERTICAL] = '|';
        _translator[BLANK] = ' ';
        _translator[UNKNOWN] = '?';
        _translator[APPLE] = 'A';
    }

    int GetSetBoard(int x, int y, Prefabs object) {
        return 0;
    }
    Prefabs GetSetBoard(int x, int y)
    {
        return BLANK;
    }

#pragma region Board Management

    int PrintBoard() {
        //Top Border
        printf(" ");
        for (int i = 0; i < GAME_WIDTH; i++)
            printf("%c", BORDER_HORIZONTAL);
        //L&R Borders w/Board
        for (int i = 0; i < GAME_HEIGHT; i++)
        {
            printf("\n%c", BORDER_VERTICAL);
            for (int j = 0; j < GAME_WIDTH; j++)
                printf("%c", _translator[GetSetBoard(i ,j)]);
            printf("%c", BORDER_VERTICAL);
        }
        //Bottom Border
        printf("\n ");
        for (int i = 0; i < GAME_WIDTH; i++)
            printf("%c", BORDER_HORIZONTAL);
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

    // Wether a step happens, validate if playing is still possible.
    bool ValidateControls(KeyBind bind) {
        return true;
    }

    // Start the board when the snake initializes
    int StartBoard() {
        _snakeBoard = Board(); // Initialized board.

#pragma region Drawing snake body.

        // Draw head.
        _snakeBoard.GetSetBoard(STARTING_POINT_X, STARTING_POINT_Y, SNAKE_HEAD);
        // Draw main body.
        for (int i = 1; i < STARTING_LENGTH - 1; i++) {
            _snakeBoard.GetSetBoard(STARTING_POINT_X, STARTING_POINT_Y - i, SNAKE_BODY_HORIZONTAL);
        }
        // Draw tail.
        _snakeBoard.GetSetBoard(STARTING_POINT_X, STARTING_POINT_Y - STARTING_LENGTH + 1, SNAKE_TAIL_HORIZONTAL);

#pragma endregion
        // Set starting direction.
        direction = RIGHT;
        return 0;
    }

#pragma region Dedicated command functions.
    int Up() {
        printf("I moved up!\n");
        direction = UP;
        return 0;
    }


    int Down() {
        printf("I moved down!\n");
        direction = DOWN;
        return 0;
    }

    int Left() {
        printf("I moved left!\n");
        direction = LEFT;
        return 0;
    }

    int Right() {
        printf("I moved right!\n");
        direction = RIGHT;
        return 0;
    }
#pragma endregion

public:
    KeyBind direction;

    Snake(bool _print=false) {
        
        StartBoard();
        _snakeBoard.ClearBoard();
        if (_print)
            _snakeBoard.PrintBoard();
    }
    int Move() {
        return 0;
    }
    int Move(KeyBind _direction) {
        if (ValidateControls(_direction))
        {
            switch (_direction)
            {
            case LEFT:
                Left();
                break;
            case RIGHT:
                Right();
                break;
            case UP:
                Up();
                break;
            case DOWN:
                Down();
                break;
            }
        }
        return 0;
    }
};
