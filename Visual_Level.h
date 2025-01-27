#pragma once
#include "Level_Base.h"

class Level_Base;

class Visual_Level : public Level_Base {

public:

	// Constructor for the Visual_Level class
	Visual_Level(std::string screen, Mario& mario);

	// Destructor for the Visual_Level class
	~Visual_Level();

protected:

	// Method to start the level loop
	Game_State start() override;

	// Method to read the next step from the file
	std::pair<int, char> read_next();

	// Variable to hold the next step
	std::pair<int, char> next_step;

	// Terminator
	static const char TERMINATOR = '~';

private: 

	// File to read the steps from
	std::ifstream steps;

	// File to read the results from
	std::ifstream result;
};