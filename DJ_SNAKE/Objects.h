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

class Snake
{
private:

    bool ValidateControls(KeyBind bind) {
        return true;
    }

    int Draw() {
        // Draw head.
        gMATRIX[STARTING_POINT_X][STARTING_POINT_Y] = 3;
        // Draw main body.
        for (int i = 1; i < STARTING_LENGTH - 1; i++) {
            gMATRIX[STARTING_POINT_X][STARTING_POINT_Y - i] = 1;
        }
        // Draw tail.
        gMATRIX[STARTING_POINT_X][STARTING_POINT_Y - STARTING_LENGTH + 1] = 4;
        // Set starting direction.
        direction = RIGHT;
        return 0;
    }

    int Up() {
        return 0;
    }

    int Down() {
        return 0;
    }

    int Left() {
        return 0;
    }

    int Right() {
        return 0;
    }

public:

    KeyBind direction;

    Snake() {
        Draw();
    }

    int Move(KeyBind _direction) {
        switch (_direction)
        {
        case LEFT:
            break;
        case RIGHT:
            break;
        case UP:
            break;
        case DOWN:
            break;
        }
        return 0;
    }
};
