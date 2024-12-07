#pragma once


# include <conio.h>
#include "Mario.h"
#include "Board.h"
#include "Barrel.h"

/**
 * @class Game
 * Manages the main game structure, including the player (Mario),
 * the game board, and progress such as score and level.
 * This class handles the game loop, player input, and other gameplay logic.
 */
class Game {

	const Board org_board; // Initialize a board to hold the orginal layout

	Board curr_board; // Initialize a board to hold the data real-time

    Mario mario; // Initialize mario with board and config in constructor

    // For exercise 2 and 3 
    //int level = 1; // Current game level
    //int score = 0; // Current game score

public:

    // Constructor for the Game class
	Game();

    // Enum for initial positions of characters
    enum DEF_POS {

        MARIO_X0 = 40, // Default Mario's position on the x-axis
        MARIO_Y0 = 23, // Default Mario's position on the y-axis

        DKONG_X0 = 40, // Default Donkey Kong's position on the x-axis
        DKONG_Y0 = 3   // Default Donkey Kong's position on the y-axis
    };

    // Starts the game loop and handles user input
    void play();
};
