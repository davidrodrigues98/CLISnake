#include "DJ_SNAKE.h"

#pragma region Configuration definition.

//Main rules.
#define GAME_WIDTH 20
#define GAME_HEIGHT 20
#define STARTING_LENGTH 5
#define STARTING_POINT_X 10
#define STARTING_POINT_Y 10
#define GAME_SPEED_MS 500

//Snake design (1-9).
#define SNAKE_TAIL_HORIZONTAL '>'           //4
#define SNAKE_BODY_HORIZONTAL '-'           //1
#define SNAKE_TAIL_VERTICAL 'v'             //5
#define SNAKE_BODY_VERTICAL '|'             //2
#define SNAKE_HEAD 'O'                      //3
#define BORDER_HORIZONTAL '_'
#define BORDER_VERTICAL '|'
#define BLANK ' '                           //0
#define UNKNOWN '?'

//Entity design (>9).
#define APPLE 'A'                           //10

#pragma endregion
#pragma region Global

// Game board array.
int gMATRIX[GAME_WIDTH][GAME_HEIGHT];

// Setting up Gainput
gainput::InputManager gManager;
const gainput::DeviceId gKeyboardId = gManager.CreateDevice<gainput::InputDeviceKeyboard>();
gainput::InputMap gMap(gManager);

#pragma endregion