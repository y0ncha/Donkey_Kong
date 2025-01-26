#pragma once
#include "Level_Base.h"

class Level_Base;
/**
 * @class Regular_Level
 * Represents the regular level of the game.
 */
class Regular_Level : public Level_Base {
	
public:

	// Constructor for the Regular_Level class
	using Level_Base::Level_Base;

	// Destructor for the Regular_Level class
	~Regular_Level() = default;

private:

	// Starts the level loop and saves the relevant data
	Game_State start() override;
};