#include "Global.h"

using namespace std;
using namespace libconfig;

GameRules::GameRules(bool _readConfig = true) {
    if (_readConfig == true)
        ReadConfig();
}

int GameRules::ReadConfig() {
	Config cfg;

    // Read the file. If there is an error, report it and exit.
    try
    {
        cfg.readFile("settings.cfg");
    }
    catch (const FileIOException& fioex)
    {
        std::cerr << "I/O error while reading file." << std::endl;
        return(EXIT_FAILURE);
    }
    catch (const ParseException& pex)
    {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
            << " - " << pex.getError() << std::endl;
        return(EXIT_FAILURE);
    }

    // Get the gane width.
    try
    {
        string game_width = cfg.lookup("game_width");
        GAME_WIDTH = stoi(game_width);
    }
    catch (const SettingNotFoundException& nfex)
    {
        cerr << "No 'game_width' setting in configuration file." << endl;
    }
    // Get the gane height.
    try
    {
        string game_height = cfg.lookup("game_height");
        GAME_HEIGHT = stoi(game_height);
    }
    catch (const SettingNotFoundException& nfex)
    {
        cerr << "No 'game_height' setting in configuration file." << endl;
    }
    // Get the starting length.
    try
    {
        string starting_length = cfg.lookup("starting_length");
        STARTING_LENGTH = stoi(starting_length);
    }
    catch (const SettingNotFoundException& nfex)
    {
        cerr << "No 'starting_length' setting in configuration file." << endl;
    }
    // Get the starting point x.
    try
    {
        string starting_point_x = cfg.lookup("starting_point_x");
        STARTING_POINT_X = stoi(starting_point_x);
    }
    catch (const SettingNotFoundException& nfex)
    {
        cerr << "No 'starting_point_x' setting in configuration file." << endl;
    }
    // Get the starting point y.
    try
    {
        string starting_point_y = cfg.lookup("starting_point_y");
        STARTING_POINT_Y = stoi(starting_point_y);
    }
    catch (const SettingNotFoundException& nfex)
    {
        cerr << "No 'starting_point_y' setting in configuration file." << endl;
    }
    // Get the game speed.
    try
    {
        string game_speed = cfg.lookup("game_speed");
        GAME_SPEED_S = stof(game_speed);
    }
    catch (const SettingNotFoundException& nfex)
    {
        cerr << "No 'game_speed' setting in configuration file." << endl;
    }
	return 0;
}