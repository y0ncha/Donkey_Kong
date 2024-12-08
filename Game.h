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

public: // todo move to private

    // Constructor for the Game class
    Game();

    // Enum for initial positions of characters
    enum CONSTS {
        MAX_BARRELS = 10 // Maximum number of barrels
    };

    // Starts the game loop and handles user input
    void play();

    void init_barrels();

    void move_barrels();

    void ctrl_barrels();

private:

	const Board org_board; // Initialize a board to hold the orginal layout

	Board curr_board; // Initialize a board to hold the data real-time

    Mario mario; // Initialize mario with board and config in constructor

    Barrel barrels[CONSTS::MAX_BARRELS]; // Initialize an array of barrels

    int frames = 0;

    // For exercise 2 and 3 
    //int level = 1; // Current game level
    //int score = 0; // Current game score
};
