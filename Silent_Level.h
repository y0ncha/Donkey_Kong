#pragma once
#include "Level_Base.h"
#include "Visual_Level.h"
#include "Config.h"
#include "Utils.h"

class Level_Base;

/**
 * @class Silent_Level
 * Represents the silent level of the game.
 */
class Silent_Level : public Visual_Level {

public:

	// Constructor for the Silent_Level class
	Silent_Level(std::string screen, Mario& mario);

	// Destructor for the Silent_Level class
	~Silent_Level() = default;

	// Perform the attack
	void perform_attack() override;

private:

	// Method to start the level loop
	Game_State start() override;

	// Method to advance the entities in the game
	Game_State advance_entities() override;

	// Method to render the level
	void render_level() override;
};