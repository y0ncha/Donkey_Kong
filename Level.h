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

	// Move constructor
	Level(Level&& other, std::string fname) noexcept;

	// Move assignment operator
	Level& operator=(Level&& other) noexcept;

	// Do not allow copy constructor and copy assignment operator
	Level(const Level&) = delete;
	Level& operator=(const Level&) = delete;

    // Starts the level loop and handles user input
    Game_State start();

    // Resets the level
    void reset_level();

    // Handle the hammer attack
    void perform_attack();

	// Getter for the board (const by reference)
    const Board& get_board() const;

	// Method to get the errors from the board validation
    const std::vector<Board::Err_Code>& get_errors();

    // Static consts for the game
    static constexpr int DEF_DELAY = 100; // Default delay in milliseconds
    static constexpr int KILLED_DELAY = 1000; // Delay after Mario is hit
	static constexpr int ATTACK_RANGE = 2; // Delay after Mario picks up the hammer

private:
  
    // Difficulty level
    Difficulty dif_lvl;

	// Game board
    Board board;

	// Game's mario by reference, same mario will continue to the next levels
    Mario& mario;

	// Hold a set of barrels
    Barrels barrels; 

	// Hold a set of ghosts
    Ghosts ghosts;

	// Entities in the game
    Point legend;
    Point pauline;
    Point donkey_kong;
    Point hammer;

    // Frame counter used to follow the level frames for barrel control (can be used for future level features)
    unsigned long int frames = 0;

    // Method to advance the entities in the game
    Game_State advance_entities();

	// Method to render the HUD
	void render_hud() const;
  
	// Method to render the level
	void render_level();

	// Method to print mario's gained points
	void print_score() const;

	// Method to check if an enemy is in the attack range
    Point is_enemy_hit(Coordinates pos, Coordinates dir);
};

