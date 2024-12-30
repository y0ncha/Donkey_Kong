#pragma once

#include "Game.h"

// Forward declaration of the Game class
class Game;

class Level {
public:
    // Constructor for the Level class
    Level(std::string fname, const Game::Display& display, Mario& mario, Game::Difficulty dif_lvl);

    // Starts the level loop and handles user input
    Game::Status start();

    enum Consts {
        DEF_DELAY = 100, // Default delay in milliseconds
        KILLED_DELAY = 1000 // Delay after Mario is hit
    };

private:
    // Game components
    const Game::Display& display; // Reference to the display
    Board board; // Initialize the board
    Mario& mario; // Reference to Mario
    Barrels barrels; // Initialize the barrels
  
    // Frame counter used to follow the level frames for barrel control (can be used for future level features)
    unsigned long int frames = 0;

    // Resets the level
    void reset_level();

	// Advances to the next level
	void advance_level(const std::string& fname);

    // Method to advance the entities in the game
    void advance_entities();

    // Method to finish the game successfully
    void finish_success();

    // Method to finish the game unsuccessfully
    void finish_failure();

    // Method to try again
    void try_again();
};