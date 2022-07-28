#include "Global.h"
#pragma once

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
