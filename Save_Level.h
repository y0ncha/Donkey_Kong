#pragma once
#include "Level_Base.h"
#include "Board.h"
#include "Utils.h"

class Level_Base;

/**
 * @class Save_Level
 * Represents the save level of the game.
 */
class Save_Level : public Level_Base {

public:

	// Constructor for the Save_Level class
	Save_Level(std::string fname, Mario& mario, Difficulty _diff);
	
	// Destructor for the Save_Level class
	~Save_Level();

	// Starts the level lop and saves the relvant data
	Game_State start() override;

	// Write the result to the file
	void write_to_result(Game_State state);

private:

	// File to save the steps
	std::ofstream steps;

	// File to save the results
	std::ofstream result;

	// Terminator
	static const char TERMINATOR = '~';
};