#include "Global.h"

GameRules::GameRules(bool _readConfig = true) {
    if (_readConfig == true)
        this->ReadConfig();
}

int GameRules::ReadConfig() {
	libconfig::Config cfg;

    // Read the file. If there is an error, report it and exit.
    try
    {
        cfg.readFile("settings.cfg");
    }
    catch (const libconfig::FileIOException& fioex)
    {
        std::cerr << "I/O error while reading file." << std::endl;
        return(EXIT_FAILURE);
    }
    catch (const libconfig::ParseException& pex)
    {
        std::cerr << "Parse error at " << pex.libconfig::ParseException::getFile() << ":" << pex.getLine()
            << " - " << pex.libconfig::ParseException::getError() << std::endl;
        return(EXIT_FAILURE);
    }

    // Get the game width.
    try
    {
        std::string game_width = cfg.lookup("game_width");
        this->GAME_WIDTH = stoi(game_width);
    }
    catch (const libconfig::SettingNotFoundException& nfex)
    {
        std::cerr << "No 'game_width' setting in configuration file." << std::endl;
    }
    // Get the game height.
    try
    {
        std::string game_height = cfg.lookup("game_height");
        this->GAME_HEIGHT = stoi(game_height);
    }
    catch (const libconfig::SettingNotFoundException& nfex)
    {
        std::cerr << "No 'game_height' setting in configuration file." << std::endl;
    }
    // Get the starting length.
    try
    {
        std::string starting_length = cfg.lookup("starting_length");
        this->STARTING_LENGTH = std::stoi(starting_length);
    }
    catch (const libconfig::SettingNotFoundException& nfex)
    {
        std::cerr << "No 'starting_length' setting in configuration file." << std::endl;
    }
    // Get the starting point x.
    try
    {
        std::string starting_point_x = cfg.lookup("starting_point_x");
        this->STARTING_POINT_X = stoi(starting_point_x);
    }
    catch (const libconfig::SettingNotFoundException& nfex)
    {
        std::cerr << "No 'starting_point_x' setting in configuration file." << std::endl;
    }
    // Get the starting point y.
    try
    {
        std::string starting_point_y = cfg.lookup("starting_point_y");
        this->STARTING_POINT_Y = stoi(starting_point_y);
    }
    catch (const libconfig::SettingNotFoundException& nfex)
    {
        std::cerr << "No 'starting_point_y' setting in configuration file." << std::endl;
    }
    // Get the game speed.
    try
    {
        std::string game_speed = cfg.lookup("game_speed");
        this->GAME_SPEED_S = stof(game_speed);
    }
    catch (const libconfig::SettingNotFoundException& nfex)
    {
        std::cerr << "No 'game_speed' setting in configuration file." << std::endl;
    }
	return 0;
}