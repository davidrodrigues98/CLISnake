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

public:
    KeyBind direction;

    Snake() {
        Draw();
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
