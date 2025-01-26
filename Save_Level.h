#pragma once
#include "Level_Base.h"
#include "Board.h"
#include "Utils.h"

class Level_Base;

class Save_Level : public Level_Base {

public:

	// Constructor for the Save_Level class
	Save_Level(std::string fname, Mario& mario, Difficulty dif_lvl, unsigned int seed);
	
	// Destructor for the Save_Level class
	~Save_Level();

	// Starts the level lop and saves the relvant data
	Game_State start() override;

	// Method to get the file name of a given type
	const std::string get_fname(const std::string& type);

private:

	// File to save the steps
	std::ofstream steps;

	// File to save the results
	std::ofstream result;

	void pure() override {} // todo delete
};