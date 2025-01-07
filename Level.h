#pragma once

#include "Config.h"
#include "Mario.h"
#include "Board.h"
#include "Barrels.h"
#include "Display.h"
#include "Ghosts.h"

/**
* @class Level
* Represents the game level and controls the game's logic.
*/
class Level {

public:

    // Constructor for the Level class
    Level(std::string fname, Mario& mario, Difficulty dif_lvl);

    // Starts the level loop and handles user input
    Game_State start();

    // Resets the level
    void reset_level();

	// Getter for the board (const by reference)
    const Board& get_board() const;

    enum Consts {
        DEF_DELAY = 100, // Default delay in milliseconds
        KILLED_DELAY = 1000 // Delay after Mario is hit
    };

private:
  
	// Game board
    Board board;

	// Game's mario by reference, same mario will continue to the next levels
    Mario& mario;

	// Hold a set of barrels
    Barrels barrels; 

	// Hold a set of ghosts
    Ghosts ghosts;

	// Entities in the game
    const Point legend;
    const Point pauline;
    const Point donkey_kong;

    // Frame counter used to follow the level frames for barrel control (can be used for future level features)
    unsigned long int frames = 0;

    // Advances to the next level
    void advance_level(const std::string& fname);

    // Method to advance the entities in the game
    Game_State advance_entities();

	// Method to render the HUD
	void render_hud() const;
  
	// Method to render the level
	void render_level();
};

