#include "Global.h"
#pragma once

/*
* Placint here all the used data structures to feed some class properties and game business logic.
*/

typedef struct Status {
    int score = 0;
    int timesEaten = 0;
    int timeMoved = 0;
} Status;

typedef enum KeyBind {
    UP,
    DOWN,
    LEFT,
    RIGHT
} KeyBind;

typedef enum MenuOptions {
    STARTGAME,
    IMPORTBOARD,
    QUIT,
    INVALID
} MenuOptions;

const char DEBUG_KeyBind_PrintString[4][6] =
{
    stringify(UP),
    stringify(DOWN),
    stringify(LEFT),
    stringify(RIGHT)
};

typedef enum Prefabs {
    SNAKE_BODY,
    BORDER_HORIZONTAL,
    BORDER_VERTICAL,
    BORDER_TOP_LEFT,
    BORDER_TOP_RIGHT,
    BORDER_BOTTOM_LEFT,
    BORDER_BOTTOM_RIGHT,
    BLANK,
    UNKNOWN,
    APPLE,
    CARRIAGE_RETURN,
    LINE_FEED
} Prefabs;

typedef struct SnakeLL {
    int x;
    int y;
    SnakeLL* next = NULL;
} SnakeLL;
