#include "Board.h"
#pragma once
/// <summary>
/// Snake movement. Board and score validation.
/// </summary>
class Snake
{
    // Game logic platform.
    Board _snakeBoard;
    Status _snakeStatus;
    SnakeLL _snakeLL;

    // Wether a step happens, validate if the given controls are valid..
    bool ValidateControls(KeyBind bind);

    // Start the board when the snake initializes
    int StartBoard();

    // Updating Linked List nodes and Game Board
    bool ProcessMove(KeyBind _direction);

public:
    KeyBind direction;

    Snake(bool _print = false);

    // Move entry function.
    bool Move(KeyBind _direction);

    void FreeMalloc();
};
