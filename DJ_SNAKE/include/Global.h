#pragma once
#include "DJ_SNAKE.h"

#define DBOUT( s )            \
{                             \
   std::ostringstream os_;    \
   os_ << s;                   \
   OutputDebugString( os_.str().c_str() );  \
}

#define N 1

#define stringify( name ) #name

class GameRules {
private:
	int ReadConfig();
public:

	GameRules(bool _readConfig);

	//Main rules.
	int GAME_WIDTH = 20;
	int GAME_HEIGHT = 20;
	int STARTING_LENGTH = 5;
	int STARTING_POINT_X = 10;
	int STARTING_POINT_Y = 10;
	float GAME_SPEED_S = 0.5;
};

const GameRules gGameRules = GameRules(true);